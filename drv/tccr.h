/* ---------------------------------------------------------------
** File name:		tccr.h
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
** Module Information:
**
** Revision History ----------------------------------------------
** ---------------------------------------------------------------
**  Date        Version     Action                  Author
** ---------------------------------------------------------------
**  2019-6-11   1.0         Created
**
** ---------------------------------------------------------------
*/

#ifndef   __TCCR_H_
#define   __TCCR_H_


//tccr addr define
#define TCCR_GPIO_PORT						(0x40120000 + 0x1C)//GPIO7

#define TCCR_BASE_ADDR						(0x40010000)
#define TCCR_EN_ADDR						(TCCR_BASE_ADDR)
#define TCCR_TIMER_RELOAD_ADDR				(TCCR_BASE_ADDR + 0x04)
#define TCCR_CC0C_ADDR						(TCCR_BASE_ADDR + 0x18)//上升沿timer count值
#define TCCR_CC1C_ADDR						(TCCR_BASE_ADDR + 0x1C)//下降沿timer count值
#define TCCR_INT_EN_ADDR					(TCCR_BASE_ADDR + 0x28)
#define TCCR_INT_MASK_ADDR					(TCCR_BASE_ADDR + 0x2C)
#define TCCR_INT_CLEAR_ADDR					(TCCR_BASE_ADDR + 0x30)
#define TCCR_INT_STATUS_ADDR				(TCCR_BASE_ADDR + 0x34)


//function define
#define TCCR_EN_ENABLE						(0x1)//BIT[0]
#define TCCR_EN_DISABLE						(0x0)

#define TCCR_EX_RELOAD_EN_ENABLE			(0x2)//BIT[1]
#define TCCR_EX_RELOAD_EN_DISABLE			(0x0)

#define TIMER_RELOAD_SEL_STOP				(0x0)//BIT[3:2]
#define TIMER_RELOAD_SEL_SOFT				(0x4)
#define TIMER_RELOAD_SEL_AUTO				(0x8)
#define TIMER_RELOAD_SEL_FALL_EDG			(0xC)

#define TIMER_CLK_SEL_STOP					(0x0)//BIT[5:4]
#define TIMER_CLK_SEL_NORMAL				(0x10)
#define TIMER_CLK_SEL_ADD_FALL_EGD			(0x20)
#define TIMER_CLK_SEL_ADD_HIGH				(0x30)

#define TCCR_INPUT_REVERSE					(0x40)//BIT[6]


enum en_tccr_int_type
{
	TCCR_INT_NEGEDGE_EN 					= 0x01,
	TCCR_INT_TIMEOUT_EN 					= 0x02,
	TCCR_INT_ALL_EN 						= 0x03,
};


typedef enum tccr_irq_type
{
    TCCR_INT_NEGEDGE = 0x1,
    TCCR_INT_TIMEOUT = 0x2,
    TCCR_INT_ALL = 0x3
} tccr_irq_type_t;
typedef enum tccr_mode_type
{
    TCCR_AS_TIMER =0x0,
    TCCR_EVENT_MODE = 0x1,
    TCCR_PULSE_WIDTH_MEASUREMENT = 0x2,
    TCCR_CAPTURE_MODE = 0x3
} tccr_mode_type_t;


typedef enum tccr_port
{
    TCCR_PORT_0 =0x0,//GPIO6 fun_5
    TCCR_PORT_1 =0x1,//GPIO7 fun_3
    TCCR_PORT_2 =0x2,//GPIO8 fun_5
    TCCR_PORT_3 =0x3//GPIO10 fun_1
}tccr_port_t;


#define CHECK_AC_TIMEOUT					(0xFFFFFF - 0x3A980)//12M/2, 60ms:0x57E40,40ms:0x3A980

//void tccr_init(tccr_mode_type_t tccr_mode,uint32_t check_count);

void tccr_init(uint32_t check_count,enum en_tccr_int_type enable_int_type);
void tccr_set_port(tccr_port_t port);

#endif
