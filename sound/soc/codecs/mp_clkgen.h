/*
 * mp_clkgen.h - Musica Pristina ALSA SoC codec driver clock configuration
 *
 * Copyright 2018 Welsh Technologies.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/regmap.h>
#include <sound/soc.h>

struct mp2019_codec_priv {
	int fmt;
	int current_clock;
	int current_regmap;
	struct regmap *clkgen_regmap;
	struct regmap *oscsel_regmap;
	struct regmap *lcd_regmap;
};



static inline void enable_DFXO_451584(struct mp2019_codec_priv *mp)
{
	
	if(mp->current_clock != 3) {
		mp->current_clock = 3;
		regmap_write(mp->oscsel_regmap, 0x01, 0xf9);
	}
}

static inline void enable_DFXO_49152(struct mp2019_codec_priv *mp)
{
	
	if(mp->current_clock != 2) {
		mp->current_clock = 2;
		regmap_write(mp->oscsel_regmap, 0x01, 0xfa);
	}
}

static inline void enable_OCXO(struct mp2019_codec_priv *mp)
{
	
    int clock;
    clock = mp->current_clock;
    pr_warn("BEGIN enable_OCXO");
    pr_warn("  mp->current_clock: %d", clock);
	if(clock != 1) {
        pr_warn("    if(mp->current_clock != 1) {");
		mp->current_clock = 1;
        pr_warn("        mp->current_clock = 1;");
		regmap_write(mp->oscsel_regmap, 0x01, 0xfc);
        pr_warn("            regmap_write(mp->oscsel_regmap, 0x01, 0xfc);");
	}
    pr_warn("END enable_OCXO");
}

static inline void clkgen_regmap_write(struct regmap *regmap, unsigned int reg, unsigned int def) 
{
    unsigned int regPageVal;
	unsigned int regAddr;
	unsigned int mask;

    regPageVal = reg >> 8;
	regmap_write(regmap, 0x01,
			regPageVal);
		
	mask = 0x00ff;
	regAddr = reg & mask;
		
	regmap_write(regmap, regAddr,
				def);

    if(reg == 0x0B4E) {
        msleep(300);
        pr_warn("*** SLEEP");    
    }

    pr_warn("*** regPageVal: %d regAddr: %d def: %d", regPageVal, regAddr, def);
}

/* default value of I2C registers for OSCSEL */
static const struct reg_default mp2019_oscsel_reg_defaults[] = {
		{ 0x03,		0xf0 },
        { 0x01,		0xfc },
};

