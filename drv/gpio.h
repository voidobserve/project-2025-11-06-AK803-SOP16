/* ---------------------------------------------------------------
** File name:		gpio.h
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

#ifndef     __GPIO_H_
#define     __GPIO_H_


/* Includes -----------------------------------------------------*/
#include "config.h"
#include "type.h"
/* Macro --------------------------------------------------------*/
/* GPIO registers addr definition */

#define GPIO_BASE_ADDR                      (0x40060000)

/*
 * gpio_data
 * @ 0x00
 */
#define GPIO_DATA_REG                       (GPIO_BASE_ADDR + 0x00)
#define GPIO_DATA_MASK                      (0xFFFF)
#define GPIO_DATA_SHIFT                     (0)

/*
 * gpio_data_out
 * @ 0x04
 */
#define GPIO_DATA_OUT_REG                   (GPIO_BASE_ADDR + 0x04)
#define GPIO_DATA_OUT_MASK                  (0xFFFF)
#define GPIO_DATA_OUT_SHIFT                 (0)

/*
 * gpio_out_en_set
 * @ 0x10
 */
#define GPIO_OUT_EN_SET_REG                 (GPIO_BASE_ADDR + 0x10)
#define GPIO_OUT_EN_SET_MASK                (0xFFFF)
#define GPIO_OUT_EN_SET_SHIFT               (0)

/*
 * gpio_out_en_clear
 * @ 0x14
 */
#define GPIO_OUT_EN_CLEAR_REG               (GPIO_BASE_ADDR + 0x14)
#define GPIO_OUT_EN_CLEAR_MASK              (0xFFFF)
#define GPIO_OUT_EN_CLEAR_SHIFT             (0)

/*
 * gpio_alt_func_set
 * @ 0x18
 */
#define GPIO_ALT_FUNC_SET_REG               (GPIO_BASE_ADDR + 0x18)
#define GPIO_ALT_FUNC_SET_MASK              (0xFFFF)
#define GPIO_ALT_FUNC_SET_SHIFT             (0)

/*
 * gpio_alt_func_clear
 * @ 0x1C
 */
#define GPIO_ALT_FUNC_CLEAR_REG             (GPIO_BASE_ADDR + 0x1C)
#define GPIO_ALT_FUNC_CLEAR_MASK            (0xFFFF)
#define GPIO_ALT_FUNC_CLEAR_SHIFT           (0)

/*
 * gpio_int_en_set
 * @ 0x20
 */
#define GPIO_INT_EN_SET_REG                 (GPIO_BASE_ADDR + 0x20)
#define GPIO_INT_EN_SET_MASK                (0xFFFF)
#define GPIO_INT_EN_SET_SHIFT               (0)

/*
 * gpio_int_en_clear
 * @ 0x24
 */
#define GPIO_INT_EN_CLEAR_REG               (GPIO_BASE_ADDR + 0x24)
#define GPIO_INT_EN_CLEAR_MASK              (0xFFFF)
#define GPIO_INT_EN_CLEAR_SHIFT             (0)

/*
 * gpio_int_type_set
 * @ 0x28
 */
#define GPIO_INT_TYPE_SET_REG               (GPIO_BASE_ADDR + 0x28)
#define GPIO_INT_TYPE_SET_MASK              (0xFFFF)
#define GPIO_INT_TYPE_SET_SHIFT             (0)

/*
 * gpio_int_type_clear
 * @ 0x2C
 */
#define GPIO_INT_TYPE_CLEAR_REG             (GPIO_BASE_ADDR + 0x2C)
#define GPIO_INT_TYPE_CLEAR_MASK            (0xFFFF)
#define GPIO_INT_TYPE_CLEAR_SHIFT           (0)

/*
 * gpio_int_pol_set
 * @ 0x30
 */
#define GPIO_INT_POL_SET_REG                (GPIO_BASE_ADDR + 0x30)
#define GPIO_INT_POL_SET_MASK               (0xFFFF)
#define GPIO_INT_POL_SET_SHIFT              (0)

/*
 * gpio_int_pol_clear
 * @ 0x34
 */
#define GPIO_INT_POL_CLEAR_REG              (GPIO_BASE_ADDR + 0x34)
#define GPIO_INT_POL_CLEAR_MASK             (0xFFFF)
#define GPIO_INT_POL_CLEAR_SHIFT            (0)

/*
 * gpio_int_status
 * @ 0x38
 */
#define GPIO_INT_STATUS_REG                 (GPIO_BASE_ADDR + 0x38)
#define GPIO_INT_POL_CLEAR_MASK             (0xFFFF)
#define GPIO_INT_POL_CLEAR_SHIFT            (0)




#define GPIO_MAX_NUM           11

typedef enum gpio_int_type
{
    GPIO_INT_LOW_LEVEL =   0x0,
    GPIO_INT_HIGH_LEVEL =  0x1,
    GPIO_INT_FALLING_EDGE =0x2,
    GPIO_INT_RISING_EDGE = 0x3
}gpio_int_type_t;



typedef enum gpio_direction
{
    GPIO_INPUT      = 0,
    GPIO_OUTPUT     = 1

} gpio_dir_t;


typedef enum gpio_bits
{
    BIT0    = 0x00000001,
    BIT1    = 0x00000002,
    BIT2    = 0x00000004,
    BIT3    = 0x00000008,
    BIT4    = 0x00000010,
    BIT5    = 0x00000020,
    BIT6    = 0x00000040,
    BIT7    = 0x00000080,
    BIT8    = 0x00000100,
    BIT9    = 0x00000200,
    BIT10   = 0x00000400
} gpio_bits_t;

typedef enum gpio_irq_type
{
    GPIO_LEVEL_SENSITIVE    = 0x0,
    GPIO_EDGE_SENSITIVE     = 0x1
} gpio_irq_type_t;

typedef enum gpio_irq_polarity_type
{
    GPIO_LOW_LEVEL_OR_FALLING_EDGE    = 0x0,
    GPIO_HIGH_LEVEL_OR_RISING_EDGE    = 0x1
} gpio_polarity_type_t;

typedef enum gpio_mode_type
{
    GPIO_PULL_DOWN  = 0x1,
    GPIO_PULL_UP    = 0x2,
    GPIO_FLOATING   = 0x3
}gpio_mode_t;


void gpio_set_port_direction(  gpio_dir_t direction);
void gpio_set_bit_direction( uint32_t bit, gpio_dir_t direction);
void gpio_set_port( uint32_t data);
void gpio_set_port( uint32_t data);
uint32_t gpio_get_port();
void gpio_set_bit(uint32_t bit, uint8_t data);
uint32_t gpio_get_bits(uint32_t bit);
void gpio_double_edge_trigger_irq(uint32_t bits);
void gpio_enable_irq(uint32_t bits);
void gpio_disable_irq(uint32_t bits);
void gpio_mask_irq(uint32_t bits);
void gpio_unmask_irq(uint32_t bits);
void gpio_clear_irq( uint32_t bits);
void gpio_set_irq_type(gpio_irq_type_t type, uint32_t bits);
void gpio_set_int_polarity(gpio_polarity_type_t polarity, uint32_t bits);
void gpio_set_mode(uint32_t bits, gpio_mode_t gpio_mode);
void gpio_set_bits_int_type(uint32_t bits ,gpio_int_type_t gpio_int);


#endif  // __GPIO_H_

