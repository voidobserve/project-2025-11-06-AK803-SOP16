/* ---------------------------------------------------------------
** File name:		rf.h
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

#ifndef     __RF_H_
#define     __RF_H_


/* Includes -----------------------------------------------------*/
#include "sys.h"

/* Macro --------------------------------------------------------*/

#define RX_CHANNEL_SINGLE				    (0x01)  //only enable single rx channel,default use channel 0
#define RX_CHANNEL_BOTH					    (0x02)  //enable both channel,use channel 0 and channel 1
#define ENABLE_RX_CHANNEL_NUM			    RX_CHANNEL_SINGLE

#define EORR_MODE_ACTIVE_BITS               (BB_RX_SW_MODE_36_BIT)

#define BB_SW_HIGH_1_BYTE                   (0x8E)
#define BB_SW_LOW_4_BYTE                    (0x89BED6AA)

#define BB_TX_PRE_MODE                      BB_TX_PRE_MODE_1_BYTE
#define BB_TX_AA_MODE                       BB_TX_AA_MODE_4_BYTE
#define BB_TX_PRE                           (0xAA)
#define BB_TX_AA_LOW_4_BYTE                 (0x8E89BED6)
#define BB_TX_AA_HIGH_1_BYTE                (0x00)

#define BB_CRC_RX_INT_COMBINED_CFG          (BB_CRC_WITHOUT_RX)     // BB_CRC_WITH_RX: CRC, RX interrupt raise together.
                                                                    // BB_CRC_WITHOUT_RX: CRC int raise without RX int.

#define BB_CRC_INTI_VAL                     (0x555555)
#define BB_WHIT_CTRL                        BB_WHIT_EN
#define BB_CRC_CTRL                         BB_CRC_EN
#define BB_WHIT_DSB                         (0x2000000)             // Disable whitening.
#define BB_WHIT_EN                          (0)                     // Enable whitening.
#define BB_CRC_DSB                          (0x1000000)             // Disable CRC24
#define BB_CRC_EN                           (0)                     // Enable CRC24

#define BB_RF_GFO_COMP                      (RF_GFO_DMX_COMP_EN | RF_GFO_DCC_COMP_EN)

#define BB_CHANNEL_0_PKG_LEN_MODE           BB_PACK_LEN_AUTO        // RX payload length got from package.
#define BB_CHANNEL_1_PKG_LEN_MODE           BB_PACK_LEN_AUTO        // RX payload length got from package.
#define BB_CHANNEL_0_PKG_LEN                (31)
#define BB_CHANNEL_1_PKG_LEN                (37)

#define BB_CHANNEL_NUMB                     (37)

#define BB_MEMEORY_ADDR                     (0x50000000)
#define BB_MEMEORY_SIZE                     (128)                   // 128 Bytes


/*****************************************************************
 * @registers
 */

#define BB_BASE_ADDR                        (0x40070000)

//----------------------------------------------------------------
// BB of grapes

/*
 * bb_soft_rst
 * @ 0x00
 */
#define BB_BB_SOFT_RST_REG                  (BB_BASE_ADDR + 0x00)
#define BB_BB_SOFT_RST_MASK                 (0x01)
#define BB_BB_SOFT_RST_SHIFT                (0)

/*
 * reg_tx_access_code_mode
 * @ 0x04
 */
#define BB_REG_TX_ACCESS_CODE_MODE_REG      (BB_BASE_ADDR + 0x04)
#define BB_CS_TXPREAMBLE_MODE_MASK          (0x030)
#define BB_CS_TXPREAMBLE_MODE_SHIFT         (4)
#define BB_CS_TXSYNCWORD_MODE_MASK          (0x03)
#define BB_CS_TXSYNCWORD_MODE_SHIFT         (0)

/*
 * reg_syncword_highpart
 * @ 0x08
 */
#define BB_REG_SYNCWORD_HIGHPART_REG        (BB_BASE_ADDR + 0x08)
#define BB_CS_SYNCWORD_LEFT4BYTES_MASK      (0xFFFFFFFF)
#define BB_CS_SYNCWORD_LEFT4BYTES_SHIFT     (0)

