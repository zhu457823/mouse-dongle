/*--------------------------------------------------------------------------
BK9001mcu_reg.h
Copyright (c) 2008-2010 Beken Corporation
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __BK9001MCU_REG_H__
#define __BK9001MCU_REG_H__

#include "absacc.h"
#define  PCHAR 		(unsigned char volatile xdata * )

sfr  P0               = 0x80;
sfr  SP               = 0x81;
sfr  DPL              = 0x82;
sfr  DPH              = 0x83;
sfr  CKCON            = 0x84;
sfr  CLK_EN_CFG       = 0x85;
sfr  PCON2            = 0x86;
sfr  PCON             = 0x87;
sfr  TCON             = 0x88;
sfr  TMOD             = 0x89;
sfr  TL0              = 0x8A;
sfr  TL1              = 0x8B;
sfr  TH0              = 0x8C;
sfr  TH1              = 0x8D;
sfr  CCMCON           = 0x8E;
sfr  CCMVAL           = 0x8F;
sfr  P1               = 0x90;
sfr  P0IN_EN          = 0x91;
sfr  DPSEL            = 0x92;
sfr  P1IN_EN          = 0x93;
sfr  P2IN_EN          = 0x94;
sfr  P3IN_EN          = 0x95;
sfr  P4IN_EN          = 0x96;
sfr  MMS              = 0x97;
sfr  SCON0            = 0x98;
sfr  SBUF0            = 0x99;
sfr  P0OUT_EN         = 0x9A;
sfr  PAGE_A           = 0x9B;
sfr  PAGE_B           = 0x9C;
sfr  PAGE_C           = 0x9D;
sfr  P1OUT_EN         = 0x9E;
sfr  P2OUT_EN         = 0x9F;
sfr  P2               = 0xA0;
sfr  MPAGE            = 0xA1;
sfr  PWM0_C            = 0xA2;
sfr  PWM0_DCLSB         = 0XA3;
sfr  PWM0_DCMSB         = 0XA4;
sfr  P3OUT_EN         = 0XA5;
sfr  WDT              = 0XA6;
sfr  P4OUT_EN         = 0xA7;
sfr  IE               = 0xA8;
sfr  P0_PU            = 0xA9;
sfr  P1_PU            = 0xAA;
sfr  P2_PU            = 0xAB;
sfr  P3_PU            = 0xAC;
sfr  P4_PU            = 0xAD;
sfr  P0_PD            = 0xAE;
sfr  P1_PD            = 0xAF;
sfr  P3               = 0xB0;
sfr  SPCR             = 0xB1;
sfr  SPDR             = 0xB2;
sfr  SPSR             = 0xB3;
sfr  P2_PD            = 0xB4;
sfr  P3_PD            = 0xB5;
sfr  P4_PD            = 0xB6;
sfr  P4               = 0xB7;
sfr  IP               = 0xB8;

sfr  ASADDR           = 0xBA;
sfr  ASADEN           = 0xBB;
sfr  ASCON            = 0xBC;
sfr  ASBUF            = 0xBD;


sfr  AIF              = 0xC0;
sfr  MD0              = 0xC1;
sfr  MD1              = 0xC2;
sfr  MD2              = 0xC3;
sfr  MD3              = 0xC4;
sfr  MD4              = 0xC5;
sfr  MD5              = 0xC6;
sfr  MDCTL            = 0xC7;
sfr  T2CON            = 0xC8;
sfr  NMI_EN           = 0xC9;
sfr  RCAP2L           = 0xCA;
sfr  RCAP2H           = 0xCB;
sfr  TL2              = 0xCC;
sfr  TH2              = 0xCD;
sfr  PWM0_RESOL        = 0xCE;
sfr  PWM1_RESOL       = 0xCF;
sfr  PSW              = 0xD0;
//sfr                 = 0xD1;
sfr  I2CM_DATA_IE     = 0xD2;
//sfr  N/A            = 0xD3;
sfr  I2CM_CALLADDR0   = 0xD4;
sfr  I2CS_DATA_IE     = 0xD5;
sfr  I2CS_TXRX_IE     = 0xD6;
sfr  I2CS_SELFADDR0   = 0xD7;
sfr  P0_OPDR          = 0xD8;
sfr  P1_OPDR          = 0xD9;
sfr  P2_OPDR          = 0xDA;
sfr  P3_OPDR          = 0xDB;
sfr  P4_OPDR          = 0xDC;
sfr  PWM1_C           = 0xDD;
sfr  PWM1_DCLSB        = 0xDE;
sfr  PWM1_DCMSB        = 0xDF;
sfr  ACC              = 0xE0;
sfr  I2CM_CTRL        = 0xE1;
sfr  I2CM_RXDATA      = 0xE2;
sfr  I2CM_TXDATA      = 0xE3;
sfr  I2CM_PRESC       = 0xE4;
sfr  I2CM_TXRX_STS    = 0XE5;
sfr  I2CM_DATA_STS    = 0XE6;
sfr  I2CM_TXRX_IE     = 0xE7;
sfr  AIE              = 0xE8;
sfr  PALT0            = 0xE9;		// timer clock select
sfr  EXSLEEP          = 0xEA;
sfr  P0_WUEN          = 0xEB;
sfr  P1_WUEN          = 0xEC;
sfr  P2_WUEN          = 0xED;
sfr  P3_WUEN          = 0xEE;
sfr  P4_WUEN          = 0xEF;
sfr  B                = 0xF0;
sfr  I2CS_CTRL        = 0xF1;
sfr  I2CS_RXDATA      = 0xF2;
sfr  I2CS_TXDATA      = 0xF3;
sfr  I2CS_PRESC       = 0xF4;
sfr  I2CS_TXRX_STS    = 0xF5;
sfr  I2CS_DATA_STS    = 0xF6;
/*Bit0~Bit6: IIC_IO,SPI_IO,UART0_IO,UART1_IO,PWM_IO,PCA_IO*/
sfr  PALT1            = 0xF7;		// second function select
sfr  AIP              = 0xF8;
sfr  P0_WUMOD         = 0xF9;
sfr  P1_WUMOD         = 0xFA;
sfr  P2_WUMOD         = 0xFB;
sfr  P3_WUMOD         = 0xFC;
sfr  P4_WUMOD         = 0xFD;



