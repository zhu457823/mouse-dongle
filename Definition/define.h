/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: define.h
Author		:
Date		: 2011/03/01
Description	: 
Version		: v0.1
Function List: 
----
History: 
<author> 	<time> 		<version > 	<desc>
			2011/03/01  	   0.1  		build this moudle 
***********************************************************/

#ifndef _DEFINE_H_
#define _DEFINE_H_


//type redefine
typedef void				VOID, *PVOID;
typedef char				BOOL;
typedef char				BOOLEAN;
typedef unsigned char		UINT8,BYTE, UCHAR, *PUCHAR;
typedef char				INT8;
typedef short				INT16;
typedef unsigned short		UINT16;
typedef unsigned long		UINT32;

#define VOLATILE        volatile
#define	XDATA			xdata
#define PDATA			pdata
#define IDATA			idata
#define	DATA			data
#define	CODE			code

// constant definition
#define FALSE			0
#define TRUE			1

#define SUCCESS			0
#define FAILURE			1


//interrupt status
#define STATUS_RX_DR 0x40
#define STATUS_TX_DS 0x20
#define STATUS_MAX_RT 0x10
#define STATUS_TX_FULL 0x01

//CD status
#define CD_INT 0x01

//FIFO_STATUS
#define FIFO_STATUS_TX_REUSE 0x40
#define FIFO_STATUS_TX_FULL 0x20
#define FIFO_STATUS_TX_EMPTY 0x10
#define FIFO_STATUS_RX_FULL 0x02
#define FIFO_STATUS_RX_EMPTY 0x01



//USB command between FW and App
#define BK_CMD_GET_FW_VERSION  0xff
#define BK_CMD_MESSAGE_PRINT   0xf1
#define BK_CMD_WRITE_REG       0xf2
#define BK_CMD_WRITE_BANK1_REG 0xa1
#define BK_CMD_WRITE_REG_TAIL  0xfe
#define BK_CMD_REG_STATUS      0xfd
#define BK_CMD_READ_REG        0xf3
#define BK_CMD_READ_REG_APPEND 0xe3
#define BK_CMD_SPI_BIT_WRITE   0xf4
#define BK_CMD_SPI_REFRESH     0xf5
#define BK_CMD_SWITCH_TO_PRX   0xf8
#define BK_CMD_SWITCH_TO_PTX   0xf9
#define BK_CMD_START_SEND   0xc1
#define BK_CMD_START_RECV   0xc2
#define BK_CMD_STOP_TEST    0xc3
#define BK_CMD_SIMPLE_RECV  0xc4
#define BK_CMD_FLUSH_TX 0x50
#define BK_CMD_FLUSH_RX 0x51
#define BK_CMD_REUSE   0x52
#define BK_CMD_PRINT_STRING  0x60
#define BK_CMD_PRINT_STRING2  0x61
#define BK_CMD_UPDATE_REG_BITS0  0xfa
#define BK_CMD_UPDATE_REG_BITS1  0xfb
#define BK_CMD_FLUSH_TX 0x50
#define BK_CMD_FLUSH_RX 0x51
#define BK_CMD_REUSE   0x52
#define BK_CMD_SIMPLE_RECV_END  0xc5
#define BK_CMD_REPORT_PER  0xc7
#define BK_CMD_2M_MODE      0xc8
#define BK_CMD_READ_PACKET_NUMBER     0xc9
#define BK_CMD_SEND_END     0xca
#define BK_CMD_CARRIER_TEST 0xcb
#define BK_CMD_BER_READ_TEST 0xcd
#define BK_SLEEP_MODE 0xce
#define BK_ZERO_ONE_PACKET_TEST 0xcf
#define BK_FREQ_AGILITY_TEST 0xd0
#define BK_CMD_ACK 0xd1
#define BK_CMD_FREQ_LINK_STATUS 0xd2
#define BK_CMD_FREQ_PER_REPORT 0xd3
#define BK_CMD_WRITE_SRF       0x80
#define BK_CMD_READ_SRF       0x81


