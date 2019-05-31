/*
 * mp.c - Musica Pristina ALSA SoC codec driver
 *
 * Copyright 2018 Welsh Technologies.
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

static const struct snd_kcontrol_new mp_snd_controls[] = {
	{
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = dac_info_volsw,
		.get = dac_get_volsw,
		.put = dac_put_volsw,
	},
};

/* set codec format */
static int mp_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct mp_codec_priv *mp = snd_soc_codec_get_drvdata(codec);

	/* I2S clock and frame master setting. */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK)
	{
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	/* setting I2S data format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK)
	{
	case SND_SOC_DAIFMT_I2S:
		break;
	default:
		return -EINVAL;
	}

	mp->fmt = fmt;
	return 0;
}

/*
 * set clock according to i2s frame clock.
 */
static int mp_set_clock(struct snd_soc_codec *codec, int frame_rate,
						int frame_width)
{
	dev_warn(codec->dev, "BEGIN mp_set_clock");

	switch (frame_rate)
	{
	case 44100:
	case 48000:
	case 88200:
	case 96000:
	case 176400:
	case 192000:
	case 352800:
	case 384000:
		break;
		/*
#if defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_768)
#endif
*/

	case 705600:
	case 768000:
		if (maxrate == 768)
		{
			break;
		}
		else
		{
			dev_err(codec->dev, "frame rate %d not supported\n",
					frame_rate);
			return -EINVAL;
		}
	default:
		dev_err(codec->dev, "frame rate %d not supported\n",
				frame_rate);
		return -EINVAL;
	}
	switch (frame_width)
	{
	case 16:
	case 24:
	case 32:
		break;
	default:
		dev_err(codec->dev, "%d-bit frame width not supported\n", frame_width);
		return -EINVAL;
	}
	/*
#if defined(CONFIG_SND_SOC_MPCODEC_XTAL_OCXO)
	dev_warn(codec->dev, "    CONFIG_SND_SOC_MPCODEC_XTAL_OCXO");
	return update_playback_OCXO(codec, frame_rate, frame_width);
#elif defined(CONFIG_SND_SOC_MPCODEC_XTAL_DFXO)
	dev_warn(codec->dev, "    CONFIG_SND_SOC_MPCODEC_XTAL_DFXO");
	return update_playback_DFXO(codec, frame_rate, frame_width);
#endif
*/
	if (ocxo == 1)
	{
		/* OCXO crystal strategy */
		dev_warn(codec->dev, "    CONFIG_SND_SOC_MPCODEC_XTAL_OCXO");
		return update_playback_OCXO(codec, frame_rate, frame_width);
	}
	else
	{
		/* Dual Frequency XO crystal strategy */
		dev_warn(codec->dev, "    CONFIG_SND_SOC_MPCODEC_XTAL_DFXO");
		return update_playback_DFXO(codec, frame_rate, frame_width);
	}

	dev_warn(codec->dev, "END mp_set_clock");
	return 0;
}

/*
 * Set PCM DAI params.
 */
static int mp_pcm_hw_params(struct snd_pcm_substream *substream,
							struct snd_pcm_hw_params *params,
							struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	int ret;

	ret = mp_set_clock(codec, params_rate(params), params_width(params));
	if (ret)
		return ret;

	return 0;
}

static int mp_dai_trigger(struct snd_pcm_substream *substream, int cmd,
						  struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;

	switch (cmd)
	{
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dev_dbg(codec->dev, "Starting audio stream\n");
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dev_dbg(codec->dev, "Stopping audio stream\n");
		break;
	default:
		break;
	}

	return 0;
}
/*
#if defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_384)
static const unsigned int mp_rates[] = {
	44100,
	48000,
	88200,
	96000,
	176400,
	192000,
	352800,
	384000,
};
#elif defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_768)
static const unsigned int mp_rates[] = {
	44100,
	48000,
	88200,
	96000,
	176400,
	192000,
	352800,
	384000,
	705600,
	768000,
};
#endif
*/
/*
#if (maxrate==768)
*/
static const unsigned int mp_rates[] = {
	44100,
	48000,
	88200,
	96000,
	176400,
	192000,
	352800,
	384000,
	705600,
	768000,
};
/*#elif (maxrate!=768)
static const unsigned int mp_rates[] = {
	44100,
	48000,
	88200,
	96000,
	176400,
	192000,
	352800,
	384000,
};
#endif
*/

#define MP_CODEC_FORMATS (SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)
// remove to force 24 / 32 bit conversion
//SNDRV_PCM_FMTBIT_S16_LE | \


#define MP_CODEC_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |   \
						SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |   \
						SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000 | \
						SNDRV_PCM_RATE_352000 | SNDRV_PCM_RATE_384000 | \
						SNDRV_PCM_RATE_705600 | SNDRV_PCM_RATE_768000)

