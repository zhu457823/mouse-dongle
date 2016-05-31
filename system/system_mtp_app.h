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
			2011/03/01  		0.1  			build this moudle 
***********************************************************/

#ifndef _SYSTEM_MTP_APP_H_
#define _SYSTEM_MTP_APP_H_

#ifdef	CHIP_BK2535
#define cMTP_LEN                                     126	// 112 

typedef struct{
	BYTE mtp_pool[cMTP_LEN];
	BOOL flash_need_write;
}FLASH_DATA;

extern FLASH_DATA XDATA Flash;

void Sys_FlashEraseAll(void);
void Sys_FlashWriteAll(void);
#endif

BOOL buf_compare(BYTE *buf1, BYTE *buf2,BYTE len);
BOOL buf_is_null(BYTE *buf,BYTE len);
void buf_copy(BYTE *form, BYTE *to, BYTE len);

void system_read_MTPrecord(void);

#endif

/***********************************************************
						end file
***********************************************************/