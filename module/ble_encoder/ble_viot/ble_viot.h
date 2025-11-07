/****************************************************************************
@FILENAME:	ble_viot.h
@FUNCTION:	encoder/decoder for ble iot packet
@AUTHOR:	flege.zhang
@DATE:		2020.05.20
@COPYRIGHT(C) ZXW 2020
*****************************************************************************/

#ifndef _BLE_VIOT__H_
#define _BLE_VIOT__H_


/********************************MACRO DEFINE********************************/
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

/*********************************ENUM DEFINE********************************/
enum en_ble_viot_ret
{
	BLE_VIOT_SUCCESS			= 0x00,
    BLE_VIOT_SAMEPACK_ERROR     = 0x01,
    BLE_VIOT_CRC_ERROR          = 0x02,
};
/*******************************STRUCT DEFINE********************************/
typedef struct
{
	uint8_t		rfu2[5];
	uint8_t		relay;
	uint8_t 	type;
	uint8_t 	version;
	uint8_t 	status; // 记录状态，根据指定按键改变这个状态的值
	uint8_t 	count;
	uint32_t 	addr;
	uint8_t 	group_index;
	uint8_t 	cmd;
	uint8_t 	para[3];
	uint8_t 	rfu[3];
}str_ble_viot_para;



uint8_t ble_viot_encoder(str_ble_viot_para* opcode_para,uint8_t rand_seed,uint8_t* out_data,uint8_t* out_data_len);

uint8_t is_ble_viot_pdu(uint8_t* ble_payload,uint8_t payload_len);

uint8_t ble_viot_decoder(uint8_t* ble_payload,uint8_t payload_len,str_ble_viot_para* opcode_para);

#endif
