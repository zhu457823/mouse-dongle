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
<author> 	<time> 		<version > 		<desc>
		  2011/03/01  	    0.1  			build this moudle 
***********************************************************/

#ifndef _SYSTEM_WORKMODE_H_
#define _SYSTEM_WORKMODE_H_


// Byte 1.	
#define	cParketIDMark	0x07

// Byte 2.
#define	cKeyLensMark	0x07
#define	cMSXY			0x08
#define	cMSData			0x10
#define	cMultiKeyData	0x20
#define	cKeyData		0x40	
#define	cSyncReq		0x80

//-----------------------------------------------------
typedef struct{
//	BYTE bKeyPadActive:1;			// 1: Key press. 0 Key release..
	BYTE bKeyUpdate:1;				// 1: Transmit key state.
	BYTE bkeyAction:1;
	BYTE bMultiKeyUpdate:1;
	BYTE bMSKeyUpdate:1;
	BYTE bMultiKeyUpdateBak:1;
	BYTE bKeyUpdateBak:1;
}bmKEY_FLAG;

typedef union{
	BYTE uKeyFlag;
	bmKEY_FLAG bKeyFlag;
}KEY_FlAG;

typedef struct{
	UCHAR KeyVal[2];	// [7];			// B0: Modify key, B1~6: KeyCode
	UCHAR KeyLens;
	KEY_FlAG KeyFlag;
}KEY_DATA;

#define	cRFDisConnectTime		20	// 202	// 250		// 2.5s
#define	cRXIdleTime				999	// 1250		// 10s
#define	cWorkTime				6		// 48ms

extern bit bUSBMode;

void system_work_mode(void);
void CheckRFDisconnect(void);
void Sys_RFPowerOn(void);
void Sys_PowerDownCtrl(void);
void system_work_ini(void);
void system_acceptdata_process(void);
void Sys_KeyScan(void);
void system_suspend(void);
void system_suspend_mode(void);
void SaveRXData(BYTE uLen);

#endif

/***********************************************************
						end file
***********************************************************/