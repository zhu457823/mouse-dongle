/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: interrupt.c
Author		: 
Date		: 2011/03/01
Description	: 
Version		: v0.1
Function List: 
----
----
History: 
<author>       <time>      <version >          <desc>
               2011/03/01        0.1                build this moudle 
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
void ISR_Timer0 (void) interrupt 1 //using 2
{
	TR0 = 0; 
	TF0 = 0;
	TL0 = (TIMER0_2MS_CNT & 0x00FF);
	TH0 = (TIMER0_2MS_CNT >> 8);	
	TR0 = 1;
	if(++uMCUTick > cMCUTickDuty)
	{							// 10ms
		u10msFlag = 0xff;
		uMCUTick = 0;
	}
	b2msFlag = 1;
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
void Usb_ISR (void) interrupt 10       // Top-level USB ISR
{ 

      if (( USBINT0 & 0x80 )|| ( USBINT0 & 0x40 ))  // Handle ep0 receive_data and send_data interrupt
      {
         handle_Control ( );
      }
      if ( USBINT0 & 0x20 )            // Handle ep1-7 receive_data interrupt
      {                                
         handle_Out( );             
      }
      if ( USBINT0 & 0x10 )            // Handle ep1-7 send_data interrupt
      {                                
         handle_In ( );
      }
      if ( USBINT0 & 0x08 )            // USB_rst interrupt
      {  
           handle_Reset ( );                               
      }
      if ( USBINT0 & 0x04 )            // Handle Suspend interrupt
      {
           handle_Suspend ( );
      }
      if ( USBINT0 & 0x02 )            // Handle resume interrupt
      {
           handle_Resume ( );
      }
      if ( USBINT0 & 0x01 )            // Handle SOF interrupt
      {  
           handle_SOF ( );
      }
      if ( USBINT1 & 0x80 )            // Handle SOF interrupt
      {  
           handle_Unsupported_Token ( );
      }
      if ( USBINT1 & 0x40 )            // Handle SOF interrupt
      {  
           handle_CRC_Err ( );
      }
      if ( USBINT1 & 0x20 )            // Handle SOF interrupt
      {  
           handle_Overtime ( );
      }
      if ( USBINT1 & 0x10 )            // Handle SOF interrupt
      {  
           handle_Data_Pid_Err ( );
      }                     
      
      AIF &= ~0x04;    // clr mcu flag     
 //     INT_USB = 0;
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
void Int0 (void) interrupt 0
{

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
void Int1 (void) interrupt 2
{
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
void int2 (void) interrupt 8    
{
    AIF=0x00;
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
void int3 (void) interrupt 9		// I2C interrupt    
{
    AIF=0x00;
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
void int5 (void) interrupt 11	// RF interrupt  
{
    AIF=0x00;
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
void int6 (void) interrupt 12  
{
    AIF=0x00;
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
void int7 (void) interrupt 13	// PWM interrupt  
{
    AIF=0x00;
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
void int8 (void) interrupt 14  	// ADC interrupt
{
#if	0
 	BYTE i;

/*
    	system.adc.adc_dat = 0x00;
    	i = ADCDL;
    	system.adc.adc_dat = ADCDH & 0x03;
    	system.adc.adc_dat = (system.adc.adc_dat << 8);
    	system.adc.adc_dat |= i;
	system.adc.adc_int = 1;
*/
#endif
    	AIF &= ~0x40;			// Clear ADC interrupt flag.
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
void int9 (void) interrupt 15	// DES interrupt.    
{
    AIF=0x00;
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
void ISR_timer1 (void) interrupt 3
{
}


void ISR_Timer2(void) interrupt 5
{
	TF2 = 0;
	EXF2 = 0;
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
void pfi (void)  interrupt 6
{  
 //   EICON &= ~0x10;     
}


/***********************************************************
						end file
***********************************************************/