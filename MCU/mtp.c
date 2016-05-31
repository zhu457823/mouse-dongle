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

#include "Headfile\includes.h"

VOLATILE bit mtp_unlock1=0; // 0=lock
VOLATILE bit mtp_unlock2=1; // 
VOLATILE bit mtp_unlock3=0; // 
VOLATILE bit mtp_unlock4=1; // 
VOLATILE bit mtp_unlock5=0; // 
VOLATILE bit mtp_unlock6=0; // 
VOLATILE bit mtp_unlock7=1; // 
VOLATILE bit mtp_unlock8=1; // 

#define if_mtp_unlock if(mtp_unlock1) if(!mtp_unlock2) if(mtp_unlock3) if(!mtp_unlock4) if(mtp_unlock5) if(mtp_unlock6) if(!mtp_unlock7) if(!mtp_unlock8)

//-------------------------------------------------------
//-------------------------------------------------------
void mtp_unlock_set(void)
{
	mtp_unlock1=1 ; 
	WaitUs(100);//(10000) ;
	mtp_unlock2=0 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock3=1 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock4=0 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock5=1 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock6=1 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock7=0 ; 
	WaitUs(100);//(10000) ; 
	mtp_unlock8=0 ; 
	WaitUs(100);//(10000);
}
//-------------------------------------------------------
//-------------------------------------------------------
void mtp_unlock_clr(void)
{
	mtp_unlock1=0 ;
	mtp_unlock2=1 ; 
	mtp_unlock3=0 ; 
	mtp_unlock4=1 ;
	mtp_unlock5=0 ; 
	mtp_unlock6=0 ; 
	mtp_unlock7=1 ; 
	mtp_unlock8=1 ;
}
//-------------------------------------------------------
//-------------------------------------------------------
#ifdef	CHIP_BK2535
UINT8 FlashReadByte(UINT8 flash_addr)
{
    UINT8 value = 0;
/*
FLASH_CTL
Control bit [7]: write, write 1 to operate, the bit will be cleared automatically after operate.
Control bit [6]: read, write 1 to operate, the bit will be cleared automatically after operate.
Control bit [5]: erase, write 1 to operate, the bit will be cleared automatically after operate.
Control bit [1]: RDN/NVR space control. 0: NVR space; 1: RDN space
Control bit [0]: clock enable bit; the clock of flash operate module will be closed when this bit=0. When the operation is finished, you should clear the clk_en bits in NVR_CTL.
Note1: only one operation can run at the same time.

For example:  read data from NVR address 0x20, the following steps are recommended.
1.	Write 0XA5 to SFR address 0XB6;
2.	Write 0XC3 to SFR address 0XB7;
3.	write 0X01 to SFR address 0xED //open clock
4.	write 0Xa5 to SFR address 0xE6 //key
5.	write 0X49 to SFR address 0xE6;
6.	write the address into 0XEE
7.	write 0X41 to SFR address 0xED; //start (NVR space)
8.	wait until bit6 changed to zero
9.	read out the data from oxEF
10.	Write 0x00 into 0XED to close the clock
11.	Write 0X00 to SFR address 0XB6;
12.	Write 0X00 to SFR address 0XB7;
*/  
    if_mtp_unlock
    {
        FLASH_CTL = 0x01;   //clock enable
#ifdef USE_RDN_SPACE    
        FLASH_CTL |= 0x02;  //rdn space
#endif
        NVR_WP0 = 0xa5;     //open the path
    	NVR_WP1 = 0xc3;     //open the path

        FLASH_KEY = 0xa5;
        FLASH_KEY = 0x49;
        FLASH_ADR = flash_addr;

        FLASH_CTL |= 0x40;
        while(FLASH_CTL & 0x40);
        value = FLASH_DAT;

        NVR_WP0 = 0x00;     //close the path
    	NVR_WP1 = 0x00;     //close the path
        FLASH_CTL = 0x00;
    }
    return value;
}

/*! \fn void FlashWriteByte(UINT8 flash_addr, UINT8 flash_data)
    \brief Write one byte at the \a flash_addr address in flash with erase firstly.

    \param flash_addr - the address need written
    \param flash_data - the flash_data need written
    \return void
*/
void FlashWriteByte(UINT8 flash_addr, UINT8 flash_data)
{
    if_mtp_unlock
    {
        FLASH_CTL = 0x01;   //clock enable
#ifdef USE_RDN_SPACE    
        FLASH_CTL |= 0x02;  //rdn space
#endif    
        NVR_WP0 = 0xa5;     //open the path
    	NVR_WP1 = 0xc3;     //open the path
        
        FLASH_KEY = 0xa5;
        FLASH_KEY = 0x49;
        FLASH_ADR = flash_addr;
        FLASH_DAT = flash_data;
        FLASH_CTL |= 0x80; // enable erase
        while(FLASH_CTL & 0x80);

        NVR_WP0 = 0x00;     //close the path
    	NVR_WP1 = 0x00;     //close the path
        FLASH_CTL = 0x00;
    }
}
/*! \fn FlashWriteBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len)
    \brief Write \a len bytes flash_data stored in \a buf  to the \a flash_addr address in flash with erase firstly.

    \param flash_addr - the address need written
    \param buf - the flash_data pointer stored the written flash_data
    \param len - the length need written
    \return void
*/
void FlashWriteBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len)
{
    UINT8 count, data1;
    mtp_unlock_set();
    while(len--)
    {
        for(count = 0; count < 3; count++)				// Retry 3 times.
        {
            FlashWriteByte(flash_addr, *flash_data);
            data1 = FlashReadByte(flash_addr);
            if(data1 == *flash_data)
                break;
        }
        flash_data++;
        flash_addr++;
    }
    mtp_unlock_clr();
}

/*! \fn void FlashReadBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len)
    \brief Read \a len bytes flash_data into \a buf from the \a flash_addr address in flash.

    \param flash_addr - the address need read
    \param buf - the flash_data pointer stored the reading flash_data
    \param len - the length need read
    \return void
*/
void FlashReadBuffer(UINT8 flash_addr, UINT8 *flash_data, UINT8 len)
{
    UINT8 count, data1, data2;
    mtp_unlock_set();
    while(len--)
    {
        for(count = 0; count < 3; count++)			// Retry 3 times.
        {
            data1 = FlashReadByte(flash_addr);
            data2 = FlashReadByte(flash_addr);
            if(data1 == data2)
                break;
        }
        *flash_data++ = data1;
        flash_addr++;
            
    }
    mtp_unlock_clr();

}
/*! \fn void FlashEraseAll(void)
    \brief Erase the whole nvr flash(256B), which will take 5ms

    \param void
    \return void
*/
void FlashEraseAll(void)
{
    if_mtp_unlock
    {
        FLASH_CTL = 0x01;   //clock enable
#ifdef USE_RDN_SPACE    
        FLASH_CTL |= 0x02;  //rdn space
#endif
        NVR_WP0 = 0xa5;     //open the path
    	NVR_WP1 = 0xc3;     //open the path

        FLASH_KEY = 0xa5;
        FLASH_KEY = 0x49;
        FLASH_CTL |= 0x20; // enable erase
        while(FLASH_CTL & 0x20);

        NVR_WP0 = 0x00;     //close the path
    	NVR_WP1 = 0x00;     //close the path
        FLASH_CTL = 0x00;
    }
}
#endif
/***********************************************************
						end file
***********************************************************/