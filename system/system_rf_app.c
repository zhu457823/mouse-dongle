/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: 
Author		: 
Date		: 2011/03/01
Description	: 
Version		: v0.3
Function List: 
----
History: 
<author> 		<time>		 <version >		 <desc>
		 		2011/03/01  		0.1 			 build this moudle 
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
void RF_RX_Check(void)
{
	UINT8 DATA sta;
	UINT8 DATA len;

	sta = BK2401_STATUS;  
	if(sta & STATUS_RX_DR)			
	{												// 1: RF Receive data
//		LEDOn();
		len = BK2401_RPL_WIDTH;    
		RF_ReadData(len);
		BK2401_STATUS=sta;	
		FLUSH_RX;
//		LEDOff();
		if((sta & 0x0e) == 0x02)						//	Pipe1 received data
		{
			if(system.powered == 0)
			{	
				if((FIFO_data[0] == DATATYPE_BIND)&&(FIFO_data[1] == MOUSE))
				{
					system.work_mode = SYSTEM_BIND;
				}
			}
		}
		else
		{
			SaveRXData(len);
		}
	}	
}

//-------------------------------------------------------
//Function: Write payload to be transmitted together with ACK packet on pipe 0.
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
void system_rf_mouse_config(void)
{
	FLUSH_TX;
	
	FIFO_data[0] = DATATYPE_MOUSE;
	FIFO_data[1] = SYSTEM_CONFIG;
	
	FIFO_data[2] = system.mouse_config.mouse_type;
	FIFO_data[3] = system.mouse_config.auto_down;
	#if	0
	FIFO_data[4] = system.mouse_config.CPI[0];
	FIFO_data[5] = system.mouse_config.CPI[1];
	FIFO_data[6] = system.mouse_config.def_CPI;
	FIFO_data[7] = system.mouse_config.usr_CPI;
	#endif
	FIFO_data[8] = system.mouse_config.low_power[0];
	FIFO_data[9] = system.mouse_config.low_power[1];

//	W_ACK_PAYLOAD(FIFO_data,10,0);
	W_ACK_PAYLOAD(FIFO_data,3,0);
}

//-------------------------------------------------------
//Function: Write payload to be transmitted together with ACK packet on pipe 1.
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
void system_rf_keyboard_config(void)
{
	BYTE len = 0;
	
	FLUSH_TX;
	
#ifdef DEBUG
	if(BK2401_FIFOSTATUS & 0x10)
	{
		DEG(("1tx emp\n"));
	}
	else
	{
		DEG(("1tx fifo\n"));
	}
#endif
	
	FIFO_data[0] = DATATYPE_KEYBOARD;
	FIFO_data[1] = SYSTEM_CONFIG;
	#if	0
	FIFO_data[2] = system.keyboard_config.keyboard_type;
	FIFO_data[3] = system.keyboard_config.BK_led;
	FIFO_data[4] = system.keyboard_config.num_pad;
	FIFO_data[5] = system.keyboard_config.small_KB;
	FIFO_data[6] = system.keyboard_config.KB_lp[0];
	FIFO_data[7] = system.keyboard_config.KB_lp[1];
	FIFO_data[8] = system.keyboard_config.fn_num;
	#endif
	len = 9;
	W_ACK_PAYLOAD(FIFO_data,len,1);

#ifdef DEBUG	
	if(BK2401_FIFOSTATUS & 0x10)
	{
		DEG(("2tx emp\n"));
	}
	else
	{
		DEG(("2tx fifo\n"));
	}
#endif

}
/***********************************************************
						end file
***********************************************************/