// EEPROM
#define  EEPROM_KEY     XBYTE[0x0910]
#define  EEPROM_STAT    XBYTE[0x0911]
#define  EEPROM_ADDR    XBYTE[0x0912]
#define  EEPROM_DAT     XBYTE[0x0913]
#define  EEPROM_CLK_EN  XBYTE[0x0914]

// RTC TIMER
#define  RTC_TIMER_CTRL XBYTE[0x0918]

/*  BIT Registers  */
/*  PSW */
sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit FL    = PSW^1;
sbit P     = PSW^0;

/*  TCON  */
sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

/*  IE  */
sbit EA    = IE^7;
sbit ES1   = IE^6;
sbit ET2   = IE^5;
sbit ES0   = IE^4;
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;

/*  P1  */
sbit INT5  = P1^7;
sbit INT4  = P1^6;
sbit INT3  = P1^5;
sbit INT2  = P1^4;
sbit TXD1  = P1^3;
sbit RXD1  = P1^2;
sbit T2EX  = P1^1;
sbit T2    = P1^0;

/*  P3  */
sbit RD    = P3^7;
sbit WR    = P3^6;
sbit T1    = P3^5;
sbit T0    = P3^4;
sbit INT1  = P3^3;
sbit INT0  = P3^2;
sbit TXD0  = P3^1;
sbit RXD0  = P3^0;

