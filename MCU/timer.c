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
<author>      <time>         <version >          <desc>
	        2011/03/01           0.1          build this moudle 
***********************************************************/

#include "Headfile\includes.h"

BYTE bdata u10msFlag;
BYTE DATA uMCUTick;
bit b2msFlag;
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
void InitSysTimer(void)
{
// Timer0/1/2 clock enable.
	CLK_EN_CFG |= 0x40 ;
	ET0 = 0; 	
	TR0 = 0; 
	TF0 = 0;
// [TMOD]
// Bit3: Gate: 0, Timer0 will clock only when TR0 = 1;
// Bit2: Counter/Timer select.  C/T = 0 Timer0 is clocked by CLK/4 or CLK/12, depending on CKCON.3.
// Bit1~0: Timer0 work mode.
	TMOD &= 0xf0; 	
	TMOD |= 0x01;						//using Timer0 as tick base
	TL0 = (TIMER0_2MS_CNT & 0x00FF);
	TH0 = (TIMER0_2MS_CNT >> 8);	
	uMCUTick = 0;
	ET0 = 1;							//enable Timer0 int
	TR0 = 1;							// Timer0 RUN control.
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
void ResetSysTimer(void)
{
	TR0 = 0; 
	TF0 = 0;
	TL0 = (TIMER0_2MS_CNT & 0x00FF);
	TH0 = (TIMER0_2MS_CNT >> 8);	
	TR0 = 1; 

//	uMCUTick = 0;
//	u10msFlag = 0;

}
//-------------------------------------------------------
void TimeOutSet(void)
{
	u10msFlag &= ~b10msDelayTimer;
}
//-------------------------------------------------------
//Function: 
//Desc	: 	1us == 10us 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
// WaitUs(10); about 75us(16MHZ)
//-------------------------------------------------------
void WaitUs(UINT32 us)	
{
	UINT16 	i;
	while (us)
	{
		for (i = 0; i < 1; ++i);
		us--;
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
void WaitMs(UINT8 ms)	
{	
	UINT8 uMS;
	TimeOutSet(); 
//	while (!IsTimeOut(ms));
	uMS = ms;
	while(1)
	{
		if(u10msFlag & b10msDelayTimer)
		{
			u10msFlag &= ~b10msDelayTimer;
			uMS--;
			if(uMS == 0)
				break;
		}
	}
}


/***********************************************************
						end file
***********************************************************/