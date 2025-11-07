/****************************************************************************
@FILENAME:	app_common.h
@FUNCTION:	app common define
@AUTHOR:	flege.zhang
@DATE:		2019.08.20
@COPYRIGHT(C) ZXW 2020
*****************************************************************************/

#include "string.h"
#include "type.h"
#include "uart.h"


/******************************COMMON DEFINE*********************************/
#define DISABLE								(0x00)
#define ENABLE								(0x01)


/****************************LOG LEVEL DEFINE********************************/
#define LOG_LEVEL_OFF						(0x00)
#define LOG_LEVEL_FATAL						(0x01)
#define LOG_LEVEL_ERROR						(0x02)
#define LOG_LEVEL_WARN						(0x04)
#define LOG_LEVEL_MAJOR						(0x10)
#define LOG_LEVEL_SECONDARY					(0x20)
#define LOG_LEVEL_DETAIL					(0x80)
#define LOG_LEVEL_ALL						(0xFF)

/***************************WAKEUP SOURCE DEFINE*****************************/
#define WAKEUP_SOURCE_NA					(0x00)
#define WAKEUP_SOURCE_AC					(0x01)
#define WAKEUP_SOURCE_LVD					(0x02)


/***************************HW DETECT TYPE DEFINE****************************/
/*RCSCAN*/
#define RC_SCAN_04KEY_TYPE					(0x0401)
#define RC_SCAN_07KEY_TYPE					(0x0701)
#define RC_SCAN_12KEY_TYPE					(0x1602)
#define RC_SCAN_16KEY_TYPE					(0x1601)
#define RC_SCAN_24KEY_TYPE					(0x2401)
#define RC_SCAN_25KEY_TYPE					(0x2501)
#define RC_SCAN_28KEY_TYPE					(0x1601)
#define RC_SCAN_29KEY_TYPE					(0x2901)
#define RC_SCAN_30KEY_TYPE					(0x3001)

/*******************************PROJECT DEFINE*******************************/
//BIT[31:28]:PROTOCOL TYPE
#define BLE									(0x30000000)//sig ble packet
#define PRT									(0x40000000)//private 2.4g packet

//BIT[27:24]:DETECT TYPE
#define RCSCAN								(0x01000000)//row and column scanning

//BIT[23:16]:FOR DEVICE TYPE
#define LMP									(0x00010000)//lamp

