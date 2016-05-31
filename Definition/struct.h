/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: struct.h
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

#ifndef _STRUCT_H_
#define _STRUCT_H_

//#include "USB\usb_descriptor.h"
//
//device ID 对码时使用
//
typedef enum _DEVICE
{
	DEVICE_NULL=0x00,
	MOUSE,		  			//鼠标
	KEYBOARD,				//键盘
	PRESENTER,				//简报器
	REMOTE,					//遥控器
	DEVICE_MAX
}DEVICES;

//
// data type 数据传输时使用
//
typedef enum _DATATYPE
{
	DATATYPE_NULL = 0x80,
	DATATYPE_MOUSE,			//鼠标
	DATATYPE_KEYBOARD=0x01,		//键盘
	DATATYPE_KB_CELL=0x03,
	DATATYPE_BIND = 0x35,	// 0xAA,
	DATATYPE_CONFIG = 0x22,
	DATATYPE_OK = 0x30,		// 0x55,
	DATATYPE_MAX
}DATATYPE;


typedef enum _MOUSE_DATA_TYPE
{
	MOUSE_DATA_STANDARD = 0x00,
	MOUSE_DATA_REMOTE,
	MOUSE_DATA_MULTI,
	MOUSE_DATA_ACTIVE,
	MOUSE_DATA_MAX
}MOUSE_DATA_TYPE;

typedef enum _KEBOARD_DATA_TYPE
{
	KEYBOARD_DATA_STANDARD = 0x00,
	KEYBOARD_DATA_MCE,
	KEYBOARD_DATA_NONSYN,
	KEYBOARD_DATA_MAX
}KEBOARD_DATA_TYPE;


// system usb point 0 data send  --> keyboard data return;
typedef struct 	_USBP0_DATA 
{
	BYTE out_report[8] ;
	BYTE kb_out_report;
	BYTE out_report_index;
	BYTE wait_out_report;

	BYTE report_id;
	BYTE report_type;
	BYTE report_cnt;
	BYTE set_report_data[50];
	BYTE get_report_data[50];
	BYTE set_report_flag;
	BYTE get_report_flag;
	BYTE reday_report_flag;		// data ready to get report request.
	BYTE aceept;					// device received set report request
}USBP0_DATA;


// system usb point 1 data send --> keyboard
typedef struct 	_USBP1_DATA
{
//	BYTE uploading_flag :1;
	BYTE uploading :1;
//	BYTE data_update :1;
	BYTE null_data	:1;
	BYTE bInitBuf3:1;
	BYTE bSOFTimer:1;
	BYTE tick;
	BYTE re_data_len;
	BYTE re_data_len_copy;
	BYTE re_data_process;
	BYTE re_data[EP1_PACKET_SIZE];//[32];
	BYTE re_data_copy[EP1_PACKET_SIZE];
	BYTE re_data3[EP1_PACKET_SIZE];
//	BYTE re_dataBak[32];
//	BYTE in_report[9] ;      //report id + key buf
	BYTE ready_to_uploading;
}USBP1_DATA;


//system usb point 2 data send --> mouse ,multi media key
typedef struct _USBP2_DATA
{
	BYTE uploading:1;
	
	BYTE bRXKeyData:1;
	
	BYTE bKBDataUpload:1;
	BYTE bKBDataUploadBak:1;
	
	BYTE bMSDataUpload:1;
	BYTE bMSDataUploadBak:1;
	
	BYTE bMediaDataUpload:1;
	BYTE bMediaDataUploadBak:1;

	BYTE bRECDataUpload:1;
	BYTE bPlay:1;

	BYTE bMultiMediaKey:1;
	BYTE bSysPWRKey:1;

	BYTE bSensorDataUpload:1;
	BYTE in_report[32] ;
	BYTE in_report_len;
	BYTE ready_to_uploading;
}USBP2_DATA;

typedef struct _USBP4_DATA
{
	BYTE uploading:1;
	BYTE in_report[16] ;
	BYTE in_report_len;
	BYTE ready_to_uploading;
}USBP4_DATA;
//cell
typedef struct _CELL
{
	BYTE mouse_cell_updata : 1;
	BYTE keyboard_cell_updata : 1;
	BYTE mouse_cell[2];
	BYTE keyboard_cell[2];
}CELL;

