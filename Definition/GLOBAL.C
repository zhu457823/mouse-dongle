/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName    : 
Author      :   
Date        : 2011/03/01
Description :
Version     : v0.1
Function List: 
----
History: 
<author> 		<time>		 <version > 		<desc>
 			 2011/03/01  			0.1 			 build this moudle 
***********************************************************/

#include "Headfile\includes.h"


XDATA VOLATILE SYS_STRUCT  system ;



bit bWriteDBFIFO;
bit bReadDBFIFO;
bit bFIFO1Full;
bit bFIFO2Full;

//
//      	RF
//
UINT8 FIFO_data[32];
// rf channel table
CODE UINT8 RF_TABLE[16]={6,24,47,67,11,29,51,69,14,33,55,73,17,36,59,76};
//CODE UINT8 RF_TABLE[16]={6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};
//latest config txt,//please optimize code here.
#if cAirRate == 0	// 250K
CODE UINT32 Bank1_Reg0_8[9]={
	0x9C23C053,
	0x80FC3DC8,
	0x00009A40,
	0xC086E419,
	0x49DCEDB4,
	0x81780780,	
	0x0002FEFF,
	0x262808E2,	
	0x1111130C
};
#elif	 cAirRate == 1	// 1M
CODE UINT32 Bank1_Reg0_8[9]={
	0x53C0239C,
	0x80FC3DC8,
	0x00009A40,
	0x8086E419,
	0x49DCEDB4,
	0x81780480,
	0x0002FEFF,
	0x262848A2,
	0x1111130C
};
#elif	  cAirRate == 2	// 2M
CODE UINT32 Bank1_Reg0_8[9]={
	0x53C0239C,
	0x80FC3DC8,
	0x00009A40,
	0x8086E419,
	0x49DCEDB4,
	0x81780780,
	0x0002FEFF,
	0x262808E2,
	0x1111130C
	
};
#endif

#ifdef	CHIP_BK2535
// bank1 reg C value
CODE UINT8 Bank1_RegC[] = 
{
	0x80, 0x01, 0x33, 0x10		// BK 2535
//	0x00,0x12,0x73,0x00		// BK2533
};	
/*************************************************
// bank1 reg D value 0x08A6
Tx_settling_sel<2:0> =[digital.add27h<1:0>,add26h<7>]:
Tx_settling_sel<2:0>	Pll settling time (us)		Note
0						40
1						50
2						60
3						70
4						80				default
5						100
6						120				Compatible with BK2533
7						130				Compatible with Nordic
**************************************************/
CODE UINT8 Bank1_RegD[]=
{
	0x14, 0xB6, 0x80, 0x01		// BK 2535
//	0x36,0xB4,0x80,0x00		// BK2533	
};	
CODE UINT8 Bank1_Ramp_Table[]=
{
//	0x00,0xC2,0x40,0x14,0xC6,0x81,0x24,0xCA,0xC2,0x34,0xCE	// BK2533
 //	0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF	 //	BK2433
	0x1A,0x28,0x92,0x26,0xCA,0xC2,0xB4,0x8D,0xEB,0xFC,0x0F	 //	BK2535
};
#endif



//this arry is used to set output power
/*ronghui
tx power(dBm)      RFcurrent(mA) reg4 value
-49	                10.74	    0089B808
-30	                13.68	    1189BD48
-25	                14.14	    1289BD48
-20	                14.82	    2289BD48
-15	                16.01	    2489BD48
-10             	17.59	    3589BD48
-5	                19.44	    5589BD48
0	                24.07	    7889BD48
5	                32.34	    8A89BFE8
9	                44.74	    FF89BFE8
*/

CODE UINT32 RF_BANK1_REG3[9] =
{
	0x80E6E419, 	// 5dbm
	0x8086E419, 	// 3dbm
	0x8086E419, 	// 0
	0x8086E419,	//-3
	0x8086E419,	// -6
	0x8086E419,	// -9
	0x8086E419,	// -12
	0x8086E419,	// -18
	0x8086E419,	// -23 
};

