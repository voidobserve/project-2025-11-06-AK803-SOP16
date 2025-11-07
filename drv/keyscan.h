#ifndef __KEYSCAN_H_
#define __KEYSCAN_H_



#define KEYSCAN_BASE_ADDR                        (0x040120100)
/*
 * top_ctrl_reg
 * @ 0x00
 */
#define KEYSCAN_TOP_CTRL_REG_REG                 (KEYSCAN_BASE_ADDR + 0x00)
#define IO_LOW_POWER_MODE                        (0x08)
#define IO_LOW_POWER_MODE_SHIFT                  (3)
#define KEYSCAN_KEY_SCAN_PWR_CTRL_EN_MASK        (0x04)
#define KEYSCAN_KEY_SCAN_PWR_CTRL_EN_SHIFT       (2)
#define KEYSCAN_LVD_PWR_CTRL_EN_MASK             (0x02)
#define KEYSCAN_LVD_PWR_CTRL_EN_SHIFT            (1)
#define KEYSCAN_PMU_CTRL_ENABLE_MASK             (0x01)
#define KEYSCAN_PMU_CTRL_ENABLE_SHIFT            (0)

/*
 * power_ctrl_reg
 * @ 0x04
 */
#define KEYSCAN_POWER_CTRL_REG_REG               (KEYSCAN_BASE_ADDR + 0x04)
#define KEYSCAN_CPU_POWER_DOWN_MASK              (0x01)
#define KEYSCAN_CPU_POWER_DOWN_SHIFT             (0)

/*
 * top_soft_reset_1
 * @ 0x0C
 */
#define KEYSCAN_TOP_SOFT_RESET_1_REG             (KEYSCAN_BASE_ADDR + 0x0C)
#define KEYSCAN_KEYSCAN_SOFT_RST_MASK          (0x02)
#define KEYSCAN_KEYSCAN_SOFT_RST_SHIFT         (1)
#define KEYSCAN_WDG_SOFT_RST_MASK           (0x01)
#define KEYSCAN_WDG_SOFT_RST_SHIFT          (0)

/*
 * top_soft_reset_2
 * @ 0x10
 */
#define KEYSCAN_TOP_SOFT_RESET_2_REG             (KEYSCAN_BASE_ADDR + 0x10)
#define KEYSCAN_WT_SOFT_RST_MASK           (0x01)
#define KEYSCAN_WT_SOFT_RST_SHIFT          (0)

/*
 * keyscan_state
 * @ 0x14
 */
#define KEYSCAN_KEYSCAN_STATE_REG                (KEYSCAN_BASE_ADDR + 0x14)
#define KEYSCAN_KSCAN_AREA_MASK					 (0X0C)
#define KEYSCAN_KSCAN_AREA_SHIFT				 (2)
#define KEYSCAN_KSCAN_BOTTON_NUM_MASK            (0x02)
#define KEYSCAN_KSCAN_BOTTON_NUM_SHIFT           (1)
#define KEYSCAN_KSCAN_RAW_INT_MASK              (0x01)
#define KEYSCAN_KSCAN_RAW_INT_SHIFT             (0)

/*
 * pmu_reg_ll
 * @ 0x18
 */
#define KEYSCAN_PMU_REG_LL_REG                   (KEYSCAN_BASE_ADDR + 0x18)
#define KEYSCAN_PMU_REG_ULL_LL_MASK              (0x0FF)
#define KEYSCAN_PMU_REG_ULL_LL_SHIFT             (0)

/*
 * pmu_reg_ml
 * @ 0x1C
 */
#define KEYSCAN_PMU_REG_ML_REG                   (KEYSCAN_BASE_ADDR + 0x1C)
#define KEYSCAN_PMU_REG_ULL_ML_MASK              (0x0FF)
#define KEYSCAN_PMU_REG_ULL_ML_SHIFT             (0)

/*
 * pmu_reg_mh
 * @ 0x20
 */
#define KEYSCAN_PMU_REG_MH_REG                   (KEYSCAN_BASE_ADDR + 0x20)
#define KEYSCAN_PMU_REG_ULL_MH_MASK              (0x0FF)
#define KEYSCAN_PMU_REG_ULL_MH_SHIFT             (0)