#define FREQ_TABLE_SIZE     0x10
#define TRANS_PARAMS        0x02
#define NUM_OF_PIPES        0x06
#define PIPE0               0x00
#define PIPE1               0x01
#define PIPE2               0x02
#define PIPE3               0x03
#define PIPE4               0x04
#define PIPE5               0x05
#define LINK_STATUS         0x00
#define LINK_CHANNEL        0x01
#define LINK_NO_MESS        0x00
#define LINK_LOSS           0x01
#define LINK_ESTABLISH      0x02
#define LINK_RELOST         0x03
#define STOP                0x04
#define CLEARED             0x00
#define TIMEOUT             0x01
#define CLEAR               0x00
#define EXT_INT0            0x00
#define T0_INTERRUPT        0x01
#define T1_INTERRUPT        0x03
#define T2_INTERRUPT        0x05
#define TX_MODE             0x00
#define RX_MODE             0x01
#define TRANS_SOURCE        0x00
#define TRANS_VALUE         0x01
#define BUTTON              0x01
#define FLUSH_TX 	 BK2401_CMD = 0xA0
#define FLUSH_RX 	 BK2401_CMD = 0x80
#define REUSE_TX_PL  BK2401_CMD = 0x10
#define NOP   		 BK2401_CMD = 0x00

#define ENABLE_RF_INTR  EX5 = 1
#define DISABLE_RF_INTR EX5 = 0



//
//	mcu definition
//
#define	SYS_CLOCK			16000000

#define	cMCUTickDuty		 4
// #define	TIMER0_1MS_CNT		(65536-(SYS_CLOCK/4000))
#define	cMCUTickDuty		 4

//固定12分频,0.75uS
#define	cSYS_CLOCK			16
#define	cSYSTEM_CLK_CNT	65536
#define	cSYSTEM_DIV		12

#define	TIMER0_10MS_CNT	52202	//(cSYSTEM_CLK_CNT-((10000*cSYS_CLOCK)/cSYSTEM_DIV))	
#define	TIMER0_8MS_CNT  (cSYSTEM_CLK_CNT-((8000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_7MS_CNT  (cSYSTEM_CLK_CNT-((7000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_6MS_CNT  (cSYSTEM_CLK_CNT-((6000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_5MS_CNT  58868	//(cSYSTEM_CLK_CNT-((5000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_4MS_CNT  60202	//(cSYSTEM_CLK_CNT-((4000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_3MS_CNT  (cSYSTEM_CLK_CNT-((3000*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_2MS_CNT  62868	//(cSYSTEM_CLK_CNT-((2000*cSYS_CLOCK)/cSYSTEM_DIV))    
#define	TIMER0_1_5MS_CNT  (cSYSTEM_CLK_CNT-((1500*cSYS_CLOCK)/cSYSTEM_DIV))
#define	TIMER0_1MS_CNT	(cSYSTEM_CLK_CNT-((1000*cSYS_CLOCK)/cSYSTEM_DIV))


#define	ENABLE_INTERRUPT	EA=1
#define	DISABLE_INTERRUPT	EA=0

sbit P_BindKey = P0^7;
sbit P_ModeKey = P0^6;
//sbit P_BindIO = P0^7;

sbit P_PCBATest = P2^0;
#define	BindKeyInput()		P0_PD &= ~0x80;		\
							P0_PU |= 0x80;	\
							P0IN_EN |= 0x80;	\
							P0OUT_EN |= 0x80
// P20
#if	1
#define	TestPortInput()		P2_PD &= ~0x01;		\
							P2_PU |= 0x01;	\
							P2IN_EN |= 0x01;	\
							P2OUT_EN |= 0x01
#endif


sbit	P_LED = P0^5;
#define	LEDOn()			P0 &= ~0x20;		\
						P0_OPDR &= ~0x20;	\
						P0IN_EN &= ~0x20;	\
						P0OUT_EN &= ~0x20

#define	LEDOff()			P0 |= 0x20;		\
						P0_OPDR &= ~0x20;	\
						P0IN_EN &= ~0x20;	\
						P0OUT_EN &= ~0x20

#define	LEDToggle()		P_LED = !P_LED;	\
						P0IN_EN &= ~0x20;	\
						P0OUT_EN &= ~0x20

//
//		mcu clk
//
#define	CKCON_CLK_16MHZ		0x00
#define	CKCON_CLK_8MHZ		0x40
#define	CKCON_CLK_4MHZ		0x80
#define	CKCON_CLK_2MHZ		0xc0

