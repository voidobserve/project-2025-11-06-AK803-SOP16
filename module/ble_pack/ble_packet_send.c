/****************************************************************************
@FILENAME:	ble_packet_send.c
@FUNCTION:	pack ble opcode then send
@AUTHOR:	flege.zhang
@DATE:		2020.04.06
*****************************************************************************/

#include "ble_packet_send.h"
#include "ble_pack_opcode.h"
#include "ble_adv.h"
#include "hal_gpio.h"

/******************************GLOBAL VARIABLE*******************************/
str_retention_memory ret_mem_data;
uint32_t GROUP_ADDR = 0x0; // 存放芯片内部的滚码的变量，在上电后通过调用ble_packet_init()读出来
const uint8_t const_group_index[] = {0x00, 0x01, 0x02, 0x03, 0x04};

#if ((BLE_ENCODER_VERSION & BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
extern str_ble_viot_para ble_viot_para;
#endif

/**********************************FUNCTION**********************************/
inline void SET_GROUP_INDEX(uint8_t new_group_index)
{
	ret_mem_data.current_group_index = new_group_index;
}

inline uint8_t GET_GROUP_INDEX()
{
	return ret_mem_data.current_group_index;
}

void null_handler(str_fun_para *para)
{
}

/***************************************************************************
 * 函数名称：set_group_handler
 * 说明：设置组号
 * 输入：需要绑定的组号
 * 输出：
 * 备注：
 * ************************************************************************/
void set_group_handler(str_fun_para *para)
{
	SET_GROUP_INDEX(para->para_a);
}

/***************************************************************************
 * 函数名称：binding_handler
 * 说明：绑定函数
 * 输入：需要绑定的组号
 * 输出：
 * 备注：
 * ************************************************************************/
void binding_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x01;
	ble_viot_para.para[0] = 0x01;
	SET_GROUP_INDEX(para->para_a);
}

/***************************************************************************
 * 函数名称：lamp_off_handler
 * 说明：开灯函数
 * 输入：具体要关灯的组号，0为全控
 * 输出：
 * 备注：
 * ************************************************************************/
void lamp_off_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x10;
	ble_viot_para.para[0] = 0x00;
	SET_GROUP_INDEX(para->para_a);
}

/***************************************************************************
 * 函数名称：lamp_on_handler
 * 说明：开灯函数
 * 输入：具体要开灯的组号，0为全控
 * 输出：
 * 备注：
 * ************************************************************************/
void lamp_on_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x10;
	ble_viot_para.para[0] = 0x01;
	SET_GROUP_INDEX(para->para_a);
}

/***************************************************************************
 * 函数名称：lamp_onoff_reverse_handler
 * 说明：开关灯函数
 * 输入：具体要开灯的组号，0为全控
 * 输出：
 * 备注：
 * ************************************************************************/
void lamp_onoff_reverse_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x10;
	ble_viot_para.para[0] = 0x02;
	// SET_GROUP_INDEX(para->para_a);
}

/***************************************************************************
 * 函数名称：dim_night_handler
 * 说明：夜灯
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void dim_night_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x1A;
	ble_viot_para.para[0] = 0x00;
}

/***************************************************************************
 * 函数名称：dimming_inc_handler
 * 说明：亮度增加设置函数
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void dimming_inc_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x01;
	ble_viot_para.para[1] = 0x01;
}

/***************************************************************************
 * 函数名称：dimming_inc_handler
 * 说明：亮度减少设置函数
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void dimming_set_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x04;
	ble_viot_para.para[1] = para->para_a;
}

/***************************************************************************
 * 函数名称：dimming_inc_handler
 * 说明：亮度减少设置函数
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void dimming_dec_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x01;
	ble_viot_para.para[1] = 0x00;
}

/***************************************************************************
 * 函数名称：dimming_50_100_switch
 * 说明：亮度50和100之间切换
 * 输入：
 * 输出：
 * 备注：
 * ************************************************************************/
