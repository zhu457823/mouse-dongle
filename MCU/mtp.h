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
<author> 	<time> 		 <version > 	     <desc>
		    2011/03/01  		0.1  	       build this moudle 
***********************************************************/

#ifndef _MTP_H_
#define _MTP_H_

void mtp_unlock_set(void);
void mtp_unlock_clr(void);

//#define USE_RDN_SPACE

UINT8 FlashReadByte(UINT8 flash_addr);
void FlashWriteByte(UINT8 flash_addr, UINT8 flash_data);
void FlashWriteBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len);
void FlashReadBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len);
void FlashEraseAll(void);


#endif

/***********************************************************
						end file
***********************************************************/