#if SYS_CLOCK==16000000
#define	CKCON_CLK_CFG			CKCON_CLK_16MHZ
#elif SYS_CLOCK==8000000
#define	CKCON_CLK_CFG			CKCON_CLK_8MHZ
#elif SYS_CLOCK==4000000
#define	CKCON_CLK_CFG			CKCON_CLK_4MHZ
#elif SYS_CLOCK==2000000
#define	CKCON_CLK_CFG			CKCON_CLK_2MHZ
#endif

//
//	mcu idle sleep
// MCU Idle, system clock not change. 
#define MCU_IDLE() 		PCON2 = 0x01	

// MCU Idle, system clock changed to RC32K. Bit0: Idle, Bit2: RC32K selected. 
#define MCU_IDLE_32K() 	PCON2 = 0x05	

// MCU Idle, system clock changed to OSC32K. Bit0: Idle, Bit1: OSC32K selected.
#define MCU_SLEEP() 		PCON2 = 0x03	

#define	CKCON_TIMER2CLK_1_12	0x00
#define	CKCON_TIMER2CLK_1_4	0x20
#define	CKCON_TIMER1CLK_1_12	0x00
#define	CKCON_TIMER1CLK_1_4	0x10
#define	CKCON_TIMER0CLK_1_12	0x00
#define	CKCON_TIMER0CLK_1_4	0x08

//		key count time
#define	SHORT_CNT			2
#define	LONG_CNT			250
#define	LONG_REPEAT_CNT		300

//
//	MTP record
//
#define MTP_STORY_FLAG	0x5A
#define MTP_STATUS_ADDR1 0x7A
#define MTP_STATUS_ADDR2 0x52
#define MTP_STATUS_ADDR3 0x56
#define MTP_STATUS_LEN 1

#define MTP_RECORD_FLAG_ADDR	0x02   // flag 0 为有功能， 1为无功能
#define MTP_RECORD_FLAG_LEN	 3

#define MTP_02_COPY_FLAG_ADDR1 0x58
#define MTP_02_COPY_FLAG_ADDR2 0x7C
#define MTP_02_COPY_FLAG_LEN	 1


#define RX0_ID_ADDR	0x06
#define RX0_ID_ADDR_LEN	5

#define VID_PID_ADDR 0x0c
#define VID_PID_LEN	4


#define IR_RELEASE_KEY_ADDR2		0x10		// 0x10~0x12
//#define BINDTIME_ADDR 0x10
//#define BINDTIME_LEN 1

//#define BIND_POWER_ADDR 0x12
//#define BIND_POWER_LEN 1

//#define CUSTOM_MOUSEKEY_ADDR 0x14
//#define CUSTOM_MOUSEKEY_LEN	3
#define IR_RELEASE_KEY_ADDR		0x14		// 0x14~0x16
#define IR_CODE_LEN		0x03		

#define MS_TYPE_ADDR 0x18
#define MS_TYPE_LEN 1

#define CPI_ADDR 0x1A
#define CPI_LEN 2

#define CPI_DEFAULT_ADDR 0x1c
#define CPI_DEFAULT_LEN 1

//#define MS_LP_ADDR 0x1E
//#define MS_LP_LEN 2
#define IR_RELEASE_KEY_ADDR1		0x1E	// 0x1D		// 0x1D~0x1f

//#define KB_TYPE_ADDR 0x20
//#define KB_TYPE_LEN 1

#define FN_F1_F12_ADDR 0x22
#define FN_F1_F12_LEN 12

#define KB_LP_ADDR 0x2E
#define KB_LP_LEN 1

#define USB_STRING_ADDR 0x30
#define USB_STRING_LEN  32 	

#define RX1_ID_ADDR	0x5A
#define RX1_ID_ADDR_LEN	5

#define CUSTOM_CPI_ADDR 0x60
#define CUSTOM_CPI_LEN 1

#define RX0_ID_COPY1_ADDR 0x62
#define RX0_ID_COPY1_LEN  5
#define RX0_ID_COPY2_ADDR 0x68
#define RX0_ID_COPY2_LEN  5

#define RX1_ID_COPY1_ADDR 0x6e
#define RX1_ID_COPY1_LEN  5
#define RX1_ID_COPY2_ADDR 0x74
#define RX1_ID_COPY2_LEN  5


//
//	bind time
//
#define BIND_WAIT_TIME 5000

