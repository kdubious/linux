/*
 * mp.h - Musica Pristina ALSA SoC codec driver header file
 *
 * Copyright 2018 Welsh Technologies.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/i2c.h>
#include <sound/soc.h>
#include "mp_clkgen.h"


static inline int update_playback_OCXO(struct snd_soc_codec *codec, int frame_rate,
									   int frame_width)
{
	struct mp_codec_priv *mp = snd_soc_codec_get_drvdata(codec);
	pr_warn("update_playback_OCXO %d %d", frame_rate, frame_width);
	regmap_write(mp->lcd_regmap, 0x01, frame_rate);
	regmap_write(mp->lcd_regmap, 0x02, frame_width);

	switch (frame_rate)
	{
	case 44100:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_03(codec);
			break;
		case 24:
			clkgen_regmap_02(codec);
			break;
		case 32:
			clkgen_regmap_01(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 48000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_06(codec);
			break;
		case 24:
			clkgen_regmap_05(codec);
			break;
		case 32:
			clkgen_regmap_04(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 88200:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_09(codec);
			break;
		case 24:
			clkgen_regmap_08(codec);
			break;
		case 32:
			clkgen_regmap_07(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 96000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_12(codec);
			break;
		case 24:
			clkgen_regmap_11(codec);
			break;
		case 32:
			clkgen_regmap_10(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 176400:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_15(codec);
			break;
		case 24:
			clkgen_regmap_14(codec);
			break;
		case 32:
			clkgen_regmap_13(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 192000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_18(codec);
			break;
		case 24:
			clkgen_regmap_17(codec);
			break;
		case 32:
			clkgen_regmap_16(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 352800:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_21(codec);
			break;
		case 24:
			clkgen_regmap_20(codec);
			break;
		case 32:
			clkgen_regmap_19(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 384000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_24(codec);
			break;
		case 24:
			clkgen_regmap_23(codec);
			break;
		case 32:
			clkgen_regmap_22(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 705600:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_27(codec);
			break;
		case 24:
			clkgen_regmap_26(codec);
			break;
		case 32:
			clkgen_regmap_25(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 768000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_30(codec);
			break;
		case 24:
			clkgen_regmap_29(codec);
			break;
		case 32:
			clkgen_regmap_28(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	default:
		dev_err(codec->dev, "frame rate %d not supported\n",
				frame_rate);
		return -EINVAL;
	}
	return 0;
}

static inline int update_playback_DFXO(struct snd_soc_codec *codec, int frame_rate,
									   int frame_width)
{
	switch (frame_rate)
	{
	case 44100:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_33(codec);
			break;
		case 24:
			clkgen_regmap_32(codec);
			break;
		case 32:
			clkgen_regmap_31(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 48000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_48(codec);
			break;
		case 24:
			clkgen_regmap_47(codec);
			break;
		case 32:
			clkgen_regmap_46(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 88200:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_36(codec);
			break;
		case 24:
			clkgen_regmap_35(codec);
			break;
		case 32:
			clkgen_regmap_34(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 96000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_51(codec);
			break;
		case 24:
			clkgen_regmap_50(codec);
			break;
		case 32:
			clkgen_regmap_49(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 176400:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_39(codec);
			break;
		case 24:
			clkgen_regmap_38(codec);
			break;
		case 32:
			clkgen_regmap_37(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 192000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_54(codec);
			break;
		case 24:
			clkgen_regmap_53(codec);
			break;
		case 32:
			clkgen_regmap_52(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 352800:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_42(codec);
			break;
		case 24:
			clkgen_regmap_41(codec);
			break;
		case 32:
			clkgen_regmap_40(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 384000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_57(codec);
			break;
		case 24:
			clkgen_regmap_56(codec);
			break;
		case 32:
			clkgen_regmap_55(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 705600:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_45(codec);
			break;
		case 24:
			clkgen_regmap_44(codec);
			break;
		case 32:
			clkgen_regmap_43(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	case 768000:
		switch (frame_width)
		{
		case 16:
			clkgen_regmap_60(codec);
			break;
		case 24:
			clkgen_regmap_59(codec);
			break;
		case 32:
			clkgen_regmap_58(codec);
			break;
		default:
			dev_err(codec->dev, "%-d-bit frame width not supported\n", frame_width);
			return -EINVAL;
		}
		break;
	default:
		dev_err(codec->dev, "frame rate %d not supported\n",
				frame_rate);
		return -EINVAL;
	}
	return 0;
}