/* default value of I2C registers for CLKGEN */
static const struct reg_default mp2019_codec_reg_defaults[] = {
        {0x0B24,0xC0},
        {0x0B25,0x00},
		{0x0502,0x01},
		{0x0505,0x03},
		{0x0957,0x17},
		{0x0B4E,0x1A},
		{0x0006,0x00},
		{0x0007,0x00},
		{0x0008,0x00},
		{0x000B,0x74},
		{0x0017,0xD0},
		{0x0018,0xFF},
		{0x0021,0x0F},
		{0x0022,0x00},
		{0x002B,0x02},
		{0x002C,0x20},
		{0x002D,0x00},
		{0x002E,0x00},
		{0x002F,0x00},
		{0x0030,0x00},
		{0x0031,0x00},
		{0x0032,0x00},
		{0x0033,0x00},
		{0x0034,0x00},
		{0x0035,0x00},
		{0x0036,0x00},
		{0x0037,0x00},
		{0x0038,0x00},
		{0x0039,0x00},
		{0x003A,0x00},
		{0x003B,0x00},
		{0x003C,0x00},
		{0x003D,0x00},
		{0x0041,0x00},
		{0x0042,0x00},
		{0x0043,0x00},
		{0x0044,0x00},
		{0x009E,0x00},
		{0x0102,0x01},
		{0x0112,0x02},
		{0x0113,0x09},
		{0x0114,0x33},
		{0x0115,0x08},
		{0x0117,0x02},
		{0x0118,0x09},
		{0x0119,0x6B},
		{0x011A,0x08},
		{0x0126,0x02},
		{0x0127,0x09},
		/* {0x0128,0x6B},
        LVDS
        */
        {0x0128,0x33},
        /* ----
         {0x0129,0x08},
         LVDS
        */
		{0x0129,0x08},
        /* ---- */
		{0x012B,0x02},
		{0x012C,0xCC},
		{0x012D,0x00},
		{0x012E,0x08},
		{0x013F,0x00},
		{0x0140,0x00},
		{0x0141,0x40},
		{0x0206,0x00},
		{0x0208,0x00},
		{0x0209,0x00},
		{0x020A,0x00},
		{0x020B,0x00},
		{0x020C,0x00},
		{0x020D,0x00},
		{0x020E,0x00},
		{0x020F,0x00},
		{0x0210,0x00},
		{0x0211,0x00},
		{0x0212,0x00},
		{0x0213,0x00},
		{0x0214,0x00},
		{0x0215,0x00},
		{0x0216,0x00},
		{0x0217,0x00},
		{0x0218,0x00},
		{0x0219,0x00},
		{0x021A,0x00},
		{0x021B,0x00},
		{0x021C,0x00},
		{0x021D,0x00},
		{0x021E,0x00},
		{0x021F,0x00},
		{0x0220,0x00},
		{0x0221,0x00},
		{0x0222,0x00},
		{0x0223,0x00},
		{0x0224,0x00},
		{0x0225,0x00},
		{0x0226,0x00},
		{0x0227,0x00},
		{0x0228,0x00},
		{0x0229,0x00},
		{0x022A,0x00},
		{0x022B,0x00},
		{0x022C,0x00},
		{0x022D,0x00},
		{0x022E,0x00},
		{0x022F,0x00},
		{0x0235,0x00},
		{0x0236,0x00},
		{0x0237,0x00},
		{0x0238,0x76},
		{0x0239,0xFA},
		{0x023A,0x01},
		{0x023B,0x00},
		{0x023C,0x00},
		{0x023D,0x50},
		{0x023E,0xC3},
		{0x0250,0x0F},
		{0x0251,0x00},
		{0x0252,0x00},
		{0x0253,0xFF},
		{0x0254,0x03},
		{0x0255,0x00},
		{0x025C,0x0F},
		{0x025D,0x00},
		{0x025E,0x00},
		{0x025F,0x43},
		{0x0260,0xAC},
		{0x0261,0x00},
		{0x026B,0x4D},
		{0x026C,0x50},
		{0x026D,0x5F},
		{0x026E,0x30},
		{0x026F,0x30},
		{0x0270,0x30},
		{0x0271,0x30},
		{0x0272,0x31},
		{0x0302,0x00},
		{0x0303,0x00},
		{0x0304,0x00},
		{0x0305,0x80},
		{0x0306,0x49},
		{0x0307,0x00},
		{0x0308,0x00},
		{0x0309,0x00},
		{0x030A,0x00},
		{0x030B,0x80},
		{0x030C,0x00},
		{0x030D,0x00},
		{0x030E,0x00},
		{0x030F,0x00},
		{0x0310,0x00},
		{0x0311,0x00},
		{0x0312,0x00},
		{0x0313,0x00},
		{0x0314,0x00},
		{0x0315,0x00},
		{0x0316,0x00},
		{0x0317,0x00},
		{0x0318,0x00},
		{0x0319,0x00},
		{0x031A,0x00},
		{0x031B,0x00},
		{0x031C,0x00},
		{0x031D,0x00},
		{0x031E,0x00},
		{0x031F,0x00},
		{0x0320,0x00},
		{0x0321,0x00},
		{0x0322,0x00},
		{0x0323,0x00},
		{0x0324,0x00},
		{0x0325,0x00},
		{0x0326,0x00},
		{0x0327,0x00},
		{0x0328,0x00},
		{0x0329,0x00},
		{0x032A,0x00},
		{0x032B,0x00},
		{0x032C,0x00},
		{0x032D,0x00},
		{0x0338,0x00},
		{0x0339,0x1F},
		{0x033B,0x00},
		{0x033C,0x00},
		{0x033D,0x00},
		{0x033E,0x00},
		{0x033F,0x00},
		{0x0340,0x00},
		{0x0341,0x00},
		{0x0342,0x00},
		{0x0343,0x00},
		{0x0344,0x00},
		{0x0345,0x00},
		{0x0346,0x00},
		{0x0347,0x00},
		{0x0348,0x00},
		{0x0349,0x00},
		{0x034A,0x00},
		{0x034B,0x00},
		{0x034C,0x00},
		{0x034D,0x00},
		{0x034E,0x00},
		{0x034F,0x00},
		{0x0350,0x00},
		{0x0351,0x00},
		{0x0352,0x00},
		{0x0359,0x00},
		{0x035A,0x00},
		{0x035B,0x00},
		{0x035C,0x00},
		{0x035D,0x00},
		{0x035E,0x00},
		{0x035F,0x00},
		{0x0360,0x00},
		{0x0802,0x00},
		{0x0803,0x00},
		{0x0804,0x00},
		{0x0805,0x00},
		{0x0806,0x00},
		{0x0807,0x00},
		{0x0808,0x00},
		{0x0809,0x00},
		{0x080A,0x00},
		{0x080B,0x00},
		{0x080C,0x00},
		{0x080D,0x00},
		{0x080E,0x00},
		{0x080F,0x00},
		{0x0810,0x00},
		{0x0811,0x00},
		{0x0812,0x00},
		{0x0813,0x00},
		{0x0814,0x00},
		{0x0815,0x00},
		{0x0816,0x00},
		{0x0817,0x00},
		{0x0818,0x00},
		{0x0819,0x00},
		{0x081A,0x00},
		{0x081B,0x00},
		{0x081C,0x00},
		{0x081D,0x00},
		{0x081E,0x00},
		{0x081F,0x00},
		{0x0820,0x00},
		{0x0821,0x00},
		{0x0822,0x00},
		{0x0823,0x00},
		{0x0824,0x00},
		{0x0825,0x00},
		{0x0826,0x00},
		{0x0827,0x00},
		{0x0828,0x00},
		{0x0829,0x00},
		{0x082A,0x00},
		{0x082B,0x00},
		{0x082C,0x00},
		{0x082D,0x00},
		{0x082E,0x00},
		{0x082F,0x00},
		{0x0830,0x00},
		{0x0831,0x00},
		{0x0832,0x00},
		{0x0833,0x00},
		{0x0834,0x00},
		{0x0835,0x00},
		{0x0836,0x00},
		{0x0837,0x00},
		{0x0838,0x00},
		{0x0839,0x00},
		{0x083A,0x00},
		{0x083B,0x00},
		{0x083C,0x00},
		{0x083D,0x00},
		{0x083E,0x00},
		{0x083F,0x00},
		{0x0840,0x00},
		{0x0841,0x00},
		{0x0842,0x00},
		{0x0843,0x00},
		{0x0844,0x00},
		{0x0845,0x00},
		{0x0846,0x00},
		{0x0847,0x00},
		{0x0848,0x00},
		{0x0849,0x00},
		{0x084A,0x00},
		{0x084B,0x00},
		{0x084C,0x00},
		{0x084D,0x00},
		{0x084E,0x00},
		{0x084F,0x00},
		{0x0850,0x00},
		{0x0851,0x00},
		{0x0852,0x00},
		{0x0853,0x00},
		{0x0854,0x00},
		{0x0855,0x00},
		{0x0856,0x00},
		{0x0857,0x00},
		{0x0858,0x00},
		{0x0859,0x00},
		{0x085A,0x00},
		{0x085B,0x00},
		{0x085C,0x00},
		{0x085D,0x00},
		{0x085E,0x00},
		{0x085F,0x00},
		{0x0860,0x00},
		{0x0861,0x00},
		{0x090E,0x03},
		{0x091C,0x04},
		{0x0943,0x00},
		{0x0949,0x00},
		{0x094A,0x00},
		{0x094E,0x49},
		{0x094F,0x02},
		{0x095E,0x00},
		{0x0A02,0x00},
		{0x0A03,0x01},
		{0x0A04,0x01},
		{0x0A05,0x01},
		{0x0A14,0x00},
		{0x0A1A,0x00},
		{0x0A20,0x00},
		{0x0A26,0x00},
		{0x0B44,0x0F},
		{0x0B4A,0x0E},
		{0x0B57,0x88},
		{0x0B58,0x02},
		{0x001C,0x01},
		{0x0B24,0xC3},
		{0x0B25,0x02},
        /* */
        {0x0B24, 0xC0},
        {0x0B25, 0x00},
        {0x0502, 0x01},
        {0x0505, 0x03},
        {0x0957, 0x17},
        {0x0B4E, 0x1A},
        {0x0018, 0xFF},
        {0x0021, 0x0F},
        {0x002C, 0x20},
        {0x002D, 0x00},
        {0x002E, 0x00},
        {0x0030, 0x00},
        {0x0036, 0x00},
        {0x0038, 0x00},
        {0x0041, 0x00},
        {0x0042, 0x00},
        {0x0112, 0x02},
        {0x0126, 0x02},
        {0x0208, 0x00},
        {0x020E, 0x00},
        {0x0212, 0x00},
        {0x0218, 0x00},
        {0x0238, 0x76},
        {0x0239, 0xFA},
        {0x023A, 0x01},
        {0x023D, 0x50},
        {0x023E, 0xC3},
        {0x0250, 0x1F},
        {0x0253, 0xFF},
        {0x0254, 0x03},
        {0x025C, 0x1F},
        {0x025F, 0x43},
        {0x0260, 0xAC},
        {0x0261, 0x00},
        {0x0305, 0x80},
        {0x0306, 0x49},
        {0x0307, 0x00},
        {0x090E, 0x03},
        {0x0949, 0x00},
        {0x094A, 0x00},
        {0x0B57, 0x88},
        {0x0B58, 0x02},
        {0x001C, 0x01},
        {0x0B24, 0xC3},
        {0x0B25, 0x02},
};

