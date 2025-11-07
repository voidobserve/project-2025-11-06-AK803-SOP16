/* ---------------------------------------------------------------
** File name:		sys.h
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
** Module Information:
**
** Revision History ----------------------------------------------
** ---------------------------------------------------------------
**	Date        Version     Action              Author
** ---------------------------------------------------------------
**	2019-1-12   1.0         Created             Yan Lei
**
** ---------------------------------------------------------------
*/

#ifndef   __SYS_H_
#define   __SYS_H_



#ifdef __cplusplus
extern "C" {    // allow C++ to use these headers
#endif

/* Includes -----------------------------------------------------*/
#include <stdbool.h>

#include "type.h"
#include "config.h"
#include "print.h"

/* Macro --------------------------------------------------------*/

#define	read_reg(addr)                      *((volatile uint32_t *)(addr))
#define	write_reg(addr, data)               *((volatile uint32_t *)(addr)) = data


#ifdef  DEBUG
#define TRACE_ENTER()                       print("%s, enter\r\n", __FUNCTION__)
#define TRACE_EXIT()                        print("%s, exit\r\n",  __FUNCTION__)
#else
#define TRACE_ENTER()
#define TRACE_EXIT()
#endif  //DEBUG


#define  ATTRIBUTE_ISR                      __attribute__((isr))
#define  ATTRIBUTE_WEAK                     __attribute__((weak))

/***
 *  Global resource
 */
#define RETENTION_MEMEORY_ADDR              (0x401201A0)//modified @20200728
#define RETENTION_MEMEORY_SIZE              (16)            // 4 * 32 Bits

/***
 *  Core control registers
 */

#define CORE_CTRL_BASE_ADDR                 (0x40020000)

#define CORE_CTRL_XCVR_REG_LL_ADDR          (CORE_CTRL_BASE_ADDR)
#define CORE_CTRL_XCVR_REG_ML_ADDR          (CORE_CTRL_BASE_ADDR + 0x04)
#define CORE_CTRL_XCVR_REG_MH_ADDR          (CORE_CTRL_BASE_ADDR + 0x08)
#define CORE_CTRL_XCVR_REG_HH_ADDR          (CORE_CTRL_BASE_ADDR + 0x0C)

#define CORE_CTRL_VCO_LL_ADDR               (CORE_CTRL_BASE_ADDR + 0x10)

#define CORE_CTRL_VCO_ML_ADDR               (CORE_CTRL_BASE_ADDR + 0x14)
#define CORE_CTRL_VCO_ML_MASK               (0xFF)
#define CORE_CTRL_VCO_ML_SHIFT              (0)

#define CORE_CTRL_VCO_MH_ADDR               (CORE_CTRL_BASE_ADDR + 0x18)
#define CORE_CTRL_VCO_MH_MASK               (0xFF)
#define CORE_CTRL_VCO_MH_SHIFT              (0)

#define CORE_CTRL_VCO_HH_ADDR               (CORE_CTRL_BASE_ADDR + 0x1C)
#define CORE_CTRL_RFPLL_REG_LL_ADDR         (CORE_CTRL_BASE_ADDR + 0x20)
#define CORE_CTRL_RFPLL_REG_ML_ADDR         (CORE_CTRL_BASE_ADDR + 0x24)
#define CORE_CTRL_RFPLL_REG_MH_ADDR         (CORE_CTRL_BASE_ADDR + 0x28)
#define CORE_CTRL_RFPLL_REG_HH_ADDR         (CORE_CTRL_BASE_ADDR + 0x2C)

#if 0
#define ANT_CAP_REG                         (CORE_CTRL_BASE_ADDR + 0x30)
#define XMFR_CAP_REG                        (CORE_CTRL_BASE_ADDR + 0x34)

#define RFE_REG_MH                          (CORE_CTRL_BASE_ADDR + 0x38)
#define RFE_RF_POWER_L_MASK                 (0xC0)

#define RFE_REG_HH                          (CORE_CTRL_BASE_ADDR + 0x3C)
#define RFE_RF_POWER_H_MASK                 (0x01)

#define ABB_LL                              (CORE_CTRL_BASE_ADDR + 0x40)
#define ABB_MH                              (CORE_CTRL_BASE_ADDR + 0x48)
#define CORE_CTRL_ABB_REG_MH_ADDR           (CORE_CTRL_BASE_ADDR + 0x48)
#define CORE_CTRL_ABB_REG_MH_MASK           (0xFF)
#define CORE_CTRL_ABB_REG_MH_SHIFT          (0)

/*
 * ADC delay
 */
#define TOP_CTRL_ADC_DELAY_REG              (CORE_CTRL_BASE_ADDR + 0x4C)

#else
#define CORE_CTRL_RFE_REG_LL_ADDR         (CORE_CTRL_BASE_ADDR + 0x30)
#define CORE_CTRL_RFE_REG_ML_ADDR         (CORE_CTRL_BASE_ADDR + 0x34)

#define CORE_CTRL_RFE_REG_MH_ADDR         (CORE_CTRL_BASE_ADDR + 0x38)
#define RFE_RF_POWER_L_MASK                 (0xC0)

#define CORE_CTRL_RFE_REG_HH_ADDR         (CORE_CTRL_BASE_ADDR + 0x3C)
#define RFE_RF_POWER_H_MASK                 (0x01)

#define CORE_CTRL_ABB_REG_LL_ADDR         (CORE_CTRL_BASE_ADDR + 0x40)
#define CORE_CTRL_ABB_REG_ML_ADDR         (CORE_CTRL_BASE_ADDR + 0x44)
#define CORE_CTRL_ABB_REG_MH_ADDR         (CORE_CTRL_BASE_ADDR + 0x48)
#define CORE_CTRL_ABB_REG_HH_ADDR         (CORE_CTRL_BASE_ADDR + 0x4C)

#endif



/***
 *  Top control registers
 */

#define TOP_CTRL_BASE_ADDR                  (0x40120100)

/*
 * Top power
 */
#define TOP_POWER_CTRL_REG                  (TOP_CTRL_BASE_ADDR + 0x04)//1:cpu power down


/*
 * Module soft reset
 */
#define WDG_SOFT_RESET_REG                  (TOP_CTRL_BASE_ADDR + 0x0C)//
#define WDG_SOFT_RESET_MASK                 (0x01)

#define TOP_SOFT_RESET_REG                  0x40020084//(TOP_CTRL_BASE_ADDR + 0x0C)
#define TIMER2_SOFT_RESET_MASK              (0x01)
#define TIMER1_SOFT_RESET_MASK              (0x02)
#define TIMER0_SOFT_RESET_MASK              (0x04)
#define GPIO_SOFT_RESET_MASK                (0x08)
#define UART_SOFT_RESET_MASK                (0x10)
#define BB_SOFT_RESET_MASK                  (0x20)
#define TCCR_SOFT_RESET_MASK                (0x40)



/*
 * Module soft reset_2
 */
#define WT_SOFT_RESET_REG                  (TOP_CTRL_BASE_ADDR + 0x10)//
#define WT_SOFT_RESET_MASK                 (0x01)

#define GPADC_SOFT_RESET_REG               0x40020088//
#define GPADC_SOFT_RESET_MASK              (0x01)

/*
 * Top clock control
 */
#define TOP_CLK_CTRL_REG                    0x4002008C//(TOP_CTRL_BASE_ADDR + 0x14)  @20200311
#define CLK_TCCR_EN_MASK                    (0x40)
#define CLK_BB_EN_MASK                      (0x20)
#define CLK_UART_EN_MASK                    (0x10)
#define CLK_GPIO_EN_MASK                    (0x08)
#define CLK_TIMER0_EN_MASK                  (0x04)
#define CLK_TIMER1_EN_MASK                  (0x02)
#define CLK_TIMER2_EN_MASK                  (0x01)
#define CLK_ALL_EN_MASK                     (0x7F)

/*
 * VDD VCO config
 */
#define TOP_VDD_VCO_REG_0                   (TOP_CTRL_BASE_ADDR + 0x1C)
#define TOP_VDD_VCO_REG_1                   (TOP_CTRL_BASE_ADDR + 0x20)

/*
 * XOSC Cap tuning
 */
#define TOP_CTRL_ANA_REG_ULL_HH_ADDR        (TOP_CTRL_BASE_ADDR + 0x34)
#define TOP_CTRL_ANA_REG_ULL_HH_MASK        (0xFF)
#define TOP_CTRL_ANA_REG_ULL_HH_SHIFT       (0)

/*
 * gain dac init
 */
#define TOP_CTRL_GAIN_DAC_INI_ADDR          (TOP_CTRL_BASE_ADDR + 0x48)
#define TOP_CTRL_GAIN_DAC_INI_MASK          (0xFF)
#define TOP_CTRL_GAIN_DAC_INI_SHIFT         (0)

/*
 * PLL digital fvco init
 */
#define TOP_CTRL_PLL_DIGITAL_FVCO_INI_ADDR  (TOP_CTRL_BASE_ADDR + 0x5C)
#define TOP_CTRL_PLL_DIGITAL_FVCO_INI_MASK  (0xFF)
#define TOP_CTRL_PLL_DIGITAL_FVCO_INI_SHIFT (0)


/*
 * Phase invert
 */
#define TOP_PHASE_INVERT_REG                (TOP_CTRL_BASE_ADDR + 0x60)

/*
 * module_mode
 * @ 0x8C
 */
#define TOP_MODULE_MODE_REG                 (TOP_CTRL_BASE_ADDR + 0x8C)
#define TOP_EN_LVD_ULL_MASK                 (0x20)
#define TOP_EN_LVD_ULL_SHIFT                (5)
#define TOP_CPU_CLK_SEL_MASK                (0x18)
#define TOP_CPU_CLK_SEL_SHIFT               (3)
#define TOP_WATCH_DOG_ON_MASK               (0x4)
#define TOP_WATCH_DOG_ON_SHIFT              (2)
#define TOP_RF_BB_MODE_MASK                 (0x3)
#define TOP_RF_BB_MODE_SHIFT                (0)



/***
 *  PAD mux registers
 */

#define PAD_MUX_BASE_ADDR                   (0x40120000)
#define PAD_GPIO_00                         (PAD_MUX_BASE_ADDR + 0x00)
#define PAD_GPIO_01                         (PAD_MUX_BASE_ADDR + 0x04)
#define PAD_GPIO_02                         (PAD_MUX_BASE_ADDR + 0x08)
#define PAD_GPIO_03                         (PAD_MUX_BASE_ADDR + 0x0C)
#define PAD_GPIO_04                         (PAD_MUX_BASE_ADDR + 0x10)
#define PAD_GPIO_05                         (PAD_MUX_BASE_ADDR + 0x14)
#define PAD_GPIO_06                         (PAD_MUX_BASE_ADDR + 0x18)
#define PAD_GPIO_07                         (PAD_MUX_BASE_ADDR + 0x1C)
#define PAD_GPIO_08                         (PAD_MUX_BASE_ADDR + 0x20)
#define PAD_GPIO_09                         (PAD_MUX_BASE_ADDR + 0x24)
#define PAD_GPIO_10                         (PAD_MUX_BASE_ADDR + 0x28)
#define PAD_GPIO_11                         (PAD_MUX_BASE_ADDR + 0x2C)
#define PAD_GPIO_12                         (PAD_MUX_BASE_ADDR + 0x30)
#define PAD_GPIO_13                         (PAD_MUX_BASE_ADDR + 0x34)
#define PAD_GPIO_14                         (PAD_MUX_BASE_ADDR + 0x38)
#define PAD_GPIO_15                         (PAD_MUX_BASE_ADDR + 0x3C)
#define PAD_GPIO_16                         (PAD_MUX_BASE_ADDR + 0x40)
#define PAD_GPIO_17                         (PAD_MUX_BASE_ADDR + 0x44)
#define PAD_GPIO_18                         (PAD_MUX_BASE_ADDR + 0x48)
#define PAD_GPIO_19                         (PAD_MUX_BASE_ADDR + 0x4C)


#define PHASE_INVERT_REG                    (0x40120160)


typedef enum cpu_clock_sel_s
{

    CPU_CLOCK_32K       = 0,
    CPU_CLOCK_6M        = 1,
    CPU_CLOCK_12M       = 2,
    CPU_CLOCK_24M       = 3

}cpu_clock_sel_t;

typedef enum rf_bb_mode_s
{
    CHIP_RF_CHIP_BB = 0,
    EXT_RF_CHIP_BB  = 1,
    CHIP_RF_EXT_BB  = 2
}rf_bb_mode_t;

/**
 * @brief 定义引脚的复用功能，具体的复用模式需要查看手册
 * 
 */
typedef enum pad_mux_function
{
#if 0
    PAD_MUX_FUNCTION_0 = 0x00,
    PAD_MUX_FUNCTION_1 = 0x10,
    PAD_MUX_FUNCTION_2 = 0x20,
    PAD_MUX_FUNCTION_3 = 0x30,
    PAD_MUX_FUNCTION_4 = 0x40,
#else
    PAD_MUX_FUNCTION_0 = 0x00,
    PAD_MUX_FUNCTION_1 = 0x04,
    PAD_MUX_FUNCTION_2 = 0x08,
    PAD_MUX_FUNCTION_3 = 0x0C,
    PAD_MUX_FUNCTION_4 = 0x10,
    PAD_MUX_FUNCTION_5 = 0x14,
    PAD_MUX_FUNCTION_6 = 0x18,
    PAD_MUX_FUNCTION_7 = 0x1C
#endif
} pad_mux_function_t;

typedef enum sys_clock_ctrl
{
    CLK_TIMER2          = 0x01,
    CLK_TIMER1          = 0x02,
    CLK_TIMER0          = 0x04,
    CLK_GPIO            = 0x08,
    CLK_UART            = 0x10,
    CLK_BB              = 0x20,
    CLK_TCCR            = 0x40,
    CLK_ALL             = 0x7F

} sys_clock_ctrl_t;


void sys_set_port_mux(uint32_t port, uint8_t function);
void sys_set_module_clock(sys_clock_ctrl_t clock_sel, uint8_t on_off);
void sys_soft_reset(uint8_t module);
void sys_set_clock(cpu_clock_sel_t clock);
uint8_t get_sys_clk_cfg(void);
void sys_init(void);
void sys_sleep_down(void);

#ifdef __cplusplus
}
#endif

#endif  // __SYS_H_

