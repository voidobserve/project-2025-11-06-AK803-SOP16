/****************************************************************************
@FILENAME:	app_cfg.h
@FUNCTION:	app config
@AUTHOR:	flege.zhang
@DATE:		2019.08.14
*****************************************************************************/

#ifndef _APP_CFG__H_
#define _APP_CFG__H_

#include "config.h"
#include "print.h"
#include "rmt_lmp_cfg.h"
#include "hal_rtc.h"


/****************************PROJECT SPECIAL DEFINE****************************/


/******************************BLE ENCODER VERSION*****************************/
#define BLE_ENCODER_VIOT							(0x03)

#define BLE_ENCODER_VERSION							BLE_ENCODER_VIOT

#define RF_SEND_DIFF_PACKET_NUM						(0x01)


/*****************************RETENTION MEMORY MAP*****************************/


/****************************ABNORMAL PROTEC FUNCTION**************************/
#define SYS_CRASH_WTD_RESET_ENABLE					ENABLE
#if(SYS_CRASH_WTD_RESET_ENABLE)
#define WATCH_DOG_RESET_TIME						2000//unit:ms
#endif

/*********************************TEST FUNCTION********************************/


/******************************LOG DEBUG FUNCTION******************************/
#define LOG_ENABLE									DISABLE//default disable log

#if(LOG_ENABLE)
#define LOG_LEVEL									LOG_LEVEL_MAJOR	//selection the log level
#else
#define LOG_LEVEL									LOG_LEVEL_OFF	//off log
#endif

#define LOG_FATAL									(LOG_LEVEL >= LOG_LEVEL_FATAL)
#define LOG_ERROR									(LOG_LEVEL >= LOG_LEVEL_ERROR)
#define LOG_WARN									(LOG_LEVEL >= LOG_LEVEL_WARN)
#define LOG_MAJOR									(LOG_LEVEL >= LOG_LEVEL_MAJOR)
#define LOG_SECONDARY								(LOG_LEVEL >= LOG_LEVEL_SECONDARY)
#define LOG_DETAIL									(LOG_LEVEL >= LOG_LEVEL_DETAIL)

#endif