static const struct snd_pcm_hw_constraint_list mp_rate_constraints = {
	.count = ARRAY_SIZE(mp_rates),
	.list = mp_rates,
};

static int mp_codec_startup(struct snd_pcm_substream *substream,
							struct snd_soc_dai *dai)
{
	int ret;

	ret = snd_pcm_hw_constraint_list(substream->runtime, 0,
									 SNDRV_PCM_HW_PARAM_RATE, &mp_rate_constraints);

	return ret;
}

static const struct snd_soc_dai_ops mp_codec_ops = {
	.startup = mp_codec_startup,
	.hw_params = mp_pcm_hw_params,
	.set_fmt = mp_set_dai_fmt,
	.trigger = mp_dai_trigger,
};

static struct snd_soc_dai_driver mp_dai = {
	/*
#if defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_384)
#if defined(CONFIG_SND_SOC_MPCODEC_XTAL_OCXO)
	.name = "Musica Pristina 384 OCXO",
#elif defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_768)
	.name = "Musica Pristina 384 DFXO",
#endif
#elif defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_768)
#if defined(CONFIG_SND_SOC_MPCODEC_XTAL_OCXO)
	.name = "Musica Pristina 768 OCXO",
#elif defined(CONFIG_SND_SOC_MPCODEC_MAXRATE_768)
	.name = "Musica Pristina 768 DFXO",
#endif
#endif
*/
	.name = "Musica Pristina",
	.playback = {
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.formats = MP_CODEC_FORMATS,
	},
	.ops = &mp_codec_ops,
};

static int mp_codec_probe(struct snd_soc_codec *codec)
{
	return 0;
}

static int mp_codec_remove(struct snd_soc_codec *codec)
{
	return 0;
}

static struct snd_soc_codec_driver mp_codec_driver = {
	.probe = mp_codec_probe,
	.remove = mp_codec_remove,
	.component_driver = {
		.controls = mp_snd_controls,
		.num_controls = ARRAY_SIZE(mp_snd_controls),
	},
};

/* LCD DRIVER */

static const struct regmap_config mp_lcd_regmap = {
	.reg_bits = 16,
	.val_bits = 24,

	.max_register = 0xFFFF,

	.cache_type = REGCACHE_RBTREE,
};

