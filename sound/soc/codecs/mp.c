/*
 * mp.c -- Musica Pristina ALSA SoC codec driver
 *
 * Copyright 2019 Welsh Technologies.
 * 
 * Author: Kevin Welsh <kwelsh@welshtechnologies.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/regmap.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include "mp.h"

static int ocxo = 1;
module_param(ocxo, int, 0644);
MODULE_PARM_DESC(ocxo, "Boolean to enable OCXO (0/1 == DFXO/OCXO)");

static int maxrate = 768;
module_param(maxrate, int, 0644);
MODULE_PARM_DESC(maxrate, "Maximum PCM rate");

/* custom function to fetch info of PCM playback volume */
static int dac_info_volsw(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = 100;
	return 0;
}

/*
 * custom function to get PCM playback volume
 */
static int dac_get_volsw(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	int l;
	int r;

	l = 100;
	r = 100;

	ucontrol->value.integer.value[0] = l;
	ucontrol->value.integer.value[1] = r;

	return 0;
}

/*
 * custom function to put PCM playback volume
 */
static int dac_put_volsw(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	int l;
	int r;

	l = ucontrol->value.integer.value[0];
	r = ucontrol->value.integer.value[1];

	return 0;
}

static int mp2019_dai_trigger(struct snd_pcm_substream *substream, int cmd,
			  struct snd_soc_dai *dai)
{
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dev_dbg(dai->dev, "Starting audio stream\n");
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dev_dbg(dai->dev, "Stopping audio stream\n");
		break;
	default:
		break;
	}

	return 0;
}

static const unsigned int mp2019_rates[] = {
	44100,  48000,  88200,  96000,  176400,
	192000, 352800, 384000, 705600, 768000,
};

static const struct snd_pcm_hw_constraint_list mp2019_rate_constraints = {
	.count = ARRAY_SIZE(mp2019_rates),
	.list = mp2019_rates,
};



static int mp2019_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct mp2019_codec_priv *mp = snd_soc_component_get_drvdata(component);

	/* I2S clock and frame master setting. */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	/* setting I2S data format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	default:
		return -EINVAL;
	}

	mp->fmt = fmt;
	return 0;
}

static int mp2019_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	int frame_rate, frame_width;
	struct snd_soc_component *component = dai->component;

	frame_rate = params_rate(params);
	frame_width = params_width(params);
	
	dev_warn(component->dev, "BEGIN mp2019_set_clock");

	switch (frame_rate) {
	case 44100:
	case 48000:
	case 88200:
	case 96000:
	case 176400:
	case 192000:
	case 352800:
	case 384000:
		break;
	case 705600:
	case 768000:
		if (maxrate == 768) {
			break;
		} else {
			dev_err(component->dev, "frame rate %d not supported\n",
				frame_rate);
			return -EINVAL;
		}
	default:
		dev_err(component->dev, "frame rate %d not supported\n",
			frame_rate);
		return -EINVAL;
	}
	switch (frame_width) {
	case 16:
	case 24:
	case 32:
		break;
	default:
		dev_err(component->dev, "%d-bit frame width not supported\n",
			frame_width);
		return -EINVAL;
	}
	if (ocxo == 1) {
		/* OCXO crystal strategy */
		dev_warn(component->dev,
			 "    CONFIG_SND_SOC_MPCODEC_XTAL_OCXO");
		return update_playback_OCXO(dai, frame_rate, frame_width);
	} else {
		/* Dual Frequency XO crystal strategy */
		dev_warn(component->dev,
			 "    CONFIG_SND_SOC_MPCODEC_XTAL_DFXO");
		return update_playback_DFXO(dai, frame_rate, frame_width);
	}

	dev_warn(component->dev, "END mp2019_set_clock");
	return 0;
}

static int mp2019_codec_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	int ret;

	ret = snd_pcm_hw_constraint_list(substream->runtime, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &mp2019_rate_constraints);

	return ret;
}


