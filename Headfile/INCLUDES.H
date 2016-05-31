/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: includes.h
Author		:
Date		: 2011/03/01
Description	: 系统头文件
Version		: v0.1
Function List: 
----
History: 
<author>       <time>                <version >             <desc>
                2011/03/01  0.1    build this moudle 
***********************************************************/

#ifndef _INCLUDES_H_
#define _INCLUDES_H_

//command
#define	cIRAddL		0x00
#define	cIRAddH		0x9f

//#define DEBUG

//#define	DEV_PHONE
#define	DEV_MIC

//#define	SAMPLERATE_12KHZ
#define	SAMPLERATE_8KHZ
#define	cRFPWR_5DBM	1 	// 0: 0DBM, 1:5DBM

#define	CHIP_BK2535		// Default BK2433

#define	cPWRBindTime		3750

#include <string.h>
#include <stdio.h>
#include <intrins.h>
#include <ABSACC.H>
#include <stdarg.h>
#include <math.h>
#include "Headfile\BK9001MCU2535_REG.H"
#include "Definition\define.h"
#include "Definition\struct.h"
#include "Definition\global.h"
#include "MCU\timer.h"
#include "MCU\rf.h"
#include "MCU\MCUInital.h"
#include "MCU\mtp.h"
#include "MCU\key.h"
#include "USB\usb_init.h"
#include "USB\usb_descriptor.h"
#include "USB\usb_interrupt_service_routine.h"
#include "USB\usb_standard_requests.h"
#include "USB\usb_uploading.h"
#include "UART\Uart.h"
#include "System\system_mtp_app.h"
#include "System\system_rf_app.h"
#include "System\system_inital.h"
#include "System\system_workmode.h"
#include "System\system_bindmode.h"
#include "System\system_testmode.h"
#include "System\system_pcmode.h"
#include "System\system_debug_mode.h"
#include "System\FreqHopper.h"
#endif

/***********************************************************
						end file
***********************************************************/