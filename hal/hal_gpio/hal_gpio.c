/****************************************************************************
@FILENAME:	hal_gpio.h
@FUNCTION:	the gpio config
@AUTHOR:	flege.zhang
@DATE:		2019.09.03
@COPYRIGHT(C) ZXW 2020
*****************************************************************************/

#include "hal_gpio.h"
#include "sys.h"
#include "int.h"

void hal_gpio_set_port(uint32_t port, gpio_dir_t direct, uint8_t hight_low)
{
	// validation check
	if (port > 19)
	{
		return;
	}

	if (direct == GPIO_OUTPUT)
	{
		sys_set_port_mux(PAD_MUX_BASE_ADDR + (port << 2), (PAD_MUX_FUNCTION_0 | 0x03)); // BIT[1]:output loopback;BIT[0]:pull,0:enable,1:disable
	}
	else
	{
		sys_set_port_mux(PAD_MUX_BASE_ADDR + (port << 2), (PAD_MUX_FUNCTION_0 | 0x02)); // BIT[1]:output loopback;BIT[0]:pull,0:enable,1:disable
	}

	gpio_set_bit_direction(1 << port, direct);

	if (direct == GPIO_OUTPUT)
	{
		gpio_set_bit(1 << port, hight_low);
	}
}

void hal_gpios_set(uint32_t bits, gpio_dir_t direct, uint8_t hight_low)
{
	for (uint8_t i = 0; i < 20; i++)
	{
		if (bits & (1 << i))
		{
			hal_gpio_set_port(i, direct, hight_low);
		}
	}
}

void hal_gpio_init()
{
	sys_set_module_clock(CLK_GPIO_EN_MASK, ON);
}

void hal_gpio_cfg_before_sleep(uint32_t reg_bits)
{
	// need define not used io(except wakeup io)

	// disable all int,avoid being interrupted.
	int_disable_irq(INT_ALL_EN_MASK);

	// set all io(except wakeup used io) as output
	for (uint8_t i = 0; i < 11; i++)
	{
		if (reg_bits & (0x1 << i))
		{
			if (i != SINGLE_LED_GPIO_INDEX)
				sys_set_port_mux(PAD_MUX_BASE_ADDR + (i << 2), PAD_MUX_FUNCTION_7 | 1);
		}
	}
	hal_gpio_set_port(SINGLE_LED_GPIO_INDEX, GPIO_OUTPUT, 0x0);

	// set as debug io,output 0
	write_reg(0x40120194, 11);
	write_reg(0x40020078, 22);
}
