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
<author>           <time>           <version >          <desc>
                     2011/03/01            0.1           build this moudle 
***********************************************************/

#include "Headfile\includes.h"


//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void BK2433_RF_Initial(void)
{
	UINT8 i,j;
	UINT8 WriteArr[4];
	
	for(i=0;i<=8;i++)					// Initial Bank1 register.
	{
		for(j = 0; j < 4; j++)
		{
			WriteArr[j] = (Bank1_Reg0_8[i] >> (8*(3 - j))) & 0xff; 
		}
		W_BANK1_ANALOG_REG(i, WriteArr);
	}
	W_BANK1_DIGITAL_REG(BK2401_CFG_0C_ARRAY,Bank1_RegC,4);
	W_BANK1_DIGITAL_REG(BK2401_CFG_0D_ARRAY,Bank1_RegD,4);
	W_BANK1_DIGITAL_REG(BK2401_RAMP_TAB_ARRAY,Bank1_Ramp_Table,11);

	TX_FREQ_OFFSET[0] = 0x00;
	TX_FREQ_OFFSET[1] = 0x00;
	TX_FREQ_OFFSET[2] = 0x00;
	TX_FREQ_OFFSET[3] = 0x96;
	RX_FREQ_OFFSET[0] = 0x00;
	RX_FREQ_OFFSET[1] = 0x00;
	RX_FREQ_OFFSET[2] = 0x00;
	RX_FREQ_OFFSET[3] = 0xA0;

	MOD_DELAY = 0x0A;
	PLL_SDM = 0x00;    
	FM_GAIN_H = 0x00;
	FM_GAIN_L = 0xB0;
	FM_KMOD_SET_H = 0x01;
	FM_KMOD_SET_L = 0x00;
	MOD_COEFFICIENT_H = 0x09;
	MOD_COEFFICIENT_L = 0xAA;
	ANA_CTRL10 = 0x82;
	ANA_CTRL11 = 0xbf;	// 0xff
	ANA_CTRL12 = 0x07;
	ANA_CTRL13 = 0x81;
// [Config]
// B7: Reserved.
// B6: 0, Reflect RX_DR as active low interrupt on the IRQ pin.
// B5: 0, Reflect TX_DR as active low interrupt on the IRQ pin.
// B4: 0, Reflect MAX_RT as active low interrupt on the IRQ pin.
// B3: 1 Enable CRC.
// B2: 1 CRC encode 2 bytes.
// B1: 1 power up, 0: power down.
// B0: 1 PRX. 0: PTX.
	BK2401_CONFIG = 0x0f;
// Enable pipe0, pipe1 auto acknowledgement.
 	BK2401_ENAA = 0X03;
// Enable pipe0, pipe1.
	BK2401_ENRX = 0X03;			// Enable RX address.
	BK2401_AW = 0x02;				// Set RX/TX address width(4 Bytes)
	BK2401_RETR =0x15;//0x14;//0x13;//0x11; //0x10;//0x12;	//0x16;		// Re-transmission delay 500us. 6 times. 2533 received ack max time about 380us 

	BK2401_RFCH = cRFNMWorkCH;	//0x64;	//0x02;		// RF Channel.
#if	cRFPWR_5DBM == 1
	#if cAirRate == 2
	BK2401_SETUP = 0x0F;
	#elif cAirRate == 1
	BK2401_SETUP = 0x07;			// (LNA gain(High gain), 5DBM, 1Mbps datarate).
	#else
	BK2401_SETUP = 0x27;			// (LNA gain(High gain), 5DBM, 250Kbps datarate).
	#endif
#else
	#if cAirRate == 2
	BK2401_SETUP = 0x0D;
	#elif cAirRate == 1
	BK2401_SETUP = 0x05;			// (LNA gain(High gain), 0DBM, 1Mbps datarate).
	#else
	BK2401_SETUP = 0x25;			// (LNA gain(High gain), 0DBM, 250Kbps datarate).
	#endif
#endif
	memcpy(BK2401_R0_ADDR,RX0_Address,5);	// Pipe0 receiver address.
	memcpy(BK2401_R1_ADDR,RX1_Address,5);	// Pipe1 receiver address.
	BK2401_R2_ADDR = 0X11;
	BK2401_R3_ADDR = 0X12;   
	BK2401_R4_ADDR = 0X13;
	BK2401_R5_ADDR = 0X14;
	memcpy(BK2401_TX_ADDR,RX0_Address,5);	// TX address.
	BK2401_R0_PW = 0X20;		// Number of  bytes in RX payload in data pipe0(32Bytes.)
	BK2401_R1_PW = 0X20;
	BK2401_R2_PW = 0X20;
	BK2401_R3_PW = 0X20;
	BK2401_R4_PW = 0X20;
	BK2401_R5_PW = 0X20;
	BK2401_DYNPD = 0X3f;
	BK2401_FEATURE = 0X07;		// Enable W_TX_Payload_NoACK command, Enable payload with ACK, Enable dynamic  payload length.
	PowerDown_RF();
	PowerUp_RF();
	PowerDown_RF();
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;

//	RF_VcoAmp_Cal();
//	RF_KMod_Cal();
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void W_BANK1_ANALOG_REG( UINT8 addr, UINT8* pvalue ) 
{
    while (!(  BK2401_SCTRL&0x80)) ;
    memcpy ( BK2401_SDATA, pvalue, 4 ) ;  // data
    BK2401_SCTRL  = addr;                       // address
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void W_BANK1_DIGITAL_REG(UINT8 *paddr, UINT8* pvalue,int len)
{
    UINT8 i;
    for(i=0;i<len;i++)
        paddr[i]=pvalue[i];
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
void ChangeTxPipe(UINT8 pipe_num)
{
    char tmp_address[5];
    
    if(pipe_num>5)
        return;

    switch(pipe_num)
    {
        case 0:
           memcpy(BK2401_R0_ADDR,RX0_Address,5);
           memcpy(BK2401_TX_ADDR,RX0_Address,5);
           memcpy(BK2401_R1_ADDR,RX1_Address,5);
            break;

        case 1:
            memcpy(BK2401_R0_ADDR,RX1_Address,5);
            memcpy(BK2401_TX_ADDR,RX1_Address,5);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        	memcpy(tmp_address,RX1_Address,5);
			
            if(pipe_num==2)
                tmp_address[0]=BK2401_R2_ADDR;
			else
            if(pipe_num==3)
                tmp_address[0]=BK2401_R3_ADDR;
			else
            if(pipe_num==4)
                tmp_address[0]=BK2401_R4_ADDR;
			else
            if(pipe_num==5)
                tmp_address[0]=BK2401_R5_ADDR;

            memcpy(BK2401_R0_ADDR,tmp_address,5);
            memcpy(BK2401_TX_ADDR,tmp_address,5);
            break;
    }

}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void ChangePublicPipe(void)
{
	memcpy(BK2401_R0_ADDR,PUBLICRX0_Address,5);
	memcpy(BK2401_TX_ADDR,PUBLICRX0_Address,5);
	memcpy(BK2401_R1_ADDR,PUBLICRX1_Address,5);
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void RF_ReadData(int bytes)
{
//	memset(FIFO_data,0,bytes) ;
	R_RX_PAYLOAD(FIFO_data,bytes);
}

//-------------------------------------------------------
//Function: 
//Desc	: 	0= 单载波 ,1=工作
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void RF_Set_Mode(BYTE mode)
{
	UINT8 WriteArr[4];
	UINT8 j;
	
	for ( j = 0; j < 4; j ++ )
	{    
		WriteArr[j] =  ( Bank1_Reg0_8[2] >> ( 8 * ( 3 - j ) ) ) & 0xff; 
	}

	if(0 == mode)		// Single Wave
	{
		WriteArr[2] &= ~0x80;
		WriteArr[3] &= 0x80;
		WriteArr[3] |= 0x40;
		W_BANK1_ANALOG_REG(2,WriteArr);
		ANA_CTRL13 |= 0x20;
	}
	else
	{
		WriteArr[2] |= 0x80;
		WriteArr[3] &= 0x80;
		WriteArr[3] |= 0x40;
		W_BANK1_ANALOG_REG(2,WriteArr);
		ANA_CTRL13 &= ~0x20;
	}
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void W_TX_PAYLOAD_NOACK(UINT8 *pBuf, UINT8 bytes)
{
    UINT8 i;
    BK2401_CMD = 0x68;
    for (i=0; i<bytes; i++)
        BK2401_FIFO = pBuf[i];
    BK2401_CMD = 0x00;
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void W_ACK_PAYLOAD(UINT8 *pBuf, UINT8 bytes, UINT8 pipe)
{
    UINT8 i;

    BK2401_CMD = 0x68 + pipe;		// Used RX mode. Write payload to be transmit together with ACK packet.
    for (i=0; i<bytes; i++)
        BK2401_FIFO = pBuf[i];
    BK2401_CMD = 0x00;	
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void R_RX_PAYLOAD ( UINT8 *pBuf, UINT8 bytes ) 
{
    UINT8 i;

    BK2401_CMD = 0x40; 	         // command
    for ( i = 0; i < bytes; i ++ )
        pBuf[i] = BK2401_FIFO; 	 // data
    BK2401_CMD = 0x00;           // end
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void W_TX_PAYLOAD(UINT8 *pBuf, UINT8 bytes)
{
    UINT8 i;
    BK2401_CMD = 0x60;
    for (i=0; i<bytes; i++)
        BK2401_FIFO = pBuf[i];
    BK2401_CMD = 0x00;
}


//-------------------------------------------------------
//Function: 
//Desc	: 	0=-10dbm,1=-5dbm,2=0dbm,3=5dbm
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void RF_Set_ouput_power(BYTE step)
{
	switch(step)
	{
		#if cAirRate == 2
		case 0:
			BK2401_SETUP = 0x0A;			// -10DB, high gain(LNA)
			break;
		case 1:
			BK2401_SETUP = 0x0B;			// -5DB, high gain(LNA)
			break;
		case 2:
			BK2401_SETUP = 0x0D;			// 0DB, high gain(LNA)
			break;
		case 3:
			BK2401_SETUP = 0x0F;			// 5DB, high gain
			break;
		#elif cAirRate == 1
		case 0:
			BK2401_SETUP = 0x01;			// -10DB, high gain(LNA)
			break;
		case 1:
			BK2401_SETUP = 0x03;			// -5DB, high gain(LNA)
			break;
		case 2:
			BK2401_SETUP = 0x05;			// 0DB, high gain(LNA)
			break;
		case 3:
			BK2401_SETUP = 0x07;			// 5DB, high gain
			break;
		#else
		case 0:
			BK2401_SETUP = 0x21;
			break;
		case 1:
			BK2401_SETUP = 0x23;
			break;
		case 2:
			BK2401_SETUP = 0x25;
			break;
		case 3:
			BK2401_SETUP = 0x27;
			break;
		#endif
		default:
			break;
	}
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;
}


//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void RF_SetLowOuput(void)
{
UINT8 i;
	UINT8 WriteArr[4];
	UINT32 reg_val;

	RF_Set_ouput_power(1);
	reg_val = RF_BANK1_REG3[4];	//-6dB reg3 20->0 [22:23]->00
	ANA_CTRL11 = RF_BANK0_CTRL11[4];
	for(i = 0; i < 4; i++)
	{
		WriteArr[i] = (reg_val >> (8*(3 - i))) & 0xff; 
	}
	W_BANK1_ANALOG_REG(3,WriteArr);
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void RF_SetNomalOuput(void)
{
	UINT8 WriteArr[4];
	UINT8 i;
	UINT32 reg_val;
	
	#if	cRFPWR_5DBM == 1
	RF_Set_ouput_power(3);
	reg_val = RF_BANK1_REG3[0];
	ANA_CTRL11 = RF_BANK0_CTRL11[0];
	#else
	RF_Set_ouput_power(2);
	reg_val = RF_BANK1_REG3[2];	//0dB reg3 20->0 [22:23]->00
	ANA_CTRL11 = RF_BANK0_CTRL11[2];
	#endif

	for(i = 0; i < 4; i++)
	{
		WriteArr[i] = (reg_val >> (8*(3 - i))) & 0xff; 
	}
	W_BANK1_ANALOG_REG(3,WriteArr);
	BK2401_CE = 0X00;
	BK2401_CE = 0X01;
}
#if 0
//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	:
//-------------------------------------------------------
void RF_VcoFreq_Cal(void)
{
	UINT8 j;
	UINT8 WriteArr[4];
	
	// reg1[9] 1->0
	for ( j = 0; j < 4; j ++ )
	{    
		WriteArr[j] =  ( Bank1_Reg0_8[1] >> ( 8 * ( 3 - j ) ) ) & 0xff; 
	}
	WriteArr[1] |= 0x02;
	W_BANK1_ANALOG_REG ( 1, WriteArr );
	WaitUs(200);// delay 500us
	WriteArr[1] &= ~0x02;
	W_BANK1_ANALOG_REG ( 1, WriteArr );
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	:
//-------------------------------------------------------
void RF_VcoAmp_Cal(void) // 幅度
{
	UINT8 WriteArr[4];
	UINT8 j;
	
	for ( j = 0; j < 4; j ++ )
	{    
		WriteArr[j] =  ( Bank1_Reg0_8[1] >> ( 8 * ( 3 - j ) ) ) & 0xff; 
	}
	WriteArr[2] |= 0x80; // reg1[23]
	W_BANK1_ANALOG_REG ( 1, WriteArr );

	for ( j = 0; j < 4; j ++ )
	{    
		WriteArr[j] =  ( Bank1_Reg0_8[2] >> ( 8 * ( 3 - j ) ) ) & 0xff; 
	}
	WriteArr[0] |= 0x02; // reg2[1]
	W_BANK1_ANALOG_REG (2, WriteArr );
	WaitUs(200);// delay 1ms
	WriteArr[1] = 0x04; // reg2[10]
	W_BANK1_ANALOG_REG (2, WriteArr );
	WaitUs(2);// delay 1us

	WriteArr[1] &= ~0x04; //
	W_BANK1_ANALOG_REG (2, WriteArr );
	WaitUs(50);// delay 100us  
	WriteArr[0] &= ~0x02;
	W_BANK1_ANALOG_REG (2, WriteArr );
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	:
//-------------------------------------------------------
void RF_KMod_Cal(void)
{
	UINT8 WriteArr[4], j;
	UINT16 freqdev=0;
	UINT16 fmgain=0;
	double temp=0;
//	char str[50];

	SwitchToTxMode();
	// Bypass gated clock（bank0.22<7>=1）
	BK2401_CFG_0C_0 |= 0x80;
	// channel=0,（bank0.5<6:0>=0）
	BK2401_RFCH &= 0x80;
	// Bypass PLL DSP SDM（bank1.Reg2<23>=0） 
	for ( j = 0; j < 4; j ++ )
	{    
		WriteArr[j] =  ( Bank1_Reg0_8[2] >> ( 8 * ( 3 - j ) ) ) & 0xff; 
	}
	WriteArr[2] &= ~0x80; 
	W_BANK1_ANALOG_REG(2, WriteArr );    
	// 进入单载波模式（bank0.63Hex<5>=1） 
	ANA_CTRL13 |= 0x20;
	// VCO校准
	RF_VcoFreq_Cal();
	WaitUs(200);
	// 打开16M clock（bank1.Reg2<1:0>=3）

	WriteArr[0] |= 0x03; 
	W_BANK1_ANALOG_REG(2, WriteArr );
	WaitUs(200);
	// 设置gm_gain, kmod_coff,Bank0.5A<0>=1Hex,Bank0.5B<7:0>=0Hex, Bank0.5C<0>=1Hex,Bank0.5D<7:0>=0Hex 
	FM_GAIN_H |= 0x01;
	FM_GAIN_L = 0;
	FM_KMOD_SET_H |= 0x01;
	FM_KMOD_SET_L = 0;

	// cal begin: Bank0.59<0>=0, 10us, Bank0.59<0>=1，100ms
	PLL_SDM &= ~0x01;
	WaitUs(200);
	PLL_SDM |= 0x01;
	WaitUs(8000);	// 20MS
	// read frequency deviation: A1=bank0.3E<4:0>, A2=bank0.3F<7:0>, A = [A1,A2]
	freqdev = ((UINT16)(BK2401_KCALOUT_H&0x3f))<<8  ; 
	freqdev += BK2401_KCALOUT_L;
//	DEG(str,"freqdev:%x , BK2401_KCALOUT_L: %x \r\n",(int)freqdev,(int)BK2401_KCALOUT_L);

	// set gain: 5aH<0>,5bH<7:0> = 300*256/A (1M) 160*256/A (250K) 
#if cAirRate == 0		// 250K
	temp = 160.0*256.0;
	fmgain = temp/freqdev;
	
#elif cAirRate == 1		// 1M
	temp = 300.0*256.0;
	fmgain = (UINT16)(temp/freqdev);

#elif cAirRate == 2		 // 2M
	temp = 600.0*256.0;
	fmgain = (UINT16)(temp/freqdev);

#endif
	FM_GAIN_H &= ~0x01;
	FM_GAIN_H |= ((UINT16)fmgain/0x100)&0x01;
	FM_GAIN_L = ((UINT16)fmgain%0x100);
	// bank0.63Hex<5>=0,bank0.22<7>=0,bank1.Reg2<1:0>=0,bank1.Reg2<23>=1,Bank0.59<0>=0
	ANA_CTRL13 &= ~0x20;
	BK2401_CFG_0C_0 &= ~0x80;
	WriteArr[0] &= ~0x03; 
	W_BANK1_ANALOG_REG(2, WriteArr );
	WriteArr[2] |= 0x80; 
	W_BANK1_ANALOG_REG(2, WriteArr ); 
	PLL_SDM &= ~0x01; 
#if cAirRate == 0		// 250K
	// Bank0.5E<4:0>=0x5，Bank0.5F<7:0>=0x1E
	MOD_COEFFICIENT_H &= ~0x3f;
	MOD_COEFFICIENT_H |= 0x05;
	MOD_COEFFICIENT_L = 0x1E;
#elif cAirRate == 1		 // 1M
	// Bank0.5E<4:0>=0x9, Bank0.5F<7:0>=0xAA
	MOD_COEFFICIENT_H &= ~0x3f;
	MOD_COEFFICIENT_H |= 0x09;
	MOD_COEFFICIENT_L = 0xAA;
#elif cAirRate == 2			// 2M
	// Bank0.5E<4:0>=0x13, Bank0.5F<7:0>=0x33
	MOD_COEFFICIENT_H &= ~0x3f;
	MOD_COEFFICIENT_H |= 0x13;
	MOD_COEFFICIENT_L = 0x33;
#endif
}
#endif
//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void SwitchToRxMode(void)
{
    FLUSH_RX;
    FLUSH_TX;
    BK2401_CE=0;
    BK2401_CONFIG=BK2401_CONFIG|0x01;//set bit 1
    BK2401_CE=1;    
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void SwitchToTxMode(void)
{
    FLUSH_TX;
    FLUSH_RX;
    BK2401_CE=0;
    BK2401_CONFIG=BK2401_CONFIG&0xfe;//clear bit 1
    BK2401_CE=1;
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void PowerUp_RF(void)
{
    BK2401_CONFIG=BK2401_CONFIG|0x02;
}

//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: 
//Return: 
//Others: 
//Author:
//Date	: 2011/03/01
//-------------------------------------------------------
void PowerDown_RF(void)
{
    BK2401_CONFIG = BK2401_CONFIG&0xfd;
}

void EnablePipe0(void)
{
	BK2401_ENRX = 0x01;
}

/***********************************************************
						end file
***********************************************************/