/*
 * pmu_reg_hh
 * @ 0x24
 */
#define KEYSCAN_PMU_REG_HH_REG                   (KEYSCAN_BASE_ADDR + 0x24)
#define KEYSCAN_PMU_REG_ULL_HH_MASK              (0x0FF)
#define KEYSCAN_PMU_REG_ULL_HH_SHIFT             (0)

/*
 * anlog_reg_ll
 * @ 0x28
 */
#define KEYSCAN_ANLOG_REG_LL_REG                 (KEYSCAN_BASE_ADDR + 0x28)
#define KEYSCAN_ANA_REG_ULL_LL_MASK              (0x0FF)
#define KEYSCAN_ANA_REG_ULL_LL_SHIFT             (0)

/*
 * anlog_reg_ml
 * @ 0x2C
 */
#define KEYSCAN_ANLOG_REG_ML_REG                 (KEYSCAN_BASE_ADDR + 0x2C)
#define KEYSCAN_ANA_REG_ULL_ML_MASK              (0x0FF)
#define KEYSCAN_ANA_REG_ULL_ML_SHIFT             (0)

/*
 * pll_digital_gain_dac_delta_01
 * @ 0x38
 */
#define KEYSCAN_PLL_DIGITAL_GAIN_DAC_DELTA_01_REG (KEYSCAN_BASE_ADDR + 0x38)
#define KEYSCAN_GAIN_DAC_DELTA0_MASK             (0x0F0)
#define KEYSCAN_GAIN_DAC_DELTA0_SHIFT            (4)
#define KEYSCAN_GAIN_DAC_DELTA1_MASK             (0x0F)
#define KEYSCAN_GAIN_DAC_DELTA1_SHIFT            (0)

/*
 * pll_digital_gain_dac_delta_23
 * @ 0x3C
 */
#define KEYSCAN_PLL_DIGITAL_GAIN_DAC_DELTA_23_REG (KEYSCAN_BASE_ADDR + 0x3C)
#define KEYSCAN_GAIN_DAC_DELTA2_MASK             (0x0F0)
#define KEYSCAN_GAIN_DAC_DELTA2_SHIFT            (4)
#define KEYSCAN_GAIN_DAC_DELTA3_MASK             (0x0F)
#define KEYSCAN_GAIN_DAC_DELTA3_SHIFT            (0)

/*
 * pll_digital_gain_dac_delta_45
 * @ 0x40
 */
#define KEYSCAN_PLL_DIGITAL_GAIN_DAC_DELTA_45_REG (KEYSCAN_BASE_ADDR + 0x40)
#define KEYSCAN_GAIN_DAC_DELTA4_MASK             (0x0F0)
#define KEYSCAN_GAIN_DAC_DELTA4_SHIFT            (4)
#define KEYSCAN_GAIN_DAC_DELTA5_MASK             (0x0F)
#define KEYSCAN_GAIN_DAC_DELTA5_SHIFT            (0)

/*
 * pll_digital_gain_dac_delta_67
 * @ 0x44
 */
#define KEYSCAN_PLL_DIGITAL_GAIN_DAC_DELTA_67_REG (KEYSCAN_BASE_ADDR + 0x44)
#define KEYSCAN_GAIN_DAC_DELTA6_MASK             (0x0F0)
#define KEYSCAN_GAIN_DAC_DELTA6_SHIFT            (4)
#define KEYSCAN_GAIN_DAC_DELTA7_MASK             (0x0F)
#define KEYSCAN_GAIN_DAC_DELTA7_SHIFT            (0)

/*
 * pll_digital_gain_dac_ini
 * @ 0x48
 */
#define KEYSCAN_PLL_DIGITAL_GAIN_DAC_INI_REG     (KEYSCAN_BASE_ADDR + 0x48)
#define KEYSCAN_GAIN_DAC_INI_MASK                (0x07F)
#define KEYSCAN_GAIN_DAC_INI_SHIFT               (0)

/*
 * pll_digital_fvco_delta_01
 * @ 0x4C
 */