void dimming_50_100_switch_handler(str_fun_para *para)
{
	uint8_t current_dim_status = ret_mem_data.current_dim_status;
	str_fun_para dim_value;
	if (current_dim_status)
	{
		dim_value.para_a = 50;
		dimming_set_handler(&dim_value);
	}
	else
	{
		dim_value.para_a = 100;
		dimming_set_handler(&dim_value);
	}
	ret_mem_data.current_dim_status ^= 0x01;
}

/***************************************************************************
 * 函数名称：wy_inc_handler
 * 说明：色温增加设置函数
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void wy_inc_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x02;
	ble_viot_para.para[1] = 0x00;
	ble_viot_para.para[2] = 0x01;
}

/***************************************************************************
 * 函数名称：wy_dec_handler
 * 说明：色温减少设置函数
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void wy_dec_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x02;
	ble_viot_para.para[1] = 0x00;
	ble_viot_para.para[2] = 0x00;
}

/***************************************************************************
 * 函数名称：color_temp_set_handler
 * 说明：色温比例设置函数
 * 输入：0-255
 * 输出：
 * 备注：
 * ************************************************************************/
void color_temp_set_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x20;
	ble_viot_para.para[0] = 0x03;

	ble_viot_para.para[1] = para->para_a;
}

/***************************************************************************
 * 函数名称：color_temp_wy_switch
 * 说明：色温黄白光切换
 * 输入：
 * 输出：
 * 备注：
 * ************************************************************************/
void color_temp_wy_switch(str_fun_para *para)
{
	uint8_t wy_status = ret_mem_data.current_wy_status;
	str_fun_para wy_value;
	if (wy_status)
	{
		wy_value.para_a = 255;
		color_temp_set_handler(&wy_value);
	}
	else
	{
		wy_value.para_a = 0;
		color_temp_set_handler(&wy_value);
	}
	ret_mem_data.current_wy_status ^= 0x01;
}

/***************************************************************************
 * 函数名称：rgb_set_handler
 * 说明：RGB颜色设置
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void rgb_set_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x24;

	ble_viot_para.para[0] = para->para_a;
	ble_viot_para.para[1] = para->para_b;
	ble_viot_para.para[2] = para->para_c;
}

/***************************************************************************
 * 函数名称：rgb_set_handler
 * 说明：RGB颜色设置
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void rgb_toggle_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x24;
	uint8_t rgb_status = ret_mem_data.current_rgb_status;
	str_fun_para rgb_value;
	switch (rgb_status)
	{
	case 0:
	{
		ble_viot_para.para[0] = 0xFF;
		ble_viot_para.para[1] = 0x00;
		ble_viot_para.para[2] = 0x00;
		break;
	}
	case 1:
	{
		ble_viot_para.para[0] = 0x00;
		ble_viot_para.para[1] = 0xFF;
		ble_viot_para.para[2] = 0x00;
		break;
	}
	case 2:
	{
		ble_viot_para.para[0] = 0x00;
		ble_viot_para.para[1] = 0x00;
		ble_viot_para.para[2] = 0xFF;
		break;
	}
	}
	ret_mem_data.current_rgb_status++;
	if (ret_mem_data.current_rgb_status > 2)
		ret_mem_data.current_rgb_status = 0;
}

/***************************************************************************
 * 函数名称：rgb_mode_set_handler
 * 说明：RGB模式设置
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void rgb_mode_set_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x23;

	ble_viot_para.para[0] = para->para_a;
	ble_viot_para.para[1] = para->para_b;
	ble_viot_para.para[2] = para->para_c;
	ble_viot_para.rfu[0] = para->para_d;
}

/***************************************************************************
 * 函数名称：rgb_mode_set_handler
 * 说明：RGB模式设置
 * 输入：无
 * 输出：
 * 备注：
 * ************************************************************************/
