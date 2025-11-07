/****************************************************************************
@FILENAME:	ble_packet_send.h
@FUNCTION:	pack ble opcode then send
@AUTHOR:	flege.zhang
@DATE:		2020.04.06
*****************************************************************************/

#ifndef __BLE_PACKET_SEND__H_
#define __BLE_PACKET_SEND__H_


#include "app_cfg.h"
#include "ble_pack_opcode.h"

// SEND_BEACON_MAX_TIMES 最大为65535
// #define SEND_BEACON_MAX_TIMES							(60000) // 在1~2次内会无法识别，在有人在中间走动时会出现5次以内无法识别，灵敏度会比 255 的低（频繁按下不同按键时，反应会比255的慢）

// #define SEND_BEACON_MAX_TIMES							(3000) // 


/*
我在demo中修改了发送次数和发送间隔，在发送间隔为10ms以下或一直发送时，接收端每隔300ms~400ms才会返回一个数据包，发送间隔超过100ms时，接收端要超过1s才会返回一个数据包，
修改发送次数几乎不影响接收端的接收时间间隔。有没有其他参数可以修改，让接收端更快的接收到并返回数据包。
*/
// #define SEND_BEACON_MAX_TIMES							(255) // 按下按键1次，灯就会变化，有1~3次内会无法识别，效果跟 60000 的相似
// #define SEND_BEACON_MAX_TIMES							(100) // 按下按键2~3次内，灯就会变化

// ================================================
#define SEND_BEACON_MAX_TIMES (75) //
// ================================================

// #define SEND_BEACON_MAX_TIMES							(60) //
// #define SEND_BEACON_MAX_TIMES							(50) // 有概率收不到，效果比			25  好
// #define SEND_BEACON_MAX_TIMES							(30) //
// #define SEND_BEACON_MAX_TIMES							(25) // 同样有概率收不到，但是比	1 会好很多，
// #define SEND_BEACON_MAX_TIMES							(20) // 切换信道后，会有错误率
// #define SEND_BEACON_MAX_TIMES							(5) // 切换信道后，再使用这个，错误率会提升
// #define SEND_BEACON_MAX_TIMES							(1) // 改成这个有概率收不到

// #define SEND_BEACON_INTERVAL							(200) //ms 
// #define SEND_BEACON_INTERVAL							(100) //ms ，灵敏度变低，灯的状态没有及时变化
// #define SEND_BEACON_INTERVAL							(50) // ms
// #define SEND_BEACON_INTERVAL							(20) //
// #define SEND_BEACON_INTERVAL							(10) //10ms，也是官方默认的配置，灵敏度会比1ms的低
// #define SEND_BEACON_INTERVAL							(5) //ms
// #define SEND_BEACON_INTERVAL							(2) //ms

// ================================================
#define SEND_BEACON_INTERVAL (1) // ms ，灵敏度是 SEND_BEACON_INTERVAL 中最高的
// ================================================

#define SEND_BEACON_CHANNEL								ADV_CHANNEL_BIT_37

/*ROLL CODE*/
#define GROUP_ADDR_ROLL_CODE_BASE						(0x1FE0)

typedef struct
{
	uint16_t para_a;
	uint16_t para_b;
	uint16_t para_c;
	uint16_t para_d;
}str_fun_para;


typedef struct
{
	uint32_t key_value; // 键值（脚位连接，哪两个脚位相连表示对应的按键按下）

	uint32_t short_press_threshold;				 // 短按时间阈值
	void (*short_press_handler)(str_fun_para *); // 短按调用的函数
	str_fun_para short_press_para;				 // 短按键值（短按要发送的键值）

	uint32_t long_press_threshold;				// 长按时间阈值
	void (*long_press_handler)(str_fun_para *); // 长按调用的函数
	str_fun_para long_press_para;				// 长按键值（长按要发送的键值）
	uint16_t pack_adv_interval;					// 发送期间，每个数据包的平均时间间隔

	uint32_t stop_press_threshold; // 停止按下的时间阈值（停止发送的时间阈值）
} str_key_fun;

typedef struct
{
	//system used,1 words
	uint8_t 	sys_reset_cause;
	uint8_t 	current_group_index;
	uint8_t		current_wy_status;
	uint8_t		current_dim_status;
	uint8_t		current_rgb_status;
	uint8_t		current_rgb_mode;
	uint16_t 	tx_count;
	uint16_t 	rand_seed;
	uint8_t 	rfu[2];
	//uint16_t 	rfu;
}str_retention_memory;


extern uint32_t GROUP_ADDR; // 存放芯片内部的滚码的变量，在上电后通过调用 ble_packet_init() 读出来


void 	null_handler(str_fun_para* para);
void 	set_group_handler(str_fun_para* para);
void 	binding_handler(str_fun_para* para);
void 	unbinding_handler(str_fun_para* para);
void 	lamp_on_handler(str_fun_para* para);
void 	lamp_off_handler(str_fun_para* para);
void 	lamp_onoff_reverse_handler(str_fun_para* para);
void 	dimming_inc_handler(str_fun_para* para);
void 	dimming_dec_handler(str_fun_para* para);
void 	dimming_50_100_switch_handler(str_fun_para* para);
void	wy_inc_handler(str_fun_para* para);
void	wy_dec_handler(str_fun_para* para);
void 	color_temp_wy_switch(str_fun_para* para);
void 	color_temp_set_handler(str_fun_para* para);

void 	dim_night_handler(str_fun_para* para);

void 	rgb_set_handler(str_fun_para* para);
void 	rgb_mode_onoff_handler(str_fun_para* para);
void 	rgb_toggle_handler(str_fun_para* para);

void 	direct_key_value(str_fun_para* para);

void 	ble_packet_init(void);
uint8_t ble_packet_send(void);

#endif

