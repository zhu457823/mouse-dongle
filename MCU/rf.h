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
		 	2011/03/01  		0.1  		build this moudle 
***********************************************************/

#ifndef _RF_H_
#define _RF_H_


//#define		cAirRate		2			// 2M data rate, 
#define		cAirRate		1			// 1M data rate,
//#define		cAirRate		0			// 250KHZ data rate

void BK2433_RF_Initial(void);
void W_BANK1_ANALOG_REG( UINT8 addr, UINT8* pvalue );
void W_BANK1_DIGITAL_REG(UINT8 *paddr, UINT8* pvalue,int len);
void ChangeTxPipe(UINT8 pipe_num);
void ChangePublicPipe(void);
void RF_ReadData(int bytes);
void RF_Set_Mode(BYTE mode);
void W_TX_PAYLOAD_NOACK(UINT8 *pBuf, UINT8 bytes);
void R_RX_PAYLOAD ( UINT8 *pBuf, UINT8 bytes );
void W_TX_PAYLOAD(UINT8 *pBuf, UINT8 bytes);
void W_ACK_PAYLOAD(UINT8 *pBuf, UINT8 bytes, UINT8 pipe);
void RF_Set_ouput_power(BYTE step);
void RF_SetLowOuput(void);
void RF_SetNomalOuput(void);
void RF_VcoFreq_Cal(void);
void RF_VcoAmp_Cal(void);
void RF_KMod_Cal(void);
void SwitchToRxMode(void);
void SwitchToTxMode(void);
void PowerUp_RF(void);
void PowerDown_RF(void);
void EnablePipe0(void);
#endif


/***********************************************************
						end file
***********************************************************/