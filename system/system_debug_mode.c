/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: 
Author		: joe  
Date		: 2011/03/01
Description	: 
Version		: v0.1
Function List: 
----
History: 
<author> <time> <version > <desc>
joe  2011/03/01  0.1  build this moudle 
***********************************************************/

#include "Headfile\includes.h"

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: joe  
//Date	: 2011/03/01
//-------------------------------------------------------
void system_debug_mode(void)
{
	while(system.work_mode == SYSTEM_DEBUG)
	{
		if(system.usbp0_data.aceept)
		{
			system.usbp0_data.aceept = 0;

			if(COMMAND_DEBUG == system.usbp0_data.set_report_data[0])
			{
				switch(system.usbp0_data.set_report_data[1])
				{
					case COM_DEBUG_RMTP : 
						memcpy(&system.usbp0_data.get_report_data[1], &Flash.mtp_pool[system.usbp0_data.set_report_data[2]], system.usbp0_data.set_report_data[3]);
				
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_DEBUG_WMTP :

						memcpy(&Flash.mtp_pool[system.usbp0_data.set_report_data[2]], &system.usbp0_data.set_report_data[4], system.usbp0_data.set_report_data[3]);
						Flash.flash_need_write = 1;
						Sys_FlashWriteAll();

						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_DEBUG_RREG :
						break;
					case COM_DEBUG_WREG :
						break;
					case COM_DEBUG_EXIT :
						system.work_mode = SYSTEM_WORK; 
						system.usbp0_data.reday_report_flag = 1;
						break;
					default:
						system.usbp0_data.reday_report_flag = 0;
						break;
				}
			}
			else if(COMMAND_CURRENT_MODE  == system.usbp0_data.set_report_data[0])
			{
				system.usbp0_data.get_report_data[1] = COMMAND_DEBUG;
				system.usbp0_data.reday_report_flag = 1;
			}
		}
	}
}

/***********************************************************
						end file
***********************************************************/