/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/ioport.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>

/* Key gpio configurations */
static struct gpiomux_setting gpio_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting gpio_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting gpio_home_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_home_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm_keypad_configs[] __initdata = {
	{
		.gpio = 106,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_keys_suspend,
		},
	},
	{
		.gpio = 107,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_keys_suspend,
		},
	},
	{
		.gpio = 108,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_home_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_home_keys_suspend,
		},
	},
};

/* SPI configurations */
static struct gpiomux_setting gpio_spi_act_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gpio_spi_cs_act_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct gpiomux_setting gpio_spi_susp_config = {

	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

/* WCNSS configurations */
static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sd_card_det_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting sd_card_det_sleep_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config sd_card_det __initdata = {
	.gpio = 38,
	.settings = {
		[GPIOMUX_ACTIVE]    = &sd_card_det_active_config,
		[GPIOMUX_SUSPENDED] = &sd_card_det_sleep_config,
	},
};


static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

/* GPIO i2c configurations */
static struct gpiomux_setting gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

/* Sensor configurations */
static struct gpiomux_setting sensor_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting accel_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting prox_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting mag_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting rgb_sda_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_sensors_configs[] __initdata = {
	{
		.gpio      = 65,		/* PROXY IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &prox_irq_config,
			[GPIOMUX_SUSPENDED] = &prox_irq_config,
		},
	},
	{
		.gpio      = 64,		/* G_SENSOR IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &accel_irq_config,
			[GPIOMUX_SUSPENDED] = &accel_irq_config,
		},
	},
	{
		.gpio      = 66,		/* MAG IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &mag_irq_config,
			[GPIOMUX_SUSPENDED] = &mag_irq_config,
		},
	},
	{
		.gpio      = 23,		/* SVC LED */
		.settings = {
			[GPIOMUX_ACTIVE] = &rgb_sda_config,
			[GPIOMUX_SUSPENDED] = &rgb_sda_config,
		},
	},
};

/* NFC configurations */

#ifdef CONFIG_SEC_NFC_I2C

static struct gpiomux_setting nfc_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting nfc_ven_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting nfc_irq_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting nfc_firmware_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_nfc_configs[] __initdata = {
	{
		.gpio		= 20,		/* NFC EN */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_ven_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_ven_cfg,
		},
	},
	{
		.gpio		= 21,		/* NFC IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_irq_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_irq_cfg,
		},
	},
	{
		.gpio		= 62,		/* NFC FIRMWARE */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_firmware_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_firmware_cfg,
		},
	},
};

#endif

/* Hall interrupt configuration */
static struct gpiomux_setting hall_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hall_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_hall_configs[] __initdata = {
	{
		.gpio = 50,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hall_active_cfg,
			[GPIOMUX_SUSPENDED] = &hall_suspend_cfg,
		},
	},
};

/* LCD configurations */
static struct gpiomux_setting lcd_rst_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting lcd_rst_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting lcd_power_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting lcd_power_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_lcd_configs[] __initdata = {
		{
		.gpio = 25,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_rst_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_rst_sus_cfg,
		},
	},
	{
		.gpio = 56,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_power_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_power_sus_cfg,
		},
	},
	{
		.gpio = 60,		
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_power_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_power_sus_cfg,
		},
	},
	{
		.gpio = 63,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_power_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_power_sus_cfg,
		},
	}
};
/* UART configurations */
static struct gpiomux_setting gpio_uart_sleep_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_uart_active_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#if defined(CONFIG_TDMB)
static struct gpiomux_setting gpio_spi_qup4_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting spi_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif
static struct msm_gpiomux_config msm_blsp_configs[] __initdata = {
	{
		.gpio      = 0,			/* BLSP1 QUP1 SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 1,			/* BLSP1 QUP1 SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 2,			/* BLSP1 QUP1 SPI_CS1 */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_cs_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 3,			/* BLSP1 QUP1 SPI_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 8,			/* BLSP1 UART2 TX */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_uart_active_config,
			[GPIOMUX_SUSPENDED] = &gpio_uart_sleep_config,
		},
	},
	{
		.gpio      = 9,			/* BLSP1 UART2 RX */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_uart_active_config,
			[GPIOMUX_SUSPENDED] = &gpio_uart_sleep_config,
		},
	},
