/* ---------------------------------------------------------------
** File name:		tccr.c
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
**  2020-12-18  2.0         Modified
** ---------------------------------------------------------------
*/


/* Includes -----------------------------------------------------*/
#include "config.h"
#include "type.h"
#include "sys.h"
#include "tccr.h"
#include "int.h"
#include "gpio.h"
/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/
#ifdef MODULE_TEST
//uint8_t timer_test_flag =0;
uint8_t test_tccr_flag =0;
volatile uint32_t check_tccr_count =0;
#endif
/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/

void tccr_set_mode(tccr_mode_type_t mode)
{
    uint32_t reg =read_reg(TCCR_EN_ADDR);
    reg &= 0xC3;
    switch (mode)
    {
        case TCCR_AS_TIMER:
        {
            reg |=TIMER_CLK_SEL_NORMAL|TIMER_RELOAD_SEL_AUTO;
            break;
        }
        case TCCR_EVENT_MODE:
        {
            reg |=TIMER_CLK_SEL_ADD_FALL_EGD|TIMER_RELOAD_SEL_AUTO|TCCR_EX_RELOAD_EN_ENABLE;
            break;
        }
        case TCCR_PULSE_WIDTH_MEASUREMENT:
        {
            reg |=TIMER_CLK_SEL_ADD_HIGH|TIMER_RELOAD_SEL_FALL_EDG|TCCR_EX_RELOAD_EN_ENABLE;
            break;
        }

        case TCCR_CAPTURE_MODE:
        {
            reg |=TIMER_CLK_SEL_NORMAL|TIMER_RELOAD_SEL_FALL_EDG|TCCR_EX_RELOAD_EN_ENABLE;
            break;
        }
        default:
        {
            break;
        }
    }
    write_reg(TCCR_EN_ADDR, reg);
}

void tccr_set_irq_type(tccr_irq_type_t tccr_int)
{
    uint32_t reg =0;
    reg =read_reg(TCCR_INT_EN_ADDR);
    reg &= 0xFC;
    reg |=tccr_int;
	write_reg(TCCR_INT_EN_ADDR,reg);
}
void tccr_set_port(tccr_port_t port)
{
    if(TCCR_PORT_0 == port)
    {
        sys_set_port_mux(PAD_GPIO_06,PAD_MUX_FUNCTION_5 | 2);

    }
    else if(TCCR_PORT_1 == port)
    {
        sys_set_port_mux(PAD_GPIO_07,PAD_MUX_FUNCTION_3 | 2);

    }
    else if(TCCR_PORT_2 == port)
    {
        sys_set_port_mux(PAD_GPIO_08,PAD_MUX_FUNCTION_5 | 2);

    }
    else if(TCCR_PORT_3 == port)
    {
        sys_set_port_mux(PAD_GPIO_10,PAD_MUX_FUNCTION_1 | 2);

    }

}

void tccr_enable(void)
{
    uint32_t reg =0;
    reg = read_reg(TCCR_EN_ADDR);
    reg |=TCCR_EN_ENABLE;
    write_reg(TCCR_EN_ADDR,reg);
}

void tccr_disable(void)
{
    uint32_t reg =0;
    reg = read_reg(TCCR_EN_ADDR);
    reg |= ~TCCR_EN_ENABLE;
    reg |=TCCR_EN_DISABLE;
    write_reg(TCCR_EN_ADDR,reg);

}

uint32_t get_tccr_reload_count(void)
{
    uint32_t reg_val =0;
    reg_val =read_reg(TCCR_TIMER_RELOAD_ADDR);
    return (0xFFFFFF&reg_val);
}


void tccr_int_mask(void)
{
    write_reg(TCCR_INT_MASK_ADDR, 0x1);
}

void tccr_int_unmask(void)
{
    write_reg(TCCR_INT_MASK_ADDR, 0x0);
}

void tccr_init(uint32_t check_count,enum en_tccr_int_type enable_int_type)
{
    uint32_t reg_val;

    //tccr clock enable
    reg_val = read_reg(TOP_CLK_CTRL_REG);
    reg_val |= CLK_TCCR_EN_MASK;
    write_reg(TOP_CLK_CTRL_REG, reg_val);
	
	write_reg(TCCR_EN_ADDR, 0x00);//disable tccr first

    //config pad mux as tccr function
    sys_set_port_mux(PAD_GPIO_07, PAD_MUX_FUNCTION_3 | 0x02);

    //timer reload
    write_reg(TCCR_TIMER_RELOAD_ADDR, check_count);//from 0 -> 0xFFFFFF,clk/2
    //When the TCCR is initialized, software force loads the RELOAD value
    write_reg(TCCR_EN_ADDR,TIMER_RELOAD_SEL_SOFT); 

    //tccr enable
    write_reg(TCCR_EN_ADDR, (TIMER_CLK_SEL_NORMAL | TIMER_RELOAD_SEL_FALL_EDG | TCCR_EX_RELOAD_EN_ENABLE | TCCR_EN_ENABLE));

    //int enable
    write_reg(TCCR_INT_EN_ADDR,enable_int_type);

    //int mask
    write_reg(TCCR_INT_MASK_ADDR, 0x0);

    //enable mcu gloabl irq
    int_enable_irq(INT_TCCR_EN_MASK);//priority default is max(0x0)
    int_set_priority(IRQN_TCCR,IRQ_PRI_0);
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void tccr_isr()
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

	 uint32_t reg_val;
	
#ifdef MODULE_TEST
    uint32_t tccr_count0 = 0x0;
    uint32_t tccr_count1 = 0x0;

    //read irq status
    reg_val = read_reg(TCCR_INT_STATUS_ADDR);

    //clear tccr all int
    write_reg(TCCR_INT_CLEAR_ADDR, 0x03);

    //clear cpu irq status
    write_reg(INT_VIC_IABR_REG, 0x0);//clear all,need check!!!

    if((reg_val & 0x2) == 0x02) //tccr timeout irq
    {
        //this means, there is no ac,need sleep
    }

    if((reg_val & 0x1) == 0x01) //negedge irq
    {
        tccr_count0 = read_reg(TCCR_CC0C_ADDR);
        tccr_count1 = read_reg(TCCR_CC1C_ADDR);

        tccr_count1 = tccr_count1 - tccr_count0;//high time count
        tccr_count0 = tccr_count0 - get_tccr_reload_count();//CHECK_AC_TIMEOUT;//low time count


        if(0 == test_tccr_flag)
        {
            print("high time count:%d \n",tccr_count1);
            print("low time count:%d \n",tccr_count0);
            print("Freq :%d \n",(6000000/(tccr_count1 + tccr_count0 + 1)));
            print("Duty :%d \n",(tccr_count1*100/(tccr_count1+1+tccr_count0)));

            test_tccr_flag = 1;
        }
    }
#else
    //read irq status
    reg_val = read_reg(TCCR_INT_STATUS_ADDR);

    //clear tccr all int
    write_reg(TCCR_INT_CLEAR_ADDR, 0x03);

    //clear cpu irq status
    write_reg(INT_VIC_IABR_REG, 0x0);//clear all,need check!!!

    if((reg_val & 0x2) == 0x02)//tccr timeout irq
    {

    }
#endif
}