/*  SCON0  */
sbit SM0   = SCON0^7; /* alternative SM0_FE_0 */
sbit SM1   = SCON0^6; /* alternative SM1_0 */
sbit SM2   = SCON0^5; /* alternative SM2_0 */
sbit REN   = SCON0^4; /* alternative REN_0 */
sbit TB8   = SCON0^3; /* alternative TB8_0 */
sbit RB8   = SCON0^2; /* alternative RB8_0 */
sbit TI    = SCON0^1; /* alternative TI_0  */
sbit RI    = SCON0^0; /* alternative RI_0  */

/*  T2CON  */
sbit TF2    = T2CON^7;
sbit EXF2   = T2CON^6;
sbit RCLK   = T2CON^5;
sbit TCLK   = T2CON^4;
sbit EXEN2  = T2CON^3;
sbit TR2    = T2CON^2;
sbit C_T2   = T2CON^1;
sbit CP_RL2 = T2CON^0;

/*  EIE  */
sbit EX9   = AIE^7;
sbit EX8   = AIE^6;	// ADC interrupt enable
sbit EX7   = AIE^5;
sbit EX6   = AIE^4;
sbit EX5   = AIE^3;
sbit EX4   = AIE^2;
sbit EX3   = AIE^1;
sbit EX2   = AIE^0;

// AIF: additional interrupt flag 
sbit INT_AES = AIF^7;
sbit INT_ADC = AIF^6;
sbit INT_PCA = AIF^5;
sbit INT_EXT = AIF^4;
sbit INT_XVR = AIF^3;
sbit INT_USB = AIF^2;
sbit INT_LBD = AIF^1;
sbit INT_SPI = AIF^0;


/*****************************************************/
//USB
#define FRAM_NO_0     XBYTE[0x0808]
#define FRAM_NO_1     XBYTE[0x0809]

#define USBINT0       XBYTE[0x080a]
#define USBINT1       XBYTE[0x080b]
#define USB_EN0       XBYTE[0x080c]
#define USB_EN1       XBYTE[0x080d]
#define EP_STATUS_IN  XBYTE[0x080e]
#define EP_STATUS_OUT XBYTE[0x080f]


#define CFG_EP0_1     XBYTE[0x0810]
#define CFG_EP0_0     XBYTE[0x0811]

#define CFG_EP1_1     XBYTE[0x0812]
#define CFG_EP1_0     XBYTE[0x0813]

#define CFG_EP2_1     XBYTE[0x0814]
#define CFG_EP2_0     XBYTE[0x0815]

#define CFG_EP3_1     XBYTE[0x0816]
#define CFG_EP3_0     XBYTE[0x0817]

#define CFG_EP4_1     XBYTE[0x0818]
#define CFG_EP4_0     XBYTE[0x0819]

#define CFG_EP5_1     XBYTE[0x081a]
#define CFG_EP5_0     XBYTE[0x081b]

#define CFG_EP6_1     XBYTE[0x081c]
#define CFG_EP6_0     XBYTE[0x081d]

#define CFG_EP7_1     XBYTE[0x081e]
#define CFG_EP7_0     XBYTE[0x081f]

#define EP_HALT       XBYTE[0x0820]
#define EP_RDY        XBYTE[0x0821]
#define FUNCT_ADR     XBYTE[0x0822]


#define  CNT0         XBYTE[0x0823]
#define  CNT1         XBYTE[0x0824]
#define  CNT2         XBYTE[0x0825]
#define  CNT3         XBYTE[0x0826]
#define  CNT4         XBYTE[0x0827]
#define  CNT5         XBYTE[0x0828]
#define  CNT6         XBYTE[0x0829]
#define  CNT7         XBYTE[0x082a]
#define  CNT0_HBIT    XBYTE[0x082b]
#define  CNT1_HBIT    XBYTE[0x082c]
#define  CNT2_HBIT    XBYTE[0x082d]
#define  CNT3_HBIT    XBYTE[0x082e]
#define  CNT4_HBIT    XBYTE[0x082f]
#define  CNT5_HBIT    XBYTE[0x0830]
#define  CNT6_HBIT    XBYTE[0x0831]
#define  CNT7_HBIT    XBYTE[0x0832]
#define  EP_ADDR_MSB  XBYTE[0x0840]

