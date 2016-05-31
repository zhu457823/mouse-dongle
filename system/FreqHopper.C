#include "Headfile\includes.h"

BYTE XDATA uRFIdleTime;
BYTE uRFCH;
BYTE XDATA uSignalQuality;
BYTE uCDDTDuty;
BYTE uCDCNT;
bit bRXEndPacket;
bit bRFRXData;
//bit bFreqHopper;
bit bCurFreqActive;			// 1: current frequency before received data. 0: always no received data.
/*-------------------------------------------------------
--------------------------------------------------------*/
void InitCarryDetect(void)
{
	uCDDTDuty = 0;
	uCDCNT = 0;
}
/*-------------------------------------------------------
--------------------------------------------------------*/
void InitFreqHopper(void)
{
	bRXEndPacket = 1;
	bRFRXData = 0;
//	bFreqHopper = 0;
	bCurFreqActive = 0;
	uRFIdleTime = 0;
	uRFCH = 0;
	uSignalQuality = 0;
	InitCarryDetect();
}
/*-------------------------------------------------------
--------------------------------------------------------*/
void RFSync(void)
{
	bRFRXData = 0;
	bCurFreqActive = 0;

	uCDCNT = 0;
	uRFIdleTime = 0;
}
/*-------------------------------------------------------
--------------------------------------------------------*/
void RF_CDProcess( )
{
	UINT8 sta;
	
	if(++uCDDTDuty > cCDDTDuty)					// Note read BK2401_CDSTATUS duty must > 150us other wise carrier detect no effect.
	{
		uCDDTDuty = 0;							// CD_INT will be cleared while readed. 
		
		sta = BK2401_CDSTATUS;					// Carrier detet convert time about 150us.
		if(CD_INT & sta)							// 1: Carrier detect.
		{
			uCDCNT++;
			if(uCDCNT == 0)
				uCDCNT = 0xff;					// uCDCNT  overflow.
		}
		else
			uCDCNT = 0;
		
//		sta = BK2401_STATUS;  
//		if(sta & STATUS_RX_DR)
		if(bRFRXData)
		{
			uCDCNT = 0;
		}

		if(u10msFlag & bRFTimer)
		{
			u10msFlag &= ~bRFTimer;
//			if((uCDCNT > cCDCNT)	 || bFreqHopper)				// Change frequency after 10ms.
			if(uCDCNT > cCDCNT)
			{
//				bFreqHopper = 0;
				RFSync();
			}
			
		}
		
	}
}
/*-------------------------------------------------------
--------------------------------------------------------*/
void FreqProcess(void)
{					
	if(bRXEndPacket)							// 已收到结束标志
	{										// loop duty about 10us.
		RF_CDProcess();						//使用RSSI检测干扰
	}
	else if(!bCurFreqActive)
	{
		RF_CDProcess();	
	}
	else
	{										
		InitCarryDetect();
		
		if(u10msFlag & bRFTimer)
		{
			u10msFlag &= ~bRFTimer;
			{
				if(bRFRXData)
				{
					bRFRXData = 0;
					uRFIdleTime = 0;
//					bCurFreqActive = 1;
				}
				else
				{
					if(bCurFreqActive)				// 
					{
						if(++uRFIdleTime > cRFTime)	// 之前收到过数据，8ms内没收到数据
						{
							RFSync();	 			// 20ms unreceived data, change rf channel
						}
					}
				}
			}
		}
	}
	
}