//
//	mouse stand key flag
//
#define SKEY_M 0x40
#define SKEY_R 0x20
#define SKEY_L 0x10
#define SKEY_TILT_L 0x08
#define SKEY_FORAWARD 0x04
#define SKEY_BACK 0x02
#define SKEY_3D 0x01
#define SKEY_TILT_R 0x80
#define SKEY_CUS1 0x40
#define SKEY_CUS2 0x20

//
//	mouse multi key flag
//
#define MKEY_M 0x40
#define MKEY_R 0x20
#define MKEY_L 0x10
#define MKEY_TILT_L 0x08
#define MKEY_FORAWARD 0x04
#define MKEY_BACK 0x02
#define MKEY_PLPA 0x01
#define MKEY_TILT_R 0x80
#define MKEY_NT 0x40
#define MKEY_PT 0x20
#define MKEY_STOP 0x10

//
//	mouse multi key flag
//
#define RKEY_MUTE 0x40
#define RKEY_R 0x20
#define RKEY_L 0x10
#define RKEY_TILT_L 0x08
#define RKEY_PT 0x04
#define RKEY_NT 0x02
#define RKEY_3D 0x01
#define RKEY_TILT_R 0x80
#define RKEY_MEDI 0x40
#define RKEY_PLPA 0x20


//
//   mouse key value
//
#define FORWARD_KEY   0x10
#define BACK_KEY   0x08
#define RIGHT_KEY  0x02
#define LEFT_KEY   0x01
#define MIDDLE_KEY 0x04
#define TILT_R_KEY 0x01
#define TILT_L_KEY 0xff

//
//	send config
//
#define CURRENT_CELL 0x20
#define CURRENT_CPI 0x40
#define SYSTEM_CONFIG 0x80

#define SYSTEM_END	0x04
#define SYSTEM_STA	0x02

#define SYSTEM_NEXT_CH 0x08


//
//		mouse data num
//
#define MOUSE_KEY_NUM	0
#define MOUSE_X 1
#define MOUSE_XY 2
#define MOUSE_Y 3
#define MOUSE_WHEEL 4
#define MOUSE_TITL 5


//
//	pc connect
//

#define PC_GET_REPORT_1 0xba
#define PC_GET_REPORT_2 0x01		// Report type: 0x01 input, 0x02 output, 0x03 feature report.

#define PC_SET_REPORT_1 0xba
#define PC_SET_REPORT_2 0x02

#define PC_GET_DATA 0x01
#define PC_GET_NONDATA 0x00

// MODE  command
#define COMMAND_KBCELL 0xB5
#define COMMAND_MSCELL 0xB6
#define COMMAND_SIGNAL 0xB7
#define COMMAND_CURRENT_MODE 0xA7

#define COMMAND_MODE  0xA0 //控制命令
#define COM_MODE_BIND 0x81 //进入对码模式
#define COM_MODE_TEST 0x82 //进入测试模式
#define COM_MODE_CODE 0x83 //进入写码模式
#define COM_MODE_DEBUG 0x84 //进入DEBUG模式

//BIND mode command
#define COMMAND_BIND  0xA1  //对码模式命令
#define COM_BIND_GET  0x01  //获取设备对码状态
#define COM_BIND_CLE  0x81  //清除对码状态
#define COM_BIND_CLE_MS 0x82 //清除鼠标对码状态
#define COM_BIND_CLE_KB 0x83 //清除键盘对码状态
#define COM_BIND_EXIT 0x84  //退出对码模式
#define ACK_BIND_GET 0x02
//TEST mode command
#define COMMAND_TEST 0xA2  //测试模式命令
#define COM_TEST_SC  0x81  //进入单载波
#define COM_TEST_CD  0x82  //FCC调试
#define COM_TEST_DAT 0X83  //数据调试
#define COM_TEST_LOW_CH 0x84
#define COM_TEST_MID_CH 0x85
#define COM_TEST_HIG_CH 0x86
#define COM_TEST_SW_HIG 0x87
#define COM_TEST_SW_LOW 0x88
#define COM_TEST_SW_STOP 0x89
#define COM_TEST_POW_5  0x8A
#define COM_TEST_POW_0  0x8B
#define COM_TEST_POW_N5  0x8C
#define COM_TEST_POW_N10  0x8D
#define COM_TEST_EXIT   0x8E
//CODE mode command
#define COMMAND_CODE 		0xA3
#define COM_CODE_RMTP 0x01
#define COM_CODE_WMTP 0x81
#define COM_CODE_CLE  0x82
#define COM_CODE_EXIT 0x83