#define  USB_PWR_CN   XBYTE[0x0841]
#define  USB_DEBUG    XBYTE[0x0842]
#define  USB_SOFT_RST XBYTE[0x0843]

// temp
#define  EP0_ADDR_DEF  XBYTE[0x0400]
#define  EP0_ADDR_DEF_1     XBYTE[0x0401]	//  ..
#define  EP0_ADDR_DEF_2     XBYTE[0x0402]
#define  EP0_ADDR_DEF_3     XBYTE[0x0403]
#define  EP0_ADDR_DEF_4     XBYTE[0x0404]
#define  EP0_ADDR_DEF_5     XBYTE[0x0405]
#define  EP0_ADDR_DEF_6     XBYTE[0x0406]
#define  EP0_ADDR_DEF_7     XBYTE[0x0407]

#define  EP1_ADDR_DEF  XBYTE[0x0440]
#define  EP2_ADDR_DEF  XBYTE[0x0480]
#define  EP3_ADDR_DEF       XBYTE[0x04c0]	//  ..
#define  EP4_ADDR_DEF       XBYTE[0x0500]	//  ..

#define  EP_PP_DEF     XBYTE[0x0370]

// BK2401
#define  BK2401_CONFIG     XBYTE[0x0880]
#define  BK2401_ENAA       XBYTE[0x0881]
#define  BK2401_ENRX       XBYTE[0x0882]
#define  BK2401_AW         XBYTE[0x0883]
#define  BK2401_RETR       XBYTE[0x0884]
#define  BK2401_RFCH       XBYTE[0x0885]
#define  BK2401_SETUP      XBYTE[0x0886]


#define  BK2401_R0_ADDR    (PCHAR(0x0887))
#define  BK2401_R1_ADDR    (PCHAR(0x088C))
#define  BK2401_R2_ADDR    XBYTE[0x0891]
#define  BK2401_R3_ADDR    XBYTE[0x0892]
#define  BK2401_R4_ADDR    XBYTE[0x0893]
#define  BK2401_R5_ADDR    XBYTE[0x0894] 

#define  BK2401_TX_ADDR    (PCHAR(0x0895))
/*
#define  BK2401_R0_ADDR_0  XBYTE[0x0887]
#define  BK2401_R0_ADDR_1  XBYTE[0x0888]
#define  BK2401_R0_ADDR_2  XBYTE[0x0889]
#define  BK2401_R0_ADDR_3  XBYTE[0x088A]
#define  BK2401_R0_ADDR_4  XBYTE[0x088B]
#define  BK2401_R1_ADDR_0  XBYTE[0x088C]
#define  BK2401_R1_ADDR_1  XBYTE[0x088D]
#define  BK2401_R1_ADDR_2  XBYTE[0x088E]
#define  BK2401_R1_ADDR_3  XBYTE[0x088F]
#define  BK2401_R1_ADDR_4  XBYTE[0x0890]
#define  BK2401_TX_ADDR_0  XBYTE[0x0895]
#define  BK2401_TX_ADDR_1  XBYTE[0x0896]
#define  BK2401_TX_ADDR_2  XBYTE[0x0897]
#define  BK2401_TX_ADDR_3  XBYTE[0x0898]
#define  BK2401_TX_ADDR_4  XBYTE[0x0899]
*/
#define  BK2401_R0_PW      XBYTE[0x089A]
#define  BK2401_R1_PW      XBYTE[0x089B]
#define  BK2401_R2_PW      XBYTE[0x089C]
#define  BK2401_R3_PW      XBYTE[0x089D]
#define  BK2401_R4_PW      XBYTE[0x089E]
#define  BK2401_R5_PW      XBYTE[0x089F]
#define  BK2401_DYNPD      XBYTE[0x08A0]
#define  BK2401_FEATURE    XBYTE[0x08A1]