//cpi
typedef struct _CPI
{
	BYTE cpi_updata : 1;
	BYTE cpi_save;
	BYTE cpi_val;
}CPI;

//
// rf send type
//
typedef enum _RF_DATA
{
	RF_DATA_WORK = 0x00,
	RF_DATA_BIND,
	RF_DATA_ACTIVE,
	RF_DATA_NULL
}RF_DATA;

//
// system  mode	 工作模式
//
typedef enum _SYSTEM_MODE
{
	SYSTEM_WORK = 0x00,	   			//connect mode normal
	SYSTEM_BIND,						//code pair mode
	SYSTEM_TEST,					    //test mode
	SYSTEM_CODE,							//PC_application
	SYSTEM_PCBA,					    //PCBA_TEST
	SYSTEM_DEBUG,
	SYSTEM_MODE_MAX
} SYSTEM_MODE;

//
// system work  mode	
//
typedef enum _SYSTEM_WORK_MODE
{
	SYSTEM_WORK_WORK = 0x00,	   
	SYSTEM_WORK_SUSPEND,		
	SYSTEM_WORK_MAX
} SYSTEM_WORK_MODE;


//
//	system test mode
//
typedef enum _SYTEM_TEST_MODE
{
	TEST_SC =0,						//单载波
	TEST_CD,						//调制
	TEST_RF_DATA,					//发送数据
	TEST_MAX
}SYTEM_TEST_MODE;

//
// timer struct definition
//
typedef struct	_TIME_STRUCT
{
	UINT32 systemTick ;		      //system timer tick
}TIME_STRUCT;

//
//system timer struct
//
typedef struct	_TIMER
{
	UINT32	TimeOutVal; 			//time out value
	UINT32	RecTickVal;			  	//softtimer setting value
} TIMER;


//
// MOUSE config
//
typedef struct	_MOUSE_CONFIG_STRUCT
{
	BYTE mouse_type;
	BYTE auto_down;
	BYTE low_power[2];
}MOUSE_CONFIG;

//
// keyboard config
//
typedef struct	_KEYBOARD_CONFIG_STRUCT
{
	BYTE keyboard_type;
	BYTE num_pad;
	BYTE BK_led;
	BYTE small_KB;
	BYTE fn_num;
	BYTE KB_lp[2];
}KEYBOARD_CONFIG;

//
// system bind flag
//
typedef struct	_BIND
{
	BYTE mouse_bind : 1;   //对码模式中当次对码标志
	BYTE keyboard_bind : 1; //对码模式中当次对码标志
	BYTE mouse_requst_cnt;
	BYTE keyboard_requst_cnt;
}BIND;

//
//	keyboard wheel
//
typedef struct _KB_WHEEL
{
	BYTE kb_wheel_flag;
	BYTE kb_wheel;
}KB_WHEEL;



typedef struct	_MTPRECORD
{
/*mtp[0].0*/	UINT8 bind_time  : 1;				//对码时间
/*mtp[0].1*/	UINT8 bind_power : 1;				//对码功率
/*mtp[0].2*/	UINT8 usb_string:1;					//USB描述符	
/*mtp[0].3*/	UINT8 ct_mskey : 1;					//鼠标自定义按键
/*mtp[0].4*/	UINT8 keyboard_bind : 1;			//键盘对码标志
/*mtp[0].5*/	UINT8 vid_pid  : 1;					//厂商 产品ID
/*mtp[0].6*/	UINT8 rx_id: 1;						//MTP是否配置有ID
/*mtp[0].7*/	UINT8 mouse_bind : 1;				//对码标志

/*mtp[1].10*/	UINT8 ms_fill: 2;					//鼠标标志填充，无意义
/*mtp[1].2*/	UINT8 ms_ct_cpi : 1;				//用户CPI
/*mtp[1].3*/	UINT8 ms_lp: 1;						//鼠标低电压
/*mtp[1].4*/	UINT8 cpi_def : 1;					//cpi 默认
/*mtp[1].5*/	UINT8 cpi : 1;						//cpi
/*mtp[1].6*/	UINT8 ms_au_down : 1;				//鼠标自动关机	
/*mtp[1].7*/	UINT8 ms_type:1;					//鼠标产品类型

/*mtp[2].0*/	UINT8 KB_lp:1;						//键盘低电压值设定
/*mtp[2].1*/	UINT8 num_pad:1;					//非同步小键盘，当产品为非同步键盘时忽略，普通键盘与MCE键盘可选功能
/*mtp[2].2*/	UINT8 KB_led:1;						//键盘背光
/*mtp[2].3*/	UINT8 small_KB:1;					//当按下numlock 键时，I,O,U等为数字键盘(与笔记本相同)
/*mtp[2].4*/	UINT8 fn_dire:1;					//FN+方向键 为 page up ,page down 等功能
/*mtp[2].5*/	UINT8 fn_numpad: 1;					//FN+I,O,U等 为数字键盘功能
/*mtp[2].6*/	UINT8 fn_f1_f12: 1;					//FN+F1--F12 多媒体功能
/*mtp[2].7*/	UINT8 KB_type : 1;					//键盘产品类型
} MTPRECORD;


