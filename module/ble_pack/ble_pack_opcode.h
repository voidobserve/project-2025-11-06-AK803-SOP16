/****************************************************************************
@FILENAME:	ble_pack_opcode.h
@FUNCTION:	pack ble opcode
@AUTHOR:	flege.zhang
@DATE:		2020.04.06
*****************************************************************************/

#ifndef __BLE_PACK_OPCODE__H_
#define __BLE_PACK_OPCODE__H_


#include "app_cfg.h"
#if((BLE_ENCODER_VERSION&BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
#include "ble_viot.h"
#endif


#if((BLE_ENCODER_VERSION&BLE_ENCODER_VIOT) == BLE_ENCODER_VIOT)
extern str_ble_viot_para ble_viot_para;
#endif

//inline void PACK_FUNC(uint8_t cmd,uint16_t para1,uint16_t para2,uint16_t para3);

#endif