#define KEYSCAN_PLL_DIGITAL_FVCO_DELTA_01_REG    (KEYSCAN_BASE_ADDR + 0x4C)
#define KEYSCAN_FVCO_DELTA0_MASK                 (0x0F0)
#define KEYSCAN_FVCO_DELTA0_SHIFT                (4)
#define KEYSCAN_FVCO_DELTA1_MASK                 (0x0F)
#define KEYSCAN_FVCO_DELTA1_SHIFT                (0)

/*
 * pll_digital_fvco_delta_23
 * @ 0x50
 */
#define KEYSCAN_PLL_DIGITAL_FVCO_DELTA_23_REG    (KEYSCAN_BASE_ADDR + 0x50)
#define KEYSCAN_FVCO_DELTA2_MASK                 (0x0F0)
#define KEYSCAN_FVCO_DELTA2_SHIFT                (4)
#define KEYSCAN_FVCO_DELTA3_MASK                 (0x0F)
#define KEYSCAN_FVCO_DELTA3_SHIFT                (0)

/*
 * pll_digital_fvco_delta_45
 * @ 0x54
 */
#define KEYSCAN_PLL_DIGITAL_FVCO_DELTA_45_REG    (KEYSCAN_BASE_ADDR + 0x54)
#define KEYSCAN_FVCO_DELTA4_MASK                 (0x0F0)
#define KEYSCAN_FVCO_DELTA4_SHIFT                (4)
#define KEYSCAN_FVCO_DELTA5_MASK                 (0x0F)
#define KEYSCAN_FVCO_DELTA5_SHIFT                (0)

/*
 * pll_digital_fvco_delta_67
 * @ 0x58
 */
#define KEYSCAN_PLL_DIGITAL_FVCO_DELTA_67_REG    (KEYSCAN_BASE_ADDR + 0x58)
#define KEYSCAN_FVCO_DELTA6_MASK                 (0x0F0)
#define KEYSCAN_FVCO_DELTA6_SHIFT                (4)
#define KEYSCAN_FVCO_DELTA7_MASK                 (0x0F)
#define KEYSCAN_FVCO_DELTA7_SHIFT                (0)

/*
 * pll_digital_fvco_ini
 * @ 0x5C
 */
#define KEYSCAN_PLL_DIGITAL_FVCO_INI_REG         (KEYSCAN_BASE_ADDR + 0x5C)
#define KEYSCAN_FVCO_INI_MASK                    (0x03F)
#define KEYSCAN_FVCO_INI_SHIFT                   (0)

/*
 * watchdog_comp_value_h
 * @ 0x64
 */
#define KEYSCAN_WATCHDOG_COMP_VALUE_H_REG        (KEYSCAN_BASE_ADDR + 0x64)
#define KEYSCAN_WDG_COMP_VAL_H_MASK              (0x0FF)
#define KEYSCAN_WDG_COMP_VAL_H_SHIFT             (0)

/*
 * watchdog_comp_value_m
 * @ 0x68
 */
#define KEYSCAN_WATCHDOG_COMP_VALUE_M_REG        (KEYSCAN_BASE_ADDR + 0x68)
#define KEYSCAN_WDG_COMP_VAL_M_MASK              (0x0FF)
#define KEYSCAN_WDG_COMP_VAL_M_SHIFT             (0)

/*
 * watchdog_comp_value_l
 * @ 0x6c
 */
#define KEYSCAN_WATCHDOG_COMP_VALUE_L_REG        (KEYSCAN_BASE_ADDR + 0x6c)
#define KEYSCAN_WDG_COMP_VAL_L_MASK              (0x0FF)
#define KEYSCAN_WDG_COMP_VAL_L_SHIFT             (0)

/*
 * watchdog_comp_vld
 * @ 0x70
 */
#define KEYSCAN_WATCHDOG_COMP_VLD_REG            (KEYSCAN_BASE_ADDR + 0x70)
#define KEYSCAN_WDG_COMP_VLD_MASK                (0x01)
#define KEYSCAN_WDG_COMP_VLD_SHIFT               (0)

/*
 * watchdog_feed_dog
 * @ 0x74
 */
