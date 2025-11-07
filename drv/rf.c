/* ---------------------------------------------------------------
** File name:		rf.c
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
//#include <stdbool.h>

#include "type.h"
#include "config.h"
#include "sys.h"
#include "rf.h"
#include "delay.h"

/* Macro --------------------------------------------------------*/

/* Global Variables ---------------------------------------------*/


/* Extern -------------------------------------------------------*/

/* Functions ----------------------------------------------------*/


//----------------------------------------------------------------

/**
 * @brief  Init the function of RF.
 */
void rf_init(void)
{
    /* Clock enable */
    sys_set_module_clock( CLK_BB_EN_MASK, ON );

    /* Softreset */
    sys_soft_reset( BB_SOFT_RESET_MASK );
}

/**
 * @brief  Config Tx premble.
 * @param  pre_mode                   @ref bb_tx_pre_mode_t "preamble mode"
 * @param  pre                        the value of preamble.
 */
void rf_set_tx_preamble( bb_tx_pre_mode_t pre_mode, uint32_t pre )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg(BB_REG_TX_ACCESS_CODE_MODE_REG);

    reg_val &=~BB_CS_TXPREAMBLE_MODE_MASK;
    reg_val |=  pre_mode<<BB_CS_TXPREAMBLE_MODE_SHIFT;
    write_reg(BB_REG_TX_ACCESS_CODE_MODE_REG,reg_val);

    reg_val &=~BB_CS_PREAMBLE_MASK;
    reg_val |= pre << BB_CS_PREAMBLE_SHIFT;
    write_reg(BB_REG_PREAMBLE_REG,reg_val);

}

/**
 * @brief  Config Tx access address, send by LSB of [aa_high+aa_low] 
 * @param  aa_mode                    @ref bb_tx_aa_mode_t "access address mode"
 * @param  aa_high                    High-byte of access address. 0 if send BLE packets.
 * @param  aa_low                     Low-byte of access address.
 */
void rf_set_tx_aa( bb_tx_aa_mode_t aa_mode, uint8_t aa_high, uint32_t aa_low )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg(BB_REG_TX_ACCESS_CODE_MODE_REG);

    reg_val &=~BB_CS_TXSYNCWORD_MODE_MASK;
    reg_val |= aa_mode<<BB_CS_TXSYNCWORD_MODE_SHIFT;
    write_reg(BB_REG_TX_ACCESS_CODE_MODE_REG,reg_val);

    reg_val = 0;
    
    reg_val = read_reg(BB_REG_SYNCWORD_HIGHPART_REG);
    reg_val &= ~BB_CS_SYNCWORD_LEFT4BYTES_MASK;
    reg_val|= aa_low << BB_CS_SYNCWORD_LEFT4BYTES_SHIFT;
    write_reg(BB_REG_SYNCWORD_HIGHPART_REG, reg_val);
    write_reg(BB_REG_SYNCWORD_LOWPART_REG, aa_high);

}

/**
 * @brief  Enable/Disable CRC and Whitening.
 * @param  whiting_ctrl               ON/OFF.
 * @param  crc_ctrl                   ON/OFF.
 */
void rf_set_whit_and_crc(bool whiting_ctrl, bool crc_ctrl)
{
    uint32_t reg_val = 0;

    reg_val = read_reg( BB_REG_CRC_WHIT_DSB_REG );
    reg_val &= ~(BB_WHIT_DSB_MASK | BB_CRC_DSB_MASK);
    reg_val |= ( (~whiting_ctrl) & 1 ) << BB_WHIT_DSB_SHIFT;
    reg_val |= ( (~crc_ctrl) & 1 ) << BB_CRC_DSB_SHIFT;

    write_reg( BB_REG_CRC_WHIT_DSB_REG, reg_val);
}

/**
 * @brief  Start the function of RF, refer to MODULE_TEST for use.
 */
void rf_start()
{
    write_reg(BB_REG_START_P_REG, 1);
}

/**
 * @brief  set tx test mode.
 * @param  test_mode                     	1:work on test mode.
 											0:work normally.
 */
void rf_set_test_mode(bool test_mode)
{
    write_reg(BB_REG_TX_TEST_WORK_ON_REG,test_mode);
}

/**
 * @brief  work on test mode and set tx type.
 * @param     message_form                 @rf_test_message_form_t "set message type".										
 */
void rf_set_test_message_form(rf_test_message_form_t   message_form)
{
    write_reg(BB_REG_TX_TEST_TYPE_REG,message_form);
}

/**
 * @brief  The length of Tx packets, PDU length if send BLE packets.
 * @param  tx_len                     the setting of length.
 */