/*
 * reg_syncword_lowpart
 * @ 0x0C
 */
#define BB_REG_SYNCWORD_LOWPART_REG         (BB_BASE_ADDR + 0x0C)
#define BB_CS_SYNCWORD_RIGHT1BYTE_MASK      (0x0FF)
#define BB_CS_SYNCWORD_RIGHT1BYTE_SHIFT     (0)

/*
 * reg_preamble
 * @ 0x10
 */
#define BB_REG_PREAMBLE_REG                 (BB_BASE_ADDR + 0x10)
#define BB_CS_PREAMBLE_MASK                 (0x0FFFFFF)
#define BB_CS_PREAMBLE_SHIFT                (0)

/*
 * reg_crc_whit_dsb
 * @ 0x14
 */
#define BB_REG_CRC_WHIT_DSB_REG             (BB_BASE_ADDR + 0x14)
#define BB_WHIT_DSB_MASK                    (0x010)
#define BB_WHIT_DSB_SHIFT                   (4)
#define BB_CRC_DSB_MASK                     (0x01)
#define BB_CRC_DSB_SHIFT                    (0)

/*
 * reg_crc_init
 * @ 0x18
 */
#define BB_REG_CRC_INIT_REG                 (BB_BASE_ADDR + 0x18)
#define BB_CS_CRCINIT_MASK                  (0x0FFFFFF)
#define BB_CS_CRCINIT_SHIFT                 (0)

/*
 * reg_channel_num
 * @ 0x1C
 */
#define BB_REG_CHANNEL_NUM_REG              (BB_BASE_ADDR + 0x1C)
#define BB_DATA_CH_IDX_MASK                 (0x03F)
#define BB_DATA_CH_IDX_SHIFT                (0)

/*
 * reg_start_p
 * @ 0x20
 */
#define BB_REG_START_P_REG                  (BB_BASE_ADDR + 0x20)
#define BB_PKTCNTL_START_P_MASK             (0x01)
#define BB_PKTCNTL_START_P_SHIFT            (0)

/*
 * reg_tx_bit_invert
 * @ 0x24
 */
#define BB_REG_TX_BIT_INVERT_REG            (BB_BASE_ADDR + 0x24)
#define BB_TX_DATA_INVERT_MASK              (0x01)
#define BB_TX_DATA_INVERT_SHIFT             (0)

/*
 * reg_tx_test_work_on
 * @ 0x28
 */
#define BB_REG_TX_TEST_WORK_ON_REG          (BB_BASE_ADDR + 0x28)
#define BB_TX_TEST_WORK_ON_MASK             (0x01)
#define BB_TX_TEST_WORK_ON_SHIFT            (0)

/*
 * reg_tx_test_type
 * @ 0x2C
 */
#define BB_REG_TX_TEST_TYPE_REG             (BB_BASE_ADDR + 0x2C)
#define BB_TX_TEST_TYPE_MASK                (0x07)
#define BB_TX_TEST_TYPE_SHIFT               (0)

/*
 * reg_tx_header
 * @ 0x30
 */
#define BB_REG_TX_HEADER_REG                (BB_BASE_ADDR + 0x30)
#define BB_TX_TEST_RXADD_MASK               (0x010)
#define BB_TX_TEST_RXADD_SHIFT              (4)
#define BB_TX_TEST_TXADD_MASK               (0x01)
#define BB_TX_TEST_TXADD_SHIFT              (0)

/*
 * reg_tx_advlen_from_cpu
 * @ 0x34
 */
#define BB_REG_TX_ADVLEN_FROM_CPU_REG       (BB_BASE_ADDR + 0x34)
#define BB_TX_ADVLEN_MASK                   (0x03F)
#define BB_TX_ADVLEN_SHIFT                  (0)

/*
 * reg_baseband_state_rw6
 * @ 0x38
 */
#define BB_REG_BASEBAND_STATE_RW6_REG       (BB_BASE_ADDR + 0x38)
#define BB_TX_TEST_INFINITE_MASK            (0x01)
#define BB_TX_TEST_INFINITE_SHIFT           (0)

/*
 * reg_bypass_tx_header
 * @ 0x3C
 */
