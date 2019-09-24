/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * mp.h - definitions for MP2019
 *
 * Copyright 2019 Welsh Technologies
 */

#ifndef __MP2019_H__
#define __MP2019_H__

#define MP2019_FORMATS (SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S24_LE)
/*
#define MP2019_FORMATS (SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)
	remove 16 to force 24 / 32 bit conversion ** SNDRV_PCM_FMTBIT_S16_LE | \
*/


#define MP2019_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |   \
						SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |   \
						SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000 | \
						SNDRV_PCM_RATE_352000 | SNDRV_PCM_RATE_384000 | \
						SNDRV_PCM_RATE_705600 | SNDRV_PCM_RATE_768000)

extern const struct regmap_config mp2019_regmap_config;

int mp2019_common_init(struct device *dev, struct regmap *regmap);

#endif

#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/i2c.h>
#include <sound/soc.h>
#include "mp_clkgen.h"

static inline int update_playback_OCXO(struct snd_soc_component *component, int frame_rate,
									   int frame_width)
{
	int nextFamily = 0;
	struct mp2019_codec_priv *mp = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "update_playback_OCXO %d %d", frame_rate, frame_width);
	regmap_write(mp->lcd_regmap, 0x01, frame_rate);
	regmap_write(mp->lcd_regmap, 0x02, frame_width);

	switch (frame_rate)
	{
	case 44100:
		nextFamily = 48;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_03(mp);
			break;
		case 24:
			clkgen_regmap_02(mp);
			break;
		case 32:
			clkgen_regmap_01(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 48000:
		nextFamily = 48;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_06(mp);
			break;
		case 24:
			clkgen_regmap_05(mp);
			break;
		case 32:
			clkgen_regmap_04(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 88200:
		nextFamily = 96;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_09(mp);
			break;
		case 24:
			clkgen_regmap_08(mp);
			break;
		case 32:
			clkgen_regmap_07(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 96000:
		nextFamily = 96;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_12(mp);
			break;
		case 24:
			clkgen_regmap_11(mp);
			break;
		case 32:
			clkgen_regmap_10(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 176400:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_15(mp);
			break;
		case 24:
			clkgen_regmap_14(mp);
			break;
		case 32:
			clkgen_regmap_13(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 192000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_18(mp);
			break;
		case 24:
			clkgen_regmap_17(mp);
			break;
		case 32:
			clkgen_regmap_16(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 352800:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_21(mp);
			break;
		case 24:
			clkgen_regmap_20(mp);
			break;
		case 32:
			clkgen_regmap_19(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 384000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_24(mp);
			break;
		case 24:
			clkgen_regmap_23(mp);
			break;
		case 32:
			clkgen_regmap_22(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 705600:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_27(mp);
			break;
		case 24:
			clkgen_regmap_26(mp);
			break;
		case 32:
			clkgen_regmap_25(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 768000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_30(mp);
			break;
		case 24:
			clkgen_regmap_29(mp);
			break;
		case 32:
			clkgen_regmap_28(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	default:
		dev_err(component->dev, "frame rate %d not supported\n",
				frame_rate);
		return -EINVAL;
	}

	pr_warn("* AES SETUP ");
	pr_warn(" * %d", frame_rate);
	pr_warn(" * %d", frame_width);
	if(nextFamily != mp->family) {
		pr_warn(" * nextFamily != mp->family ");

		switch (nextFamily)
		{
		case 48:
			pr_warn("    44.1 / 48: 0x03, 0x33, then 0x37");
			regmap_write(mp->aes_regmap, 0x03, 0x33);
			msleep(10);
			regmap_write(mp->aes_regmap, 0x03, 0x37);
			break;
		case 96:
			pr_warn("    88.2 / 96: 0x03, 0x13, then 0x17");
			regmap_write(mp->aes_regmap, 0x03, 0x13);
			msleep(10);
			regmap_write(mp->aes_regmap, 0x03, 0x17);
			break;
		case 192:
			pr_warn("    176.8 / 192: 0x03, 0x03, then 0x07");
			regmap_write(mp->aes_regmap, 0x03, 0x03);
			msleep(10);
			regmap_write(mp->aes_regmap, 0x03, 0x07);
			break;
		default:
			pr_warn("    AES nextFamily: %d", nextFamily);
			break;
		}

		pr_warn("    AES nextFamily: %d", nextFamily);
		mp->family = nextFamily;
		pr_warn("    AES mp->family: %d", mp->family);

	}

	return 0;
}

static inline int update_playback_DFXO(struct snd_soc_component *component,
									   int frame_rate, int frame_width)
{
	int nextFamily;
	struct mp2019_codec_priv *mp = snd_soc_component_get_drvdata(component);
	switch (frame_rate)
	{
	case 44100:
		nextFamily = 48;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_33(mp);
			break;
		case 24:
			clkgen_regmap_32(mp);
			break;
		case 32:
			clkgen_regmap_31(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 48000:
		nextFamily = 48;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_48(mp);
			break;
		case 24:
			clkgen_regmap_47(mp);
			break;
		case 32:
			clkgen_regmap_46(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 88200:
		nextFamily = 96;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_36(mp);
			break;
		case 24:
			clkgen_regmap_35(mp);
			break;
		case 32:
			clkgen_regmap_34(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 96000:
		nextFamily = 96;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_51(mp);
			break;
		case 24:
			clkgen_regmap_50(mp);
			break;
		case 32:
			clkgen_regmap_49(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 176400:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_39(mp);
			break;
		case 24:
			clkgen_regmap_38(mp);
			break;
		case 32:
			clkgen_regmap_37(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 192000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_54(mp);
			break;
		case 24:
			clkgen_regmap_53(mp);
			break;
		case 32:
			clkgen_regmap_52(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 352800:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_42(mp);
			break;
		case 24:
			clkgen_regmap_41(mp);
			break;
		case 32:
			clkgen_regmap_40(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 384000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_57(mp);
			break;
		case 24:
			clkgen_regmap_56(mp);
			break;
		case 32:
			clkgen_regmap_55(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 705600:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_45(mp);
			break;
		case 24:
			clkgen_regmap_44(mp);
			break;
		case 32:
			clkgen_regmap_43(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 768000:
		nextFamily = 192;
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_60(mp);
			break;
		case 24:
			clkgen_regmap_59(mp);
			break;
		case 32:
			clkgen_regmap_58(mp);
			break;
		default:
			dev_err(component->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	default:
		dev_err(component->dev, "frame rate %d not supported\n",
				frame_rate);
		return -EINVAL;
	}
	if(nextFamily != mp->family) {
		regmap_write(mp->aes_regmap, 0x03, 0x83);
		switch (nextFamily)
		{
		case 48:
			regmap_write(mp->aes_regmap, 0x03, 0x37);
			break;
		case 96:
			regmap_write(mp->aes_regmap, 0x03, 0x17);
			break;
		case 192:
			regmap_write(mp->aes_regmap, 0x03, 0x07);
			break;
		}
		mp->family = nextFamily;	
	}
	return 0;
}
