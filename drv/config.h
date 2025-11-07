/* ---------------------------------------------------------------
** File name:		config.h
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
** Module Information:
**
** Revision History ----------------------------------------------
** ---------------------------------------------------------------
**  Date        Version     Action                  Author
** ---------------------------------------------------------------
**  2019-5-17   1.0         Created
**
** ---------------------------------------------------------------
*/

#ifndef   __CONFIG_H_
#define   __CONFIG_H_

/* Includes -----------------------------------------------------*/

/* Macro --------------------------------------------------------*/


//  SOFT_VERSION
#define SDK_VERSION     (0x00010102)    // V1.1.2
#define SDK_DATE        (0x20210821)    // 2021.08.21

// #define DEBUG

// #define MODULE_TEST

// #define ENABLE_JTAG
#ifdef  ENABLE_JTAG
//#define ENABLE_JTAG_ON_GPIO7_9         // GPIO7.8.9 as jtag
#define ENABLE_JTAG_ON_GPIO4_6           // GPIO4.5.6 as jtag
#endif


#endif  // #ifndef   __CONFIG_H_
