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
<author> 		<time> 			<version > 		<desc>
			  2011/03/01  		  0.1  			build this moudle 
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
void system_test_mode(void)
{
	BYTE i=0;
	BYTE channel = 0;
	BYTE sc_sub_mode = 0;
	BYTE sc_count = 0;
	BYTE uTestCHIndex;
	BYTE uLEDBlinkDuty;
	
	BK2401_RETR = 0x00;						
	BK2401_ENAA = 0x00;
	BK2401_ENRX = 0x00;
	PowerUp_RF();
	SwitchToTxMode();
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;
	
	i = 1;
	uTestCHIndex = TEST_CHANNEL[i];	
	BK2401_RFCH=RF_TABLE[uTestCHIndex];
	channel = RF_TABLE[uTestCHIndex];

	RF_SetLowOuput();
//	RF_Set_Mode(1);
	RF_Set_Mode(0);
	system.work_sub_mode = TEST_SC;
	
	uLEDBlinkDuty = 0;
	
	if(get_bindkey())
		system.Key.bKey.bBindKeyState = 1;
	
	while(system.work_mode == SYSTEM_TEST)
	{
		if(u10msFlag & bSysCheck)
		{
			u10msFlag &= ~bSysCheck;
			Sys_KeyScan();
			if(system.Key.bKey.bBindKeyValid)
			{
				system.Key.bKey.bBindKeyValid = 0;
				i++;
				if(i>=3)
				{
					i=0;
				}
				uTestCHIndex = TEST_CHANNEL[i];	
				BK2401_RFCH=RF_TABLE[uTestCHIndex];
				channel = uTestCHIndex;
			}

			if(++uLEDBlinkDuty > 99)
			{
				uLEDBlinkDuty = 0;
				LEDToggle();
			}
			
			switch(system.work_sub_mode)  	//测试模式
			{
				case TEST_SC:				//单载波	
					break;
					
				case TEST_CD:				//调试 ，FCC测试
					FIFO_data[0] = 0xCC;
					FIFO_data[1] = 0xCC;
					FIFO_data[2] = 0xCC;
					FIFO_data[3] = 0xCC;
					FIFO_data[4] = 0xCC;
					FIFO_data[5] = 0xCC;
					FIFO_data[6] = 0xCC;
					FIFO_data[7] = 0xCC;
					FIFO_data[8] = 0xCC;
					FIFO_data[9] = 0xCC;
					FIFO_data[10] = 0xCC;
					FIFO_data[11] = 0xCC;
					FIFO_data[12] = 0xCC;
					FIFO_data[13] = 0xCC;
					FIFO_data[14] = 0xCC;
					FIFO_data[15] = 0xCC;
					FIFO_data[16] = 0xCC;
					FIFO_data[17] = 0xCC;
					FIFO_data[18] = 0xCC;
					FIFO_data[19] = 0xCC;
					FIFO_data[20] = 0xCC;
					FIFO_data[21] = 0xCC;
					FIFO_data[22] = 0xCC;
					FIFO_data[23] = 0xCC;
					FIFO_data[24] = 0xCC;
					W_TX_PAYLOAD_NOACK(FIFO_data,25);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,25);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,25);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,25);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,25);
					WaitUs(50);
					break;
					
				case TEST_RF_DATA:			//发送数据
					FIFO_data[0] = DATATYPE_MOUSE;
					FIFO_data[1] = 0;	
					FIFO_data[2] = 0;
					FIFO_data[3] = 2;
					FIFO_data[4] = 0;
					W_TX_PAYLOAD_NOACK(FIFO_data,5);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,5);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,5);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,5);
					WaitUs(50);
					W_TX_PAYLOAD_NOACK(FIFO_data,5);
					WaitUs(50);
					break;
					
				default:
					system.work_sub_mode = TEST_SC;
					break;
			}

			switch(sc_sub_mode)
			{
				case 0 :
					break;
					
				case 1 :
					sc_count++;
					if(sc_count >= 2)
					{
						sc_count = 0;
						channel++;
						if(channel >= 82)
						{
							channel = 0;
						}		
						BK2401_RFCH=channel;
					}
					break;
					
				case 2 :
					sc_count++;
					if(sc_count >= 2)
					{
						sc_count = 0;
						if(channel == 0)
						{
							channel = 82;	
						}else{
							channel--;
						}		
						BK2401_RFCH=channel;
					}
					break;
					
				default:
					break;
			}
		}
		
		//usb data dispose
		if(system.usbp0_data.aceept)
		{
			system.usbp0_data.aceept = 0;

			if(COMMAND_TEST == system.usbp0_data.set_report_data[0])
			{
				switch(system.usbp0_data.set_report_data[1])
				{
					case COM_TEST_SC : 
						system.work_sub_mode = TEST_SC; 
						RF_Set_Mode(0);
						system.usbp0_data.reday_report_flag = 1; 
						break;
						
					case COM_TEST_CD: 
						system.work_sub_mode = TEST_CD; 
						RF_Set_Mode(1); 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_DAT: 
						system.work_sub_mode = TEST_RF_DATA; 
						RF_Set_Mode(1);  
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_LOW_CH:   
						i=0;
						uTestCHIndex = TEST_CHANNEL[i];	
						BK2401_RFCH=RF_TABLE[uTestCHIndex];
						channel = uTestCHIndex;
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_MID_CH:  
						i=1;
						uTestCHIndex = TEST_CHANNEL[i];	
						BK2401_RFCH=RF_TABLE[uTestCHIndex];
						channel = uTestCHIndex;
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_HIG_CH: 
						i=2;
						uTestCHIndex = TEST_CHANNEL[i];	
						BK2401_RFCH=RF_TABLE[uTestCHIndex];
						channel = uTestCHIndex;
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_SW_HIG: 
						sc_sub_mode = 1; 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_SW_LOW: 
						sc_sub_mode = 2; 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_SW_STOP: 
						sc_sub_mode = 0; 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_POW_5: 
						RF_Set_ouput_power(3); 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_POW_0: 
						RF_Set_ouput_power(2); 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_POW_N5: 
						RF_Set_ouput_power(1); 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_POW_N10: 
						RF_Set_ouput_power(0); 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					case COM_TEST_EXIT:  
						system.work_mode = SYSTEM_WORK; 
						system.usbp0_data.reday_report_flag = 1;
						break;
						
					default : 
						system.usbp0_data.reday_report_flag = 0; 
						break;
				}
			}
			else if(COMMAND_CURRENT_MODE  == system.usbp0_data.set_report_data[0])
			{
				system.usbp0_data.get_report_data[1] = COMMAND_TEST;
				system.usbp0_data.reday_report_flag = 1;
			}
		}
	}
	BK2433_RF_Initial();
	SwitchToRxMode();
	PowerUp_RF();
}

/***********************************************************
						end file
***********************************************************/