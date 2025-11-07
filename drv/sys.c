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
**	2019-6-13   1.0         Created
**
** ---------------------------------------------------------------
*/
#include "config.h"
#include "sys.h"

// 设置引脚的复用功能
inline void sys_set_port_mux(uint32_t port, uint8_t function)
{
    //*((volatile uint32_t *)(port)) = function;
    write_reg(port, function);
}

void sys_set_module_clock( sys_clock_ctrl_t clock_sel, uint8_t on_off)
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( TOP_CLK_CTRL_REG );

    if ( ON == on_off )
    {
        reg_val |= clock_sel;
    }
    else// if ( OFF == on_off )//saving 4 bytes
    {
        reg_val &= ~clock_sel;
    }

    write_reg(TOP_CLK_CTRL_REG, reg_val);
}

void sys_soft_reset( uint8_t module )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( TOP_SOFT_RESET_REG );

    reg_val |= module;
    write_reg(TOP_SOFT_RESET_REG, reg_val);
    reg_val &= ~module;
    write_reg(TOP_SOFT_RESET_REG, reg_val);
}

void sys_set_clock( cpu_clock_sel_t clock )
{
    uint32_t    reg_val = 0;

    reg_val = read_reg( TOP_MODULE_MODE_REG );
    reg_val &= ~TOP_CPU_CLK_SEL_MASK;
    reg_val |= clock << TOP_CPU_CLK_SEL_SHIFT;
    write_reg( TOP_MODULE_MODE_REG, reg_val );
}

uint8_t get_sys_clk_cfg(void)
{
    uint32_t    reg_val = 0;
    reg_val = read_reg( TOP_MODULE_MODE_REG );
    reg_val &=TOP_CPU_CLK_SEL_MASK;
    reg_val = reg_val>>TOP_CPU_CLK_SEL_SHIFT;
    return (0xFF&reg_val);
}
void sys_init()
{
    write_reg(0X4012012C, 0XCF);// SFR FOR RC-OSC
    write_reg(0X40020018, 0X52); // wave form
    write_reg(0X40120148, 0X4C);
    write_reg(0X4002001C, 0X13);
#ifdef ENABLE_JTAG_ON_GPIO7_9
    sys_set_port_mux(PAD_GPIO_07, PAD_MUX_FUNCTION_1|3);//RXD
    sys_set_port_mux(PAD_GPIO_08, PAD_MUX_FUNCTION_1|3);//TXD
    sys_set_port_mux(PAD_GPIO_09, PAD_MUX_FUNCTION_1|3);//TXD
#elif defined (ENABLE_JTAG_ON_GPIO4_6)
    sys_set_port_mux(PAD_GPIO_04, PAD_MUX_FUNCTION_3|3);//RXD
    sys_set_port_mux(PAD_GPIO_05, PAD_MUX_FUNCTION_3|3);//TXD
    sys_set_port_mux(PAD_GPIO_06, PAD_MUX_FUNCTION_3|3);//TXD
#endif
}

void sys_sleep_down(void)
{
	/*bug fixed:sleep can't wakeup,modified by flege,20200526*/
	write_reg(0x4012012C,0xF0);//before is 0xD0//0xD8//0xC8//0x40
	
    write_reg(TOP_POWER_CTRL_REG, 0x1);//sleep
}