CODE UINT8 RF_BANK0_CTRL11[14] = 
{
	0xff,	// 5dB
	0xff,	// 3db
	0xbf,	// 0
	0xb0,	// -3
	0xab,	// -6
	0xa7,	// -9
	0xa4,	// -12
	0xa3,	// -18
	0xa1,	// -23
	0x86,	// -27
	0x84,	// -30
	0x83,	// -33
	0x81,	// -36
	0x80		// -54
};
// rx0 tx  addr
//PDATA UINT8 RX0_Address[]={0x19,0x19,0x13,0x16,0x00};   
XDATA UINT8 RX0_Address[] =	{0x15,0x29,0x23,0xC6,0x00}; 	// {0x15,0x59,0x23,0xC6,0x01}; 		//
// rx1  addr
//PDATA UINT8 RX1_Address[]={0x14,0x56,0x64,0x7D,0x16};  
XDATA UINT8 RX1_Address[] = {0x10,0x56,0x24,0xCD,0x17};	// {0x10,0x76,0x14,0xCD,0x16};

//XDATA BYTE RX0_ADDR_TEMP[5];
//XDATA BYTE RX1_ADDR_TEMP[5];

CODE BYTE PUBLICRX0_Address[5] = {0x01,0x02,0x03,0x04,0x05};
CODE BYTE PUBLICRX1_Address[5] = {0x05,0x04,0x03,0x02,0x01};

CODE BYTE TESTRX0_Address[5] = {0x11,0x22,0x13,0x04,0x05};	// {0xf0,0xf0,0xf0,0xf0,0xf0};
CODE BYTE TESTRX1_Address[5] = {0x0f,0x0f,0x0f,0x0f,0x0f};

CODE BYTE TEST_CHANNEL[3]={0,2,15};

BYTE f1_f12[12] = {0,1,6,7,15,11,12,13,14,9,10,8};
BYTE key_null;
BYTE numlock_sta;


CODE BYTE MultiMediaKey[13][2] = {
	{0x0, 0x0},
	#if	1
	{0xe9, 0x0},			// Volume incement
	{0xea, 0x0},			// Volume decment
	{0xe2, 0x0},			// Mute
	{0xb5, 0x0},			// Scan next track.
	{0xb6, 0x0},			// Scan previous track.
	{0xcd, 0x0},	// 0xb0,			// play/pause
	{0xb7, 0x0},	// stop 0xb1,			// pause
	{0xb3, 0x0},			// fast forward
	{0xb4, 0x0},			// Rewind
	{0x21,0x02},			// www Search
	{0x23,0x02},			// ckMediaHome
	{0x40,0x00}			// ckMediaMenu
	#endif
};

CODE BYTE SysPWRKey[3] = {
	0x01,	// ACPI:Power 
	0x02,	// ACPI:Sleep
	0x04	// ACPI:Wake up 
};
#if	0
//muti media
CODE BYTE media_key[57][3] = 
{
	{0x03,0x24,0x02},   //WWW back  0
	{0x03,0x25,0x02},   //WWW forward 1
	{0x03,0x26,0x02},	//WWW Stop  2
	{0x03,0x27,0x02},   //WWW Refresh 3
	{0x03,0x21,0x02},	//WWW Search 4
	{0x03,0x2A,0x02},	//WWW Favorites  5
	{0x03,0x23,0x02},   //WWW Home 6
	{0x03,0x8A,0x01},	//Mail  7
	{0x03,0xE2,0x00},	//Mute 8
	{0x03,0xEA,0x00},	//Volume-  9              
	{0x03,0xE9,0x00},	//Volume+   10            
	{0x03,0xCD,0x00},	//Play/Pause  11           
	{0x03,0xB7,0x00},	//Stop  12 
	{0x03,0xB6,0x00},	//Prev Track 13           
	{0x03,0xB5,0x00},	//Next Track  14          
	{0x03,0x83,0x01},	//Media Select  15        
	{0x03,0x94,0x01},	//My Computer   16        
	{0x03,0x92,0x01},	//Calculator   17         
	{0x03,0x09,0x02},	//More Info  18           
	{0x03,0xB2,0x00},	//Record     19           
	{0x03,0xB3,0x00},	//Forward     20          
	{0x03,0xB4,0x00},	//Rewind      21          
	{0x03,0x8D,0x00},	//Guide        22         
	{0x03,0x04,0x00},	//<Reserved>   23         
	{0x03,0x00,0x00},	//Eject(Mac)   24         
	{0x03,0x01,0x03},	//H1   25
	{0x03,0x02,0x03},	//H2   26
	{0x03,0x03,0x03},	//H3 	27
	{0x03,0x04,0x03},	//H4    28
	{0x03,0x05,0x03},	//H5	29
	{0x03,0x06,0x03},	//H6	30
	{0x03,0x07,0x03},	//H7    31
	{0x03,0x08,0x03},	//H8	32
	{0x03,0x09,0x03},	//H9	33
	{0x03,0x0A,0x03},	//H10	34
	{0x03,0x0B,0x03},	//H11	35
	{0x03,0x0C,0x03},	//H12	36
	{0x03,0x0D,0x03},	//H13	37
	{0x03,0x0E,0x03},	//H14	38
	{0x03,0x0F,0x03},	//H15	39
	{0x03,0x10,0x03},	//H16	40
	{0x03,0x11,0x03},	//H17	41
	{0x03,0x12,0x03},	//H18	42
	{0x03,0x13,0x03},	//H19	43
	{0x03,0x14,0x03},	//H20	44
	{0x04,0x0D,0x00},	//MCE key       		45        	
	{0x04,0x47,0x00},	//MCE:My Music       	46   
	{0x04,0x4A,0x00},	//MCE:My Video        	47  
	{0x04,0x46,0x00},	//MCE:My TV             48
	{0x04,0x8D,0x00},	//MCE:Program Manual    49          
	{0x04,0x25,0x00},	//MCE:Live TV           50
	{0x04,0x48,0x00},	//MCE:Recorded TV       51
	{0x04,0x69,0x00},	//MCE:Messenger         52
	{0x04,0x24,0x00},	//MCE:DVD Menu          53
	{0x04,0x49,0x00},	//MCE:My Picture        54
	{0x04,0x50,0x00},	//MCE:My Radio          55
	{0x04,0x74,0x00},	//CDROM Eject    		56
};