#define KEYSCAN_WATCHDOG_FEED_DOG_REG            (KEYSCAN_BASE_ADDR + 0x74)
#define KEYSCAN_WDG_FEED_MASK                    (0x01)
#define KEYSCAN_WDG_FEED_SHIFT                   (0)

/*
 * watchdog_interrupt_clear
 * @ 0x78
 */
#define KEYSCAN_WATCHDOG_INTERRUPT_CLEAR_REG     (KEYSCAN_BASE_ADDR + 0x78)
#define KEYSCAN_WDG_INT_CLR_MASK                 (0x01)
#define KEYSCAN_WDG_INT_CLR_SHIFT                (0)

/*
 * watchdog_counter_value_h
 * @ 0x7c
 */
#define KEYSCAN_WATCHDOG_COUNTER_VALUE_H_REG     (KEYSCAN_BASE_ADDR + 0x7c)
#define KEYSCAN_WDG_COUNTER_VAL_H_MASK           (0x0FF)
#define KEYSCAN_WDG_COUNTER_VAL_H_SHIFT          (0)

/*
 * watchdog_counter_value_m
 * @ 0x80
 */
#define KEYSCAN_WATCHDOG_COUNTER_VALUE_M_REG     (KEYSCAN_BASE_ADDR + 0x80)
#define KEYSCAN_WDG_COUNTER_VAL_M_MASK           (0x0FF)
#define KEYSCAN_WDG_COUNTER_VAL_M_SHIFT          (0)

/*
 * watchdog_counter_value_l
 * @ 0x84
 */
#define KEYSCAN_WATCHDOG_COUNTER_VALUE_L_REG     (KEYSCAN_BASE_ADDR + 0x84)
#define KEYSCAN_WDG_COUNTER_VAL_L_MASK           (0x0FF)
#define KEYSCAN_WDG_COUNTER_VAL_L_SHIFT          (0)

/*
 * watchdog_state
 * @ 0x88
 */
#define KEYSCAN_WATCHDOG_STATE_REG               (KEYSCAN_BASE_ADDR + 0x88)
#define KEYSCAN_WDG_FLAG_MASK                    (0x010)
#define KEYSCAN_WDG_FLAG_SHIFT                   (4)
#define KEYSCAN_WDG_INT_MASK                     (0x08)
#define KEYSCAN_WDG_INT_SHIFT                    (3)
#define KEYSCAN_WDG_INT_EN_MASK                  (0x04)
#define KEYSCAN_WDG_INT_EN_SHIFT                 (2)
#define KEYSCAN_WDG_FSM_VAL_MASK                 (0x03)
#define KEYSCAN_WDG_FSM_VAL_SHIFT                (0)

/*
 * module_mode
 * @ 0x8C
 */
#define KEYSCAN_MODULE_MODE_REG                  (KEYSCAN_BASE_ADDR + 0x8C)
#define KEYSCAN_KEY_SCAN_EN_MASK                 (0x040)
#define KEYSCAN_KEY_SCAN_EN_SHIFT                (6)
#define KEYSCAN_EN_LVD_ULL_MASK                  (0x020)
#define KEYSCAN_EN_LVD_ULL_SHIFT                 (5)
#define KEYSCAN_CPU_CLK_SEL_MASK                 (0x018)
#define KEYSCAN_CPU_CLK_SEL_SHIFT                (3)
#define KEYSCAN_WATCH_DOG_EN_MASK                (0x04)
#define KEYSCAN_WATCH_DOG_EN_SHIFT               (2)
#define KEYSCAN_RF_KEYSCAN_MODE_MASK             (0x03)
#define KEYSCAN_RF_KEYSCAN_MODE_SHIFT            (0)

/*
 * wakeup_source
 * @ 0x90
 */
#define KEYSCAN_WAKEUP_SOURCE_REG                (KEYSCAN_BASE_ADDR + 0x90)
#define KEYSCAN_WAKEUP_SOURCE_MASK               (0x08)
#define KEYSCAN_WAKEUP_SOURCE_SHIFT              (3)
/*
 * aon_dbg_info_sel
 * @ 0x94
 */
