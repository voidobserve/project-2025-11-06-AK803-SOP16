/* ---------------------------------------------------------------
** File name:		pwm.h
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

#ifndef   __PWM_H_
#define   __PWM_H_

/* Includes -----------------------------------------------------*/
#include "type.h"
#include "timer.h"

/* Macro --------------------------------------------------------*/

typedef enum pwm_channel
{
    PWM_CHANNEL_0   = 0,

    PWM_CHANNEL_MAX = PWM_CHANNEL_0
} pwm_channel_t;
typedef enum pwm_port
{
    PWM_PORT_0   = 0x1,//gpio2
    PWM_PORT_1   = 0x2,//gpio7
    PWM_PORT_ALL = 0x3
} pwm_port_t;

typedef enum pwm_cycle_div
{
    PWM_CYCLE_DIV_2 = 1,
    PWM_CYCLE_DIV_4 = 2,
    PWM_CYCLE_DIV_8 = 3
} pwm_cycle_div_t;

#define PWM_DEAD_ZONE_WIDTH_MAX         (0x3F)

#define PWM0_EN                         (0x01)


#define PWM0_RVSE_EN                    (0x01)



/* Registers ----------------------------------------------------*/

#define TIMER0_LOAD_COUNT               (0x40030000)
//#define TIMER0_CONTROL_REG              (0x40030008)

#define TIMER0_PWM_CONTROL              (0x400300B0)
#define TIMER0_PWM0_DUTY_CYCLE          (0x400300B4)

#define TIMER0_PWN_EN                   (0x400300CC)

#define TIMER0_PWM_CYCLE_DIV            (0x400300D0)

#define TIMER0_PWM_BOUND_EN_REG         (0x400300D4)
#define PWM_BOUND_EN_0_MASK             (0x01)
#define PWM_BOUND_EN_0_SHIFT            (0x00)


#define TIMER0_PWM_BOUND_VAL_REG        (0x400300D8)
#define PWM_BOUND_VAL_MASK              (0x3F)
#define PWM_BOUND_VAL_SHIFT             (0x00)


/* Functions prototype ------------------------------------------*/

/**
 * @brief  Config PWM cycle.
 * @param  timer_count             parameter range:0~1023.   
 */
void 		pwm_set_cycle( uint32_t timer_count);


void 		pwm_init( void );
void 		pwm_enable( uint8_t enable );
void 		pwm_disable( uint8_t enable );
void 		pwm_set_duty(pwm_channel_t pwm_channel, uint32_t duty_cycle);
uint32_t 	pwm_get_duty(pwm_channel_t pwm_channel);
error_t 	pwm_set_cycle_div(pwm_channel_t pwm_channel,pwm_cycle_div_t cycle_div);
uint8_t 	pwm_get_cycle_div( pwm_channel_t pwm_channel);
void        pwm_set_port(pwm_port_t port_en);

#endif  // #ifndef   __PWM_H_