#define BB_REG_BYPASS_TX_HEADER_REG         (BB_BASE_ADDR + 0x3C)
#define BB_BYPASS_TX_HEADER_MASK            (0x01)
#define BB_BYPASS_TX_HEADER_SHIFT           (0)

/*
 * reg_pll_settling_time
 * @ 0x40
 */
#define BB_REG_PLL_SETTLING_TIME_REG        (BB_BASE_ADDR + 0x40)
#define BB_RF_PLL_SETTLING_TIME_MASK        (0x0FF)
#define BB_RF_PLL_SETTLING_TIME_SHIFT       (0)

/*
 * reg_rf_bb_set
 * @ 0x44
 */
#define BB_REG_RF_BB_SET_REG                (BB_BASE_ADDR + 0x44)
#define BB_RF_SET_BB_CTRL_MASK              (0x01)
#define BB_RF_SET_BB_CTRL_SHIFT             (0)

/*
 * reg_power_delay
 * @ 0x48
 */
#define BB_REG_POWER_DELAY_REG              (BB_BASE_ADDR + 0x48)
#define BB_TXPWRDN_MASK                     (0x0FF00)
#define BB_TXPWRDN_SHIFT                    (8)
#define BB_TXPWRUP_MASK                     (0x0FF)
#define BB_TXPWRUP_SHIFT                    (0)

/*
 * reg_soft_ctrl_bb
 * @ 0x4C
 */
#define BB_REG_SOFT_CTRL_BB_REG             (BB_BASE_ADDR + 0x4C)
#define BB_SOFT_EN_TRX_MASK                 (0x010)
#define BB_SOFT_EN_TRX_SHIFT                (4)
#define BB_SOFT_EN_PA_MASK                  (0x01)
#define BB_SOFT_EN_PA_SHIFT                 (0)

/*
 * reg_pll_digital
 * @ 0x50
 */
#define BB_REG_PLL_DIGITAL_REG              (BB_BASE_ADDR + 0x50)
#define BB_SEL_VC_CLK_MASK                  (0x01F0000)
#define BB_SEL_VC_CLK_SHIFT                 (16)
#define BB_DT_DAC_MASK                      (0x07000)
#define BB_DT_DAC_SHIFT                     (12)
#define BB_DT_DIV_MASK                      (0x0700)
#define BB_DT_DIV_SHIFT                     (8)
#define BB_MODE_2M_MASK                     (0x01)
#define BB_MODE_2M_SHIFT                    (0)

/*
 * reg_byp_gfilter
 * @ 0x54
 */
#define BB_REG_BYP_GFILTER_REG              (BB_BASE_ADDR + 0x54)
#define BB_BYP_GFILTER_MASK                 (0x01)
#define BB_BYP_GFILTER_SHIFT                (0)

/*
 * reg_gdata_ext
 * @ 0x58
 */
#define BB_REG_GDATA_EXT_REG                (BB_BASE_ADDR + 0x58)
#define BB_GDATA_EXT_MASK                   (0x0FF)
#define BB_GDATA_EXT_SHIFT                  (0)

/*
 * reg2ctrl_buf_wfin
 * @ 0x5C
 */
#define BB_REG2CTRL_BUF_WFIN_REG            (BB_BASE_ADDR + 0x5C)
#define BB_REG2CTRL_BUF_WFIN_MASK           (0x01)
#define BB_REG2CTRL_BUF_WFIN_SHIFT          (0)

/*
 * reg_interrupt_ctrl
 * @ 0x60
 */
#define BB_REG_INTERRUPT_CTRL_REG           (BB_BASE_ADDR + 0x60)
#define BB_REG2CTRL_TX_INT_MASK_MASK        (0x010)
#define BB_REG2CTRL_TX_INT_MASK_SHIFT       (4)
#define BB_REG2CTRL_TX_INT_EN_MASK          (0x01)
#define BB_REG2CTRL_TX_INT_EN_SHIFT         (0)

/*
 * reg interrupt
 * @ 0x64
 */
#define BB_REG_INTERRUPT_REG                (BB_BASE_ADDR + 0x64)
#define BB_CTRL2REG_TX_RAW_INT_STATE_MASK   (0x01)
#define BB_CTRL2REG_TX_RAW_INT_STATE_SHIFT  (0)

