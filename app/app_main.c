/* ---------------------------------------------------------------
** File name:		main.c
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
** Module Information:
**
** Revision History ----------------------------------------------
** ---------------------------------------------------------------
**  Date        Version     Action                  Author
** ---------------------------------------------------------------
**  2019-5-17   1.0         Created
**
** ---------------------------------------------------------------
*/

/* Includes -----------------------------------------------------*/
#include "type.h"
#include "sys.h"
#include "int.h"
#include "lvd.h"
#include "tccr.h"
#include "timer.h"
#include "delay.h"
#include "timer_mgt.h"
#include "wakeup_timer.h"
#include "rf.h"
#include "uart.h"
#include "rcscan.h"
#include "key_process.h"
#include "stdlib.h"
// #include "gpadc.h"
#if (SYS_CRASH_WTD_RESET_ENABLE)
#include "watchdog.h"
#endif
#include "hal_rtc.h"
#include "ble_adv.h"

/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/

/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/

/*
 1. Global variables stored from RAM start address.
 2. Local variables stored from stack top.
*/

#ifndef SYSTEM_NOT_SLEEP
volatile uint8_t sys_sleep_enable = 0x0;
volatile uint32_t sys_sleep_count = 0x0;
#endif

extern str_retention_memory ret_mem_data;
extern str_key_info key_info;

uint32_t rtc_rcscan_t = 0;
uint32_t rtc_adv_start_t = 0;
uint32_t rtc_sys_sleep_t = 0;

#ifndef SYSTEM_NOT_SLEEP
void sys_reset_state_check()
{
	// read sys reset cause
	uint32_t reg_value = read_reg(WAKEUP_SOURE_STATE);
	uint8_t *p_retmem = (uint8_t *)&ret_mem_data;

	// reset by wakeup timer
	if (reg_value == WAKEUP_BY_WUT)
	{
		// get saved state by word from retention memory
		for (uint8_t i = 0; i < 16; i++)
		{
			p_retmem[i] = *((volatile uint32_t *)(RETENTION_MEMEORY_ADDR + (i << 2)));
		}

#if LOG_MAJOR
		print("RESET WT\n");
#endif
	}
	// first power on
	else if (reg_value == WAKEUP_BY_FPO)
	{
		memset(p_retmem, 0x0, RETENTION_MEMEORY_SIZE);
		ret_mem_data.current_group_index = 0x01; // default group index is 0x01,master using 0x00

#if LOG_MAJOR
		print("RESET 1ST\n");
#endif
	}

#if LOG_SECONDARY
	// log out reterntion memory by byte
	uint8_t *p_u8retmem = (uint8_t *)&ret_mem_data;
	print("RETMEM:");
	for (uint8_t i = 0; i < 16; i++)
	{
		print("%x ", p_u8retmem[i]);
	}
	print("\r\n");
#endif
}
#endif

