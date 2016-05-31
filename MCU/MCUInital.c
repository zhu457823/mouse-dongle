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
<author>     <time>        <version >          <desc>
              2011/03/01         0.1            build this moudle 
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
void mcu_io_inital(void)
{
	P0 = 0xff;
	P0IN_EN = 0xcf;
	P0OUT_EN = 0xcf;		// Input/output select register. 1: input, 0:output. P0.4: IR output; P0.5: SYNC Input; P0.6: USB or IR Mode select		
	P0_OPDR = 0x0 ;				// 1: Open drain, 0: not open drain.
	P0_PU = 0xcf ;				// 1: Pullhigh, 0: Disable Pullhigh
	P0_PD = 0x0 ;				// 1: Pulldown, 0: Disable pulldown

	P2IN_EN = 0xff ;
	P2OUT_EN = 0xff;
	P2_OPDR = 0x0 ;
	P2_PU = 0xff ;
	P2_PD = 0x0 ;

	if(bUSBMode)
	{
		P1IN_EN = 0xf3 ;		// 当作为USB使用时，需要将P12 P13 高阻态。
		P1OUT_EN = 0xff;		// P12 P13 Not input and output  no pullup an pulldown
		P1_OPDR = 0x0 ;
		P1_PU = 0xf3 ;
		P1_PD = 0x0 ;
	}
	else
	{
		P1IN_EN = 0xff ;
		P1OUT_EN = 0xff;
		P1_OPDR = 0x0 ;
		P1_PU = 0xff ;
		P1_PD = 0x0 ;
	}
	
	P3IN_EN = 0xff ;
	P3OUT_EN = 0xff ;
	P3_OPDR = 0x0 ;
	P3_PU = 0xff ;
	P3_PD = 0x0 ;

	P4IN_EN = 0xff;
	P4OUT_EN = 0xff;
	P4_OPDR = 0x0;
	P4_PU = 0xff;
	P4_PD = 0x0;
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
void mcu_clk_inital(void)
{
// [PCON]
// Bit7(SMOD): 1: The baund rate for UART0 is double.
// Bit6(EUSB): 1: 48MHZ(USB) clock will exist.
// Bit5(CMD_RST): 1: Reset MCU.
// Bit4(Latch_en)
// Bit3(Deep_sleep)
// Bit2(RC32K_SEL): 1: System will select RC32K(when reset, the bit will be set to 1 ). interrupt and software can clear it.
// Bit1(OSC32K_SEL): 1: System will select OSC32K. interrupt and software can clear it.
// Bit0(IDLE): 1: System entry stop mode.
	PCON2 = 0 ;			// After reset MCU entry sleep mode(PCON.1 = 1)
	WaitUs(500);
	

	
//	bUSBMode = 0;
//	if(P_ModeKey)
		bUSBMode = 1;

//	mcu_io_inital();

// [CLK_EN_CFG]
// Bit7: 1: ADC clock enable.
// Bit6: 1: Timer0/1/2 clock enable.
// Bit5: 1: UART clock enable.
// Bit4: 1: PWM clock enable.
// Bit3: 1: SPI clock enable.
// Bit2: 1: I2C clock enable.
// Bit1: 1: DES clock enable.
// Bit0: 1: MDU(Multiplication Division unit) clock enable.
	CLK_EN_CFG = 0 ;
// B7~6: MCU clock: 16MHZ.
// B5: 1: set Timer2 clock source 16MHZ/4, Default is 16MHZ/12.
// B4: Control timer 1 clock source.
// B3: Control timer 0 clock source.
// B2~0: Unused.
	CKCON = CKCON_CLK_CFG;

	WaitUs(1500);

	if(bUSBMode)
	{
		PCON2 = 0x40;			// Enable USB(48MHZ) 
		AIP |= 0x04;				// Set extern interrupt 4(USB interrupt) to high priority.
	}
	else
	{
		WaitUs(500);
	}
}

/***********************************************************
						end file
***********************************************************/