typedef union {MTPRECORD mtp_flag; UINT8 mtp[3];} MTPFLAG;

typedef struct{
	BYTE bKeyOK : 1;		// Bit0
	BYTE bKeyDN : 1;		// Bit1
	BYTE bKeyR : 1;
	BYTE bKeyUp : 1;
	BYTE bKeyL : 1;
	BYTE bKeyREC : 1;
	BYTE bmKeyMap : 2;
}bKEY_MAP;

typedef	union{
	bKEY_MAP bKey;
	UINT8 uKey;
}KEY_VAL;

typedef struct{
	BYTE bBindKeyState : 1;			// 1: press, 0: release.
	BYTE bBindKeyValid : 1;
}bKEY_FLAG;

typedef union{
	bKEY_FLAG bKey;
	UINT8 uKey;
}KEY_PAD;
// system state struct definition
typedef struct	_SYS_STRUCT
{
//====================================
	
	BIND bind;
	BYTE bind_power;
	BYTE bind_time;
	BYTE powered;					//系统上电标志 0 上电  1 上电结束，进入工作模式
	UINT16 wPWROnBindTime;
	BYTE work_mode;
	BYTE work_sub_mode;
	
	BYTE mouse_vol_flag;

	BYTE vid_pid[4];

	BYTE uPacketID;
	BYTE uError;

	BYTE uMultiKey[2];
	BYTE uLastMultiKey;
	BYTE szMSData[3];
	BYTE uKeyLens;
	BYTE szKeyData[7];
	BYTE szLastKeyData[7];
	BYTE szACCGyroData[12];

	KEY_PAD Key; 
	CELL cell;
	
	MOUSE_CONFIG mouse_config;

//	TIME_STRUCT time ;
	MTPFLAG mtp_record;
	USBP0_DATA usbp0_data;		
 	USBP1_DATA usbp1_data;	   	//keyboard
	USBP2_DATA usbp2_data;		//mouse midia key
	USBP4_DATA usbp4_data;		//
	
}SYS_STRUCT;

//---------------------------------------------------------
//
// 				USB struct
//
//----------------------------------------------------------
typedef struct {
   unsigned char ReportID;
   void (*hdlr)();
} VectorTableEntry;

typedef struct _USB_PACKET_FORMAT
{
	char FeatureId;
	char MessageType;
	char SequenceNumber;
	char len;
	char** pPayload;
}USB_PACKET_FORMAT,*pUSB_PACKET_FORMAT;


typedef struct{
   unsigned char Length;
   pUSB_PACKET_FORMAT Ptr;
} BufferStructure;

typedef union {unsigned int i; unsigned char c[2]; } WORD; // union

#ifdef	DEV_PHONE	
typedef struct {
	BYTE uMICMute;		// 1: mute, 0: not mute.
	WORD wMICVolume;
	WORD wMICMinVolume;
	WORD wMICMaxVolume;
	WORD wMICRes;
	BYTE uMICInterfaceAlter;

	BYTE uSPKMute;
	WORD wSPKVolume;	
	WORD wSPKMinVolume;
	WORD wSPKMaxVolume;
	WORD wSPKRes;
	BYTE uSPKInterfaceAlter;
}USBPhoneAttri;
#endif

#ifdef	DEV_MIC
typedef struct {
	BYTE uMICMute;		// 1: mute, 0: not mute.
	WORD wMICVolume;
	WORD wMICMinVolume;
	WORD wMICMaxVolume;
	WORD wMICRes;
	BYTE uMICInterfaceAlter;
}USBPhoneAttri;
#endif

#endif

/***********************************************************
						end file
***********************************************************/
