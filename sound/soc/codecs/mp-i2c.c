// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * mp ASoC I2C driver
 *
 * Copyright (c) Welsh Technologies
 *
 *     Kevin Welsh <kwelsh@welshtechnologies.com>
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/i2c.h>
#include <linux/regmap.h>

#include "mp.h"

static int mp_i2c_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_i2c(client, &mp_regmap_config);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	return mp_common_init(&client->dev, regmap);
}

static const struct of_device_id mp2019_of_match[] = {
	{ .compatible = "mp,mp2019", },
	{ }
};
MODULE_DEVICE_TABLE(of, mp_of_match);

static const struct i2c_device_id mp2019_i2c_ids[] = {
	{ "mp", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, mp2019_i2c_ids);

static struct i2c_driver mp2019_clock_i2c_driver = {
	.driver = {
		.name	= "mp2019",
		.of_match_table = of_match_ptr(mp2019_of_match),
	},
	.id_table	= mp2019_i2c_ids,
	.probe		= mp2019_i2c_probe,
};

module_i2c_driver(mp2019_i2c_driver);

MODULE_DESCRIPTION("ASoC MP I2C driver");
MODULE_AUTHOR("Kevin Welsh <kwelsh@welshtechnologies.com>");
MODULE_LICENSE("GPL");