#define  BK2401_CFG_0C_0    XBYTE[0x08A2]
#define  BK2401_CFG_0D_3    XBYTE[0x08A9]
/*
#define  BK2401_CFG_0C_1    XBYTE[0x08A3]
#define  BK2401_CFG_0C_2    XBYTE[0x08A4]
#define  BK2401_CFG_0C_3    XBYTE[0x08A5]
#define  BK2401_CFG_0D_0    XBYTE[0x08A6]
#define  BK2401_CFG_0D_1    XBYTE[0x08A7]
#define  BK2401_CFG_0D_2    XBYTE[0x08A8]
#define  BK2401_CFG_0D_3    XBYTE[0x08A9]
#define  BK2401_RAMP_TAB_0    XBYTE[0x08AA]
#define  BK2401_RAMP_TAB_1    XBYTE[0x08AB]
#define  BK2401_RAMP_TAB_2    XBYTE[0x08AC]
#define  BK2401_RAMP_TAB_3    XBYTE[0x08AD]
#define  BK2401_RAMP_TAB_4    XBYTE[0x08AE]
#define  BK2401_RAMP_TAB_5    XBYTE[0x08AF]
#define  BK2401_RAMP_TAB_6    XBYTE[0x08B0]
#define  BK2401_RAMP_TAB_7    XBYTE[0x08B1]
#define  BK2401_RAMP_TAB_8    XBYTE[0x08B2]
#define  BK2401_RAMP_TAB_9    XBYTE[0x08B3]
#define  BK2401_RAMP_TAB_A    XBYTE[0x08B4]
*/
#define  BK2401_CFG_0C_ARRAY    (PCHAR(0X08A2))
#define  BK2401_CFG_0D_ARRAY    (PCHAR(0X08A6))
#define  BK2401_RAMP_TAB_ARRAY  (PCHAR(0X08AA))

#define  BK2401_CE         XBYTE[0x08B5]
#define  BK2401_CMD        XBYTE[0x08B6]
#define  BK2401_FIFO       XBYTE[0x08B7]
#define  BK2401_SDATA      (PCHAR(0x08B8))
#define  BK2401_SDATA_0    XBYTE[0x08B8]
#define  BK2401_SDATA_1    XBYTE[0x08B9]
#define  BK2401_SDATA_2    XBYTE[0x08BA]
#define  BK2401_SDATA_3    XBYTE[0x08BB]
/*
#define  BK2401_sdata_1    XBYTE[0x08B9]
#define  BK2401_sdata_2    XBYTE[0x08BA]
#define  BK2401_sdata_3    XBYTE[0x08BB]
*/
#define  BK2401_SCTRL      XBYTE[0x08BC]
#define  BK2401_KCALOUT_H  XBYTE[0x08BE]
#define  BK2401_KCALOUT_L  XBYTE[0x08BF]
#define  BK2401_STATUS     XBYTE[0x08C0]
#define  BK2401_OBSERVETX  XBYTE[0x08C1]
#define  BK2401_CDSTATUS   XBYTE[0x08C2]
#define  BK2401_FIFOSTATUS XBYTE[0x08C3]
#define  BK2401_RPL_WIDTH  XBYTE[0x08C4]
#define  BK2401_MBIST_ST   XBYTE[0x08C5]
#define  BK2401_BIT_CNT    (PCHAR(0x08C8))
/*
#define  BK2401_bit_cnt_1  XBYTE[0x08C9]
#define  BK2401_bit_cnt_2  XBYTE[0x08CA]
#define  BK2401_bit_cnt_3  XBYTE[0x08CB]
*/
#define  BK2401_ERR_CNT    (PCHAR(0x08CC))
/*
#define  BK2401_err_cnt_1  XBYTE[0x08CD]
#define  BK2401_err_cnt_2  XBYTE[0x08CE]
#define  BK2401_err_cnt_3  XBYTE[0x08CF]
*/
#define  TX_FREQ_OFFSET    (PCHAR(0x08D0))
/*
#define  TX_FREQ_OFFSET_1  XBYTE[0x08D1]
#define  TX_FREQ_OFFSET_2  XBYTE[0x08D2]
#define  TX_FREQ_OFFSET_3  XBYTE[0x08D3]
*/
#define  RX_FREQ_OFFSET    (PCHAR(0x08D4))
/*
#define  TX_FREQ_OFFSET_1  XBYTE[0x08D5]
#define  TX_FREQ_OFFSET_2  XBYTE[0x08D6]
#define  TX_FREQ_OFFSET_3  XBYTE[0x08D7]
*/
#define  MOD_DELAY         XBYTE[0x08D8]
#define  PLL_SDM           XBYTE[0x08D9]
#define  FM_GAIN_H         XBYTE[0x08DA]
#define  FM_GAIN_L         XBYTE[0x08DB]
#define  FM_KMOD_SET_H     XBYTE[0x08DC]
#define  FM_KMOD_SET_L     XBYTE[0x08DD]
#define  MOD_COEFFICIENT_H XBYTE[0x08DE]
#define  MOD_COEFFICIENT_L XBYTE[0x08DF]
#define  ANA_CTRL10         XBYTE[0x08E0]
#define  ANA_CTRL11         XBYTE[0x08E1]		//
#define  ANA_CTRL12         XBYTE[0x08E2]
#define  ANA_CTRL13         XBYTE[0x08E3]