static inline void clkgen_regmap_01(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 1)
    {
        mp->current_regmap = 1;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_02(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 2)
    {
        mp->current_regmap = 2;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_03(struct mp2019_codec_priv *mp)
{
    
    pr_warn("   ***  clkgen_regmap_03");

    enable_OCXO(mp);

    if(mp->current_regmap != 3)
    {
        mp->current_regmap = 3;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_04(struct mp2019_codec_priv *mp)
{
    
    pr_warn("   ***  clkgen_regmap_04");

    enable_OCXO(mp);
    pr_warn("   POST enable_OCXO(mp);");
    if(mp->current_regmap != 4)
    {
        mp->current_regmap = 4;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x27);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x23);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_05(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 5)
    {
        mp->current_regmap = 5;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x68);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xC9);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x08);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_06(struct mp2019_codec_priv *mp)
{
    
    pr_warn("   ***  clkgen_regmap_06");

    enable_OCXO(mp);

    if(mp->current_regmap != 6)
    {
        mp->current_regmap = 6;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x27);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x23);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_07(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 7)
    {
        mp->current_regmap = 7;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_08(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 8)
    {
        mp->current_regmap = 8;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_09(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 9)
    {
        mp->current_regmap = 9;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_10(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 10)
    {
        mp->current_regmap = 10;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0xE0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0xB3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_11(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 11)
    {
        mp->current_regmap = 11;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x27);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x23);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}

static inline void clkgen_regmap_12(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 12)
    {
        mp->current_regmap = 12;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x27);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x23);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_13(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 13)
    {
        mp->current_regmap = 13;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_14(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 14)
    {
        mp->current_regmap = 14;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_15(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 15)
    {
        mp->current_regmap = 15;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_16(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 16)
    {
        mp->current_regmap = 16;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x9F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x8C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x5A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_17(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 17)
    {
        mp->current_regmap = 17;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x27);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x23);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_18(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 18)
    {
        mp->current_regmap = 18;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0xE0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0xB3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_19(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 19)
    {
        mp->current_regmap = 19;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x53);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x5D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_20(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 20)
    {
        mp->current_regmap = 20;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_21(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 21)
    {
        mp->current_regmap = 21;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_22(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 22)
    {
        mp->current_regmap = 22;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xBB);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_23(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 23)
    {
        mp->current_regmap = 23;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0xE0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0xB3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_24(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 24)
    {
        mp->current_regmap = 24;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x9F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x8C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x5A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_25(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 25)
    {
        mp->current_regmap = 25;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x53);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x5D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_26(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 26)
    {
        mp->current_regmap = 26;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_27(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 27)
    {
        mp->current_regmap = 27;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x95);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x53);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x5D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_28(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 28)
    {
        mp->current_regmap = 28;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x9E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x64);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_29(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 29)
    {
        mp->current_regmap = 29;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x9E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x9C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x64);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_30(struct mp2019_codec_priv *mp)
{
    
    enable_OCXO(mp);

    if(mp->current_regmap != 30)
    {
        mp->current_regmap = 30;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0xFA);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xBB);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x88);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_31(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 31)
    {
        mp->current_regmap = 31;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x30);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x2B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x91);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_32(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 32)
    {
        mp->current_regmap = 32;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x81);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_33(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 33)
    {
        mp->current_regmap = 33;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x30);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x2B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x91);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_34(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 34)
    {
        mp->current_regmap = 34;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x21);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x56);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_35(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 35)
    {
        mp->current_regmap = 35;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x81);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_36(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 36)
    {
        mp->current_regmap = 36;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x30);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x2B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x91);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_37(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 37)
    {
        mp->current_regmap = 37;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x24);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_38(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 38)
    {
        mp->current_regmap = 38;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x81);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_39(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 39)
    {
        mp->current_regmap = 39;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x21);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x56);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_40(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 40)
    {
        mp->current_regmap = 40;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x87);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x58);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_41(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 41)
    {
        mp->current_regmap = 41;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x65);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_42(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 42)
    {
        mp->current_regmap = 42;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xAC);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x24);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_43(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 43)
    {
        mp->current_regmap = 43;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x93);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x0F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xB1);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x49);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_44(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 44)
    {
        mp->current_regmap = 44;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x96);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x40);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xCB);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x61);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_45(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_451584(mp);

    if(mp->current_regmap != 45)
    {
        mp->current_regmap = 45;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFE);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x09);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x31);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x97);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x87);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x58);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x92);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x10);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x1E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_46(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 46)
    {
        mp->current_regmap = 46;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x6F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_47(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 47)
    {
        mp->current_regmap = 47;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x70);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_48(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 48)
    {
        mp->current_regmap = 48;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x6F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_49(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 49)
    {
        mp->current_regmap = 49;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x60);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xDF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x2E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x19);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_50(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 50)
    {
        mp->current_regmap = 50;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x70);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x5F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_51(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 51)
    {
        mp->current_regmap = 51;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x50);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x6F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_52(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 52)
    {
        mp->current_regmap = 52;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x5D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_53(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 53)
    {
        mp->current_regmap = 53;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x70);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x4F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x46);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x66);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_54(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 54)
    {
        mp->current_regmap = 54;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x60);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xDF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x2E);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x19);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_55(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 55)
    {
        mp->current_regmap = 55;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xBB);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_56(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 56)
    {
        mp->current_regmap = 56;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0xA0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x9F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x8C);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0xB3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_57(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 57)
    {
        mp->current_regmap = 57;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xBF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x5D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x0D);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_58(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 58)
    {
        mp->current_regmap = 58;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x87);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0xFF);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x76);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x43);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_59(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 59)
    {
        mp->current_regmap = 59;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x87);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x2F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x3F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0x19);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x5A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}


static inline void clkgen_regmap_60(struct mp2019_codec_priv *mp)
{
    
    enable_DFXO_49152(mp);

    if(mp->current_regmap != 60)
    {
        mp->current_regmap = 60;
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC0);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0502, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0505, 0x03);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0957, 0x17);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B4E, 0x1A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0018, 0xFD);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0021, 0x0B);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002C, 0x32);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002D, 0x04);
        clkgen_regmap_write(mp->clkgen_regmap, 0x002E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0030, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0036, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0038, 0x8A);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0041, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0042, 0x05);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0112, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0126, 0x06);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0208, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x020E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0212, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0218, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0238, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0239, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023A, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023D, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x023E, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0250, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0253, 0x1F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0254, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025C, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x025F, 0x7F);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0260, 0xBB);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0261, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0305, 0x80);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0306, 0x86);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0307, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x090E, 0x00);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0949, 0x02);
        clkgen_regmap_write(mp->clkgen_regmap, 0x094A, 0x20);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B57, 0x07);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B58, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x001C, 0x01);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B24, 0xC3);
        clkgen_regmap_write(mp->clkgen_regmap, 0x0B25, 0x02);
    }
}