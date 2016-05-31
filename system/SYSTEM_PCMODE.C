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
<author> 		<time> 		<version > 		<desc>
			 2011/03/01 		 0.1 				 build this moudle 
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
void system_pc_mode(void)
{
	while(system.work_mode == SYSTEM_CODE)
	{
		if(system.usbp0_data.aceept)
		{
			system.usbp0_data.aceept = 0;

			if(COMMAND_CODE == system.usbp0_data.set_report_data[0])
			{
				switch(system.usbp0_data.set_report_data[1])
				{
					case COM_CODE_RMTP :
						memcpy(&system.usbp0_data.get_report_data[1], &Flash.mtp_pool[system.usbp0_data.set_report_data[2]], system.usbp0_data.set_report_data[3]);
			
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_CODE_WMTP :
		
						memcpy(&Flash.mtp_pool[system.usbp0_data.set_report_data[2]], &system.usbp0_data.set_report_data[4], system.usbp0_data.set_report_data[3]);
						Flash.flash_need_write = 1;
						Sys_FlashWriteAll();
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_CODE_CLE:
						Sys_FlashEraseAll();
						memset(&Flash.mtp_pool[0], 0xff, cMTP_LEN);

						system.usbp0_data.reday_report_flag = 1;
						system.mtp_record.mtp_flag.mouse_bind = 0;	
						system.mtp_record.mtp_flag.keyboard_bind = 0; //擦完mtp清RAM区的对码标志
						break;
					case COM_CODE_EXIT :
						system.work_mode = SYSTEM_WORK; 
						system.usbp0_data.reday_report_flag = 1;
						break;
				}
			}
			else if(COMMAND_CURRENT_MODE  == system.usbp0_data.set_report_data[0])
			{
				system.usbp0_data.get_report_data[1] = COMMAND_CODE;
				system.usbp0_data.reday_report_flag = 1;
			}

			system.usbp0_data.set_report_data[0] = 0x00;
			system.usbp0_data.set_report_data[1] = 0x00;
			system.usbp0_data.set_report_data[2] = 0x00;
		}
	}
}

/***********************************************************
						end file
***********************************************************/