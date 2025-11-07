/*************************************************************************
	> File Name: hal_clock.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Jul 2019 22:09:57 CST
 ************************************************************************/

#ifndef _HAL_CLOCK_H
#define _HAL_CLOCK_H

#include "sys.h"
#include "timer.h"
#include "int.h"

#define CLOCK_SYS_CLOCK_HZ 12000000//12MHz

#define HAL_CLOCK_HZ CLOCK_SYS_CLOCK_HZ

enum{
    //how much 1us = ? ticks
    HAL_CLOCK_1S_TICKS = HAL_CLOCK_HZ,
    HAL_CLOCK_1MS_TICKS = (HAL_CLOCK_1S_TICKS / 1000),
    HAL_CLOCK_1US_TICKS = (HAL_CLOCK_1MS_TICKS / 1000),
};
//#define HAL_CLOCK_1US_TICKS  (0.001)
void hal_rtc_init(void);
void hal_rtc_core_timer_handler(void);

uint32_t hal_clock_get_system_tick_rtc(void);
uint32_t hal_clock_time_exceed_rtc(uint32_t *ref, uint32_t span_us);


#endif

