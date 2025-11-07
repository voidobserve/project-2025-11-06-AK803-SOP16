 /* ---------------------------------------------------------------
** File name:		gpio.c
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
** Module Information:
**
** Revision History ----------------------------------------------
** ---------------------------------------------------------------
**  Date        Version     Action                  Author
** ---------------------------------------------------------------
**  2019-5-27   1.0         Created  
**  2020-12-18  2.0         Modified 
** ---------------------------------------------------------------
*/


/* Includes -----------------------------------------------------*/
#include "type.h"
#include "sys.h"
#include "gpio.h"
#include "int.h"
/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/
#ifdef MODULE_TEST
volatile uint8_t test_gpio_flag =0;
#endif
/* Extern -------------------------------------------------------*/
/* Functions ----------------------------------------------------*/

void gpio_set_port_direction(  gpio_dir_t direction)
{
    if ( GPIO_INPUT == direction )
    {
        write_reg(GPIO_OUT_EN_CLEAR_REG, GPIO_OUT_EN_CLEAR_MASK);
    }
    else
    {
        write_reg(GPIO_OUT_EN_SET_REG,GPIO_OUT_EN_SET_MASK);
    }
}
void gpio_set_bit_direction( uint32_t bit, gpio_dir_t direction)
{
    uint32_t reg_val = 0;
    if( GPIO_INPUT == direction)
    {
        write_reg(GPIO_OUT_EN_CLEAR_REG, bit);
    }
    else if(GPIO_OUTPUT == direction)
    {
        write_reg(GPIO_OUT_EN_SET_REG,bit);
    }
}
void gpio_set_port( uint32_t data)
{
    write_reg(GPIO_DATA_OUT_REG,data);
}
uint32_t gpio_get_port()
{
    return read_reg(GPIO_DATA_REG);
}
void gpio_set_bit(uint32_t bit, uint8_t data)
{
    uint32_t reg_val = read_reg(GPIO_DATA_OUT_REG);
	if(data)
	{
		reg_val |=bit;
	}
	else
	{
		reg_val &=~bit;
	}
    write_reg(GPIO_DATA_OUT_REG,reg_val);
}
uint32_t gpio_get_bits(uint32_t bit)
{
    return (bit & read_reg(GPIO_DATA_REG));

}

void gpio_enable_irq(uint32_t bits)
{
    write_reg(GPIO_INT_EN_SET_REG,bits); 
}

void gpio_disable_irq(uint32_t bits)
{
    write_reg(GPIO_INT_EN_CLEAR_REG,bits); 
}

void gpio_set_irq_type( gpio_irq_type_t type, uint32_t bits)
{

    if(GPIO_LEVEL_SENSITIVE == type)
    {
        write_reg(GPIO_INT_TYPE_CLEAR_REG,bits);
    }
    else if(GPIO_EDGE_SENSITIVE == type)
    {
        write_reg(GPIO_INT_TYPE_SET_REG,bits);
    }
}

void gpio_set_int_polarity(gpio_polarity_type_t polarity, uint32_t bits)
{
    if(GPIO_HIGH_LEVEL_OR_RISING_EDGE == polarity)
    {
        write_reg(GPIO_INT_POL_SET_REG,bits);
    }
    else if(GPIO_LOW_LEVEL_OR_FALLING_EDGE == polarity)
    {
        write_reg(GPIO_INT_POL_CLEAR_REG,bits);
    }
}
void gpio_clear_irq( uint32_t bits)
{
    write_reg(GPIO_INT_STATUS_REG,bits);
}
uint32_t gpio_int_status(void)
{
    return read_reg(GPIO_INT_STATUS_REG);
}


void gpio_set_bits_int_type(uint32_t bits ,gpio_int_type_t gpio_int)
{
    write_reg(GPIO_INT_EN_SET_REG,bits); 
    
    switch (gpio_int)
    {
        case GPIO_INT_LOW_LEVEL:
        {
            write_reg(GPIO_INT_TYPE_CLEAR_REG,bits);
            write_reg(GPIO_INT_POL_CLEAR_REG,bits);
            break;
        }
        case GPIO_INT_HIGH_LEVEL:
        {
            write_reg(GPIO_INT_TYPE_CLEAR_REG,bits);
            write_reg(GPIO_INT_POL_SET_REG,bits);
            break;
        }
        case GPIO_INT_FALLING_EDGE:
        {
            write_reg(GPIO_INT_TYPE_SET_REG,bits);
            write_reg(GPIO_INT_POL_CLEAR_REG,bits);
            break;
        }
        case GPIO_INT_RISING_EDGE:
        {
            write_reg(GPIO_INT_TYPE_SET_REG,bits);
            write_reg(GPIO_INT_POL_SET_REG,bits);
            break;
        }
        default:
        {
            break;
        }

    }
}
void gpio_set_mode(uint32_t bits,gpio_mode_t gpio_mode)
{
    for(uint8_t i=0;i<GPIO_MAX_NUM;i++)
    {
        if(bits &(0x1<<i))
        {
            sys_set_port_mux(PAD_MUX_BASE_ADDR+(i<<2),PAD_MUX_FUNCTION_0|gpio_mode);
        }
    }

}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void gpio_isr()
{
    uint32_t reg_val =gpio_int_status();
#ifdef MODULE_TEST
    for(int8_t i=0;i<GPIO_MAX_NUM;i++)
    {
        if(reg_val&(0x1<<i))
        {
            if(0 == test_gpio_flag)
            {
                test_gpio_flag = i+1;
            }
        }
    }
#else

#endif
    gpio_clear_irq(reg_val);

}