static int mp_lcd_i2c_probe(struct i2c_client *client,
							const struct i2c_device_id *id)
{
	struct device_node *clkgen_np;
	struct i2c_client *clkgen_client;
	struct mp_codec_priv *mp;
	int ret;

	dev_warn(&client->dev, "BEGIN mp_lcd_i2c_probe");

	clkgen_np = of_parse_phandle(client->dev.of_node, "mp,clkgen", 0);
	if (!clkgen_np)
	{
		dev_err(&client->dev, "Failed to get clock generator phandle\n");
		return -ENODEV;
	}
	clkgen_client = of_find_i2c_device_by_node(clkgen_np);
	of_node_put(clkgen_np);
	if (!clkgen_client)
	{
		dev_dbg(&client->dev, "Clock generator I2C client not found\n");
		return -EPROBE_DEFER;
	}
	mp = i2c_get_clientdata(clkgen_client);
	put_device(&clkgen_client->dev);
	mp->lcd_regmap = devm_regmap_init_i2c(client, &mp_lcd_regmap);
	if (IS_ERR(mp->lcd_regmap))
	{
		ret = PTR_ERR(mp->lcd_regmap);
		dev_err(&client->dev,
				"Failed to allocate lcd regmap: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, mp);

	dev_warn(&client->dev, "END mp_lcd_i2c_probe");

	return 0;
}

static int mp_lcd_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id mp_lcd_id[] = {
	{"mp_lcd", 0},
	{},
};

MODULE_DEVICE_TABLE(i2c, mp_lcd_id);

static const struct of_device_id mp_lcd_dt_ids[] = {
	{
		.compatible = "mp,codec-lcd",
	},
	{/* sentinel */}};
MODULE_DEVICE_TABLE(of, mp_lcd_dt_ids);

static struct i2c_driver mp_lcd_i2c_driver = {
	.driver = {
		.name = "mp_lcd",
		.of_match_table = mp_lcd_dt_ids,
	},
	.probe = mp_lcd_i2c_probe,
	.remove = mp_lcd_i2c_remove,
	.id_table = mp_lcd_id,
};

/* END LCD DRIVER */

static const struct regmap_config mp_codec_regmap = {
	.reg_bits = 8,
	.val_bits = 8,

	.max_register = 0xFF,

	.cache_type = REGCACHE_RBTREE,
};

static const struct regmap_config mp_oscsel_regmap = {
	.reg_bits = 8,
	.val_bits = 8,

	.max_register = 0xFF,

	.cache_type = REGCACHE_RBTREE,
};

static int mp_oscsel_i2c_probe(struct i2c_client *client,
							   const struct i2c_device_id *id)
{
	struct device_node *clkgen_np;
	struct i2c_client *clkgen_client;
	struct mp_codec_priv *mp;
	int ret;
	int i;
	char name[80];
	char *strategy;
	char *rate;

	dev_warn(&client->dev, "BEGIN mp_oscsel_i2c_probe");

	clkgen_np = of_parse_phandle(client->dev.of_node, "mp,clkgen", 0);
	if (!clkgen_np)
	{
		dev_err(&client->dev, "Failed to get clock generator phandle\n");
		return -ENODEV;
	}
	clkgen_client = of_find_i2c_device_by_node(clkgen_np);
	of_node_put(clkgen_np);
	if (!clkgen_client)
	{
		dev_dbg(&client->dev, "Clock generator I2C client not found\n");
		return -EPROBE_DEFER;
	}
	mp = i2c_get_clientdata(clkgen_client);
	put_device(&clkgen_client->dev);
	mp->oscsel_regmap = devm_regmap_init_i2c(client, &mp_oscsel_regmap);
	if (IS_ERR(mp->oscsel_regmap))
	{
		ret = PTR_ERR(mp->oscsel_regmap);
		dev_err(&client->dev,
				"Failed to allocate oscillator selector regmap: %d\n", ret);
		return ret;
	}
	dev_warn(&client->dev, "    BEGIN i2c_set_clientdata(client, mp);");
	i2c_set_clientdata(client, mp);
	dev_warn(&client->dev, "    BEGIN i2c_set_clientdata(client, mp);");

	dev_warn(&client->dev, "BEGIN snd_soc_register_codec");


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
	snprintf(mp_dai.name, sizeof(mp_dai.name), "%s %d %s", mp_dai.name, maxrate, strategy);
	dev_warn(&client->dev, "*** and the name is: %s", mp_dai.name);

	*/

	ret = snd_soc_register_codec(&clkgen_client->dev, &mp_codec_driver, &mp_dai, 1);

	dev_warn(&client->dev, "END snd_soc_register_codec");
	if (ret)
		return ret;

	dev_warn(&client->dev, "    BEGIN default OSCSEL regs");

	for (i = 0; i < ARRAY_SIZE(mp_oscsel_reg_defaults); i++)
	{
		regmap_write(mp->oscsel_regmap, mp_oscsel_reg_defaults[i].reg,
					 mp_oscsel_reg_defaults[i].def);
	}

	dev_warn(&client->dev, "    END default OSCSEL regs");
	dev_warn(&client->dev, "    BEGIN default CLKGEN regs");

	for (i = 0; i < ARRAY_SIZE(mp_codec_reg_defaults); i++)
	{

		clkgen_regmap_write(mp->clkgen_regmap, mp_codec_reg_defaults[i].reg,
							mp_codec_reg_defaults[i].def);
	}

	dev_warn(&client->dev, "    END default CLKGEN regs");

	dev_warn(&client->dev, "END mp_oscsel_i2c_probe");

	return 0;
}

static int mp_oscsel_i2c_remove(struct i2c_client *client)
{
	snd_soc_unregister_codec(&client->dev);

	return 0;
}

static const struct i2c_device_id mp_oscsel_id[] = {
	{"mp_oscsel", 0},
	{},
};

MODULE_DEVICE_TABLE(i2c, mp_oscsel_id);

static const struct of_device_id mp_oscsel_dt_ids[] = {
	{
		.compatible = "mp,codec-oscsel",
	},
	{/* sentinel */}};
MODULE_DEVICE_TABLE(of, mp_oscsel_dt_ids);

static struct i2c_driver mp_oscsel_i2c_driver = {
	.driver = {
		.name = "mp_oscsel",
		.of_match_table = mp_oscsel_dt_ids,
	},
	.probe = mp_oscsel_i2c_probe,
	.remove = mp_oscsel_i2c_remove,
	.id_table = mp_oscsel_id,
};

static int mp_i2c_probe(struct i2c_client *client,
						const struct i2c_device_id *id)
{
	struct mp_codec_priv *mp;
	int ret;

	dev_warn(&client->dev, "BEGIN mp_i2c_probe");

	mp = devm_kzalloc(&client->dev, sizeof(*mp), GFP_KERNEL);
	if (!mp)
		return -ENOMEM;

	// defaults
	mp->current_clock = 0;
	mp->current_regmap = 0;


	dev_warn(&client->dev, "  PRE i2c_set_clientdata");
	i2c_set_clientdata(client, mp);

	dev_warn(&client->dev, "  PRE devm_regmap_init_i2c");
	mp->clkgen_regmap = devm_regmap_init_i2c(client, &mp_codec_regmap);
	if (IS_ERR(mp->clkgen_regmap))
	{
		ret = PTR_ERR(mp->clkgen_regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	dev_warn(&client->dev, "END mp_i2c_probe");

	return 0;
}

static int mp_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id mp_codec_id[] = {
	{"mp_clkgen", 0},
	{},
};

MODULE_DEVICE_TABLE(i2c, mp_codec_id);

static const struct of_device_id mp_codec_dt_ids[] = {
	{
		.compatible = "mp,codec-clkgen",
	},
	{/* sentinel */}};
MODULE_DEVICE_TABLE(of, mp_codec_dt_ids);

static struct i2c_driver mp_i2c_driver = {
	.driver = {
		.name = "mp_clkgen",
		.of_match_table = mp_codec_dt_ids,
	},
	.probe = mp_i2c_probe,
	.remove = mp_i2c_remove,
	.id_table = mp_codec_id,
};

static int __init mp_codec_init(void)
{
	int ret;

	ret = i2c_add_driver(&mp_i2c_driver);
	if (ret)
	{
		return ret;
	}
	ret = i2c_add_driver(&mp_oscsel_i2c_driver);
	if (ret)
	{
		i2c_del_driver(&mp_i2c_driver);
	}
	ret = i2c_add_driver(&mp_lcd_i2c_driver);
	if (ret)
	{
		i2c_del_driver(&mp_oscsel_i2c_driver);
		i2c_del_driver(&mp_i2c_driver);
	}
	return ret;
}

module_init(mp_codec_init);

static void __exit mp_codec_exit(void)
{
	i2c_del_driver(&mp_lcd_i2c_driver);
	i2c_del_driver(&mp_oscsel_i2c_driver);
	i2c_del_driver(&mp_i2c_driver);
}

module_exit(mp_codec_exit);



MODULE_DESCRIPTION("Musica Pristina ALSA SoC codec driver");
MODULE_AUTHOR("Francesco Lavra <francescolavra.fl@gmail.com>");
MODULE_AUTHOR("Kevin Welsh <kwelsh@welshtechnologies.com>");
MODULE_LICENSE("GPL");