//DEBUG mode command
#define COMMAND_DEBUG 0xA4
#define COM_DEBUG_RMTP 0x01
#define COM_DEBUG_WMTP 0x81
#define COM_DEBUG_RREG 0x10
#define COM_DEBUG_WREG 0x90
#define COM_DEBUG_EXIT 0xFF
#define ACK_MTP_DATA   0x02
#define ACK_REG_DATA   0x03

//cell signal uploding 
#define UPL_CELL_MS 0x51
#define UPL_CELL_KB 0x52
#define UPL_SIGNAL  0x61

//---------------------------------------------------------
//					key code
//---------------------------------------------------------
#define	ckVolInc		0x01
#define	ckVolDec	0x02
#define	ckMute		0x03
#define	ckNXTTrack	0x04
#define	ckPreTrack	0x05
#define	ckMediaPlay	0x06
#define	ckMediaStop		0x07

#define	ckFastForward	0x08
#define	ckRewind		0x09
#define	ckPWR			0x20


#define	cKeyREC			0x01
#define	cKeyPlay		0x02
#define	cKeyLeft			0x04
#define	cKeyPower		0x08

#define	cKeyBind		0x10
#define	cKeyMSRight		0x20
#define	cKeyOK			0x40
#define	cKeyVolDec		0x80

#define	cKeyPGDN		0x01
#define	cKeyHome		0x02
#define	cKeyDN			0x04
#define	cKeyUP			0x08

#define	cKeyPGUP		0x10
#define	cKeyWin			0x20
#define	cKeyRight		0x40
#define	cKeyVolINC		0x80

#define null	0x00


//字母
#define kA 0x04		//A
#define kB 0x05		//B
#define kC 0x06		//C
#define kD 0x07		//D
#define kE 0x08 		//E
#define kF 0x09		//F
#define kG 0x0A		//G
#define kH 0x0B		//H
#define kI 0x0C		//I
#define kJ 0x0D		//J
#define kK 0x0E	    //K
#define kL 0x0F		//L
#define kM 0x10		//M
#define kN 0x11		//N
#define kO 0x12  	//O
#define kP 0x13		//P
#define kQ 0x14 		//Q
#define kR 0x15		//R
#define kS 0x16	    //S
#define kT 0x17		//T
#define kU 0x18		//U
#define kV 0x19		//V
#define kW 0x1A 		//W
#define kX 0x1B		//X
#define kY 0x1C		//Y
#define kZ 0x1D		//Z

//F1 -- F12
#define kF1  0x3A	//F1
#define kF2  0x3B	//F2
#define kF3  0x3C	//F3
#define kF4  0x3D	//F4
#define kF5  0x3E	//F5
#define kF6  0x3F	//F6
#define kF7  0x40	//F7
#define kF8  0x41	//F8
#define kF9  0x42	//F9
#define kF10 0x43	//F10
#define kF11 0x44	//F11
#define kF12 0x45	//F12

//上数字
#define k0 0x27		//) 0
#define k1 0x1E		//! 1
#define k2 0x1F		//@ 2
#define k3 0x20		//# 3
#define k4 0x21		//$ 4
#define k5 0x22		//%5
#define k6 0x23		//^6
#define k7 0x24		//& 7
#define k8 0x25		//* 8
#define k9 0x26		//( 9
#define kMi    0x2D	//—— _
#define kEq    0x2E	//+=

// num pad
#define kNLock 	 0x53			//Num lock
#define kNMulti  0x55			//*
#define kNDivi   0x54			// /
#define kNPlus 	 0x57			//+
#define kNMinus  0x56			//-
#define kN9 	 0x61			//9
#define kN8 	 0x60			//8
#define kN7 	 0x5F   		//7
#define kN6 	 0x5E			//6
#define kN5 	 0x5D			//5
#define kN4 	 0x5C			//4
#define kN3 	 0x5B			//3
#define kN2 	 0x5A			//2
#define kN1 	 0x59			//1
#define kN0 	 0x62			//0
#define kNP  	 0x63			//.
#define kNEnter  0x58			//（小Enter）

//控制
#define kHome 	 0x4A	//Home
#define kIns 	 0x49	//insert
#define kDel	 0x4C	//delete
#define kEnd 	 0x4D	//end
#define kPaUp    0x4B	//page up
#define kPaDo    0x4E	//page down

