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
<author> 		<time> 		<version > 	<desc>
				2011/03/01  	  0.1  		build this moudle 
***********************************************************/

#ifndef _USB_STANDARD_REQUESTS_H_
#define _USB_STANDARD_REQUESTS_H_

void Get_Status (void) ;
void Clear_Feature ( ) ;
void Set_Feature (void) ; 
void Set_Address (void);
void Get_Descriptor (void) ;
void Get_Configuration (void)   ;
void Set_Configuration (void) ;
void Get_Interface (void)    ;
void Set_Interface (void);
void Get_Idle(void) ;
void Get_Protocol(void) ;
void Set_Protocol (void);
void Set_Idle (void);
void Get_Report (void);
void Set_Report (void); 

extern void AudioInit(void);
extern void SET_CUR(void);
extern void SET_MIN(void);
extern void SET_MAX(void);
extern void SET_RES(void);
extern void SET_MEM(void);
extern void GET_CUR(void);
extern void GET_MIN(void);
extern void GET_MAX(void);
extern void GET_RES(void);
extern void GET_MEM(void);
extern void GET_STAT(void);
#endif

/***********************************************************
						end file
***********************************************************/