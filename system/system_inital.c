/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: 
Author		: 
Date		: 2011/03/01
Description	: 
Version		: v0.1
Function List: 
----
History: 
<author>            <time>         <version >             <desc>
                     2011/03/01           0.1             build this moudle 
***********************************************************/

#include "Headfile\includes.h"

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
void system_inital(void)
{
	WaitUs(5);
	
	mcu_clk_inital();
	mcu_io_inital();
	memset(&system, 0, sizeof(SYS_STRUCT));	
	DISABLE_INTERRUPT;	
	InitSysTimer();
	WaitUs(600);
//	system_read_MTPrecord();
	BK2433_RF_Initial();

	AudioInit();
	if(bUSBMode)
		usb_ini();
	
	ENABLE_INTERRUPT;

	#ifdef DEBUG
	UartOpen();
	#endif

	PowerUp_RF();
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
void system_check_workmode(void)
{
	BindKeyInput();
//	TestPortInput();
	
	system.work_mode = SYSTEM_WORK;
	if(get_bindkey())
		system.work_mode = SYSTEM_TEST;
	#if	0
	else if(!P_PCBATest)
		system.work_mode = SYSTEM_PCBA;
	#endif
	else
	{
		if(system.mtp_record.mtp_flag.mouse_bind == 0)
			system.work_mode = SYSTEM_BIND;
	}
	
}
/***********************************************************
						end file
***********************************************************/