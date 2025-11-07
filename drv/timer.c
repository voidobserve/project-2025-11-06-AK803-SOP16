/* ---------------------------------------------------------------
** File name:		timer.c
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
#include "config.h"
#include "timer.h"
#include "sys.h"
#include "int.h"
#include "gpio.h"
/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/
#ifdef MODULE_TEST
uint8_t test_timer0_int_flag = 0;
uint8_t test_timer1_int_flag = 0;
uint8_t test_timer2_int_flag = 0;
uint8_t test_tick_timer_int_flag = 0;
#endif

/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/

void timer_clk_config(uint8_t timer, uint8_t clk_sel)
{
	uint32_t reg_val =0;

	reg_val =read_reg(TIMER_CLK_SEL);

#if 1
	reg_val &= ~(TOP_TIMER1_CLK_SEL_MASK<<(timer<<1));
    reg_val |= clk_sel << (timer<<1);
#else
	switch( timer )
	{
        case TIMER0:
            reg_val &= ~TOP_TIMER1_CLK_SEL_MASK;
            reg_val |= clk_sel << TOP_TIMER1_CLK_SEL_SHIFT;
        break;

        case TIMER1:
            reg_val &= ~TOP_TIMER2_CLK_SEL_MASK;
            reg_val |= clk_sel << TOP_TIMER2_CLK_SEL_SHIFT;
        break;

        case TIMER2:
            reg_val &= ~TOP_TIMER3_CLK_SEL_MASK;
            reg_val |= clk_sel << TOP_TIMER3_CLK_SEL_SHIFT;
        break;

        default:
        break;
	}
#endif

	write_reg(TIMER_CLK_SEL,reg_val);
}


void timerN_LoadCount(uint8_t timer_sel,uint32_t timer_load_count)
{
    switch (timer_sel)
    {
        case TIMER0:
        {
            write_reg(TIMER0_LOAD_COUNT_ADDR, timer_load_count);
            break;
        }
        case TIMER1:
        {
            write_reg(TIMER2_LOAD_COUNT_ADDR, timer_load_count);

            break;
        }
        case TIMER2:
        {
            write_reg(TIMER2_LOAD_COUNT_ADDR, timer_load_count);

            break;
        }
        default:
        {
            break;
        }
    }
}

void timer0_enable(void)
{
    uint32_t reg = read_reg(TIMER0_CONTROL_REG);
    reg |= TIMER_ON_ENABLE;
    write_reg(TIMER0_CONTROL_REG, reg);
}
void timer0_disable(void)
{
    uint32_t reg = read_reg(TIMER0_CONTROL_REG);
    reg &= ~TIMER_ON_ENABLE;
    write_reg(TIMER0_CONTROL_REG, reg);

}
void timer0_mask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER0_CONTROL_REG );
    reg |= TIMER_INT_MASK_ENABLE;

    write_reg( TIMER0_CONTROL_REG, reg );
}
void timer0_unmask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER0_CONTROL_REG );
    reg &= ~TIMER_INT_MASK_ENABLE;

    write_reg( TIMER0_CONTROL_REG, reg );
}

void timer1_enable(void)
{
    uint32_t reg = read_reg(TIMER1_CONTROL_REG);
    reg |= TIMER_ON_ENABLE;
    write_reg(TIMER1_CONTROL_REG, reg);
}
void timer1_disable(void)
{
    uint32_t reg = read_reg(TIMER1_CONTROL_REG);
    reg &= ~TIMER_ON_ENABLE;
    write_reg(TIMER1_CONTROL_REG, reg);

}
void timer1_mask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER1_CONTROL_REG );
    reg |= TIMER_INT_MASK_ENABLE;

    write_reg( TIMER1_CONTROL_REG, reg );
}
void timer1_unmask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER1_CONTROL_REG );
    reg &= ~TIMER_INT_MASK_ENABLE;

    write_reg( TIMER1_CONTROL_REG, reg );
}

void timer2_enable(void)
{
    uint32_t reg = read_reg(TIMER2_CONTROL_REG);
    reg |= TIMER_ON_ENABLE;
    write_reg(TIMER2_CONTROL_REG, reg);
}
void timer2_disable(void)
{
    uint32_t reg = read_reg(TIMER2_CONTROL_REG);
    reg &= ~TIMER_ON_ENABLE;
    write_reg(TIMER2_CONTROL_REG, reg);
}
void timer2_mask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER2_CONTROL_REG );
    reg |= TIMER_INT_MASK_ENABLE;

    write_reg( TIMER2_CONTROL_REG, reg );
}
void timer2_unmask_irq(void)
{
    uint32_t    reg = 0;

    reg = read_reg( TIMER2_CONTROL_REG );
    reg &= ~TIMER_INT_MASK_ENABLE;

    write_reg( TIMER2_CONTROL_REG, reg );
}

void timer0_clear_int(void)
{
    read_reg(TIMER0_EOI);
}
void timer1_clear_int(void)
{
    read_reg(TIMER1_EOI);
}
void timer2_clear_int(void)
{
    read_reg(TIMER2_EOI);
}

/**
 * @brief 
 * 
 * @param  clk_sel timer_clock_e
 * @param timer_load_count 
 */