#define kEsc 	 	0x29	//ESC
#define kCaps 		0x39	//Caps lock
#define kTab        0x2B	//tab
#define kScrol 		0x47	//Scroll lock
#define kPrcsc		0x46	//prcsc sysrq
#define kPause 		0x48	//Pause break
#define kBack 		0x2A	//Back space
#define kEnter 		0x28	//Enter
#define kSpace 		0x2C	//space

#define kLCtrl 		0x01	//左ctrl
#define kLAlt     	0x04    //左Alt
#define kLShift 	0x02	//左Shift
#define kLWin 		0x08	//左windows
#define kRWin 		0x80	//右windows
#define kRShift 	0x20	//右Shift
#define kRAlt 		0x40	//右Alt
#define kRCtrl 		0x10	//右Ctrl
#define kApp 		0x65	//Application

#define kVBar 		0x31	//|"\"
#define kDQuote 	0x34    //" '
#define kColon 		0x33	//: ;
#define kThrow 		0x35	//~ `
#define kLTS 		0x36	//<,
#define kGTS 		0x37	//>.
#define kQM 		0x38	//?/
#define kBR 		0x30	//}]
#define kBL 		0x2F	//{[

#define kUp		0x52		//Up arrow
#define kLeft 	0x50		//Left arrow
#define kRight 	0x4F		//Right arrow
#define kDown 	0x51		//Down arrow

#define kK14	0x89		//international key
#define kKR_L	0x91		//
#define kK107	0x85		//
#define kK45	0x64		//
#define kK42	0x32		//
#define kK131	0x8b 		//
#define kK132	0x8a		//
#define kK133 	0x88		//
#define kK56	0x87		//
#define kKR_R	0x90		//

//---User key Define------
#define	ckMoKey		0x72
#define	ckEnVoice	0x73


// ct key
#define L_Ctrl  0xC0
#define L_Alt   0x69
#define L_Shift 0x2F
#define L_Win	0x30
#define R_Ctrl  0x80
#define R_Alt   0xA9
#define R_Shift 0x4F
#define R_Win 	0x51

//fn key
#define FN_F1 0xC2
#define FN_F2 0xC3
#define FN_F3 0x23
#define FN_F4 0x63
#define FN_F5 0xE0
#define FN_F6 0x66
#define FN_F7 0x27
#define FN_F8 0xC7
#define FN_F9 0xCA
#define FN_F10 0xEA  
#define FN_F11 0x6A
#define FN_F12 0xAA

#define FN_INS 0xCC
#define FN_UP 0x6E
#define FN_DOWN 0xAB
#define FN_LEFT 0xAE
#define FN_RIGHT 0xAC

#define FN_7 0xE5
#define FN_8 0xE6
#define FN_9 0xE7
#define FN_ZERO 0xE8      //*
#define FN_U 0x05         //4
#define FN_I 0x06         //5
#define FN_O 0x07         //6
#define FN_P 0x08         //-
#define FN_J 0x45         //1
#define FN_K 0x46         //2
#define FN_L 0x47        //3
#define FN_Colon 0x48     //+
#define FN_M 0x85          //0
#define FN_GTS 0x87       //.
#define FN_QM  0xA8       // /


// end package
#define END_NULL 0xFF


//----------------------------------------------------------
//
//						usb
//
//----------------------------------------------------------
// ---------------------------------------------------------
// Report IDs
// ---------------------------------------------------------
//#define OUT_BLINK_PATTERNID     0x06 
#define OUT_BLINK_ENABLEID      0x02
#define OUT_BLINK_RATEID        0x03
#define IN_BLINK_SELECTORID     0x04
#define IN_BLINK_STATSID        0x05
#define FEATURE_BLINK_DIMMERID  0x07

#define BK_USB_FEATURE_CMD  0x06
#define BK_USB_REPORT_CMD  0x07

// ---------------------------------------------------------
// Report Sizes (in bytes)
// ---------------------------------------------------------
//#define OUT_BLINK_PATTERNSize    31
#define OUT_BLINK_ENABLESize     0x01
#define OUT_BLINK_RATESize       0x02
#define IN_BLINK_SELECTORSize    0x01
#define IN_BLINK_STATSSIZE       0x02
#define FEATURE_BLINK_DIMMERSIZE 0x01


