/****************************************************************************
@FILENAME:	key_process.c
@FUNCTION:	key process
@AUTHOR:	flege.zhang
@DATE:		2020.05.04
*****************************************************************************/
#include "key_process.h"
#include "rcscan.h"
#include "delay.h"

str_key_info key_info;
extern const str_key_fun keys_func_table[];
extern str_retention_memory ret_mem_data;

void key_process_init()
{
	memset(&key_info, 0x0, sizeof(str_key_info));
	ble_packet_init();
}

void key_process(uint32_t key_value, uint32_t press_time)
{
	str_key_fun *p_key_fun;
	for (uint8_t i = 0; i < KEYS_FUNCTION_NUM; ++i)
	{
		if (key_value == keys_func_table[i].key_value)
		{
			p_key_fun = (str_key_fun *)&keys_func_table[i];

			if (press_time >= p_key_fun->stop_press_threshold)
			{
				// 如果到了长按的截止时间，关闭LED，表示不发送信号
				hal_gpio_set_port(SINGLE_LED_GPIO_INDEX, GPIO_OUTPUT, 0x0);
				return;
			}
			else if (press_time >= p_key_fun->long_press_threshold)
			{
				// check whether continuous transmission is required
				if (p_key_fun->pack_adv_interval)
				{
					// pack packet only when it's pack interval
					if (0x00 == ((press_time - p_key_fun->long_press_threshold) % p_key_fun->pack_adv_interval))
					{
						// 调用长按对应的函数
						p_key_fun->long_press_handler((str_fun_para *)&p_key_fun->long_press_para);
					}
					else
					{
						return;
					}
				}
				else
				{
					// only pack one times
					if (press_time == p_key_fun->long_press_threshold)
					{
						// 调用长按对应的函数
						p_key_fun->long_press_handler((str_fun_para *)&p_key_fun->long_press_para);
						ret_mem_data.tx_count++;
					}
				}

				// 调用短按对应的函数
				p_key_fun->short_press_handler((str_fun_para *)&p_key_fun->short_press_para);
				goto send_adv_label; // 每次检测到HOLD，发送数据包
			}
			else if (press_time == p_key_fun->short_press_threshold)
			{
				// 短按
				// 将键值写入

				// 调用短按对应的函数
				p_key_fun->short_press_handler((str_fun_para *)&p_key_fun->short_press_para);
				ret_mem_data.tx_count++;
				goto send_adv_label; // 短按松手后，发送数据包
			}
			else
			{
				// do nothing
				return;
			}
		}
	}
	
	return;
send_adv_label:
	ble_packet_send(); // 发送数据包
}
