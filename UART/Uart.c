/***********************************************************
Copyright (C),Tech Esense Co., Ltd.
FileName		: Uart.c
Author			: joe
Date			: 2010-11-03
Description		: 
Version			: 1.0bate
Function List	: 
--
History			: 
<author> <time>	<version> <desc>
************************************************************/

#include "Headfile\includes.h"

//-------------------------------------------------------
//Function		: UartOpen
//Description	: 								  
//Calls			: 
//Called By		: 
//Input			: 		
//Output		: 
//Return		: 
//Others		: joe
//DATE			: 2010-11-17 
//-------------------------------------------------------
#ifdef DEBUG
#define UART_BAUD_RATE			(65536-(SYS_CLOCK/(32*38400)))
void UartOpen(void)
{
	CLK_EN_CFG |= 0x60 ;			// Enable timer and UART clock.
// [SCON]
// B7~6: UART Work mode. (work mode 1).
// B5[SM2]: 1: Multiprocesser communication enable.
// B4: 1: Receive enable.
// B3[TB8]:
// B2[RB8]:
// B1[TI]: Transmit interrupt flag.
// B0[RI]: Receive interrupt flag.
	SCON0 = 0x50;    
	RCAP2H = UART_BAUD_RATE>>8 ;
	RCAP2L =UART_BAUD_RATE & 0xff;
	TH2 = UART_BAUD_RATE>>8 ;
	TL2 =UART_BAUD_RATE & 0xff;
// B5: RCLK=1, select timer2 as the UART received clock.
// B4: TCLK=1, select timer2 as the UART transmit clock.
	T2CON  = 0x30;
	TR2    = 1;		// Timer2 RUN control.
	SM2=0;
	TI=1;
	PALT |= 0x80 ; 	// IO is UART function..
	ES0=0; 			// Disable UART interrupt.
}

#endif

/***********************************************************
						end Uart.c
************************************************************/