// endpoint number
#define  EP_0          0x0
#define  EP_1          0x1
#define  EP_2          0x2
#define  EP_3          0x3
#define  EP_4          0x4
#define  EP_5          0x5
#define  EP_6          0x6
#define  EP_7          0x7



// Standard Descriptor Types
#define  DSC_DEVICE          0x01      // Device Descriptor
#define  DSC_CONFIG          0x02      // Configuration Descriptor
#define  DSC_STRING          0x03      // String Descriptor
#define  DSC_INTERFACE       0x04      // Interface Descriptor
#define  DSC_ENDPOINT        0x05      // Endpoint Descriptor


// Standard Request Codes
#define  GET_STATUS          0x00      // Code for Get Status
#define  CLEAR_FEATURE       0x01      // Code for Clear Feature
#define  SET_FEATURE         0x03      // Code for Set Feature
#define  SET_ADDRESS         0x05      // Code for Set Address
#define  GET_DESCRIPTOR      0x06      // Code for Get Descriptor
#define  SET_DESCRIPTOR      0x07      // Code for Set Descriptor(not used)
#define  GET_CONFIGURATION   0x08      // Code for Get Configuration
#define  SET_CONFIGURATION   0x09      // Code for Set Configuration
#define  GET_INTERFACE       0x0A      // Code for Get Interface
#define  SET_INTERFACE       0x0B      // Code for Set Interface
#define  SYNCH_FRAME         0x0C      // Code for Synch Frame(not used)


#define  DEVICE     0
#define  INTERFACE  1
#define  ENDPOINT   2

#ifndef  MSB
	#define  MSB 0
#endif

#ifndef  LSB
	#define  LSB 1
#endif

// Define wIndex bitmaps
#define  IN_EP1              0x81      // Index values used by Set and Clear
#define  OUT_EP1             0x01      // commands for Endpoint_Halt
#define  IN_EP2              0x82
#define  OUT_EP2             0x02
#define  IN_EP3              0x83
#define  OUT_EP3             0x03
#define  IN_EP4              0x84
#define  OUT_EP4             0x04
#define  IN_EP5              0x85
#define  OUT_EP5             0x05
#define  IN_EP6              0x86
#define  OUT_EP6             0x06
#define  IN_EP7              0x87
#define  OUT_EP7             0x07

#define EP_IDLE  0x00
#define EP_TX    0x11
#define EP_RX    0x10
#define EP_SET_ADDRESS 0x21
#define EP_WAIT_STATUS 0x20
#define EP_STALL 0xaa


#ifdef _USB_LOW_SPEED_
#define  EP0_PACKET_SIZE         0x40  
// This value can be 8,16,32,64 
// depending on device speed, see USB spec
#else
#define  EP0_PACKET_SIZE         0x40
#endif /* _USB_LOW_SPEED_ */
#ifdef	SAMPLERATE_8KHZ
#define  EP1_PACKET_SIZE         0x0010		//0x0040
// Can range 0 - 1024 depending on data and transfer type
#define  EP1_PACKET_SIZE_LE      0x1000	//0x4000
// IMPORTANT- this should be Little-Endian version of EP1_PACKET_SIZE
#endif
#ifdef	SAMPLERATE_12KHZ
#define  EP1_PACKET_SIZE         0x0018		//0x0040
// Can range 0 - 1024 depending on data and transfer type
#define  EP1_PACKET_SIZE_LE      0x1800	//0x4000
// IMPORTANT- this should be Little-Endian version of EP1_PACKET_SIZE
#endif
#define  EP2_PACKET_SIZE         0x0020
// Can range 0 - 1024 depending on data and transfer type

#define  EP2_PACKET_SIZE_LE      0x2000	//0x4000
// IMPORTANT- this should be Little-Endian version of EP2_PACKET_SIZE

#define  EP3_PACKET_SIZE         0x0020		// 0x0040
// Can range 0 - 1024 depending on data and transfer type

#define  EP3_PACKET_SIZE_LE      0x2000	// 0x4000
// IMPORTANT- this should be Little-Endian version of EP2_PACKET_SIZE

#define  EP4_PACKET_SIZE         0x0020		// 0x0040
#define  EP4_PACKET_SIZE_LE      0x2000	//0x4000