/*
 * ctrl2reg buf_flag
 * @ 0x68
 */
#define BB_CTRL2REG_BUF_FLAG_REG            (BB_BASE_ADDR + 0x68)
#define BB_CTRL2REG_BUF_FULL_MASK           (0x01)
#define BB_CTRL2REG_BUF_FULL_SHIFT          (0)

/*
 * bbram_debug_infor
 * @ 0x6C
 */
#define BB_BBRAM_DEBUG_INFOR_REG            (BB_BASE_ADDR + 0x6C)
#define BB_CTRL2REG_DEB_INFO_MASK           (0xFFFFFFFF)
#define BB_CTRL2REG_DEB_INFO_SHIFT          (0)

/*
 * reg_tx_int_clear
 * @ 0x70
 */
#define BB_REG_TX_INT_CLEAR_REG             (BB_BASE_ADDR + 0x70)
#define BB_REG2CTRL_TX_INT_CLS_MASK         (0x01)
#define BB_REG2CTRL_TX_INT_CLS_SHIFT        (0)

/*
 * reg_bbram_state_clear
 * @ 0x74
 */
#define BB_REG_BBRAM_STATE_CLEAR_REG        (BB_BASE_ADDR + 0x74)
#define BB_REG2CTRL_STA_CLS_MASK            (0x01)
#define BB_REG2CTRL_STA_CLS_SHIFT           (0)

/*
 * reg_diag_cntl
 * @ 0x78
 */
#define BB_REG_DIAG_CNTL_REG                (BB_BASE_ADDR + 0x78)
#define BB_DIAG_CNTL_MASK                   (0x01)
#define BB_DIAG_CNTL_SHIFT                  (0)

// BB of apple end.
//----------------------------------------------------------------



/* Structures --------------------------------------------------*/

typedef enum bb_crc_rx_int_e
{
    BB_CRC_WITH_RX          = 0,
    BB_CRC_WITHOUT_RX       = 1
}bb_crc_rx_int_t;

typedef enum bb_tx_pre_mode_s
{
    BB_TX_PRE_MODE_1_BYTE   = 0,
    BB_TX_PRE_MODE_2_BYTE   = 1,
    BB_TX_PRE_MODE_3_BYTE   = 2
}bb_tx_pre_mode_t;

typedef enum bb_tx_aa_mode_s
{
    BB_TX_AA_MODE_3_BYTE    = 0,
    BB_TX_AA_MODE_4_BYTE    = 1,
    BB_TX_AA_MODE_5_BYTE    = 2
}bb_tx_aa_mode_t;

typedef enum tx_preamble_mode_s
{
    TX_PRE_MODE_1_BYTE   = 0,
    TX_PRE_MODE_2_BYTE   = 1,
    TX_PRE_MODE_3_BYTE   = 2
}tx_preamble_mode_t;
typedef enum tx_syncword_mode_s
{
    TX_AA_MODE_3_BYTE    = 0,
    TX_AA_MODE_4_BYTE    = 1,
    TX_AA_MODE_5_BYTE    = 2
}tx_syncword_mode_t;

typedef enum bb_pack_len_mode_s
{
    BB_PACK_LEN_AUTO        = 0,
    BB_PACK_LEN_MANUAL      = 1
}bb_pack_len_mode_t;

enum bb_channel_sel
{
    BB_CHANNEL_0_ONLY       = 0,
    BB_CHANNEL_0_1          = 1
};

typedef enum bb_ram_model
{
    BBRAM_MODEL_FIFO        = 0,
    BBRAM_MOBEL_SINGLE_RAM  = 2
} bb_ram_model_t;

typedef enum bb_channel
{
    BB_CHANNEL_0            = 1,
    BB_CHANNEL_1            = 2
} bb_channel_t;

typedef enum bb_rx_syncword_mode_e
{
    BB_RX_SW_MODE_32_BIT    = 0,
    BB_RX_SW_MODE_36_BIT    = 1,
    BB_RX_SW_MODE_40_BIT    = 2
}bb_rx_syncword_mode_t;

