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
<author>		 <time> 			<version > 		<desc>
			2011/03/01  			0.1  			build this moudle 
***********************************************************/

#include "Headfile\includes.h"

XDATA BYTE RX0_ADDR_TEMP[5];
XDATA BYTE RX1_ADDR_TEMP[5];

XDATA BYTE IR_Code_Tmp[3];
XDATA BYTE mouse_bind_step;
XDATA BYTE keyboard_bind_step;

XDATA UINT16 wBindTime;
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
void system_bind_mode(void)
{
	BYTE uLEDDuty;
	uLEDDuty = 0;
	DEG(("bind mode\n"));
//	BK2401_RFCH = 105;
	PowerUp_RF();
	BK2401_CE = 0x01;
	RF_SetLowOuput();
	wBindTime = 0;
	
	system.bind.keyboard_bind = 0;
	system.bind.mouse_bind = 0;

	system.mtp_record.mtp_flag.mouse_bind = 0;
	system.usbp0_data.aceept = 0;
	system.bind.keyboard_requst_cnt = 0;
	system.usbp0_data.get_report_data[0] = 0x00;
	system.usbp0_data.get_report_data[1] = 0x00;
	system.usbp0_data.get_report_data[2] = 0x00;
	system.usbp0_data.get_report_data[3] = 0x00;
	system.usbp0_data.get_report_data[4] = 0x00;
	system.cell.keyboard_cell[0] = 0x00;
	system.cell.keyboard_cell[1] = 0x00;
	system.cell.mouse_cell[0] = 0x00;
	system.cell.mouse_cell[1] = 0x00;
	mouse_bind_step = 0x00;
	keyboard_bind_step = 0x00;
//	ChangePublicPipe();
	RX0_ADDR_TEMP[0] = 0x00;
	RX0_ADDR_TEMP[1] = 0x00;
	RX0_ADDR_TEMP[2] = 0x00;
	RX0_ADDR_TEMP[3] = 0x00;
	RX0_ADDR_TEMP[4] = 0x00;
	RX1_ADDR_TEMP[0] = 0x00;
	RX1_ADDR_TEMP[1] = 0x00;
	RX1_ADDR_TEMP[2] = 0x00;
	RX1_ADDR_TEMP[3] = 0x00;
	RX1_ADDR_TEMP[4] = 0x00;

	IR_Code_Tmp[0] = 0;
	IR_Code_Tmp[1] = 0;
	IR_Code_Tmp[2] = 0;
	FLUSH_RX;
	FLUSH_TX;
	BK2401_STATUS = 0x70;
	DEG(("sta = %bu\n",(char)BK2401_STATUS));
	DEG(("fifo=%bu\n",(BYTE)BK2401_FIFOSTATUS));

	while(1)					//对码30S
	{
		system_bind_data_dispose();
		system_bind_usb_process();
		if(u10msFlag & bSysCheck)
		{
			u10msFlag &= ~bSysCheck;
			if(++uLEDDuty > cBindLEDDuty)
			{
				uLEDDuty = 0;
				LEDToggle();
			}
			wBindTime++;
			if(wBindTime > cBDTime)
			{
				wBindTime = 0;
				break;
			}
		}
		if(system.bind.mouse_bind)
		{	// Bind OK.
			LEDOff();
			Delay(100);
			
			LEDOn();
			Delay(100);	
			LEDOff();
			Delay(100);
			
			LEDOn();
			Delay(100);	
			LEDOff();
			Delay(100);

			LEDOn();
			Delay(100);	
			LEDOff();
			Delay(100);
			break;
		}
		else if(system.work_mode != SYSTEM_BIND)
		{	// Bind fail.
			break;
		}
	}
	ChangeTxPipe(0);
	RF_SetNomalOuput();
//	RF_AutoChannelSwitch();
	BK2401_RFCH = cRFNMWorkCH;
	system.work_mode=SYSTEM_WORK;
	LEDOff();
}
#ifdef	CHIP_BK2535
/*! \fn void application_page_data_dispose_step3(UINT8 value)
    \brief Dongle writes the paged flag into mtp.

    Writing 0x5A into mtp address 0x02 means system has been configured.\n
    Writing the 7th bit of mtp address 0x08 to 0 means mouse has been paged with dongle.\n
    Writing the 4th bit of mtp address 0x08 to 0 means mouse has been paged with dongle.
    \param void
    \return void
*/
void Sys_bind_data_dispose_step3(UINT8 value)
{
    Flash.mtp_pool[MTP_STATUS_ADDR1] = MTP_STORY_FLAG;	
    Flash.mtp_pool[MTP_STATUS_ADDR2] = MTP_STORY_FLAG;	
    Flash.mtp_pool[MTP_STATUS_ADDR3] = MTP_STORY_FLAG;	

    Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] &= value;
    Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1] &= value;
    Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2] &= value;
}
#endif
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
void system_bind_data_dispose(void)
{
	BYTE bind_sta;
	
	BYTE bind_temp[5];
	BYTE bind_len;
	bind_temp[0] = 0x00;
	bind_temp[1] = 0x00;
	bind_temp[2] = 0x00;
	bind_temp[3] = 0x00;
	bind_temp[4] = 0x00;
	bind_sta = 0x00;
	bind_len = 0x00;
	
	bind_sta = BK2401_STATUS;
	if(bind_sta & STATUS_RX_DR)
	{
		bind_len = BK2401_RPL_WIDTH;    
		RF_ReadData(bind_len);
		BK2401_STATUS=bind_sta;	
		FLUSH_RX;
		
		DEG(("%bu %bu\n",FIFO_data[0],FIFO_data[1]));
/*
	Bind step: 
	      first: TX DATATYPE_BIND packet; 
	      second: TX DATATYPE_CONFIG packet; third: TX DATATYPE_OK packet.
*/
		if(DATATYPE_BIND == FIFO_data[0])   //对码请求+地址
		{	
			// Bind step 1.
			switch(FIFO_data[1])		
			{
				case MOUSE:	
					if(system.mtp_record.mtp_flag.mouse_bind == 0)
					{
						RX0_ADDR_TEMP[0] = FIFO_data[2];
						RX0_ADDR_TEMP[1] = FIFO_data[3];
						RX0_ADDR_TEMP[2] = FIFO_data[4];
						RX0_ADDR_TEMP[3] = FIFO_data[5];
						RX0_ADDR_TEMP[4] = FIFO_data[6];

//						system.cell.mouse_cell[0] = FIFO_data[7] & 0x0F;
//						system.cell.mouse_cell[1] = FIFO_data[8];
						IR_Code_Tmp[0] = FIFO_data[7];			// IR ADDL
						IR_Code_Tmp[1] = FIFO_data[8];			// IR ADDH
						IR_Code_Tmp[2] = FIFO_data[9];			// IR key release code
//						system_rf_mouse_config();
						mouse_bind_step = 1;
					}
					break;
					
				case KEYBOARD:		
					if(system.mtp_record.mtp_flag.keyboard_bind == 0)
					{
						RX1_ADDR_TEMP[0] = FIFO_data[2];
						RX1_ADDR_TEMP[1] = FIFO_data[3];
						RX1_ADDR_TEMP[2] = FIFO_data[4];
						RX1_ADDR_TEMP[3] = FIFO_data[5];
						RX1_ADDR_TEMP[4] = FIFO_data[6];

						system.cell.keyboard_cell[0] = FIFO_data[7] & 0x0F;
						system.cell.keyboard_cell[1] = FIFO_data[8];
						
//						system_rf_keyboard_config();
						keyboard_bind_step = 1;
					}
					break;
					
				default:
					break;
			}
		}
		else if(DATATYPE_CONFIG == FIFO_data[0])
		{	
			// Bind step 2.
			switch(FIFO_data[1])		
			{
				case MOUSE:	
					if(system.mtp_record.mtp_flag.mouse_bind == 0)
					{
						RX0_ADDR_TEMP[0] = FIFO_data[2];
						RX0_ADDR_TEMP[1] = FIFO_data[3];
						RX0_ADDR_TEMP[2] = FIFO_data[4];
						RX0_ADDR_TEMP[3] = FIFO_data[5];
						RX0_ADDR_TEMP[4] = FIFO_data[6];

//						system.cell.mouse_cell[0] = FIFO_data[7] & 0x0F;
//						system.cell.mouse_cell[1] = FIFO_data[8];

						IR_Code_Tmp[0] = FIFO_data[7];
						IR_Code_Tmp[1] = FIFO_data[8];
						IR_Code_Tmp[2] = FIFO_data[9];
//						system_rf_mouse_config();
						if(mouse_bind_step == 1)
							mouse_bind_step = 2;
					}
					break;
					
				case KEYBOARD:	
					if(system.mtp_record.mtp_flag.keyboard_bind == 0)
					{
						RX1_ADDR_TEMP[0] = FIFO_data[2];
						RX1_ADDR_TEMP[1] = FIFO_data[3];
						RX1_ADDR_TEMP[2] = FIFO_data[4];
						RX1_ADDR_TEMP[3] = FIFO_data[5];
						RX1_ADDR_TEMP[4] = FIFO_data[6];

						system.cell.keyboard_cell[0] = FIFO_data[7] & 0x0F;
						system.cell.keyboard_cell[1] = FIFO_data[8];
						
//						system_rf_keyboard_config();
						if(keyboard_bind_step == 1)
							keyboard_bind_step = 2;
					}
					break;
					
				default:
					break;
			}
		}
		else if(DATATYPE_OK == FIFO_data[0])   //完成一次设备对码
		{	
			// Bind step 3.
			switch(FIFO_data[1])		
			{
				case MOUSE:	
					if(system.mtp_record.mtp_flag.mouse_bind == 0)
					{
						RX0_ADDR_TEMP[0] = FIFO_data[2];
						RX0_ADDR_TEMP[1] = FIFO_data[3];
						RX0_ADDR_TEMP[2] = FIFO_data[4];
						RX0_ADDR_TEMP[3] = FIFO_data[5];
						RX0_ADDR_TEMP[4] = FIFO_data[6];

//						system.cell.mouse_cell[0] = FIFO_data[7] & 0x0F;
//						system.cell.mouse_cell[1] = FIFO_data[8];

						IR_Code_Tmp[0] = FIFO_data[7];
						IR_Code_Tmp[1] = FIFO_data[8];
						IR_Code_Tmp[2] = FIFO_data[9];
	
						if(mouse_bind_step != 0x00)
						{
							Sys_bind_data_dispose_step3(~0x80); 	// 0x80
							system.bind.mouse_bind = 1;
							system.mtp_record.mtp_flag.mouse_bind = system.bind.mouse_bind;
							memcpy(&Flash.mtp_pool[RX0_ID_ADDR], &FIFO_data[2], RX0_ID_ADDR_LEN);             
							memcpy(&Flash.mtp_pool[RX0_ID_COPY1_ADDR], &FIFO_data[2], RX0_ID_ADDR_LEN); 
							memcpy(&Flash.mtp_pool[RX0_ID_COPY2_ADDR], &FIFO_data[2], RX0_ID_ADDR_LEN);
							memcpy(&RX0_Address[0], &FIFO_data[2], RX0_ID_ADDR_LEN);
							
							Flash.flash_need_write = 1;
							Sys_FlashWriteAll();
						}
					}
					break;
					
				case KEYBOARD:	
					if(system.mtp_record.mtp_flag.keyboard_bind == 0)
					{
						RX1_ADDR_TEMP[0] = FIFO_data[2];
						RX1_ADDR_TEMP[1] = FIFO_data[3];
						RX1_ADDR_TEMP[2] = FIFO_data[4];
						RX1_ADDR_TEMP[3] = FIFO_data[5];
						RX1_ADDR_TEMP[4] = FIFO_data[6];

						system.cell.keyboard_cell[0] = FIFO_data[7] & 0x0F;
						system.cell.keyboard_cell[1] = FIFO_data[8];
		
						if(keyboard_bind_step != 0x00)
						{
							Sys_bind_data_dispose_step3(~0x10); 	// 0x10
							system.bind.keyboard_bind = 1;
							system.mtp_record.mtp_flag.keyboard_bind = system.bind.keyboard_bind;
							memcpy(&Flash.mtp_pool[RX1_ID_ADDR], &FIFO_data[2], RX1_ID_ADDR_LEN);             
							memcpy(&Flash.mtp_pool[RX1_ID_COPY1_ADDR], &FIFO_data[2], RX1_ID_ADDR_LEN); 
							memcpy(&Flash.mtp_pool[RX1_ID_COPY2_ADDR], &FIFO_data[2], RX1_ID_ADDR_LEN);
							memcpy(&RX1_Address[0], &FIFO_data[2], RX1_ID_ADDR_LEN);
							Flash.flash_need_write = 1;
							Sys_FlashWriteAll();
						}
	
					}
					break;
				default:
					break;
			}
		}
	}	
}
#ifdef	CHIP_BK2535
/*! \fn void application_page_usb_process_clear_page_flag(UINT8 type)
    \brief Dongle clears the paged flag of mouse or keyboard in mtp.
    
    \param type - MOUSE/KEYBOARD
    \return void
*/
void Sys_bind_usb_process_clear_page_flag(UINT8 type)
{
	if(type == MOUSE)
		Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] |= 0x80;
	else
		Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] |= 0x10;
	Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1] = Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];
	Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2] = Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];
}