//power manager
CODE BYTE power_key[3][2] = 
{
	{0x02,0x01},	//ACPI:Power                 
	{0x02,0x02},	//ACPI:Sleep                 
	{0x02,0x04},	//ACPI:Wake up               
};

//mce media
CODE BYTE mce_key[12][2] = 
{
	{0x04,0x0D},	//MCE key               	
	{0x04,0x47},	//MCE:My Music          
	{0x04,0x4A},	//MCE:My Video          
	{0x04,0x46},	//MCE:My TV             
	{0x04,0x8D},	//MCE:Program Manual              
	{0x04,0x25},	//MCE:Live TV           
	{0x04,0x48},	//MCE:Recorded TV       
	{0x04,0x69},	//MCE:Messenger         
	{0x04,0x24},	//MCE:DVD Menu          
	{0x04,0x49},	//MCE:My Picture        
	{0x04,0x50},	//MCE:My Radio          
	{0x04,0x74},	//CDROM Eject           
};
#endif
//----------------------------------------------------------
//
//						usb
//
//----------------------------------------------------------


volatile bit OutUsbDataHit = 0;

// These are response packets used for
code unsigned char ONES_PACKET[2] = {0x01, 0x00};
// Communication with host
code unsigned char ZERO_PACKET[2] = {0x00, 0x00};
code unsigned char TWO_PACKET[2] = {0x02, 0x00};

XDATA unsigned char idle_rate =0;

VOLATILE bit Remote_Wakeup=0;
VOLATILE bit usb_suspend = 0;

BYTE set_protocol_status = 1;

unsigned char USB0_STATE = DEV_DEFAULT;  // Holds the current USB State
                                       // def. in F3xx_USB0_InterruptServiceRoutine.h


IDATA unsigned char DATASIZE;                 // Size of data to return
IDATA unsigned char DATASENT;                 // Amount of data sent so far
unsigned char* DATAPTR;                // Pointer to data to return

IDATA unsigned char EP_STATE[5] ={EP_IDLE, EP_STALL, EP_STALL,EP_STALL,EP_STALL};

//IDATA BYTE uOutTokenCMDIndex;
unsigned char USB_STRING[66];

unsigned char set_report_status_phace=0;

IDATA unsigned char wait_tx_status=0;

#if ((defined DEV_MIC) ||(defined DEV_PHONE))
XDATA USBPhoneAttri  USBPhone; 
#endif

/***********************************************************
                		end file
***********************************************************/
