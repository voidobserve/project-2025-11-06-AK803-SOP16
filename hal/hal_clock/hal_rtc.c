/*************************************************************************
	> File Name: hal_clock.c
	> Author: by ty
	> Mail: 
	> Created Time: Wed 03 Jul 2019 22:10:00 CST
 ************************************************************************/

#include "hal_rtc.h"

//system tick
//#define PHY_SYSTEM_TICK reg_system_tick

//get system tick function
/*
AK801 can only use core timer(@16MHz,24Bit),max 1048ms
1.init core timer at main(),as follows:
	static volatile uint32_t core_timer_count_ms = 0x0;
	core_timer_init(CLOCK_SYS_CLOCK_HZ);//interrupt frequency:1000ms
	core_timer_set_int(ON);//enable core timer int
	core_timer_enable();//enable core timer
	
2.increace core_timer_count_ms at core_timer_isr(),as follows:
	ATTRIBUTE_ISR void core_timer_isr()
	{
		read_reg(CORE_TIMER_CORET_CSR_REG);//read clear
		core_timer_count_ms += 1000;//increace 1000ms
	}
*/
volatile uint32_t core_timer_count_ms;

void hal_rtc_init(void)
{
	core_timer_count_ms = 0;
	
	//config timer
	int_set_priority(IRQN_TICK_TIMER,IRQ_PRI_0);
	core_timer_init(CLOCK_SYS_CLOCK_HZ);
	core_timer_set_int(ON);
	core_timer_enable();
}

void hal_rtc_core_timer_handler()
{
	core_timer_count_ms += 1000;//increace 1000ms
}

uint32_t hal_clock_get_system_tick_rtc(void){
    uint32_t tick_ms;
	tick_ms = core_timer_count_ms+(CLOCK_SYS_CLOCK_HZ - get_core_timer_value())/(CLOCK_SYS_CLOCK_HZ/1000);//core timer is a down counter,ticks to ms

    return tick_ms*HAL_CLOCK_1MS_TICKS;//tick
}

uint32_t hal_clock_time_exceed_rtc(uint32_t *ref, uint32_t span_us)
{
	if((hal_clock_get_system_tick_rtc() - *ref) > span_us*HAL_CLOCK_1US_TICKS)
	{
		*ref=hal_clock_get_system_tick_rtc();
		return true;
	}
	else
	{
		return false;
	}
}