#define KEYSCAN_AON_DBG_INFO_SEL_REG             (KEYSCAN_BASE_ADDR + 0x94)
#define KEYSCAN_CORE2AON_DBG_INV_EN_MASK         (0x010)
#define KEYSCAN_CORE2AON_DBG_INV_EN_SHIFT        (4)
#define KEYSCAN_AON_DBG_INFO_SEL_MASK            (0x0F)
#define KEYSCAN_AON_DBG_INFO_SEL_SHIFT           (0)

/*
 * retention_mem_space_00
 * @ 0xA0
 */
#define KEYSCAN_RETENTION_MEM_SPACE_00_REG       (KEYSCAN_BASE_ADDR + 0xA0)
#define KEYSCAN_RETEN_MEM_SPACE_00_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_00_SHIFT         (0)

/*
 * retention_mem_space_01
 * @ 0xA4
 */
#define KEYSCAN_RETENTION_MEM_SPACE_01_REG       (KEYSCAN_BASE_ADDR + 0xA4)
#define KEYSCAN_RETEN_MEM_SPACE_01_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_01_SHIFT         (0)

/*
 * retention_mem_space_02
 * @ 0xA8
 */
#define KEYSCAN_RETENTION_MEM_SPACE_02_REG       (KEYSCAN_BASE_ADDR + 0xA8)
#define KEYSCAN_RETEN_MEM_SPACE_02_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_02_SHIFT         (0)

/*
 * retention_mem_space_03
 * @ 0xAC
 */
#define KEYSCAN_RETENTION_MEM_SPACE_03_REG       (KEYSCAN_BASE_ADDR + 0xAC)
#define KEYSCAN_RETEN_MEM_SPACE_03_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_03_SHIFT         (0)

/*
 * retention_mem_space_04
 * @ 0xB0
 */
#define KEYSCAN_RETENTION_MEM_SPACE_04_REG       (KEYSCAN_BASE_ADDR + 0xB0)
#define KEYSCAN_RETEN_MEM_SPACE_04_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_04_SHIFT         (0)

/*
 * retention_mem_space_05
 * @ 0xB4
 */
#define KEYSCAN_RETENTION_MEM_SPACE_05_REG       (KEYSCAN_BASE_ADDR + 0xB4)
#define KEYSCAN_RETEN_MEM_SPACE_05_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_05_SHIFT         (0)

/*
 * retention_mem_space_06
 * @ 0xB8
 */
#define KEYSCAN_RETENTION_MEM_SPACE_06_REG       (KEYSCAN_BASE_ADDR + 0xB8)
#define KEYSCAN_RETEN_MEM_SPACE_06_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_06_SHIFT         (0)

/*
 * retention_mem_space_07
 * @ 0xBC
 */
#define KEYSCAN_RETENTION_MEM_SPACE_07_REG       (KEYSCAN_BASE_ADDR + 0xBC)
#define KEYSCAN_RETEN_MEM_SPACE_07_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_07_SHIFT         (0)

/*
 * retention_mem_space_08
 * @ 0xC0
 */
#define KEYSCAN_RETENTION_MEM_SPACE_08_REG       (KEYSCAN_BASE_ADDR + 0xC0)
#define KEYSCAN_RETEN_MEM_SPACE_08_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_08_SHIFT         (0)

/*
 * retention_mem_space_09
 * @ 0xC4
 */
#define KEYSCAN_RETENTION_MEM_SPACE_09_REG       (KEYSCAN_BASE_ADDR + 0xC4)
#define KEYSCAN_RETEN_MEM_SPACE_09_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_09_SHIFT         (0)

/*
 * retention_mem_space_10
 * @ 0xC8
 */
#define KEYSCAN_RETENTION_MEM_SPACE_10_REG       (KEYSCAN_BASE_ADDR + 0xC8)
#define KEYSCAN_RETEN_MEM_SPACE_10_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_10_SHIFT         (0)

/*
 * retention_mem_space_11
 * @ 0xCC
 */
#define KEYSCAN_RETENTION_MEM_SPACE_11_REG       (KEYSCAN_BASE_ADDR + 0xCC)
#define KEYSCAN_RETEN_MEM_SPACE_11_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_11_SHIFT         (0)

/*
 * retention_mem_space_12
 * @ 0xD0
 */
