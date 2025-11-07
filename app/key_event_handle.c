#include "key_event_handle.h"
#include "../drv/type.h"
#include "../module/ble_pack/ble_pack_opcode.h"

volatile u8 sys_status = 0x00;

/**
 * @brief 根据传参，初始化键值处理包
 *
 * @param cmd
 * @param status
 * @param para_0
 * @param para_1
 * @param para_2
 * @return * void
 */
void key_event_handle_package_init(u8 cmd, u8 status, u8 para_0, u8 para_1, u8 para_2)
{
    ble_viot_para.cmd = cmd;
    sys_status = status;
    ble_viot_para.status = sys_status;
    ble_viot_para.para[0] = para_0;
    ble_viot_para.para[1] = para_1;
    ble_viot_para.para[2] = para_2;
}

/**
 * @brief 滚码累加
 *
 */
void key_event_handle_roll_code_add(void)
{
    ble_viot_para.count++;
    ble_viot_para.count %= 256; //
}

// 关机
void key_event_handle_off(void)
{
    key_event_handle_package_init(0x01, 0x00, 170, 170, 170);
}

/**
 * @brief 色温 加
 *
 */
void key_event_handle_color_temp_add(void)
{
    key_event_handle_roll_code_add();
    key_event_handle_package_init(0x04, sys_status, 170, 170, 170);
}

/**
 * @brief 色温 减
 *
 */
void key_event_handle_color_temp_sub(void)
{
    key_event_handle_roll_code_add();
    key_event_handle_package_init(0x05, sys_status, 170, 170, 170);
}

/**
 * @brief 亮度 加
 *
 */
void key_event_handle_brightness_add(void)
{
    key_event_handle_roll_code_add();
    key_event_handle_package_init(0x02, sys_status, 170, 170, 170);
}

/**
 * @brief 亮度 减
 *
 */
void key_event_handle_brightness_sub(void)
{
    key_event_handle_roll_code_add();
    key_event_handle_package_init(0x03, sys_status, 170, 170, 170);
}

/**
 * @brief 
 * 
 */


