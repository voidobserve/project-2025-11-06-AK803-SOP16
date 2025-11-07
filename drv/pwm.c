/* ---------------------------------------------------------------
** File name:		pwm.c
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
#include "config.h"
#include "sys.h"
#include "pwm.h"

/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/

/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/

void pwm_init(void)
{
    uint32_t    reg_val = 0;

    /* Reset pwm module */
    sys_soft_reset(TIMER0_SOFT_RESET_MASK);

    /* Disable all PWM and clear some registers */
    write_reg( TIMER0_PWN_EN, 0 );
    write_reg( TIMER0_PWM_CYCLE_DIV, 0 );

    /* Diable all complement */
    write_reg( TIMER0_PWM_CONTROL, 0);

    /* Diable dead zone in all channel */
    write_reg( TIMER0_PWM_BOUND_EN_REG, 0 );

    /* Timer0 clock enable */
    reg_val = read_reg( TOP_CLK_CTRL_REG );
    reg_val = reg_val | CLK_TIMER0_EN_MASK;
    write_reg( TOP_CLK_CTRL_REG, reg_val );
}

/**
 * @brief  Config PWM cycle.
 * @param  timer_count             parameter range:0~1023.   
 */
void pwm_set_cycle( uint32_t timer_count)
{
    write_reg( TIMER0_LOAD_COUNT, timer_count);
}

void pwm_set_port_mux(uint8_t enable, uint8_t function)
{
	for(int i =0;i<6;i++)
	{
		if(enable &(0x1<<i))
		{
			sys_set_port_mux((PAD_GPIO_03 + (i << 2)), function);
		}	
	}
}
void pwm_set_port(pwm_port_t port_en)
{
    if(PWM_PORT_0 == port_en)
    {
        sys_set_port_mux(PAD_GPIO_02, PAD_MUX_FUNCTION_1|3);
        sys_set_port_mux(PAD_GPIO_07, PAD_MUX_FUNCTION_0|3);
    }
    else if(PWM_PORT_1 == port_en)
    {
        sys_set_port_mux(PAD_GPIO_02, PAD_MUX_FUNCTION_0|3);
        sys_set_port_mux(PAD_GPIO_07, PAD_MUX_FUNCTION_5|3);

    }
    else if(PWM_PORT_ALL == port_en)
    {
         sys_set_port_mux(PAD_GPIO_02, PAD_MUX_FUNCTION_1|3);
         sys_set_port_mux(PAD_GPIO_07, PAD_MUX_FUNCTION_5|3);
    }
}

void pwm_enable( uint8_t enable )
{ 
    pwm_set_port(enable); //set this port mux as pwm function
    write_reg( TIMER0_CONTROL_REG, 0x3);  // Timer0 enable
    write_reg( TIMER0_PWN_EN, 0x1);  // pwm output enable
}

void pwm_disable( uint8_t enable )
{
    uint32_t reg_val = read_reg(TIMER0_PWN_EN);

    reg_val &= ~0x1;
    write_reg( TIMER0_PWN_EN, reg_val);
}


void pwm_set_duty(pwm_channel_t pwm_channel, uint32_t duty_cycle)
{
    write_reg( ( TIMER0_PWM0_DUTY_CYCLE + ((uint8_t)pwm_channel<<2)), duty_cycle);
}

uint32_t pwm_get_duty(pwm_channel_t pwm_channel)
{
    uint32_t reg_val = 0;

	if(pwm_channel > PWM_CHANNEL_MAX)
	{
    	return 0x0;
	}

	reg_val = read_reg( TIMER0_PWM0_DUTY_CYCLE + ((uint8_t)pwm_channel<<2));

    return reg_val;
}

error_t pwm_set_cycle_div(pwm_channel_t pwm_channel,pwm_cycle_div_t cycle_div)
{
    uint32_t    reg_val = 0;

    /* Judge the parameter */
    reg_val = read_reg(TIMER0_LOAD_COUNT);
    reg_val = reg_val % (1 << (uint8_t)cycle_div);
	
    if (0 != reg_val )
    {
        return ERR_NOT_SUPPORTED;
    }

	if(pwm_channel > PWM_CHANNEL_MAX)
	{
		return ERR_NOT_SUPPORTED;
	}

    reg_val = read_reg(TIMER0_PWM_CYCLE_DIV);

	reg_val = (reg_val&(~(0x03<<(pwm_channel<<1)))) | (cycle_div<<(pwm_channel<<1));
	write_reg(TIMER0_PWM_CYCLE_DIV, reg_val);

    return ERR_NO_ERROR;
}

uint8_t pwm_get_cycle_div( pwm_channel_t pwm_channel)
{
    uint32_t reg_val = read_reg( TIMER0_PWM_CYCLE_DIV );

    reg_val = ( reg_val >> ((uint8_t)pwm_channel)<<1) & 0x03;

    return reg_val;
}