#define KEYSCAN_RETENTION_MEM_SPACE_12_REG       (KEYSCAN_BASE_ADDR + 0xD0)
#define KEYSCAN_RETEN_MEM_SPACE_12_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_12_SHIFT         (0)

/*
 * retention_mem_space_13
 * @ 0xD4
 */
#define KEYSCAN_RETENTION_MEM_SPACE_13_REG       (KEYSCAN_BASE_ADDR + 0xD4)
#define KEYSCAN_RETEN_MEM_SPACE_13_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_13_SHIFT         (0)

/*
 * retention_mem_space_14
 * @ 0xD8
 */
#define KEYSCAN_RETENTION_MEM_SPACE_14_REG       (KEYSCAN_BASE_ADDR + 0xD8)
#define KEYSCAN_RETEN_MEM_SPACE_14_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_14_SHIFT         (0)

/*
 * retention_mem_space_15
 * @ 0xDC
 */
#define KEYSCAN_RETENTION_MEM_SPACE_15_REG       (KEYSCAN_BASE_ADDR + 0xDC)
#define KEYSCAN_RETEN_MEM_SPACE_15_MASK          (0x0FF)
#define KEYSCAN_RETEN_MEM_SPACE_15_SHIFT         (0)

/*
 * key_scan_cfg
 * @ 0xE0
 */
#define KEYSCAN_KEY_SCAN_CFG_REG                 (KEYSCAN_BASE_ADDR + 0xE0)
#define KEYSCAN_KEY_PWIDEN_MASK                  (0x040)
#define KEYSCAN_KEY_PWIDEN_SHIFT                 (6)
#define KEYSCAN_KSCAN_IO_POL_MASK                (0x020)
#define KEYSCAN_KSCAN_IO_POL_SHIFT               (5)
#define KEYSCAN_KSCAN_FREQ_MASK                  (0x018)
#define KEYSCAN_KSCAN_FREQ_SHIFT                 (3)
#define KEYSCAN_KSCAN_MODE_MASK                  (0x07)
#define KEYSCAN_KSCAN_MODE_SHIFT                 (0)
//#define KEYSCAN_AREA1							 (1)
//#define KEYSCAN_AREA2							 (2)
//#define KEYSCAN_AREA3							 (4)
/*
 * key_scan_cycle
 * @ 0xE4
 */
#define KEYSCAN_KEY_SCAN_CYCLE_REG               (KEYSCAN_BASE_ADDR + 0xE4)
#define KEYSCAN_KSCAN_CYCLES_MASK                (0x0FF)
#define KEYSCAN_KSCAN_CYCLES_SHIFT               (0)

/*
 * kscan_io_valid_h
 * @ 0xE8
 */
#define KEYSCAN_KSCAN_IO_VALID_H_REG             (KEYSCAN_BASE_ADDR + 0xE8)
#define KEYSCAN_KSCAN_IO_VALID_H_MASK            (0x07)
#define KEYSCAN_KSCAN_IO_VALID_H_SHIFT           (0)

/*
 * kscan_io_valid_l
 * @ 0xEC
 */
#define KEYSCAN_KSCAN_IO_VALID_L_REG             (KEYSCAN_BASE_ADDR + 0xEC)
#define KEYSCAN_KSCAN_IO_VALID_L_MASK            (0x0FF)
#define KEYSCAN_KSCAN_IO_VALID_L_SHIFT           (0)

/*
 * kscan_ctrl
 * @ 0xF0
 */
#define KEYSCAN_KSCAN_CTRL_REG                   (KEYSCAN_BASE_ADDR + 0xF0)
#define KEYSCAN_KSCAN_INT_CLEAR_MASK             (0x02)
#define KEYSCAN_KSCAN_INT_CLEAR_SHIFT            (1)
#define KEYSCAN_KSCAN_START_MASK                 (0x01)
#define KEYSCAN_KSCAN_START_SHIFT                (0)

/*
 * kscan_int_cfg
 * @ 0xF4
 */