void main(void)
{
	// init sys
	sys_init();
	sys_set_clock(CPU_CLOCK_24M);
	// sys_set_clock(CPU_CLOCK_12M);

	// init io
	hal_gpio_init(); // 打开GPIO时钟
	// hal_gpio_set_port(SINGLE_LED_GPIO_INDEX,GPIO_OUTPUT, GPIO_HIGH); // 不能设置为高电平，在不按遥控器时，灯会一直闪

	// init rtc
	hal_rtc_init();

	// config unsleep
	write_reg(TOP_POWER_CTRL_REG, 0x00);
	// off wakeup timer
	wakeup_timer_disable();
	wt_int_clear();

#if (SYS_CRASH_WTD_RESET_ENABLE)
	// init watch dog
	wdg_int_clear();
	wdg_feed_dog();
	watchdog_init(WATCH_DOG_RESET_TIME);
#endif

#if (LOG_ENABLE)
	uart_init(UART_BAUDRATE_115200);
	uart_set_port(UART_PORT_TX1RX1);
#endif

#ifndef SYSTEM_NOT_SLEEP
	sys_reset_state_check();
#endif

	// lvd_init();
	// lvd_threshold_set(LVD_THR_3);
	{ // 关闭LVD模块
		uint32_t reg_val = 0;
		reg_val = read_reg(MODULE_MODE_REG);
		// reg_val |= LVD_EN;
		reg_val &= ~(0x01 << 5);
		write_reg(MODULE_MODE_REG, reg_val);
	}

	key_process_init(); //

	// peripherals enable
#if ((PRODUCT_SELECTION & RCSCAN) == RCSCAN)
	rcscan_init();
#endif

	// init rf
	rf_init();
#if LOG_MAJOR
	print("system up!\r\n");
#endif

	while (1)
	{
		// generate rand seed!!don't delete it!!
		ret_mem_data.rand_seed += rand();
#if (SYS_CRASH_WTD_RESET_ENABLE)
		wdg_feed_dog();
#endif

		// 5ms 扫描一次按键
		if (hal_clock_time_exceed_rtc(&rtc_rcscan_t, 5000))
		{
			rcscan_scan(); //
		}

		if (key_info.handle_flag)
		{
			key_info.handle_flag = 0x0; // avoid reentry

#ifndef SYSTEM_NOT_SLEEP
			sys_sleep_enable = 0;
			sys_sleep_count = 0;
#endif
			key_process(key_info.curr_key, key_info.pressed_time);
		}

		// 5ms 扫描一次广播发送
		if (hal_clock_time_exceed_rtc(&rtc_adv_start_t, 5000))
		// if (hal_clock_time_exceed_rtc(&rtc_adv_start_t, 10000)) // 10 ms扫描一次广播发送
		{
			ble_adv_start();

			// ble_packet_send(); // 准备数据包
			// ble_adv_start();   // 打开对应的模块，发送数据包
		}

#ifndef SYSTEM_NOT_SLEEP
		// 5ms累计一次休眠倒计时
		if (hal_clock_time_exceed_rtc(&rtc_sys_sleep_t, 5000))
		{
			sys_sleep_count += TIMER0_IRQ_INTERVAL;

			if (sys_sleep_count >= SYS_SLEEP_TIME_MS)
			{
				sys_sleep_enable = 1;
			}
		}

		/*sleep when conditions are met*/
		if (sys_sleep_enable)
		{
			sys_sleep_count = 0;
			sys_sleep_enable = 0;
#if LOG_MAJOR
			print("enter sleep\r\n");
#endif
			// config not wakeup io as output low,for power saving
			hal_gpio_cfg_before_sleep(UNUSED_IO);

			// RETENTION_MEMEORY_ADDR 地址是不连续，偏移地址为0x4N，且必须以字节方式操作
			uint8_t *p_retmem = (uint8_t *)&ret_mem_data;
			for (uint8_t i = 0; i < 16; i++)
			{
				*((volatile uint32_t *)(RETENTION_MEMEORY_ADDR + (i << 2))) = p_retmem[i];
			}

			// 配置唤醒引脚
			wakeup_timer_init(WAKEUP_IO, 0x1, 0x0, 0x1);

#if (SYS_CRASH_WTD_RESET_ENABLE)
			// disable wtd
			wdg_int_clear();
			wdg_feed_dog();
			watchdog_disable();
#endif

			// hal_gpio_set_port(SINGLE_LED_GPIO_INDEX,GPIO_INPUT, 0); // 输入上拉
			// 配置LED端口为输入下拉
			sys_set_port_mux(PAD_MUX_BASE_ADDR + (SINGLE_LED_GPIO_INDEX << 2), (PAD_MUX_FUNCTION_0 | 0x01)); // 功能--作为GPIO，使能下拉，禁止上拉
			gpio_set_bit_direction(1 << SINGLE_LED_GPIO_INDEX, GPIO_INPUT);									 // 输入模式

			// 进入休眠，唤醒是重新跑main函数的
			sys_sleep_down();

			// 必须要延时10ms
			delay_ms(10);

			// init io
			hal_gpio_init(); // 打开GPIO时钟
			// hal_gpio_set_port(SINGLE_LED_GPIO_INDEX,GPIO_OUTPUT, GPIO_HIGH); // 不能设置为高电平，在不按遥控器时，灯会一直闪

			// init rtc
			hal_rtc_init();

			// config unsleep
			write_reg(TOP_POWER_CTRL_REG, 0x00);
			// off wakeup timer
			wakeup_timer_disable();
			wt_int_clear();

#if (SYS_CRASH_WTD_RESET_ENABLE)
			// init watch dog
			wdg_int_clear();
			wdg_feed_dog();
			watchdog_init(WATCH_DOG_RESET_TIME);
#endif

#if LOG_ERROR
			print("unsleep\n");
#endif
		}
#endif
	}
}