void rf_set_tx_len( uint8_t tx_len )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( BB_REG_TX_ADVLEN_FROM_CPU_REG );
    reg_val &= ~BB_TX_ADVLEN_MASK;
    //reg_val |= (tx_len - 2 );

    reg_val |= tx_len;
    write_reg( BB_REG_TX_ADVLEN_FROM_CPU_REG, reg_val );
    reg_val = 1 << BB_TX_DATA_INVERT_SHIFT;
    write_reg( BB_REG_TX_BIT_INVERT_REG, reg_val );
}

/**
 * @brief  Config the channel number of RF.
 * @param  channel_num                channel number, 37/38/39/...
 */
void rf_set_channel_num(uint8_t channel_num)
{
    uint32_t reg_val;

    write_reg(BB_REG_CHANNEL_NUM_REG, channel_num);

    reg_val = read_reg(CORE_CTRL_BASE_ADDR);
    reg_val &= 0xF0;
    reg_val |= 0x07;    //BIT[2:0] config to 0b'111
    write_reg(CORE_CTRL_BASE_ADDR, reg_val);
    
    delay_us(500);

    reg_val = read_reg(CORE_CTRL_BASE_ADDR);
    reg_val &= 0xF0;
    reg_val |= 0x01;    //BIT[2:0] config to 0b'001
    write_reg(CORE_CTRL_BASE_ADDR, reg_val);
}

/**
 * @brief  Get the status of RF interrupt.
 * @return uint8_t                    @ref int status "user guide: reg_interrupt_RO".
 */
uint8_t rf_get_int_status()
{
    return  (uint8_t)read_reg(BB_REG_INTERRUPT_REG);
}

uint8_t rf_get_buffer_status()
{
    uint32_t reg_val = 0;

    reg_val = read_reg(BB_CTRL2REG_BUF_FLAG_REG);

    return  (uint8_t)reg_val;
}
void rf_enable_int(void)
{
    uint32_t reg_val = 0;

    reg_val = read_reg(BB_REG_INTERRUPT_CTRL_REG);
    reg_val |=BB_REG2CTRL_TX_INT_EN_MASK;

    write_reg(BB_REG_INTERRUPT_CTRL_REG,BB_REG2CTRL_TX_INT_EN_MASK);
}

void rf_disable_int(void)
{
    uint32_t reg_val = 0;

    reg_val = read_reg(BB_REG_INTERRUPT_CTRL_REG);

    reg_val &= ~BB_REG2CTRL_TX_INT_EN_MASK;
    write_reg(BB_REG_INTERRUPT_CTRL_REG, reg_val);
}

void rf_mask_int(void)
{
    uint32_t reg_val = 0;

    reg_val = read_reg(BB_REG_INTERRUPT_CTRL_REG);

	reg_val |= BB_REG2CTRL_TX_INT_MASK_MASK;


    write_reg(BB_REG_INTERRUPT_CTRL_REG, reg_val);
}

void rf_unmask_int(void)
{
    uint32_t reg_val = 0;

    reg_val = read_reg(BB_REG_INTERRUPT_CTRL_REG);

	reg_val &= ~BB_REG2CTRL_TX_INT_MASK_MASK;


    write_reg(BB_REG_INTERRUPT_CTRL_REG, reg_val);
}

void rf_int_clear( uint32_t int_clear )
{
    write_reg( BB_REG_TX_INT_CLEAR_REG, int_clear );
}

void rf_set_tx_pattern()
{
    uint32_t reg_val = 0;

    reg_val = read_reg( BB_REG_TX_TEST_WORK_ON_REG );
    reg_val &= ~BB_TX_TEST_WORK_ON_MASK;
    reg_val |= 0x1C;
    write_reg( BB_REG_TX_TEST_WORK_ON_REG, reg_val);

    reg_val = read_reg( BB_REG_TX_TEST_TYPE_REG );
    reg_val &= ~BB_TX_TEST_TYPE_MASK;
    reg_val |= 0x0;
    write_reg( BB_REG_TX_TEST_TYPE_REG, reg_val );
}
inline void rf_set_bb_mode( rf_bb_mode_t rf_bb_mode)
{
    uint32_t reg_val = 0;

    reg_val = read_reg(TOP_MODULE_MODE_REG);
    reg_val &= ~TOP_RF_BB_MODE_MASK;
    reg_val |= rf_bb_mode << TOP_RF_BB_MODE_SHIFT;

    write_reg(TOP_MODULE_MODE_REG, reg_val);
};

/**
 * @brief  Config RF power level
 * @param  rf_power                   0~7
 */
void rf_set_power( uint8_t rf_power )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( CORE_CTRL_BASE_ADDR );
    reg_val &=~0x70;
    reg_val |= (rf_power&0x07)<<4;

    write_reg(CORE_CTRL_BASE_ADDR, reg_val);
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void rx_isr()
{
#ifdef MODULE_TEST
	//DO SOMETHING
#endif
}

ATTRIBUTE_ISR ATTRIBUTE_WEAK void tx_isr()
{
#ifdef MODULE_TEST
    //DO SOMETHING
#endif
	
}


