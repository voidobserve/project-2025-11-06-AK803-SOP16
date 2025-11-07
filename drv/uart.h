/* ---------------------------------------------------------------
** File name:		uart.h
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

#ifndef     __UART_H_
#define     __UART_H_


/* Includes -----------------------------------------------------*/
#include "type.h"
#include "config.h"

/* Macro --------------------------------------------------------*/
#define	UART_BASE_ADDR						(0x40000000)

/*
 * uart_data
 * @ 0x00
 */
#define BB_UART_DATA_REG                    (UART_BASE_ADDR + 0x00)
#define UART_DATA_MASK                      (0xFF)
#define UART_DATA_SHIFT                     (0)

/*
 * uart_state
 * @ 0x04
 */
#define UART_STATE_REG                      (UART_BASE_ADDR + 0x04)
#define UART_RX_BUF_OVERRUN_MASK            (0x8)
#define UART_RX_BUF_OVERRUN_SHIFT           (3)
#define UART_TX_BUF_OVERRUN_MASK            (0x4)
#define UART_TX_BUF_OVERRUN_SHIFT           (2)
#define UART_RX_BUF_FULL_MASK               (0x2)
#define UART_RX_BUF_FULL_SHIFT              (1)
#define UART_TX_BUF_FULL_MASK               (0x1)
#define UART_TX_BUF_FULL_SHIFT              (0)

/*
 * uart_ctrl
 * @ 0x08
 */
#define UART_CTRL_REG                       (UART_BASE_ADDR + 0x08)
#define UART_TX_HIGHSPEED_MODE_MASK         (0x40)
#define UART_TX_HIGHSPEED_MODE_SHIFT        (6)
#define UART_RX_OVERRUN_INT_EN_MASK         (0x20)
#define UART_RX_OVERRUN_INT_EN_SHIFT        (5)
#define UART_TX_OVERRUN_INT_EN_MASK         (0x10)
#define UART_TX_OVERRUN_INT_EN_SHIFT        (4)
#define UART_RX_INT_EN_MASK                 (0x8)
#define UART_RX_INT_EN_SHIFT                (3)
#define UART_TX_INT_EN_MASK                 (0x4)
#define UART_TX_INT_EN_SHIFT                (2)
#define UART_RX_EN_MASK                     (0x2)
#define UART_RX_EN_SHIFT                    (1)
#define UART_TX_EN_MASK                     (0x1)
#define UART_TX_EN_SHIFT                    (0)

/*
 * uart_int
 * @ 0x0c
 */
#define UART_INT_REG                        (UART_BASE_ADDR + 0x0c)
#define UART_RX_OVERRUN_INT_MASK            (0x8)
#define UART_RX_OVERRUN_INT_SHIFT           (3)
#define UART_TX_OVERRUN_INT_MASK            (0x4)
#define UART_TX_OVERRUN_INT_SHIFT           (2)
#define UART_RX_INT_MASK                    (0x2)
#define UART_RX_INT_SHIFT                   (1)
#define UART_TX_INT_MASK                    (0x1)
#define UART_TX_INT_SHIFT                   (0)

/*
 * uart_baud_div
 * @ 0x0c
 */
#define UART_BAUD_DIV_REG                   (UART_BASE_ADDR + 0x10)
#define UART_BAUD_DIV_MASK                  (0xFFFFF)
#define UART_BAUD_DIV_SHIFT                 (0)


#define	UART_CLK							(12000000) //24->12
#define	UART_DIV							(UART_CLK / 115200)



typedef enum uart_baud_rate_e
{
    UART_BAUDRATE_500000    = 500000,
    UART_BAUDRATE_115200    = 115200,
    UART_BAUDRATE_57600     = 57600,
    UART_BAUDRATE_38400     = 38400,
    UART_BAUDRATE_19200     = 19200,
    UART_BAUDRATE_9600      = 9600,
    UART_BAUDRATE_4800      = 4800,
    UART_BAUDRATE_2400      = 2400,
}uart_baud_rate_t;

typedef enum uart_port_e
{
    UART_PORT_TX0RX0 = 0,//tx:gpio1  rx:gpio0
    UART_PORT_TX0RX1 = 1,//tx:gpio1  rx:gpio8
    UART_PORT_TX1RX0 = 2,//tx:gpio9 rx:gpio0
    UART_PORT_TX1RX1 = 3 //tx:gpio9 rx:gpio8
}uart_port_t;



void 	uart_init( uart_baud_rate_t baud_rate_index);
void    uart_set_port(uart_port_t tx_rx_port);
void 	uart_set_baudrate( uart_baud_rate_t baud_rate_index);
void 	uart_set_recv_int( uint8_t enable_recv_int );
uint8_t uart_get_rx_int_status(void);
uint8_t uart_get_rx_status(void);
void 	uart_putc( uint8_t c);
uint8_t uart_getc(void);

#endif  // __UART_H_