#define  ANA_IND           XBYTE[0x08F9]
#define  CHIP_ID_H         XBYTE[0x08FA]
#define  CHIP_ID_L         XBYTE[0x08FB]
#define  DEVICE_ID         (PCHAR(0x08FC))
/*
#define  device_id_l       XBYTE[0x08FD]
#define  device_id_2       XBYTE[0x08FE]
#define  device_id_3       XBYTE[0x08FF]
*/



//FLASH¡¡control
#define  FLASH_KEY           XBYTE[0x0900]
#define  FLASH_CTL           XBYTE[0x0901]
#define  FLASH_ADR           XBYTE[0x0902]
#define  FLASH_ADR_H         XBYTE[0x0903]
#define  FLASH_DAT           XBYTE[0x0904]
#define  NVR_WP0           XBYTE[0x0905]
#define  NVR_WP1           XBYTE[0x0906]
#define  NVR_WF0           XBYTE[0x0907] 
#define  NVR_WF1           XBYTE[0x0908]
#define  NVR_WF_MAIN       XBYTE[0x0909]  

//RTC TIMER
#define  RTC_TIMER_CTL     XBYTE[0x0918]
#define  RTC_COUNT_H        XBYTE[0x0919]
#define  RTC_COUNT_L        XBYTE[0x091a]

//ADC
#define  ADC_DATA_L         XBYTE[0x0920]
#define  ADC_DATA_H         XBYTE[0x0921]
#define  ADC_CTL           XBYTE[0x0922]
#define  ADC_RATE          XBYTE[0x0923]
#define  ADC_CTL2          XBYTE[0x0924]

//KEY WAKE
#define  KEY_EN            XBYTE[0x0928]
#define  KEY_STATUS        XBYTE[0x0929]

//RNG
#define  RNG_DATA          XBYTE[0x0930]
#define  RNG_CTRL          XBYTE[0x0931]

//PCA
#define  CCAP0H            XBYTE[0x0960]
#define  CCAP1H            XBYTE[0x0961]
#define  CCAP2H            XBYTE[0x0962]
#define  CCAP3H            XBYTE[0x0963]
#define  CCAP4H            XBYTE[0x0964]
#define  CCAP5H            XBYTE[0x0965]
#define  CCAP0L            XBYTE[0x0966]
#define  CCAP1L            XBYTE[0x0967]
#define  CCAP2L            XBYTE[0x0968]
#define  CCAP3L            XBYTE[0x0969]
#define  CCAP4L            XBYTE[0x096a]
#define  CCAP5L            XBYTE[0x096b]
#define  CCAMP0            XBYTE[0x096c]
#define  CCAMP1            XBYTE[0x096d]
#define  CCAMP2            XBYTE[0x096e]
#define  CCAMP3            XBYTE[0x096f]
#define  CCAMP4            XBYTE[0x0970]
#define  CCAMP5            XBYTE[0x0971]
#define  CCON              XBYTE[0x0972]
#define  CH                XBYTE[0x0973]
#define  CL                XBYTE[0x0974]
#define  CMOD              XBYTE[0x0975]
#define  CCAPO             XBYTE[0x0976]



