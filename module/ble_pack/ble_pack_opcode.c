/****************************************************************************
@FILENAME:	ble_pack_opcode.h
@FUNCTION:	pack ble opcode
@AUTHOR:	flege.zhang
@DATE:		2020.04.06
*****************************************************************************/

#include "ble_pack_opcode.h"

#if((BLE_ENCODER_VERSION&BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
str_ble_viot_para ble_viot_para;
#endif

inline void PACK_FUNC(uint8_t cmd,uint16_t para1,uint16_t para2,uint16_t para3)
{
#if((BLE_ENCODER_VERSION&BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
	ble_viot_para.cmd = cmd;
	ble_viot_para.para[0] = para1;
	ble_viot_para.para[1] = para2;
	ble_viot_para.para[2] = para3;
#endif
}