// HID Descriptor Types
#define DSC_HID                    0x21  // HID Class Descriptor
#define DSC_HID_REPORT            0x22   // HID Report Descriptor

#define	cRequestType		0x60
#define	cStandardReq		0x0
#define	cClassReq			0x20
#define	cVendorReq			0x40

// Standard Request Codes
#define  GET_STATUS              0x00  // Code for Get Status
#define  CLEAR_FEATURE           0x01  // Code for Clear Feature
#define  SET_FEATURE             0x03  // Code for Set Feature
#define  SET_ADDRESS             0x05  // Code for Set Address
#define  GET_DESCRIPTOR          0x06  // Code for Get Descriptor
#define  SET_DESCRIPTOR          0x07  // Code for Set Descriptor(not used)
#define  GET_CONFIGURATION       0x08  // Code for Get Configuration
#define  SET_CONFIGURATION       0x09  // Code for Set Configuration
#define  GET_INTERFACE           0x0A  // Code for Get Interface
#define  SET_INTERFACE           0x0B  // Code for Set Interface
#define  SYNCH_FRAME             0x0C  // Code for Synch Frame(not used)

// HID Request Codes
#define GET_REPORT              0x01   // Code for Get Report
#define GET_IDLE                0x02   // Code for Get Idle
#define GET_PROTOCOL            0x03   // Code for Get Protocol
#define SET_REPORT              0x09   // Code for Set Report
#define SET_IDLE                0x0A   // Code for Set Idle
#define SET_PROTOCOL            0x0B   // Code for Set Protocol

// USB audio class request codes.
#define		cSET_CUR		0x01		// Current setting attribute.
#define		cSET_MIN		0x02		// Mininum setting attribute.
#define		cSET_MAX		0x03		// Maxnum setting attribute.
#define		cSET_RES		0x04		// Resolution attribute.
#define		cSET_MEM		0x05		// Memory space attribute.
#define		cGET_CUR		0x81
#define		cGET_MIN		0x82
#define		cGET_MAX		0x83
#define		cGET_RES		0x84
#define		cGET_MEM		0x85
#define		cGET_STAT		0xff
//---------------------------------------------------
// Control selector(CS) code.
// Terminal control selectors
#define		cCopyProtCtrl_CS	0x01

// Feature unit control selectors
#define		cMuteCtrl_CS	0x01
#define		cVolumeCtrl_CS	0x02

// Endpoint control selectors
#define		cSamFreqCtrl_CS	0x01
#define		cPitchCtrl_CS		0x02
//--------------------------------------------------
// Define device states
#define  DEV_ATTACHED            0x00  // Device is in Attached State
#define  DEV_POWERED             0x01  // Device is in Powered State
#define  DEV_DEFAULT             0x02  // Device is in Default State
#define  DEV_ADDRESS             0x03  // Device is in Addressed State
#define  DEV_CONFIGURED          0x04  // Device is in Configured State
#define  DEV_SUSPENDED           0x05  // Device is in Suspended State

// Define bmRequestType bitmaps
#define  IN_DEVICE               0x00  // Request made to device, direction is IN

#define  OUT_DEVICE              0x80  // Request made to device, direction is OUT

#define  IN_INTERFACE            0x01  // Request made to interface, direction is IN

#define  OUT_INTERFACE           0x81  // Request made to interface, direction is OUT

#define  IN_ENDPOINT             0x02  // Request made to endpoint, direction is IN

#define  OUT_ENDPOINT            0x82  // Request made to endpoint, direction is OUT

// Define wIndex bitmaps
#define  IN_EP1                  0x81  // Index values used by Set and Clear feature

#define  OUT_EP1                 0x01  // commands for Endpoint_Halt

#define  IN_EP2                  0x82
#define  OUT_EP2                 0x02

// Define wValue bitmaps for Standard Feature Selectors
#define  DEVICE_REMOTE_WAKEUP    0x01  // Remote wakeup feature(not used)
#define  ENDPOINT_HALT           0x00  // Endpoint_Halt feature selector

//
//	adc
//
#define ADC_ENABLE CLK_EN_CFG |= 0x80				// CLK_EN_CFG, Enable ADC clock. 
#define ADC_DISABLE CLK_EN_CFG &= ~0x80 



#define	cRFNMWorkCH	0x06	// 0x64
#define	cRFTestCH		0x64
#endif
/***********************************************************
						end file
***********************************************************/
