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
<author>          <time>            <version >             <desc>
			2011/03/01            0.1               build this moudle 
***********************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#define	bSysCheck			0x01
//#define	bLEDTimer			0x02
#define	bRFTimer			0x02
#define	bRFConnectTimer	0x04
#define	b10msDelayTimer	0x08

extern BYTE bdata u10msFlag;
extern BYTE DATA uMCUTick;
extern bit b2msFlag;

void InitSysTimer(void);
void ResetSysTimer(void);
void WaitUs(UINT32 us);
void WaitMs(UINT8 ms);

#endif

/***********************************************************
						end file
***********************************************************/