static const struct regmap_config mp2019_lcd_regmap_config = {
	.reg_bits = 16,
	.val_bits = 24,
	.max_register = 0xFFFF,
	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL_GPL(mp2019_lcd_regmap_config);

static const struct regmap_config mp2019_clock_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0xFF,
	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL_GPL(mp2019_clock_regmap_config);

static const struct regmap_config mp2019_oscsel_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0xFF,
	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL_GPL(mp2019_oscsel_regmap_config);

static const struct snd_soc_dai_ops mp2019_dai_ops = {
	.startup = mp2019_codec_startup,
	.hw_params = mp2019_hw_params,
	.set_fmt = mp2019_set_dai_fmt,
	.trigger = mp2019_dai_trigger,
};

static const struct snd_kcontrol_new mp2019_controls[] = {
	{
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = dac_info_volsw,
		.get = dac_get_volsw,
		.put = dac_put_volsw,
	},
};

static struct snd_soc_dai_driver mp2019_dai = {
	.name = "Musica Pristina",
	.playback =
		{
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.formats = MP2019_FORMATS,
		},
	.ops = &mp2019_dai_ops,
};


/*
int mp2019_common_init(struct device *dev, struct regmap *regmap)
{
	struct mp2019_private *mp2019;

	mp2019 = devm_kzalloc(dev, sizeof(struct mp2019_private), GFP_KERNEL);
	if (!mp2019)
		return -ENOMEM;

	mp2019->regmap = regmap;
	dev_set_drvdata(dev, mp2019);

	return devm_snd_soc_register_component(dev, &soc_component_dev_mp2019,
					       &mp2019_dai, 1);
}
EXPORT_SYMBOL_GPL(mp2019_common_init);
*/



static int mp2019_codec_probe(struct snd_soc_component *component)
{
	return 0;
}

static void mp2019_codec_remove(struct snd_soc_component *component)
{
}

static const struct snd_soc_component_driver soc_component_dev_mp2019 = {
	.probe = mp2019_codec_probe,
	.remove = mp2019_codec_remove,
	.controls = mp2019_controls,
	.num_controls = ARRAY_SIZE(mp2019_controls),
	.idle_bias_on = 1,
	.use_pmdown_time = 1,
	.endianness = 1,
	.non_legacy_dai_naming = 1,
};


/* LCD DRIVER */

static int mp2019_lcd_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device_node *clkgen_np;
	struct i2c_client *clkgen_client;
	struct mp2019_codec_priv *mp;
	int ret;

	dev_warn(&i2c->dev, "BEGIN mp2019_lcd_i2c_probe");

	clkgen_np = of_parse_phandle(i2c->dev.of_node, "mp,clkgen", 0);
	if (!clkgen_np) {
		dev_err(&i2c->dev,
			"Failed to get clock generator phandle\n");
		return -ENODEV;
	}
	clkgen_client = of_find_i2c_device_by_node(clkgen_np);
	of_node_put(clkgen_np);
	if (!clkgen_client) {
		dev_dbg(&i2c->dev, "Clock generator I2C client not found\n");
		return -EPROBE_DEFER;
	}
	mp = i2c_get_clientdata(clkgen_client);
	put_device(&clkgen_client->dev);
	mp->lcd_regmap = devm_regmap_init_i2c(i2c, &mp2019_lcd_regmap_config);
	if (IS_ERR(mp->lcd_regmap)) {
		ret = PTR_ERR(mp->lcd_regmap);
		dev_err(&i2c->dev, "Failed to allocate lcd regmap: %d\n",
			ret);
		return ret;
	}

	i2c_set_clientdata(i2c, mp);

	dev_warn(&i2c->dev, "END mp2019_lcd_i2c_probe");

	return 0;
}

static int mp2019_lcd_i2c_remove(struct i2c_client *i2c)
{
	return 0;
}

static const struct i2c_device_id mp2019_lcd_id[] = {
	{ "mp2019_lcd", 0 },
	{ },
};

MODULE_DEVICE_TABLE(i2c, mp2019_lcd_id);

static const struct of_device_id mp2019_lcd_dt_ids[] = {
	{
		.compatible = "mp,codec-lcd",
	},
	{ }
};
MODULE_DEVICE_TABLE(of, mp2019_lcd_dt_ids);