void rgb_mode_onoff_handler(str_fun_para *para)
{
	ble_viot_para.cmd = 0x23;

	uint8_t rgb_status = ret_mem_data.current_rgb_mode;
	if (rgb_status)
	{
		ble_viot_para.para[0] = 0x01;
	}
	else
	{
		ble_viot_para.para[0] = 0x00;
	}
	ble_viot_para.para[1] = 0x02;
	ble_viot_para.para[2] = 50;
	ble_viot_para.rfu[0] = 50;
	ret_mem_data.current_rgb_mode ^= 0x01;
}

/***************************************************************************
 * 函数名称：direct_key_vlaue
 * 说明：直接发送按键键值
 * 输入：0x00-0xff
 * 输出：
 * 备注：
 * ************************************************************************/
void direct_key_value(str_fun_para *para)
{
	ble_viot_para.cmd = 0xFF;
	ble_viot_para.para[0] = para->para_a;

	// ble_viot_para.cmd = para->para_a;
}

void ble_packet_init()
{
	GROUP_ADDR = *(uint32_t *)(GROUP_ADDR_ROLL_CODE_BASE); // 从这个地址下面读取滚码

#if ((BLE_ENCODER_VERSION & BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
	memset(&ble_viot_para, 0x0, sizeof(str_ble_viot_para));
#endif
}

uint8_t ble_packet_send()
{
	uint8_t ret = 0xFF;
	uint8_t encoded_data[31]; // 存放最终编码好的数据

	uint8_t encoded_data_len;
	uint8_t index = 0x0;
	uint8_t *group_index = &ret_mem_data.current_group_index;
	uint16_t rand_seed = ret_mem_data.rand_seed;
	// uint16_t tx_count = ret_mem_data.tx_count++;
	uint16_t tx_count = ret_mem_data.tx_count;
	uint8_t channel_switch = 0;

	// hal_gpio_set_port(SINGLE_LED_GPIO_INDEX, GPIO_OUTPUT, 0x1); //  发送期间，点亮LED
	// sys_sleep_count = 0; // 发送数据包，清空睡眠计时

	// validation check,if group index get error,reset as master group index
	// 检查有效性
	*group_index = (*group_index > GROUP_INDEX_MAX) ? 0x00 : *group_index;

#if ((BLE_ENCODER_VERSION & BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
	ble_viot_para.type = 0x00;
	ble_viot_para.version = 0x00;
	ble_viot_para.count = tx_count; // count increace ( USER_TO_DO 需要改成短按才加一，长按不加)
	ble_viot_para.addr = GROUP_ADDR;
	ble_viot_para.group_index = *group_index;

	// encode packet
	ret = ble_viot_encoder(&ble_viot_para, rand_seed, encoded_data, &encoded_data_len);
#endif
#if LOG_MAJOR
	print("ble_pack_send!\r\n");
#endif
	// send encoded packet

#if 0
	ble_adv_send(index, encoded_data, encoded_data_len, SEND_BEACON_MAX_TIMES, SEND_BEACON_INTERVAL, ADV_CHANNEL_BIT_37);

#else
	switch (channel_switch)
	{
	case 0:
		ble_adv_send(index, encoded_data, encoded_data_len, SEND_BEACON_MAX_TIMES, SEND_BEACON_INTERVAL, ADV_CHANNEL_BIT_37);
		channel_switch = 1;
		break;

	case 1:
		ble_adv_send(index, encoded_data, encoded_data_len, SEND_BEACON_MAX_TIMES, SEND_BEACON_INTERVAL, ADV_CHANNEL_BIT_38);
		channel_switch = 2;
		break;

	case 2:
		ble_adv_send(index, encoded_data, encoded_data_len, SEND_BEACON_MAX_TIMES, SEND_BEACON_INTERVAL, ADV_CHANNEL_BIT_39);
		channel_switch = 0;
		break;
	}
#endif

#if ((BLE_ENCODER_VERSION & BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
	memset(&ble_viot_para, 0x0, sizeof(str_ble_viot_para));
#endif

	return ret;
}
