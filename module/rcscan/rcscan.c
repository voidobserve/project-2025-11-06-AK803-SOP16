/****************************************************************************
@FILENAME:	rcscan.c
@FUNCTION:	key scan
@AUTHOR:	flege.zhang
@DATE:		2020.05.04
*****************************************************************************/

#include "rcscan.h"
#include "sys.h"
#include "key_process.h"
#include "ble_packet_send.h"

extern str_retention_memory ret_mem_data;

#if ((PRODUCT_SELECTION & RCSCAN) == RCSCAN)
extern str_key_info key_info;

uint8_t get_bits_num(uint32_t bits)
{
	uint8_t bits_num = 0x0;

	for (uint8_t i = 0; i < 21; i++)
	{
		if (bits & (1 << i))
		{
			bits_num++;
		}
	}

	return bits_num;
}

uint8_t get_bit_position(uint32_t bits, uint8_t index)
{
	uint8_t position = 0x0;
	uint32_t bits_temp = bits;

	// GPIO0 could not be detected previously,by huangjun
	// from GPIO20 - GPIO00
	for (signed char i = 20; i >= 0; i--)
	{
		if (bits_temp & (1 << i))
		{
			if ((position++) == index)
			{
				return i;
			}
		}
	}

	return 31;
}

void rcscan_init()
{
	memset(&key_info, 0x0, sizeof(str_key_info));
}

uint32_t rcscan_scan()
{
	uint32_t scaned_key = 0x0;
	uint32_t port_value;
	uint32_t input_io_pressed;
	uint8_t input_io_pressed_num;
	uint8_t output_io_num = get_bits_num(OTPUT_GPIO_BITS);
	uint8_t input_bit_index, output_bit_index;
	uint8_t is_gnd_pressed;

	/********************************************************/
	/*[performance]*/
	/*[with  print]:preesed 3KEY,6 io,spend 2.040ms*/
	/*[none  print]:preesed 3KEY,6 io,spend 440us*/
	/********************************************************/

	/*init io*/
	// set INPUT_GPIO_BITS io as input
	hal_gpios_set(INPUT_GPIO_BITS, GPIO_INPUT, GPIO_LOW);
	// set OTPUT_GPIO_BITS io as output,and output low
	hal_gpios_set(OTPUT_GPIO_BITS, GPIO_OUTPUT, GPIO_LOW);

	// get input io state,if input io has been pressed,with the following processing,the pressed io will be set as 1
	input_io_pressed = ((~INPUT_GPIO_BITS) | read_reg(GPIO_DATA_REG)) ^ 0xFFFFFFFF;

	/*check pressed?*/
	if (input_io_pressed)
	{
		/*go here,means that key has been pressed!*/

		/*scan who has been pressed?*/

		// get pressed input io number
		input_io_pressed_num = get_bits_num(input_io_pressed);

		for (uint8_t i = 0; i < input_io_pressed_num; i++)
		{
			// get the pressed input bit index
			input_bit_index = get_bit_position(input_io_pressed, i);
			for (uint8_t j = 0; j < output_io_num; j++)
			{

				hal_gpios_set(OTPUT_GPIO_BITS, GPIO_OUTPUT, GPIO_HIGH);

				/*set the one io as OUTPUT low,number from left of bin,index from 0*/
				output_bit_index = get_bit_position(OTPUT_GPIO_BITS, j);
				if ((1 << output_bit_index) != GNDB)
				{
					hal_gpio_set_port(output_bit_index, GPIO_OUTPUT, GPIO_LOW);
					/*read input io,and check it's 0?*/
					if (!(read_reg(GPIO_DATA_REG) & (1 << input_bit_index)))
					{
						scaned_key |= ((1 << input_bit_index) | (1 << output_bit_index));
						break; // 直接跳出本次循环层
					}
					hal_gpio_set_port(output_bit_index, GPIO_OUTPUT, GPIO_HIGH);
				}
				else
				{
					// set other OUTPUT io as output high
					hal_gpios_set(OTPUT_GPIO_BITS, GPIO_OUTPUT, GPIO_HIGH);
					if (!(read_reg(GPIO_DATA_REG) & (1 << input_bit_index)))
					{
						scaned_key |= ((1 << input_bit_index) | GNDB);
						break; // 直接跳出本次循环层
					}
				}
			}
		}
	}

scaned_key_label:

	key_info.curr_key = scaned_key; // 存放当前的键值
	
	/* 
		如果是有效的按键键值，并且当前键值与上一次的键值相等，
		说明按键按下且未松手（可能是短按，也可能是长按）
	*/
	if (scaned_key && (key_info.curr_key == key_info.last_key)) 
	{
		key_info.pressed_time += TIMER1_IRQ_INTERVAL; // 累加按下的时间
		key_info.handle_flag = 0x01; // 给标志位置一，表示需要处理按键事件

#if LOG_SECONDARY
		print("K:%x,T:%d\n", scaned_key, key_info.pressed_time);
#endif
	}
	else
	{
		// 如果不是有效键值或当前键值与上一次的键值相等，说明按键松开
		key_info.pressed_time = 0x0; // 清空按键按下的时间计数
		// power off led
		hal_gpio_set_port(SINGLE_LED_GPIO_INDEX, GPIO_OUTPUT, 0x0); // 熄灭LED灯
	}

	key_info.last_key = scaned_key; // 存放上一次的键值

	return scaned_key;// 返回扫描到的键值
#endif

	return 0;
}