/*! \fn void application_page_usb_process_clear_mouse(void)
    \brief Dongle clears the paged flag and rf address of mouse in mtp.
    
    \param void
    \return void
*/
void Sys_bind_usb_process_clear_mouse(void)
{
    //refresh all flag
    Sys_bind_usb_process_clear_page_flag(MOUSE);
    //erase id position
    memset(&Flash.mtp_pool[RX0_ID_ADDR], 0xff, RX0_ID_ADDR_LEN);
    memset(&Flash.mtp_pool[RX0_ID_COPY1_ADDR], 0xff, RX0_ID_ADDR_LEN);
    memset(&Flash.mtp_pool[RX0_ID_COPY2_ADDR], 0xff, RX0_ID_ADDR_LEN);
    //clear ram flag
    //system_idata.mtp_record.mtp_flag.mouse_page = 0;	
    //application_dongle_rf_mouse_configure();
}

/*! \fn void application_page_usb_process_clear_kbd(void)
    \brief Dongle clears the paged flag and rf address of keyboard in mtp.
    
    \param void
    \return void
*/
void Sys_bind_usb_process_clear_kbd(void)
{
    //refresh all flag
    Sys_bind_usb_process_clear_page_flag(KEYBOARD);
    //erase id position
    memset(&Flash.mtp_pool[RX1_ID_ADDR], 0xff, RX1_ID_ADDR_LEN);
    memset(&Flash.mtp_pool[RX1_ID_COPY1_ADDR], 0xff, RX1_ID_ADDR_LEN);
    memset(&Flash.mtp_pool[RX1_ID_COPY2_ADDR], 0xff, RX1_ID_ADDR_LEN);
    //clear ram flag
    //system_idata.mtp_record.mtp_flag.keyboard_page = 0;
    //application_dongle_rf_keyboard_configure();
}
#endif
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
void system_bind_usb_process(void)
{
	BYTE bind_temp[5];
	bind_temp[0] = 0x00;
	bind_temp[1] = 0x00;
	bind_temp[2] = 0x00;
	
	if(system.usbp0_data.aceept)
	{
		system.usbp0_data.aceept = 0;

		if(COMMAND_BIND == system.usbp0_data.set_report_data[0])
		{
			switch(system.usbp0_data.set_report_data[1])
			{
				case COM_BIND_GET :
					bind_temp[0] = ~Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];

					system.usbp0_data.get_report_data[1] = (bind_temp[0] & 0x80) ? 1 : 0;
					system.usbp0_data.get_report_data[2] = (bind_temp[0] & 0x10) ? 1 : 0;
					system.usbp0_data.reday_report_flag = 1;
					break;
				case COM_BIND_CLE : 

					Sys_bind_usb_process_clear_mouse();
                    			Sys_bind_usb_process_clear_kbd();
					Flash.flash_need_write = 1;
					Sys_FlashWriteAll();

					system.mtp_record.mtp_flag.mouse_bind = 0;	
					system.mtp_record.mtp_flag.keyboard_bind = 0;	
					system_rf_mouse_config();
					system_rf_keyboard_config();
					system.usbp0_data.reday_report_flag = 1;
					break;
				case COM_BIND_CLE_MS:
	
					Sys_bind_usb_process_clear_mouse();
					Flash.flash_need_write = 1;
					Sys_FlashWriteAll();

					system.mtp_record.mtp_flag.mouse_bind = 0;	
					system_rf_mouse_config();
					system.usbp0_data.reday_report_flag = 1;
					break;
				case COM_BIND_CLE_KB: 

                    		Sys_bind_usb_process_clear_kbd();
					Flash.flash_need_write = 1;
					Sys_FlashWriteAll();

					system.mtp_record.mtp_flag.keyboard_bind = 0;
					system_rf_keyboard_config();
					system.usbp0_data.reday_report_flag = 1;
					break; 
				case COM_BIND_EXIT: 
					system.work_mode = SYSTEM_WORK;
					system.usbp0_data.reday_report_flag = 1;
					break;
				default:
					system.usbp0_data.reday_report_flag = 0;
					break;
			}
		}
		else
		{
			switch(system.usbp0_data.set_report_data[0])
			{	// Get report request.
				case COMMAND_CURRENT_MODE :
					system.usbp0_data.get_report_data[1] = COMMAND_BIND;
					system.usbp0_data.reday_report_flag = 1;
					break;
				case COMMAND_KBCELL :
					system.usbp0_data.get_report_data[1] = system.cell.keyboard_cell[0];
					system.usbp0_data.get_report_data[2] = system.cell.keyboard_cell[1];
					system.usbp0_data.reday_report_flag = 1;
					break;
				case COMMAND_MSCELL :
					system.usbp0_data.get_report_data[1] = system.cell.mouse_cell[0];
					system.usbp0_data.get_report_data[2] = system.cell.mouse_cell[1];
					system.usbp0_data.reday_report_flag = 1;
					break;
				default:
					system.usbp0_data.reday_report_flag = 0;
					break;
			}
		}

		system.usbp0_data.set_report_data[0] = 0x00;
		system.usbp0_data.set_report_data[1] = 0x00;
		system.usbp0_data.set_report_data[2] = 0x00;
	}
}
/***********************************************************
						end file
***********************************************************/