void timer0_init(uint8_t clk_sel,uint32_t timer_load_count)
{
	timer_clk_config(TIMER0, clk_sel);
    sys_set_module_clock(CLK_TIMER0, ON); 
    write_reg(TIMER0_LOAD_COUNT_ADDR, timer_load_count);
    write_reg(TIMER0_CONTROL_REG, TIMER_EN_ENABLE|EX_RELOAD_EN_ENABLE | TIMER_INT_MASK_DISABLE);
    read_reg(TIMER0_EOI);
    int_enable_irq(INT_TIM0_EN_MASK);
}

void timer1_init(uint8_t clk_sel,uint32_t timer_load_count)
{
	timer_clk_config(TIMER1, clk_sel);
    sys_set_module_clock(CLK_TIMER1, ON);
    write_reg(TIMER1_LOAD_COUNT_ADDR, timer_load_count);
    write_reg(TIMER1_CONTROL_REG, TIMER_EN_ENABLE|EX_RELOAD_EN_ENABLE | TIMER_INT_MASK_DISABLE);
    read_reg(TIMER1_EOI);
    int_enable_irq(INT_TIM1_EN_MASK);
}
void timer2_init(uint8_t clk_sel,uint32_t timer_load_count)
{
	timer_clk_config(TIMER2, clk_sel);
    sys_set_module_clock(CLK_TIMER2, ON); 
    write_reg(TIMER2_LOAD_COUNT_ADDR, timer_load_count);
    write_reg(TIMER2_CONTROL_REG, TIMER_EN_ENABLE|EX_RELOAD_EN_ENABLE | TIMER_INT_MASK_DISABLE);
    read_reg(TIMER2_EOI);
    int_enable_irq(INT_TIM2_EN_MASK);

}

void core_timer_init(uint32_t timer_load_count)
{
    write_reg(CORE_TIMER_CORET_RVR_REG, timer_load_count);
    write_reg(CORE_TIMER_CORET_CVR_REG, 0); 
}

void core_timer_set_int(BOOL on_off)
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( CORE_TIMER_CORET_CSR_REG );

    if ( ON == on_off )
    {
        reg_val |= 2;
    }
    else
    {
        reg_val &= ~2;
    }
    write_reg(CORE_TIMER_CORET_CSR_REG, reg_val);

    int_enable_irq(INT_TICK_TIMER_EN_MASK);
}

void core_timer_enable()
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( CORE_TIMER_CORET_CSR_REG );
    reg_val |= 1;
    write_reg(CORE_TIMER_CORET_CSR_REG, reg_val);
}

void core_timer_disable()
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( CORE_TIMER_CORET_CSR_REG );
    reg_val &= ~1;
    write_reg(CORE_TIMER_CORET_CSR_REG, reg_val);
}

uint32_t    get_core_timer_value()
{
    return read_reg( CORE_TIMER_CORET_CVR_REG );
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void timer0_isr()
{
    if(read_reg(TIMER0_INT_STATUS))
    {
        read_reg(TIMER0_EOI);//read clear

#ifdef MODULE_TEST
        if(test_timer0_int_flag)
        {
            gpio_set_bit(BIT0, 0x1);
            test_timer0_int_flag = 0;
        }
        else
        {

            gpio_set_bit(BIT0, 0x0);
            test_timer0_int_flag = 1;
        }
#else
		//DO SOMETHING
#endif
    }

}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void timer1_isr()
{
    if(read_reg(TIMER1_INT_STATUS))
    {
        read_reg(TIMER1_EOI);//read clear

#ifdef MODULE_TEST

        if(test_timer1_int_flag)
        {
            gpio_set_bit(BIT1, 0x1);
            test_timer1_int_flag = 0;
        }
        else
        {
            gpio_set_bit(BIT1, 0x0);
            test_timer1_int_flag = 1;
        }
#else
		//DO SOMETHING
#endif
	}
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void timer2_isr()
{
    if(read_reg(TIMER2_INT_STATUS))
    {
        read_reg(TIMER2_EOI);//read clear

#ifdef MODULE_TEST

        if(test_timer2_int_flag)
        {
            gpio_set_bit(BIT2, 0x1);
            test_timer2_int_flag = 0;
        }
        else
        {
            gpio_set_bit(BIT2, 0x0);
            test_timer2_int_flag = 1;
        }
#else
		//DO SOMETHING
#endif
    }
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void core_timer_isr()
{
    read_reg(CORE_TIMER_CORET_CSR_REG);//read clear

#ifdef MODULE_TEST
    if(test_tick_timer_int_flag)
    {
        gpio_set_bit(BIT3, 0x1);
        test_tick_timer_int_flag = 0;
    }
    else
    {
        gpio_set_bit(BIT3, 0x0);
        test_tick_timer_int_flag = 1;
    }
#else
	//DO SOMETHING
#endif
}



