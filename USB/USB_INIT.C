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
			2011/03/01  			0.1  			build this moudle 
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
void usb_ini(void)
{
// Bit7: 1, D+ pull up enable with chip.
// Bit2(usb reset):
// Bit1(usb suspend): 1, USB module entry idle state.
// Bit0(Remote wakeup): .
	USB_PWR_CN &= ~0x02;	// Clear USB suspend.
	while (CFG_EP0_1 != 0xc0)
		CFG_EP0_1 = 0xc0;

	Delay(300);
	EP_ADDR_MSB = 0x3F;		// MSB of Endpoint 0~5 address.

//	CFG_EP0_1 = 0xc0;
// Bit7(DIR) of CFG_EP0_1 is clear or set by software except that it is cleared by hardware when SETUP token comming. 
	CFG_EP0_1 = 0xc0;   // 0x1 1 0000 00;  dir = out ;  ep0_en = 1 ; 
	CFG_EP0_0 = 0x00;   // addr = 0x00

//    CFG_EP1_1 = 0xec;   // 0x 1 11 011 00;  dir = in ;  mod = INT ; ep_len = 64
	CFG_EP1_1 = 0xCC;   // 0x 1 10 011 00;  dir = in ;  mod = ISO ; ep_len = 64
	CFG_EP1_0 = 0x40;   // FIFO1 address = 0x440
    
	CFG_EP2_1 = 0xec;   // 0x 1 11 011 00;  dir = in ; mod = INT ; ep_len = 64
//	CFG_EP2_1 = 0x4C;   // 0x 0 10 011 00;  dir = out ; mod = ISO ; ep_len = 64
	CFG_EP2_0 = 0x80;   // FIFO2 address = 0x480

	CFG_EP3_1 = 0xec;
	CFG_EP3_0 = 0xc0;	// FIFO3 address = 0x4c0.
	
	CFG_EP4_1 = 0xed;	// FIFO4 address = 0x500
	CFG_EP4_0 = 0x00;	// Interrupt in

	CFG_EP5_1 = 0xed;	// FIFO4 address = 0x540
	CFG_EP5_0 = 0x40;
	
	USBINT0 = 0xff;
	USBINT1 = 0xff;		// Clear USB interrrupt flag.
// [USB_EN0]
// Bit7: Data received on EP0 interrupt enable bit.
// Bit6: Data send on EP0 interrupt enable bit.
// Bit5: Data received on EP1~7 interrupt enable bit.
// Bit4: Data send on EP1~7 interrupt enable bit.
// Bit3: USB reset interrupt enable bit.
// Bit2: USB suspend interrupt enable bit.
// Bit1: USB resume interrupt enable bit.
// Bit0: USB start of frame interrupt enable bit.
#ifdef	CHIP_BK2535
	USB_EN0 = 0xff;	//0xfe;
#endif
// [USB_EN1]
// Bit7: unsupported token received interrupt enable bit.
// Bit6: CRC16 check error interrupt enable bit.
// Bit5: Timeout interrupt enable bit.
// Bit4: EP1~7 transfer PID error enable bit.
// Bit3~0: unused.
	USB_EN1 = 0x00;
    
	system.usbp1_data.ready_to_uploading = 1;
	system.usbp2_data.ready_to_uploading = 1;
	system.usbp4_data.ready_to_uploading = 1;
	system.usbp0_data.report_id = 0;
	system.usbp0_data.report_type = 0;
	system.usbp0_data.set_report_flag = 0;
	system.usbp0_data.get_report_flag = 0;
	system.usbp0_data.reday_report_flag = 0;
	system.usbp0_data.aceept = 0;

	usb_suspend = 0;
//	EXINT_MOD &= ~ 0x04 ;  	 // int4(usb_int)  level detected
	USB_PWR_CN |= 0x80 ;   	 // enable pull_up on D+
	EX4 = 1;					// Enable USB interrupt.
	EA = 1;
}

//-----------------------------------------------------------------------------
// Delay
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - seconds
//
// Used for a small pause, approximately 80 us in Full Speed,
// and 1 ms when clock is configured for Low Speed
//
// ----------------------------------------------------------------------------
void Delay(int num)
{
	int x,y;
	for(y=0;y<num;y++)
	{
		for(x = 0;x < 500;x)
			x++;
	}
}



/***********************************************************
						end file
***********************************************************/