typedef enum bbram_mode
{
    BBRAM_FIFO_RX           = 0,
    BBRAM_FIFO_TX           = 1,
    BBRAM_SINGLE_RAM_RX     = 2,
    BBRAM_SINGLE_RAM_TX     = 3,
    BBRAM_FIFO_TXRX         = 4     // RX: use buffer0 (0-63). TX: use buffer1 (64_127).
} bbram_mode_t;

typedef enum rx_tx_mode
{
    RF_TX_MODE              = 0,
    RF_RX_MODE              = 1
} rx_tx_mode_t;

typedef enum rf_gfo_comp
{
    RF_GFO_COMP_DISABLE     = 0,
    RF_GFO_DMX_COMP_EN      = 1,
    RF_GFO_DCC_COMP_EN      = 2
} rf_gfo_comp_t;



typedef enum rf_test_message_form
{
    MESSAGE_FORM_PRBS9      =0,
    MESSAGE_FORM_0xF0       =1,
    MESSAGE_FORM_0xAA       =2,
    MESSAGE_FORM_PRBS15     =3,
    MESSAGE_FORM_ALL1       =4,
    MESSAGE_FORM_ALL0       =5,
    MESSAGE_FORM_0x0F       =6,
    MESSAGE_FORM_0x55       =7
}rf_test_message_form_t;


#define rf_soft_reset()                 write_reg(BB_BASE_ADDR, 0x1)
#define rf_write_finish()               write_reg(BB_REG2CTRL_BUF_WFIN_REG, 0x1)
#define rf_get_int()                    ( BB_CTRL2REG_TX_RAW_INT_STATE_MASK & read_reg(BB_REG_INTERRUPT_REG) )


/* Function prototype -------------------------------------------*/

/**
 * @brief  Init the function of RF.
 */
void rf_init(void);

/**
 * @brief  The length of Tx packets, PDU length if send BLE packets.
 * @param  tx_len                     the setting of length.
 */
void rf_set_tx_len(uint8_t tx_len);

/**
 * @brief  Config the channel number of RF.
 * @param  channel_num                channel number, 37/38/39/...
 */
void rf_set_channel_num(uint8_t channel_num);

/**
 * @brief  Config RF power level
 * @param  rf_power                   0~7
 */
void rf_set_power(uint8_t rf_power);

/**
 * @brief  Enable/Disable CRC and Whitening.
 * @param  whiting_ctrl               ON/OFF.
 * @param  crc_ctrl                   ON/OFF.
 */
void rf_set_whit_and_crc(bool whiting_ctrl, bool crc_ctrl);

/**
 * @brief  Config Tx access address, send by LSB of [aa_high+aa_low] 
 * @param  aa_mode                    @ref bb_tx_aa_mode_t "access address mode"
 * @param  aa_high                    High-byte of access address. 0 if send BLE packets.
 * @param  aa_low                     Low-byte of access address.
 */
void rf_set_tx_aa( bb_tx_aa_mode_t aa_mode, uint8_t aa_high, uint32_t aa_low );

/**
 * @brief  Config Tx premble.
 * @param  pre_mode                   @ref bb_tx_pre_mode_t "preamble mode"
 * @param  pre                        the value of preamble.
 */
void rf_set_tx_preamble( bb_tx_pre_mode_t pre_mode, uint32_t pre );

/**
 * @brief  set tx test mode.
 * @param  test_mode                     	1:work on test mode.
 											0:work normally.
 */
void rf_set_test_mode(bool test_mode);

/**
 * @brief  work on test mode and set tx type.
 * @param     message_form                 @rf_test_message_form_t "set message type".										
 */
void rf_set_test_message_form(rf_test_message_form_t   message_form);

/**
 * @brief  Get the status of RF interrupt.
 * @return uint8_t                    @ref int status "user guide: reg_interrupt_RO".
 */
uint8_t rf_get_int_status();

/**
 * @brief  Start the function of RF, refer to MODULE_TEST for use.
 */
void rf_start();



uint8_t rf_get_buffer_status();
void rf_int_clear( uint32_t int_clear );
void rf_set_tx_pattern();
void rf_set_bb_mode( rf_bb_mode_t rf_bb_mode);

#endif  // __RF_H_

