/****************************************************************************
@FILENAME:	isr.c
@FUNCTION:	isr handler,stong isr function define
@AUTHOR:	flege.zhang
@DATE:		2020.04.18
*****************************************************************************/


#include "app_cfg.h"
#include "ble_adv.h"
#include "timer.h"
#include "timer_mgt.h"
#include "tccr.h"
#include "int.h"
#include "watchdog.h"
#include "uart.h"
#include "rcscan.h"
#include "key_process.h"



#ifndef SYSTEM_NOT_SLEEP
extern volatile uint8_t sys_sleep_enable;
extern volatile uint32_t sys_sleep_count;
#endif


ATTRIBUTE_ISR void tx_isr()
{

}

ATTRIBUTE_ISR void rx_isr()
{
	
}

ATTRIBUTE_ISR void gpio_isr()
{

}

ATTRIBUTE_ISR void timer0_isr()
{
    if(read_reg(TIMER0_INT_STATUS))
    {
        read_reg(TIMER0_EOI);//read clear


    }
}

ATTRIBUTE_ISR void timer1_isr()
{
    if(read_reg(TIMER1_INT_STATUS))
    {
        read_reg(TIMER1_EOI);//read clear
		//ble_adv_start();
    }
}

ATTRIBUTE_ISR void timer2_isr()
{
    if(read_reg(TIMER2_INT_STATUS))
    {
        read_reg(TIMER2_EOI);//read clear
    }
}

ATTRIBUTE_ISR void core_timer_isr()
{
    read_reg(CORE_TIMER_CORET_CSR_REG);//read clear
	hal_rtc_core_timer_handler();
}

ATTRIBUTE_ISR void tccr_isr()
{
    /*
    __      ______
      |     |     |
      |_____|     |_________________________
      A     B     A       C
      A:irq,tccr timer reload,record current timer count as TCCR_CC1C_ADDR
      B:tccr record current timer count as TCCR_CC0C_ADDR
      C:irq, tccr timeout
    */
}

ATTRIBUTE_ISR void lvd_isr()
{

}

ATTRIBUTE_ISR void wdt_isr()
{
    if(read_reg(WATCHDOG_STATE_REG))
    {
        wdg_int_clear();
        wdg_feed_dog();
    }
}

ATTRIBUTE_ISR void uart_isr()
{
}