static struct i2c_driver mp2019_lcd_i2c_driver = {
	.driver =
		{
			.name = "mp2019_lcd",
			.of_match_table = mp2019_lcd_dt_ids,
		},
	.probe = mp2019_lcd_i2c_probe,
	.remove = mp2019_lcd_i2c_remove,
	.id_table = mp2019_lcd_id,
};

/* END LCD DRIVER */

/* mp2019 I2C */
static int mp2019_oscsel_i2c_probe(struct i2c_client *i2c,
			       const struct i2c_device_id *id)
{
	struct device_node *clkgen_np;
	struct i2c_client *clkgen_client;
	struct mp2019_codec_priv *mp;
	int ret;
	int i;

	dev_warn(&i2c->dev, "BEGIN mp2019_oscsel_i2c_probe");

	clkgen_np = of_parse_phandle(i2c->dev.of_node, "mp,clkgen", 0);
	if (!clkgen_np) {
		dev_err(&i2c->dev,
			"Failed to get clock generator phandle\n");
		return -ENODEV;
	}
	clkgen_client = of_find_i2c_device_by_node(clkgen_np);
	of_node_put(clkgen_np);
	if (!clkgen_client) {
		dev_dbg(&i2c->dev, "Clock generator I2C client not found\n");
		return -EPROBE_DEFER;
	}
	mp = i2c_get_clientdata(clkgen_client);
	put_device(&clkgen_client->dev);
	mp->oscsel_regmap = devm_regmap_init_i2c(i2c, &mp2019_oscsel_regmap_config);
	if (IS_ERR(mp->oscsel_regmap)) {
		ret = PTR_ERR(mp->oscsel_regmap);
		dev_err(&i2c->dev,
			"Failed to allocate oscillator selector regmap: %d\n",
			ret);
		return ret;
	}
	dev_warn(&i2c->dev, "    BEGIN i2c_set_clientdata(client, mp);");
	i2c_set_clientdata(i2c, mp);
	dev_warn(&i2c->dev, "    BEGIN i2c_set_clientdata(client, mp);");

	dev_warn(&i2c->dev, "BEGIN devm_snd_soc_register_component");

	/*
	if(maxrate == 768) {
		rate = "768";
	} else {
		rate = "384";
	}
	strcpy(name, "Musica Pristina ");
	strcpy(name, rate);
	strcpy(name, " ");
	strcpy(name, strategy);


	if(ocxo == 1) {
		strategy = "OCXO";
	} else {
		strategy = "DFXO";
	}

	dev_warn(&client->dev, "    STRATEGY: %s", strategy);
	snprintf(mp2019_dai.name, sizeof(mp2019_dai.name), "%s %d %s", mp2019_dai.name, maxrate, strategy);
	dev_warn(&client->dev, "*** and the name is: %s", mp2019_dai.name);


	ret = snd_soc_register_codec(&clkgen_client->dev, &mp2019_codec_driver,
	 			     &mp2019_dai, 1);
	*/

	dev_warn(&i2c->dev, "    client->dev");
	dev_warn(&clkgen_client->dev, "    &clkgen_client->dev");

	ret = devm_snd_soc_register_component(&clkgen_client->dev,
			&soc_component_dev_mp2019, &mp2019_dai, 1);
	

		dev_warn(&i2c->dev, "END devm_snd_soc_register_component");
	if (ret)
		return ret;

	dev_warn(&i2c->dev, "    BEGIN default OSCSEL regs");

	for (i = 0; i < ARRAY_SIZE(mp2019_oscsel_reg_defaults); i++) {
		regmap_write(mp->oscsel_regmap, mp2019_oscsel_reg_defaults[i].reg,
			     mp2019_oscsel_reg_defaults[i].def);
	}

	dev_warn(&i2c->dev, "    END default OSCSEL regs");
	dev_warn(&i2c->dev, "    BEGIN default CLKGEN regs");

	for (i = 0; i < ARRAY_SIZE(mp2019_codec_reg_defaults); i++) {
		clkgen_regmap_write(mp->clkgen_regmap,
				    mp2019_codec_reg_defaults[i].reg,
				    mp2019_codec_reg_defaults[i].def);
	}

	dev_warn(&i2c->dev, "    END default CLKGEN regs");

	dev_warn(&i2c->dev, "END mp2019_oscsel_i2c_probe");

	return 0;
}

