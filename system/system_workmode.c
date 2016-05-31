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
			  2011/03/01  	 0.1  		build this moudle 
***********************************************************/

#include "Headfile\includes.h"

bit bFIFOReady;
bit bRFConnect;
bit bRFIdle;
bit bUSBMode;
BYTE uRFDisConnectTime;
//BYTE uRFPacketID;
UINT16 XDATA wRXIdleTime;
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
void system_work_mode(void)
{
	system_work_ini();

	while(SYSTEM_WORK == system.work_mode)
	{
		switch(system.work_sub_mode)
		{
			case SYSTEM_WORK_WORK:
				RF_RX_Check();
				FreqProcess();
				CheckRFDisconnect();
				if(bUSBMode)
				{
					usb_uploading();

					system_acceptdata_process();
				}
				
				if(u10msFlag & bSysCheck)
				{
					u10msFlag &= ~bSysCheck;
					if(!bUSBMode)
						Sys_PowerDownCtrl();
				}

				if(bUSBMode)
				{
					system_suspend();
				}		
				break;
				
			case SYSTEM_WORK_SUSPEND:
				system_suspend_mode();
				break;
				
			default:
				break;
		}
		
	}
	
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
void system_work_ini(void)
{
	InitFreqHopper();
	uRFDisConnectTime = 0;
	bRFConnect = 0;
	bRFIdle = 0;
	wRXIdleTime = 0;
	
	system.work_sub_mode = SYSTEM_WORK_WORK;
	system.bind.keyboard_requst_cnt = 3;

	memset(FIFO_data, 0,32);
//	memset(&system.usbp1_data.in_report,0,8);
	memset(&system.usbp1_data.re_data_copy,0,EP1_PACKET_SIZE);
	memset(&system.usbp1_data.re_data,0,EP1_PACKET_SIZE);
	
	memset(&system.usbp1_data.re_data3,0,EP1_PACKET_SIZE);
	system.usbp1_data.bInitBuf3 = 0;

	memset(&system.usbp2_data.in_report,0,9);

	system.powered = 0;
	RF_SetNomalOuput();
	SwitchToRxMode();

	FLUSH_TX;								
	FLUSH_RX;
	
	LEDOff();
//	uRFPacketID = 0;
}
//-------------------------------------------------------
// Uploading release key state while RF disconnect.
//-------------------------------------------------------
void CheckRFDisconnect(void)
{
	BYTE i;
	if(u10msFlag & bRFConnectTimer)
	{
		u10msFlag &= ~bRFConnectTimer;
		uRFDisConnectTime++;
		
		if(bRXEndPacket)
			uRFDisConnectTime = 0;

		if(uRFDisConnectTime > cRFDisConnectTime)
		{
			uRFDisConnectTime = 0;
			if(bRFConnect)
			{
				bRFConnect = 0;
				bRXEndPacket = 1;
				if(bUSBMode)
				{
					// USB
					if(system.szKeyData[0] || system.szKeyData[1]	\
						|| system.szKeyData[2] || system.szKeyData[3]	\
						|| system.szKeyData[4] || system.szKeyData[5] || system.szKeyData[6])
					{
						system.usbp2_data.bKBDataUpload = 1;
						for(i = 0; i < 7; i++)
						{
							system.szKeyData[i] = 0;
							system.szLastKeyData[i] = 0;
						}
						system.uKeyLens = 0;
					}
					
					if((system.uMultiKey[0]) || (system.uMultiKey[1]))
					{
						system.usbp2_data.bMediaDataUpload = 1;
						system.uMultiKey[0] = 0;
						system.uMultiKey[1] = 0;
						system.uLastMultiKey = 0;
					}

					if(system.szMSData[0])
					{
						system.usbp2_data.bMSDataUpload = 1;
						system.szMSData[0] = 0;
						system.szMSData[1] = 0;
						system.szMSData[2] = 0;
					}
				}
				
			}
		}
	}
}
//-------------------------------------------------------
//-------------------------------------------------------
void Sys_RFPowerOn(void)
{	
		PowerUp_RF();
		BK2401_CE = 1;
		
		FLUSH_TX;
		FLUSH_RX;
		BK2401_STATUS = (STATUS_MAX_RT|STATUS_TX_DS|STATUS_RX_DR);
}

//-------------------------------------------------------
// Function: over cRXIdleTime no received data, entry power down mode
//-------------------------------------------------------
void Sys_PowerDownCtrl(void)
{
	UINT8 uTmp;
	wRXIdleTime++;
	if(bRFIdle)
	{					// cRXIdleTime
		if(wRXIdleTime >= cWorkTime)
		{	
//			LEDOff();
	
			uTmp = CLK_EN_CFG;
			CLK_EN_CFG = 0x40;			// Only enable Timer0,1,2 clock.
			PowerDown_RF();
			WaitUs(10);
			#if	1
			TF0=0;					// Clear timer0 overflow flag.
			TR0 = 0; 				// Timer0 stop.
			TL0 = (65127 & 0x00FF);	// Timer0 is clocked by CLK/4, about 50ms.
			TH0 = (65127 >> 8);			
			TR0 = 1; 	
			#endif
//			MCU_SLEEP();			// PowerDown(OSC32K Select, IDLE)
			MCU_IDLE_32K();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			PCON2 &= ~0x06;			//  
			WaitUs(60);				// After wakeup RC OSC 16MHZ used, after 400us switche to XOSC 16MHZ automatically. 
			SwitchToRxMode();
			Sys_RFPowerOn();
//			LEDOn();

			CLK_EN_CFG = uTmp;
			wRXIdleTime = 0;
			InitSysTimer();
		}
	}
	else
	{					// Normal work
		if(wRXIdleTime > cRXIdleTime)
		{
//			wRXIdleTime = 0;
			bRFIdle = 1;
		}
	}
}
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
void Sys_KeyScan(void)
{
	KeyScan();
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
void system_acceptdata_process(void)
{
	if(system.usbp0_data.aceept)
	{
		system.usbp0_data.aceept = 0;

		switch(system.usbp0_data.set_report_data[0])
		{
			case COMMAND_MODE :
				switch(system.usbp0_data.set_report_data[1])
				{	// 0xA0, 0x81
					case COM_MODE_BIND : 
						system.work_mode = SYSTEM_BIND; 
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_MODE_CODE : 
						system.work_mode = SYSTEM_CODE; 
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_MODE_TEST : 
						system.work_mode = SYSTEM_TEST; 
						system.usbp0_data.reday_report_flag = 1;
						break;
					case COM_MODE_DEBUG: 
						system.work_mode = SYSTEM_DEBUG;
						system.usbp0_data.reday_report_flag = 1;
						break; 
					default:
						system.usbp0_data.reday_report_flag = 0;
						break;
				}
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
			case COMMAND_SIGNAL :
				system.usbp0_data.get_report_data[1] = uSignalQuality;
				uSignalQuality = 0;
				system.usbp0_data.reday_report_flag = 1;
				break;
			case COMMAND_CURRENT_MODE :
				system.usbp0_data.get_report_data[1] = COMMAND_MODE;
				system.usbp0_data.reday_report_flag = 1;
				break;
			default :
				system.usbp0_data.reday_report_flag = 0;
				break;
		}

		system.usbp0_data.set_report_data[0] = 0x00;
		system.usbp0_data.set_report_data[1] = 0x00;
		system.usbp0_data.set_report_data[2] = 0x00;
	}
	#if	0
	if(system.cpi.cpi_updata == 1)
	{
		if(0 == system.cpi.cpi_save)
		{
			MTP_ADR=CUSTOM_CPI_ADDR;  //写0
		 	MTP_DAT=0x00; 
			MTP_CTL|=0x80;
			while(MTP_CTL & 0x80);
			MTP_ADR=CUSTOM_CPI_ADDR; //clear
		 	MTP_CTL|=0x20;
			system.cpi.cpi_save = 1;
		}
		if(system.cpi.cpi_save)
		{
			if((MTP_CTL & 0x20) == 0)
			{
				MTP_ADR=CUSTOM_CPI_ADDR;  
			 	MTP_DAT=system.cpi.cpi_val; 
				MTP_CTL|=0x80;
				while(MTP_CTL & 0x80);
				system.cpi.cpi_save = 0;
				system.cpi.cpi_updata = 0;
			}
		}
	}
	#endif
	//  NUMLOCK P_LED
}
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
void system_suspend(void)
{
//	BYTE i;
	
	if(usb_suspend)
	{
		system.work_sub_mode = SYSTEM_WORK_SUSPEND;
		#if 0
		for(i = 0; i < 10; i++)
		{
			LEDToggle();
			WaitUs(10000);
		}
		#endif
	}
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
void system_suspend_mode(void)
{
	UINT8 i,TEMP;
//	UINT8 sta,len;
	
	LEDOff();
	USB_EN0 |= 0x02;				// USB Resume interrupt enable.
	USB_PWR_CN |= 0x02;			// USB Enter lowpower mode.

	TEMP = CLK_EN_CFG;
	CLK_EN_CFG = 0x40;			// Only enable Timer0,1,2 clock.
	PALT1 = 0;
	PCON2 &= ~0x40;  			// close 48M_en         	
//	PCON |= 0x04;

	while(1)
	{
		PowerDown_RF();
		#if	0
		TF0=0;					// Clear timer0 overflow flag.
		TR0 = 0; 				// Timer0 stop.
		TL0 = (65050 & 0x00FF);	// Timer0 is clocked by CLK/4, about 60ms.
		TH0 = (65050 >> 8);			
		TR0 = 1; 	
		#endif
		PCON2 |= 0x05;			// PowerDown(OSC32K Select, IDLE)
		i=0;						// PowerUp
		
		
		PowerUp_RF();
		WaitUs(60);
		#if	0
//		PCON2 |= 0x04;
		TF0=0;
		TR0 = 0; 
		TL0 = (65500 & 0x00FF);
		TH0 = (65500 >> 8);			
		TR0 = 1; 	
		PCON2 |=0x05;	//PowerDown

//		PCON2 |=0x04;
		
		sta=BK2401_STATUS;  
		if(sta & STATUS_RX_DR)
		{
			len = BK2401_RPL_WIDTH;    
			RF_ReadData(len);
			//if((FIFO_data[0] & 0x01) == 0x00)   				//鼠标处理
			//{
			if((FIFO_data[0] & 0xF0) != 0xF0)	
			{
				PCON2 |= 0x40;
				PCON2 &= ~0x06; 
				CLK_EN_CFG = TEMP;
				
				FLUSH_RX;  
				BK2401_STATUS = sta; 

		        if(Remote_Wakeup)
		        {
				while (CFG_EP1_1 != 0xec);
		        	USB_PWR_CN = 0x80;
		        	Delay(10);
		       	USB_PWR_CN  = 0x84;
				 
				USB_PWR_CN |= 0x01;
				Delay(5);
				USB_PWR_CN &= ~0x01;

				usb_suspend = 0;
	       		system.work_sub_mode = SYSTEM_WORK_WORK;	
		        }
			else
			{				
				USB_PWR_CN |= 0x02;
				CLK_EN_CFG=0x40;
				PCON2 &= ~ 0x40;  // close 48M_en    				
			}
			}
			else
			{
				FLUSH_RX;  
				BK2401_STATUS = sta; 
			}
		}	
		//}
		#endif
		if(usb_suspend == 0)
		{
			#if	0
			system.usbp1_data.in_report[0] = 0x00;
			system.usbp1_data.in_report[2] = 0x00;
			system.usbp1_data.in_report[3] = 0x00;
			system.usbp1_data.in_report[4] = 0x00;
			system.usbp1_data.in_report[5] = 0x00;
			system.usbp1_data.in_report[6] = 0x00;
			system.usbp1_data.in_report[7] = 0x00;
			
			system.usbp1_data.uploading = 1;
			if(system.media_uploading_flag) 
			{
				system.media_uploading_flag = 0;
				system.media_uploading = 1;
				system.usbp2_data.uploading = 1;
				system.media_key[0] = 0x03;
				system.media_key[1] = 0x00;
				system.media_key[2] = 0x00;
			}
			if(system.power_uploading_flag)
			{
				system.power_uploading_flag = 0;
				system.power_uploading = 1;
				system.usbp2_data.uploading = 1;
				system.power_key[0] = 0x02;
				system.power_key[1] = 0x00;
			}
			#endif
			PCON2 |= 0x40;				// USB enable, 48MHZ clock enable.   
			PCON2 &= ~0x06;				//  
			CLK_EN_CFG = TEMP;
		
	    		while (CFG_EP1_1 != 0xCC)
	        		USB_PWR_CN = 0x80;		// Bit7: D+ pullup enable.
	        	USB_PWR_CN = 0x84;			// Bit2: USB Reset
	       	 	system.work_sub_mode = SYSTEM_WORK_WORK;	
		#if 0		
			for(i = 0; i < 7; i++)
			{
				LEDToggle();
				WaitUs(4000);
			}
		#endif
	       	break;
		}	
	}
}
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
void PacketHeadDecode(void)
{
	if(FIFO_data[1] & cSyncReq)
	{
		ResetSysTimer();
	}	
	bRXEndPacket = 0;
}
//====================================================
/*-------------------------------------------------------
uMICBuf composition of packet head and packet payload.
Low nibble of packet head is packet lens. High nibble of packet head is packet format.
Packet lens must less 15.
按键数据包两个字节head byte.
 ______________     ______________
|      Head        |+  |    payload       |
|_____________|    |____________ |
---------------------------------------------------------*/
void SaveRXData(BYTE uLen)
{
	BYTE DATA i,j;
	BYTE DATA uLens;
	if(!uLen)
		return;
	else
	{
		PacketHeadDecode();
		bRFRXData = 1;
		bCurFreqActive = 1;
		bRFConnect = 1;
		
		bRFIdle = 0;
		wRXIdleTime = 0;
		if((FIFO_data[0] & cParketIDMark) != system.uPacketID)
		{			
			uRFDisConnectTime = 0;
			system.uPacketID = FIFO_data[0] & cParketIDMark;
//			if(bUSBMode)
//			{
				i = 2;

				if(FIFO_data[1] & cMSData)
				{
					i = 3;
					#if 1
					if(FIFO_data[1] & cMSXY)
					{
						system.szMSData[0] = FIFO_data[2] & 0x7f;
						system.szMSData[1] = FIFO_data[3];
						system.szMSData[2] = FIFO_data[4];
						system.usbp2_data.bMSDataUpload = 1;
						i = 5;
					}
					else if(system.szMSData[0] != (FIFO_data[2] & 0x7f))
					{
						system.szMSData[0] = FIFO_data[2] & 0x7f;
						system.szMSData[1] = 0;
						system.szMSData[2] = 0;
						system.usbp2_data.bMSDataUpload = 1;
					}
					#endif
			
				}
	
			
				if(FIFO_data[1] & cMultiKeyData)
				{
					system.uMultiKey[0] = FIFO_data[i];
					i++;
					system.usbp2_data.bMediaDataUpload = 1;
					if(system.uMultiKey[0] == system.uLastMultiKey) //&& system.uLastMultiKey)
						system.usbp2_data.bMediaDataUpload = 0;
					system.uLastMultiKey = system.uMultiKey[0];
				}
				
				if(FIFO_data[1] & cKeyData)
				{
					system.szKeyData[0] = 0;
					system.szKeyData[1] = 0;
					system.szKeyData[2] = 0;
					system.szKeyData[3] = 0;
					system.szKeyData[4] = 0;
					system.szKeyData[5] = 0;
					system.szKeyData[6] = 0;
					
					uLens = FIFO_data[1] & cKeyLensMark;
					for(j = 0; j < uLens; j++)
					{
						system.szKeyData[j] = FIFO_data[i];
						i++;
					}
					system.usbp2_data.bKBDataUpload = 0;
					
					if(uLens == system.uKeyLens)
					{
						if(uLens)
						{
							for(j = 0; j < uLens; j++)
							{
								if(system.szKeyData[j] != system.szLastKeyData[j])
								{
									system.usbp2_data.bKBDataUpload = 1;
									break;
								}
							}
						}
					}
					else
						system.usbp2_data.bKBDataUpload = 1;
					
					for(j = 0; j < 7; j++)
					{
						system.szLastKeyData[j] = system.szKeyData[j];
					}
					system.uKeyLens = uLens;
				}
//			}
			
		}
		else
		{
			i = 2;

			if(FIFO_data[1] & cMSData)
			{
				if(system.szMSData[0] != (FIFO_data[2] & 0x7f))
					system.usbp2_data.bMSDataUpload = 1;
				
				system.szMSData[0] = FIFO_data[2] & 0x7f;
				i = 3;
				if(FIFO_data[1] & cMSXY)
				{
					system.szMSData[1] = FIFO_data[3];
					system.szMSData[2] = FIFO_data[4];
					system.usbp2_data.bMSDataUpload = 1;
					i = 5;
				}
				else
				{
					system.szMSData[1] = 0;
					system.szMSData[2] = 0;
				}
			}

			if(FIFO_data[1] & cMultiKeyData)
			{
				system.uMultiKey[0] = FIFO_data[i];
				i++;
				system.usbp2_data.bMediaDataUpload = 1;
				if(system.uMultiKey[0] == system.uLastMultiKey)	// && system.uLastMultiKey)
					system.usbp2_data.bMediaDataUpload = 0;
				system.uLastMultiKey = system.uMultiKey[0];
			}
			
			if(FIFO_data[1] & cKeyData)
			{
				system.szKeyData[0] = 0;
				system.szKeyData[1] = 0;
				system.szKeyData[2] = 0;
				system.szKeyData[3] = 0;
				system.szKeyData[4] = 0;
				system.szKeyData[5] = 0;
				system.szKeyData[6] = 0;
				uLens = FIFO_data[1] & cKeyLensMark;
				for(j = 0; j < uLens; j++)
				{
					system.szKeyData[j] = FIFO_data[i];
					i++;
				}
				system.usbp2_data.bKBDataUpload = 0;
				if(uLens == system.uKeyLens)
				{
					if(uLens)
					{
						for(j = 0; j < uLens; j++)
						{
							if(system.szKeyData[j] != system.szLastKeyData[j])
							{
								system.usbp2_data.bKBDataUpload = 1;
								break;
							}
						}
					}
				}
				else
					system.usbp2_data.bKBDataUpload = 1;
				
				for(j = 0; j < 7; j++)
				{
					system.szLastKeyData[j] = system.szKeyData[j];
				}
				system.uKeyLens = uLens;

			}
			
		}
	}
}

/***********************************************************
						end file
***********************************************************/
