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
		  		2011/03/01 		 0.1  		build this moudle 
***********************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

extern XDATA VOLATILE  SYS_STRUCT  system ;


extern UINT8 FIFO_data[32];
extern CODE UINT8 RF_TABLE[16];
extern CODE UINT32 Bank1_Reg0_8[];
extern CODE UINT8 Bank1_RegC[];
extern CODE UINT8 Bank1_RegD[];
extern CODE UINT8 Bank1_Ramp_Table[];
extern CODE UINT32 RF_BANK1_REG3[9];
extern CODE UINT8 RF_BANK0_CTRL11[14];
extern XDATA UINT8 RX0_Address[];
extern XDATA UINT8 RX1_Address[];

extern CODE BYTE PUBLICRX0_Address[5];
extern CODE BYTE PUBLICRX1_Address[5];
extern CODE BYTE TESTRX0_Address[5];
extern CODE BYTE TESTRX1_Address[5];
extern CODE BYTE TEST_CHANNEL[3];

extern BYTE f1_f12[12];
extern BYTE key_null;
extern BYTE numlock_sta;


extern CODE BYTE MultiMediaKey[13][2];
extern CODE BYTE SysPWRKey[3];
extern volatile bit OutUsbDataHit;
extern code unsigned char ONES_PACKET[2];
extern code unsigned char ZERO_PACKET[2];
extern code unsigned char TWO_PACKET[2];
extern XDATA unsigned char idle_rate;
extern VOLATILE bit Remote_Wakeup;
extern VOLATILE bit usb_suspend ;
extern BYTE set_protocol_status;
extern unsigned char USB0_STATE;  // Holds the current USB State
extern IDATA unsigned char DATASIZE;                 // Size of data to return
extern IDATA unsigned char DATASENT;                 // Amount of data sent so far
extern unsigned char* DATAPTR;                // Pointer to data to return
extern IDATA unsigned char EP_STATE[5];
extern unsigned char USB_STRING[66];

extern unsigned char set_report_status_phace;

extern IDATA unsigned char wait_tx_status;
#if ((defined DEV_MIC) ||(defined DEV_PHONE))
extern XDATA USBPhoneAttri  USBPhone;
#endif

extern bit bWriteDBFIFO;
extern bit bReadDBFIFO;
extern bit bFIFO1Full;
extern bit bFIFO2Full;
extern bit bFIFOReady;
#endif


/***********************************************************
						end file
***********************************************************/
