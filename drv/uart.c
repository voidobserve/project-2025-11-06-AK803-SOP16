/* ---------------------------------------------------------------
** File name:		uart.c
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
**
** ---------------------------------------------------------------
*/


/* Includes -----------------------------------------------------*/
#include "type.h"
#include "config.h"
#include "uart.h"
#include "sys.h"

/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/

/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/
void uart_init(uart_baud_rate_t baud_rate_index)
{
    uint32_t    reg_val = 0;

    /* Clock enable */
    sys_set_module_clock( CLK_UART_EN_MASK, ON );

    /* Reset UART module */
    sys_soft_reset(UART_SOFT_RESET_MASK);
    
    /*cpu clk*/
    reg_val = 0;
    reg_val = read_reg( TOP_MODULE_MODE_REG );
    reg_val &= TOP_CPU_CLK_SEL_MASK;
    reg_val = reg_val>>TOP_CPU_CLK_SEL_SHIFT;

   /*divisor = freq / baudrate,  freq = 3000000<<reg_val ,divisor>=16*/
#if 0

    reg_val = 3000000*(0x1<<reg_val)/baudrate;

#else
    uint32_t quotient = 0x0;
    reg_val = (3000000<<reg_val);

    while(1)
    {
        if(reg_val >= baud_rate_index)
        {
            quotient++;
            reg_val -= baud_rate_index;
        }
        else
        {
            break;
        }
    }

    reg_val = quotient;
#endif
    
    write_reg(UART_BAUD_DIV_REG, reg_val);
    reg_val =0;

    /* Enable Rx, Tx & Rx interrupt */
    reg_val = UART_RX_EN_MASK | UART_TX_EN_MASK | UART_RX_INT_EN_MASK;
    write_reg(UART_CTRL_REG, reg_val);

}

void uart_set_baudrate( uart_baud_rate_t baud_rate_index)
{
    uint32_t    reg_val = 0;
    /*cpu clk*/
    reg_val = 0;
    reg_val = read_reg( TOP_MODULE_MODE_REG );
    reg_val &= TOP_CPU_CLK_SEL_MASK;
    reg_val = reg_val>>TOP_CPU_CLK_SEL_SHIFT;

    if(!reg_val)
    {
        return;
    }
    /* Baud rate */
    if((baud_rate_index>= 2400)&&(baud_rate_index<=600000))
    {
        
    }
    else 
    {
        baud_rate_index =115200;
    }
   /*divisor = freq / baudrate,  freq = 3000000<<reg_val ,divisor>=16*/
#if 0

    reg_val = 3000000*(0x1<<reg_val)/baudrate;

#else
    uint32_t quotient = 0x0;
    reg_val = (3000000<<reg_val);

    while(1)
    {
        if(reg_val >= baud_rate_index)
        {
            quotient++;
            reg_val -= baud_rate_index;
        }
        else
        {
            break;
        }
    }

    reg_val = quotient;
#endif

    write_reg(UART_BAUD_DIV_REG, reg_val);

}

void uart_set_port(uart_port_t tx_rx_port)
{
    switch (tx_rx_port)
    {
        case 0x0:
        {
            sys_set_port_mux(PAD_GPIO_00, PAD_MUX_FUNCTION_1|2);    //RXD
            sys_set_port_mux(PAD_GPIO_01, PAD_MUX_FUNCTION_1|3);      //TXD
            break;
        }
        case 0x1:
        {

            sys_set_port_mux(PAD_GPIO_08, PAD_MUX_FUNCTION_3|2);  //RXD
            sys_set_port_mux(PAD_GPIO_01, PAD_MUX_FUNCTION_1|3);      //TXD

            break;
        }
        case 0x2:
        {
            sys_set_port_mux(PAD_GPIO_00, PAD_MUX_FUNCTION_1|2);    //RXD
            sys_set_port_mux(PAD_GPIO_09, PAD_MUX_FUNCTION_3|3);      //TXD

            break;
        }
        case 0x3:
        {
            sys_set_port_mux(PAD_GPIO_08, PAD_MUX_FUNCTION_3|2);  //RXD
            sys_set_port_mux(PAD_GPIO_09, PAD_MUX_FUNCTION_3|3);      //TXD
            break;
        }
        default:
        {
            break;
        }

    }

}

void uart_set_recv_int( uint8_t enable_recv_int )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg(UART_CTRL_REG);

    if ( TRUE == enable_recv_int )
    {
        reg_val = reg_val | UART_RX_INT_EN_MASK;
    }
    else
    {
        reg_val = reg_val & (~UART_RX_INT_EN_MASK);
    }

    write_reg(UART_CTRL_REG, reg_val);
}

uint8_t uart_get_rx_int_status()
{
    uint8_t reg_val = 0;

    reg_val = read_reg(UART_INT_REG);
    return ( reg_val & UART_RX_INT_MASK ) >> UART_RX_INT_SHIFT;
}

uint8_t uart_get_rx_status()
{
    uint8_t reg_val = 0;

    reg_val = read_reg(UART_STATE_REG);
    return ( reg_val & UART_RX_BUF_FULL_MASK ) >> UART_RX_BUF_FULL_SHIFT ;
}

void uart_putc( uint8_t c)
{
    uint32_t    reg_val = 0;

    /* If TX buffer is empty */
    while ((read_reg(UART_STATE_REG) & UART_TX_BUF_FULL_MASK));
    write_reg(BB_UART_DATA_REG, c);

    /* Clear Tx interrupt */
    //write_reg(UART_INT_REG, UART_TX_INT_MASK);
}

uint8_t uart_getc()
{
    uint8_t    reg_val = 0;

    reg_val = read_reg(BB_UART_DATA_REG);

    return reg_val;
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void uart_isr()
{
    uint32_t reg_val=0;
    reg_val =read_reg(UART_INT_REG);
    
    /*RX interrupt */
    if(UART_RX_INT_MASK & reg_val)
    {
#ifdef MODULE_TEST

        uint8_t aa = uart_getc();
        uart_putc(aa + 1);          // temp test code.   
#endif

    }
    /*TX interrupt*/
    else if(UART_TX_INT_MASK & reg_val)
    {
        
    }
    write_reg(UART_INT_REG, UART_RX_INT_MASK | UART_TX_INT_MASK);

}

