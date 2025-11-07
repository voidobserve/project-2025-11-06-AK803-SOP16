#include "app_select.h"
#include "ble_packet_send.h"
#include "rcscan.h"

#if (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_28KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		{(BIT1 | BIT3), 5, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT1 | BIT4), 5, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT1 | BIT5), 5, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT1 | BIT6), 5, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT3), 5, direct_key_value, {0x21}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x21}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT4), 5, direct_key_value, {0x22}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x22}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT5), 5, direct_key_value, {0x23}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x23}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT6), 5, direct_key_value, {0x24}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x24}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT3), 5, direct_key_value, {0x31}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x31}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT4), 5, direct_key_value, {0x32}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x32}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT5), 5, direct_key_value, {0x33}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x33}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT6), 5, direct_key_value, {0x34}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x34}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT2 | BIT3), 5, direct_key_value, {0x41}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x41}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT4), 5, direct_key_value, {0x42}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x42}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT5), 5, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT6), 5, direct_key_value, {0x44}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x44}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT0 | BIT3), 5, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT4), 5, direct_key_value, {0x52}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x52}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT5), 5, direct_key_value, {0x53}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x53}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT6), 5, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT7 | BIT3), 5, direct_key_value, {0x61}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x61}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT4), 5, direct_key_value, {0x62}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x62}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT5), 5, direct_key_value, {0x63}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x63}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT6), 5, direct_key_value, {0x64}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x64}, SEND_BEACON_MAX_TIMES, 60000},

		{(GNDB | BIT3), 5, direct_key_value, {0x01}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x01}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT4), 5, direct_key_value, {0x02}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x02}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT5), 5, direct_key_value, {0x03}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x03}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT6), 5, direct_key_value, {0x04}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x04}, SEND_BEACON_MAX_TIMES, 60000},
};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_04KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		{(BIT7 | BIT3), 5, direct_key_value, {0x10}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x10}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT4 | BIT1), 5, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT6 | GNDB), 5, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT6 | BIT1), 5, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, 60000},
};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_07KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		{(BIT0 | BIT3), 50, direct_key_value, {0x01}, 2000, null_handler, {0x0}, 300, 10000},
		{(BIT0 | BIT4), 50, direct_key_value, {0x02}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT0 | BIT5), 50, direct_key_value, {0x03}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT0 | BIT6), 50, direct_key_value, {0x04}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT7 | BIT3), 50, direct_key_value, {0x11}, 2000, null_handler, {0x0}, 300, 10000},
		{(BIT7 | BIT4), 50, direct_key_value, {0x12}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | BIT5), 50, direct_key_value, {0x13}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | BIT6), 50, direct_key_value, {0x14}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT8 | BIT3), 50, direct_key_value, {0x21}, 2000, null_handler, {0x0}, 300, 10000},
		{(BIT8 | BIT4), 50, direct_key_value, {0x22}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | BIT5), 50, direct_key_value, {0x23}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | BIT6), 50, direct_key_value, {0x24}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT9 | BIT3), 50, direct_key_value, {0x31}, 2000, null_handler, {0x0}, 300, 10000},
		{(BIT9 | BIT4), 50, direct_key_value, {0x32}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT9 | BIT5), 50, direct_key_value, {0x33}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT9 | BIT6), 50, direct_key_value, {0x34}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(GNDB | BIT3), 50, direct_key_value, {0x41}, 2000, null_handler, {0x0}, 300, 10000},
		{(GNDB | BIT4), 50, direct_key_value, {0x42}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(GNDB | BIT5), 50, direct_key_value, {0x43}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(GNDB | BIT6), 50, direct_key_value, {0x44}, 2000, null_handler, {0x0}, 0x0, 10000},

};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_12KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		/*
			脚位连接（哪两个脚位相连表示对应的按键按下）
					短按时间阈值	短按调用的函数	短按键值	长按时间阈值	长按调用的函数		长按键值  每个数据包的平均时间间隔  停止按下的时间阈值（停止发送的时间阈值）
		*/
		{(GNDB | BIT5), 5, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, 60000},

		{(GNDB | BIT6), 5, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, 60000},

		{(GNDB | BIT7), 5, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, 60000},

		{(GNDB | BIT4), 5, direct_key_value, {0x04}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x04}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT5), 5, direct_key_value, {0x45}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x45}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT6), 5, direct_key_value, {0x25}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x25}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT7), 5, direct_key_value, {0x35}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x35}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT4), 5, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT5), 5, direct_key_value, {0x15}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x15}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT6), 5, direct_key_value, {0x01}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x01}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT7), 5, direct_key_value, {0x03}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x03}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT4), 5, direct_key_value, {0x02}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x02}, SEND_BEACON_MAX_TIMES, 60000},
};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_19KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		// 开灯
		{(BIT2 | BIT5), 50, lamp_on_handler, {0x00}, 2000, null_handler, {0x0}, 300, 10000},

		// 关灯
		{(BIT2 | BIT6), 50, lamp_off_handler, {0x00}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 亮度+
		{(BIT2 | BIT7), 50, dimming_inc_handler, {0x00}, 2000, dimming_inc_handler, {0x0}, 100, 10000},

		// 色温-
		{(BIT2 | BIT8), 50, wy_dec_handler, {0x00}, 2000, wy_dec_handler, {0x0}, 100, 10000},

		// 绑定
		{(BIT1 | BIT5), 50, binding_handler, {0x00}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 色温-
		{(BIT1 | BIT6), 50, wy_inc_handler, {0x00}, 2000, wy_inc_handler, {0x0}, 100, 10000},

		// 亮度-
		{(BIT1 | BIT7), 50, dimming_dec_handler, {0x00}, 2000, dimming_dec_handler, {0x0}, 100, 10000},

		// 关灯
		{(BIT1 | BIT8), 50, lamp_off_handler, {0x00}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 白光
		{(BIT4 | BIT5), 50, color_temp_set_handler, {0xFF}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 中性光
		{(BIT4 | BIT6), 50, color_temp_set_handler, {0x80}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 暖光
		{(BIT4 | BIT7), 50, color_temp_set_handler, {0x00}, 2000, null_handler, {0x0}, 0x0, 10000},

		// 小夜灯
		{(BIT4 | BIT8), 50, dim_night_handler, {0x00}, 2000, null_handler, {0x0}, 0x0, 10000},
};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_25KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		// K5
		{(BIT4 | BIT3), 50, direct_key_value, {0x01}, 2000, binding_handler, {0x0}, 300, 10000},

		// K4
		{(BIT4 | BIT0), 50, direct_key_value, {0x02}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT4 | BIT2), 50, direct_key_value, {0x03}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT4 | BIT9), 50, direct_key_value, {0x04}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT4 | GNDB), 50, direct_key_value, {0x05}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT5 | BIT3), 50, direct_key_value, {0x06}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT5 | BIT0), 50, direct_key_value, {0x07}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT5 | BIT2), 50, direct_key_value, {0x08}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT5 | BIT9), 50, direct_key_value, {0x09}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT5 | GNDB), 50, direct_key_value, {0x0A}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT6 | BIT3), 50, direct_key_value, {0x0B}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT6 | BIT0), 50, direct_key_value, {0x0C}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT6 | BIT2), 50, direct_key_value, {0x0D}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT6 | BIT9), 50, direct_key_value, {0x0E}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT6 | GNDB), 50, direct_key_value, {0x0F}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT7 | BIT3), 50, direct_key_value, {0x10}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | BIT0), 50, direct_key_value, {0x11}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | BIT2), 50, direct_key_value, {0x12}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | BIT9), 50, direct_key_value, {0x13}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT7 | GNDB), 50, direct_key_value, {0x14}, 2000, null_handler, {0x0}, 0x0, 10000},

		{(BIT8 | BIT3), 50, direct_key_value, {0x15}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | BIT0), 50, direct_key_value, {0x16}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | BIT2), 50, direct_key_value, {0x17}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | BIT9), 50, direct_key_value, {0x18}, 2000, null_handler, {0x0}, 0x0, 10000},
		{(BIT8 | GNDB), 50, direct_key_value, {0x19}, 2000, null_handler, {0x0}, 0x0, 10000},
};
#elif (PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_30KEY)
const str_key_fun keys_func_table[KEYS_FUNCTION_NUM] =
	{
		/*
			脚位连接（哪两个脚位相连表示对应的按键按下）
					短按时间阈值	短按调用的函数	短按键值	长按时间阈值	长按调用的函数		长按键值  每个数据包的平均时间间隔  停止按下的时间阈值（停止发送的时间阈值）
		*/
		{(BIT0 | BIT1), 5, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x11}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT3), 5, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x12}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT4), 5, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x13}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT5), 5, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x14}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT0 | BIT6), 5, direct_key_value, {0x15}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x15}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT2 | BIT1), 5, direct_key_value, {0x21}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x21}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT3), 5, direct_key_value, {0x22}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x22}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT4), 5, direct_key_value, {0x23}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x23}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT5), 5, direct_key_value, {0x24}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x24}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT2 | BIT6), 5, direct_key_value, {0x25}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x25}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT7 | BIT1), 5, direct_key_value, {0x31}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x31}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT3), 5, direct_key_value, {0x32}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x32}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT4), 5, direct_key_value, {0x33}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x33}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT5), 5, direct_key_value, {0x34}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x34}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT7 | BIT6), 5, direct_key_value, {0x35}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x35}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT9 | BIT1), 5, direct_key_value, {0x41}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x41}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT3), 5, direct_key_value, {0x42}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x42}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT4), 5, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x43}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT5), 5, direct_key_value, {0x44}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x44}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT9 | BIT6), 5, direct_key_value, {0x45}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x45}, SEND_BEACON_MAX_TIMES, 60000},

		{(BIT10 | BIT1), 5, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x51}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT3), 5, direct_key_value, {0x52}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x52}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT4), 5, direct_key_value, {0x53}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x53}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT5), 5, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x54}, SEND_BEACON_MAX_TIMES, 60000},
		{(BIT10 | BIT6), 5, direct_key_value, {0x55}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x55}, SEND_BEACON_MAX_TIMES, 60000},

		{(GNDB | BIT1), 5, direct_key_value, {0x61}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x61}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT3), 5, direct_key_value, {0x62}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x62}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT4), 5, direct_key_value, {0x63}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x63}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT5), 5, direct_key_value, {0x64}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x64}, SEND_BEACON_MAX_TIMES, 60000},
		{(GNDB | BIT6), 5, direct_key_value, {0x65}, SEND_BEACON_MAX_TIMES, direct_key_value, {0x65}, SEND_BEACON_MAX_TIMES, 60000},
};
#endif