#define KEYSCAN_KSCAN_INT_CFG_REG                (KEYSCAN_BASE_ADDR + 0xF4)
#define KEYSCAN_KSCAN_INT_MASK_MASK              (0x02)
#define KEYSCAN_KSCAN_INT_MASK_SHIFT             (1)
#define KEYSCAN_KSCAN_INT_ENABLE_MASK            (0x01)
#define KEYSCAN_KSCAN_INT_ENABLE_SHIFT           (0)

/*
 * kscan_val0
 * @ 0x10
 */
#define KEYSCAN_KSCAN_VAL0_REG                   (KEYSCAN_BASE_ADDR + 0x10)
#define KEYSCAN_KSCAN_VAL0_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL0_SHIFT                 (0)

/*
 * kscan_val1
 * @ 0x30
 */
#define KEYSCAN_KSCAN_VAL1_REG                   (KEYSCAN_BASE_ADDR + 0x30)
#define KEYSCAN_KSCAN_VAL1_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL1_SHIFT                 (0)

/*
 * kscan_val2
 * @ 0x34
 */
#define KEYSCAN_KSCAN_VAL2_REG                   (KEYSCAN_BASE_ADDR + 0x34)
#define KEYSCAN_KSCAN_VAL2_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL2_SHIFT                 (0)

/*
 * kscan_val3
 * @ 0x74
 */
#define KEYSCAN_KSCAN_VAL3_REG                   (KEYSCAN_BASE_ADDR + 0x74)
#define KEYSCAN_KSCAN_VAL3_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL3_SHIFT                 (0)

/*
 * kscan_val4
 * @ 0x78
 */
#define KEYSCAN_KSCAN_VAL4_REG                   (KEYSCAN_BASE_ADDR + 0x78)
#define KEYSCAN_KSCAN_VAL4_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL4_SHIFT                 (0)

/*
 * kscan_val5
 * @ 0xF8
 */
#define KEYSCAN_KSCAN_VAL5_REG                   (KEYSCAN_BASE_ADDR + 0xF8)
#define KEYSCAN_KSCAN_VAL5_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL5_SHIFT                 (0)

/*
 * kscan_val6
 * @ 0xFC
 */
#define KEYSCAN_KSCAN_VAL6_REG                   (KEYSCAN_BASE_ADDR + 0xFC)
#define KEYSCAN_KSCAN_VAL6_MASK                  (0x0FF)
#define KEYSCAN_KSCAN_VAL6_SHIFT                 (0)


typedef enum keyscan_area_type
{
    KEYSCAN_AREA1       =0x1,
    KEYSCAN_AREA2       =0x2,
    KEYSCAN_AREA3       =0x4,
    KEYSCAN_AREA_ALL    =0x7
}keyscan_area_t;

typedef enum keyscan_frquency_type
{
    KEYSCAN_FRQ_32K =0x0,
    KEYSCAN_FRQ_16K =0x1,   
    KEYSCAN_FRQ_8K  =0x2, 
    KEYSCAN_FRQ_4K  =0x3

}keyscan_frquency_t;


typedef enum keyscan_area_scan_time
{
    KEYSCAN_UNEQUAL  =0x0,
    KEYSCAN_EQUILONG =0x1
}keyscan_area_scan_t;
void keyscan_clear_int(void);
void keyscan_start(void);
void keyscan_int_enable(void);
void keyscan_int_disable(void);
void keyscan_enable(void);
void keyscan_disable(void);
void keyscan_set_pwiden(keyscan_area_scan_t pwiden);
void keyscan_set_area(uint8_t area);
void keyscan_set_pol(uint8_t pol);
void keyscan_set_freq(keyscan_frquency_t freq);
void keyscan_set_cycle(uint8_t scan_cycle);
uint8_t keyscan_read_kscan_area(void);
uint8_t keyscan_read_int_state(void);
void keyscan_set_io_valid(uint16_t val);
void keyscan_pwr_ctrl_enable(void);
void keyscan_pwr_ctrl_disable(void);
void get_keyscan_value(uint32_t * key_high,uint32_t * key_low);
uint8_t get_keyscan_key_number(void);
void keyscan_init(uint32_t reg_bits,keyscan_area_t area,uint8_t scan_level,uint8_t scan_cycle);
void keyscan_io_set_before_sleep(uint32_t gpio_bits);
#endif