#ifdef CONFIG_SEC_NFC_I2C
	{	/*  NFC   */
		.gpio      = 10,		/* BLSP1 QUP3 I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &nfc_gpio_i2c_config,
		},
	},
	{
		.gpio      = 11,		/* BLSP1 QUP3 I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &nfc_gpio_i2c_config,
		},
	},
#endif
	{
		.gpio      = 6,			/* BLSP1 QUP2 I2C_SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 7,			/* BLSP1 QUP2 I2C_SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 18,		/* BLSP1 QUP5 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 19,		/* BLSP1 QUP5 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#if defined(CONFIG_TDMB)
	{
		.gpio	   = 12,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_qup4_config,
			[GPIOMUX_SUSPENDED] = &spi_suspend_config,
		},
	},
	{
		.gpio	   = 13,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_qup4_config,
			[GPIOMUX_SUSPENDED] = &spi_suspend_config,
		},
	},
	{
		.gpio	   = 14,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_qup4_config,
			[GPIOMUX_SUSPENDED] = &spi_suspend_config,
		},
	},
	{
		.gpio	   = 15,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_qup4_config,
			[GPIOMUX_SUSPENDED] = &spi_suspend_config,
		},
	},
#endif
};
/* Camera configurations */
static struct gpiomux_setting gpio_suspend_config[] = {
	{
		.func = GPIOMUX_FUNC_GPIO,  /* IN-NP */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_GPIO,  /* O-LOW */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
};

static struct gpiomux_setting cam_settings[] = {
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 0 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 1 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

	{
		.func = GPIOMUX_FUNC_1, /*i2c suspend*/ /* 2 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*active 0*/ /* 3 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend 0*/ /* 4 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_OUT_LOW,
	},
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 5 */
		.drv = GPIOMUX_DRV_4MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 6 */
		.drv = GPIOMUX_DRV_4MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
	{
		.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */ //7 Haarika
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},
	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */ //8
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 9 */
		.drv = GPIOMUX_DRV_6MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 10 */
		.drv = GPIOMUX_DRV_6MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
};

static struct msm_gpiomux_config msm_csensor_configs[] __initdata = {
#if !defined(CONFIG_MACH_MS01_KOR_LTE)
	{
		.gpio = 0, /* CIS_SPI_MOSI */
		.settings = {
			[GPIOMUX_ACTIVE]	= &cam_settings[5],
#if defined(CONFIG_MACH_MS01_EUR_3G)
			[GPIOMUX_SUSPENDED] = &cam_settings[5],
#else
			[GPIOMUX_SUSPENDED] = &cam_settings[8],
#endif
		},
	},
	{
		.gpio = 1, /* CIS_SPI_MISO */
		.settings = {
			[GPIOMUX_ACTIVE]	= &cam_settings[5],
#if defined(CONFIG_MACH_MS01_EUR_3G)
			[GPIOMUX_SUSPENDED] = &cam_settings[5],
#else
			[GPIOMUX_SUSPENDED] = &cam_settings[8],
#endif
		},
	},
	{
		.gpio = 3, /* CIS_SPI_SCLK */
		.settings = {
			[GPIOMUX_ACTIVE]	= &cam_settings[5],
#if defined(CONFIG_MACH_MS01_EUR_3G)
			[GPIOMUX_SUSPENDED] = &cam_settings[5],
#else
			[GPIOMUX_SUSPENDED] = &cam_settings[8],
#endif
		},
	},
#endif
	{
		.gpio = 26, /* CAM_MCLK0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[9],
			[GPIOMUX_SUSPENDED] = &cam_settings[10],
		},
	},
#if defined(CONFIG_MACH_S3VE3G_EUR)
	{
		.gpio = 27, /* CAM_MCLK1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[6],
			[GPIOMUX_SUSPENDED] = &cam_settings[6],
		},

	},
#else
	{
		.gpio = 27, /* CAM_MCLK1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[7],
			[GPIOMUX_SUSPENDED] = &cam_settings[8],
		},

	},
#endif
	{
		.gpio = 29, /* CCI_I2C_SDA0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 30, /* CCI_I2C_SCL0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 37, /* CAM1_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 28, /* CAM2_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 112, /* CAM_ANALOG_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 114, /* CAM_IO_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 34, /* AF_SDA */
		.settings = {
			/*[GPIOMUX_ACTIVE] = &gpio_i2c_config,*/
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
#if defined(CONFIG_MACH_MS01_EUR_3G) || defined(CONFIG_MACH_MS01_EUR_LTE) || defined(CONFIG_MACH_MS01_KOR_LTE)
		.gpio = 33, /* AF_SCL */
#else
		.gpio = 36, /* AF_SCL */
#endif
		.settings = {
			/*[GPIOMUX_ACTIVE] = &gpio_i2c_config,*/
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
};

/* Touch */
static struct gpiomux_setting melfas_int_act_cfg = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting melfas_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#if !defined(CONFIG_MACH_MS01_KOR_LTE)
static struct gpiomux_setting gpio_i2c_tkey_act_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_i2c_tkey_sus_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif
static struct msm_gpiomux_config msm_melfas_configs[] __initdata = {
	{
		.gpio = 17,
		.settings = {
			[GPIOMUX_ACTIVE] = &melfas_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &melfas_int_sus_cfg,
		},
	},
};
#if !defined(CONFIG_MACH_MS01_KOR_LTE)
static struct msm_gpiomux_config msm_keyboad_cypress_configs[] __initdata = {
	{
		.gpio      = 49,		/* 2_TOUCH_INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_tkey_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_tkey_sus_config,
		},
	},
	{
		.gpio      = 66,		/* 2_TOUCH_I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_tkey_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_tkey_sus_config,
		},
	},
	{
		.gpio      = 114,		/* 2_TOUCH_I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_tkey_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_tkey_sus_config,
		},
	},
};
#endif

/* EarJack configurations */
static struct gpiomux_setting earjack_gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting earjack_gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_earjack_gpio_configs[] __initdata = {
	{
		.gpio = 35, /* EAR_SWITCH */
		.settings = {
			[GPIOMUX_ACTIVE]    = &earjack_gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &earjack_gpio_suspend_cfg,
		},
	}
};

static struct gpiomux_setting codec_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting codec_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm_cdc_reset_config[] __initdata = {
	{
		.gpio   = 72,
		.settings = {
			[GPIOMUX_ACTIVE]    = &codec_active_cfg,
			[GPIOMUX_SUSPENDED] = &codec_suspend_cfg,
		},
	}
};

#ifdef CONFIG_MMC_MSM_SDC3_SUPPORT
static struct gpiomux_setting sdc3_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc3_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc3_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc3_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm8226_sdc3_configs[] __initdata = {
	{
		/* DAT3 */
		.gpio      = 39,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT2 */
		.gpio      = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT1 */
		.gpio      = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_data_1_suspend_cfg,
		},
	},
	{
		/* DAT0 */
		.gpio      = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CMD */
		.gpio      = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CLK */
		.gpio      = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
};

static void msm_gpiomux_sdc3_install(void)
{
	msm_gpiomux_install(msm8226_sdc3_configs,
			    ARRAY_SIZE(msm8226_sdc3_configs));
}
#else
static void msm_gpiomux_sdc3_install(void) {}
#endif /* CONFIG_MMC_MSM_SDC3_SUPPORT */

/* TX_GTR_THRESH configurations */
static struct gpiomux_setting tx_gtr_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm8226_tx_gtr_configs[] __initdata = {
	{
		/* TX_GTR_THRESH */
		.gpio      = 87,
		.settings = {
			[GPIOMUX_ACTIVE]    = &tx_gtr_cfg,
			[GPIOMUX_SUSPENDED] = &tx_gtr_cfg,
		},
	},
};

/* MUIC configurations */
static struct gpiomux_setting gpio_muic_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config muic_configs[] __initdata = {
	{
		.gpio      = 4,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_muic_config,
			[GPIOMUX_SUSPENDED] = &gpio_muic_config,
		},
	},
	{
		.gpio      = 5,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_muic_config,
			[GPIOMUX_SUSPENDED] = &gpio_muic_config,
		},
	},
};

/* NC pin configurations */
#define NC_GPIO_CONFIG(gpio_num) { \
		.gpio = gpio_num, \
		.settings = {	\
			[GPIOMUX_ACTIVE] = &nc_active_cfg,	\
			[GPIOMUX_SUSPENDED] = &nc_suspend_cfg, } \
	}

static struct gpiomux_setting nc_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting nc_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hw_chk_bit_gpio_cfg = {
        .func = GPIOMUX_FUNC_GPIO,
        .drv = GPIOMUX_DRV_2MA,
        .pull = GPIOMUX_PULL_NONE,
        .dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config hw_rev_configs[] __initdata = {
#if !defined(CONFIG_TDMB)
        {
                .gpio = 15,     /* HW_REV(0) */
                .settings = {
                        [GPIOMUX_ACTIVE] = &hw_chk_bit_gpio_cfg,
                        [GPIOMUX_SUSPENDED] = &hw_chk_bit_gpio_cfg,
                },
        },
        {
                .gpio = 14,     /* HW_REV(1) */
                .settings = {
                        [GPIOMUX_ACTIVE] = &hw_chk_bit_gpio_cfg,
                        [GPIOMUX_SUSPENDED] = &hw_chk_bit_gpio_cfg,
                },
        },
        {
                .gpio = 13,     /* HW_REV(2) */
                .settings = {
                        [GPIOMUX_ACTIVE] = &hw_chk_bit_gpio_cfg,
                        [GPIOMUX_SUSPENDED] = &hw_chk_bit_gpio_cfg,
                },
        },
        {
                .gpio = 12,      /* HW_REV(3) */
                .settings = {
                        [GPIOMUX_ACTIVE] = &hw_chk_bit_gpio_cfg,
                        [GPIOMUX_SUSPENDED] = &hw_chk_bit_gpio_cfg,
                },
        },
#endif
		{
                .gpio = 22,      /* CHECK_DS_SS */
                .settings = {
                        [GPIOMUX_ACTIVE] = &hw_chk_bit_gpio_cfg,
                        [GPIOMUX_SUSPENDED] = &hw_chk_bit_gpio_cfg,
                },
		},
};

#if defined(CONFIG_MACH_MS01_EUR_LTE) || defined(CONFIG_MACH_MS01_KOR_LTE)
static struct gpiomux_setting nc_cfg = {
        .func = GPIOMUX_FUNC_GPIO,
        .drv = GPIOMUX_DRV_2MA,
        .pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
};
static struct msm_gpiomux_config nc_configs[] __initdata = {
	{
		.gpio = 22,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 23,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 36,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 53,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 54,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 55,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
		.gpio = 67,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
};
#endif

/* BERLUTI 3G NC configs */
static struct msm_gpiomux_config berluti3g_nc_gpio_cfgs[] __initdata = {
#if defined(CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
	NC_GPIO_CONFIG(16),				/* As we will not ESD so ESD pin should be NC */
#endif
	NC_GPIO_CONFIG(24),
	NC_GPIO_CONFIG(53),
	NC_GPIO_CONFIG(54),
	NC_GPIO_CONFIG(55),
#ifndef CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL
	NC_GPIO_CONFIG(60),
#endif
	NC_GPIO_CONFIG(80),
	NC_GPIO_CONFIG(88),
	NC_GPIO_CONFIG(89),
	NC_GPIO_CONFIG(90),
	NC_GPIO_CONFIG(91),
	NC_GPIO_CONFIG(92),
	NC_GPIO_CONFIG(93),
	NC_GPIO_CONFIG(94),
	NC_GPIO_CONFIG(97),
	NC_GPIO_CONFIG(98),
	NC_GPIO_CONFIG(99),
	NC_GPIO_CONFIG(100),
	NC_GPIO_CONFIG(103),
	NC_GPIO_CONFIG(104),
	NC_GPIO_CONFIG(110),
	NC_GPIO_CONFIG(113),
	NC_GPIO_CONFIG(115),
	NC_GPIO_CONFIG(116),
};

void __init msm8226_init_gpiomux(void)
{
	int rc;

	rc = msm_gpiomux_init_dt();
	if (rc) {
		pr_err("%s failed %d\n", __func__, rc);
		return;
	}

	/* Keypad */
	msm_gpiomux_install(msm_keypad_configs,
		ARRAY_SIZE(msm_keypad_configs));

	/* HallSensors */
	msm_gpiomux_install(msm_hall_configs,
		ARRAY_SIZE(msm_hall_configs));

	/* BLSP */
	msm_gpiomux_install(msm_blsp_configs,
		ARRAY_SIZE(msm_blsp_configs));
	/*HW */
	msm_gpiomux_install(hw_rev_configs,
	ARRAY_SIZE(hw_rev_configs));


	/* WCNSS */
	msm_gpiomux_install(wcnss_5wire_interface,
		ARRAY_SIZE(wcnss_5wire_interface));

	/*T_FLASH_DETECT */
	msm_gpiomux_install(&sd_card_det, 1);

	/* TX_GTR */
	msm_gpiomux_install(msm8226_tx_gtr_configs,
		ARRAY_SIZE(msm8226_tx_gtr_configs));

	/* LCD */
	msm_gpiomux_install_nowrite(msm_lcd_configs,
		ARRAY_SIZE(msm_lcd_configs));

	/* Camera */
	msm_gpiomux_install(msm_csensor_configs,
		ARRAY_SIZE(msm_csensor_configs));

	/* Touch */
	msm_gpiomux_install(msm_melfas_configs,
		ARRAY_SIZE(msm_melfas_configs));

#if !defined(CONFIG_MACH_MS01_KOR_LTE)
	/* Touch Key */
	msm_gpiomux_install(msm_keyboad_cypress_configs,
		ARRAY_SIZE(msm_keyboad_cypress_configs));
#endif
#ifdef CONFIG_SEC_NFC_I2C
	/* NFC */
	msm_gpiomux_install(msm_nfc_configs,
		ARRAY_SIZE(msm_nfc_configs));
#endif

	/* Sensors */
	msm_gpiomux_install(msm_sensors_configs,
		ARRAY_SIZE(msm_sensors_configs));

	/* SDCC3 */
	msm_gpiomux_sdc3_install();

	/* Codec */
	msm_gpiomux_install(msm_cdc_reset_config,
		ARRAY_SIZE(msm_cdc_reset_config));

	/* Earjack */
	msm_gpiomux_install(msm_earjack_gpio_configs,
		ARRAY_SIZE(msm_earjack_gpio_configs));

	/* MUIC */
	msm_gpiomux_install(muic_configs,
			ARRAY_SIZE(muic_configs));

	/* NC */
	msm_gpiomux_install(berluti3g_nc_gpio_cfgs, ARRAY_SIZE(berluti3g_nc_gpio_cfgs));
#if defined(CONFIG_MACH_MS01_EUR_LTE) || defined(CONFIG_MACH_MS01_KOR_LTE)
	msm_gpiomux_install(nc_configs, ARRAY_SIZE(nc_configs));
#endif
}