static int mp2019_oscsel_i2c_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_component(&i2c->dev);
	return 0;
}

static const struct i2c_device_id mp2019_oscsel_id[] = {
	{ "mp2019_oscsel", 0 },
	{},
};
MODULE_DEVICE_TABLE(i2c, mp2019_oscsel_id);

static const struct of_device_id mp2019_oscsel_dt_ids[] = {
	{
		.compatible = "mp,codec-oscsel",
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, mp2019_oscsel_dt_ids);

static struct i2c_driver mp2019_oscsel_i2c_driver = {
	.driver =
		{
			.name = "mp2019_oscsel",
			.of_match_table = mp2019_oscsel_dt_ids,
		},
	.probe = mp2019_oscsel_i2c_probe,
	.remove = mp2019_oscsel_i2c_remove,
	.id_table = mp2019_oscsel_id,
};
/* end mp2019_oscel I2C */











/* mp2019 I2C */
static const struct of_device_id mp2019_of_match[] = {
	{
		.compatible = "mp,mp-clkgen",
	},
	{}
};
MODULE_DEVICE_TABLE(of, mp2019_of_match);

static int mp2019_i2c_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct mp2019_codec_priv *mp;
	int ret;

	dev_warn(&client->dev, "BEGIN mp2019_i2c_probe");

	mp = devm_kzalloc(&client->dev, sizeof(*mp), GFP_KERNEL);
	if (!mp)
		return -ENOMEM;

	mp->current_clock = 0;
	mp->current_regmap = 0;

	dev_warn(&client->dev, "  PRE i2c_set_clientdata");
	i2c_set_clientdata(client, mp);

	dev_warn(&client->dev, "  PRE devm_regmap_init_i2c");
	mp->clkgen_regmap = devm_regmap_init_i2c(client, &mp2019_clock_regmap_config);
	if (IS_ERR(mp->clkgen_regmap)) {
		ret = PTR_ERR(mp->clkgen_regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	dev_warn(&client->dev, "END mp2019_i2c_probe");

	return 0;
}

static int mp2019_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id mp2019_codec_id[] = {
	{ "mp2019", 0 },
	{},
};
MODULE_DEVICE_TABLE(i2c, mp2019_codec_id);

static struct i2c_driver mp2019_i2c_driver = {
	.driver =
		{
			.name = "mp_clkgen",
			.of_match_table = mp2019_of_match,
		},
	.probe = mp2019_i2c_probe,
	.remove = mp2019_i2c_remove,
	.id_table = mp2019_codec_id,
};

static int __init mp2019_codec_init(void)
{
	int ret;

	ret = i2c_add_driver(&mp2019_i2c_driver);
	if (ret) {
		return ret;
	}
	ret = i2c_add_driver(&mp2019_oscsel_i2c_driver);
	if (ret) {
		i2c_del_driver(&mp2019_i2c_driver);
	}
	ret = i2c_add_driver(&mp2019_lcd_i2c_driver);
	if (ret) {
		i2c_del_driver(&mp2019_oscsel_i2c_driver);
		i2c_del_driver(&mp2019_i2c_driver);
	}
	return ret;
}
module_init(mp2019_codec_init);

static void __exit mp2019_codec_exit(void)
{
	i2c_del_driver(&mp2019_lcd_i2c_driver);
	i2c_del_driver(&mp2019_oscsel_i2c_driver);
	i2c_del_driver(&mp2019_i2c_driver);
}
module_exit(mp2019_codec_exit);

MODULE_DESCRIPTION("ASoC MP2019 Musica Pristina driver");
MODULE_AUTHOR("Kevin Welsh <kwelsh@welshtechnologies.com>");
MODULE_LICENSE("GPL");