//AES
#define  AES_KEY00         XBYTE[0x0980]
#define  AES_KEY01         XBYTE[0x0981]
#define  AES_KEY02         XBYTE[0x0982]
#define  AES_KEY03         XBYTE[0x0983]
#define  AES_KEY04         XBYTE[0x0984]
#define  AES_KEY05         XBYTE[0x0985]
#define  AES_KEY06         XBYTE[0x0986]
#define  AES_KEY07         XBYTE[0x0987]
#define  AES_KEY08         XBYTE[0x0988]
#define  AES_KEY09         XBYTE[0x0989]
#define  AES_KEY0A         XBYTE[0x098A]
#define  AES_KEY0B         XBYTE[0x098B]
#define  AES_KEY0C         XBYTE[0x098C]
#define  AES_KEY0D         XBYTE[0x098D]
#define  AES_KEY0E         XBYTE[0x098E]
#define  AES_KEY0F         XBYTE[0x098F]
#define  AES_TEXTIN00      XBYTE[0x0990]
#define  AES_TEXTIN01      XBYTE[0x0991]
#define  AES_TEXTIN02      XBYTE[0x0992]
#define  AES_TEXTIN03      XBYTE[0x0993]
#define  AES_TEXTIN04      XBYTE[0x0994]
#define  AES_TEXTIN05      XBYTE[0x0995]
#define  AES_TEXTIN06      XBYTE[0x0996]
#define  AES_TEXTIN07      XBYTE[0x0997]
#define  AES_TEXTIN08      XBYTE[0x0998]
#define  AES_TEXTIN09      XBYTE[0x0999]
#define  AES_TEXTIN0A      XBYTE[0x099A]
#define  AES_TEXTIN0B      XBYTE[0x099B]
#define  AES_TEXTIN0C      XBYTE[0x099C]
#define  AES_TEXTIN0D      XBYTE[0x099D]
#define  AES_TEXTIN0E      XBYTE[0x099E]
#define  AES_TEXTIN0F      XBYTE[0x099F]
#define  AES_TEXTOUT00     XBYTE[0x09A0]
#define  AES_TEXTOUT01     XBYTE[0x09A1]
#define  AES_TEXTOUT02     XBYTE[0x09A2]
#define  AES_TEXTOUT03     XBYTE[0x09A3]
#define  AES_TEXTOUT04     XBYTE[0x09A4]
#define  AES_TEXTOUT05     XBYTE[0x09A5]
#define  AES_TEXTOUT06     XBYTE[0x09A6]
#define  AES_TEXTOUT07     XBYTE[0x09A7]
#define  AES_TEXTOUT08     XBYTE[0x09A8]
#define  AES_TEXTOUT09     XBYTE[0x09A9]
#define  AES_TEXTOUT0A     XBYTE[0x09AA]
#define  AES_TEXTOUT0B     XBYTE[0x09AB]
#define  AES_TEXTOUT0C     XBYTE[0x09AC]
#define  AES_TEXTOUT0D     XBYTE[0x09AD]
#define  AES_TEXTOUT0E     XBYTE[0x09AE]
#define  AES_TEXTOUT0F     XBYTE[0x09AF]
#define  AES_CTL           XBYTE[0x09B0]
#define  AES_INT           XBYTE[0x09B1]

#define  AES_KEY_ARRAY        (PCHAR(0x0980))
#define  AES_TEXTIN_ARRAY     (PCHAR(0x0990))
#define  AES_TEXTOUT_ARRAY    (PCHAR(0x09A0))



#endif
/***********************************************************
						end file
***********************************************************/