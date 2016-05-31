
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
<author>		 <time> 		<version >		 <desc>
			2011/03/01  		0.1  			build this moudle 
***********************************************************/

#include "Headfile\includes.h"

BYTE uReportNO;
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
void usb_uploading(void)
{
	BYTE i;
	if(system.usbp2_data.ready_to_uploading)
	{
		if(system.usbp2_data.bKBDataUpload)
		{
			system.usbp2_data.in_report[0] = 0x01;			// Keyboard Report ID
			
			uReportNO = 8;
			if(system.usbp2_data.bRECDataUpload)
			{
				system.usbp2_data.bRECDataUpload = 0;
				system.szKeyData[1] = 0;
				for(i = 1; i < 8; i++)
				{
					system.usbp2_data.in_report[i] = 0;
				}
				system.usbp2_data.bKBDataUpload = 0;
			}
			else
			{
				for(i = 1; i < 8; i++)
				{
					system.usbp2_data.in_report[i] = system.szKeyData[i-1];
				}
				if((system.szKeyData[0] == 0) && (system.szKeyData[1] == kF11))
				{
					system.usbp2_data.bRECDataUpload = 1;
				}
				else
					system.usbp2_data.bKBDataUpload = 0;
			}
			system.usbp2_data.uploading = 1;
		}
		else if(system.usbp2_data.bMediaDataUpload)
		{
			system.usbp2_data.bMediaDataUpload = 0;

			if(system.uMultiKey[0] == 0)
			{
				if(system.usbp2_data.bSysPWRKey)
				{
					system.usbp2_data.bSysPWRKey = 0;
					system.usbp2_data.in_report[0] = 0x05;			// System power Report ID.
					uReportNO = 2;
					system.usbp2_data.in_report[1] = 0;
				}
				else	// if(system.usbp2_data.bMultiMediaKey)
				{
					system.usbp2_data.bMultiMediaKey = 0;
					system.usbp2_data.in_report[0] = 0x04;			// MultiMedia Report ID.
					uReportNO = 3;
					system.usbp2_data.in_report[1] = 0;
					system.usbp2_data.in_report[2] = 0;
				}
				system.usbp2_data.uploading = 1;
			}
			else if(system.uMultiKey[0] < ckPWR)
			{
				system.usbp2_data.bMultiMediaKey = 1;
				system.usbp2_data.in_report[0] = 0x04;				// MultiMedia Report ID.
				uReportNO = 3;
				system.usbp2_data.in_report[1] = MultiMediaKey[system.uMultiKey[0]][0];
				system.usbp2_data.in_report[2] = MultiMediaKey[system.uMultiKey[0]][1];
				system.usbp2_data.uploading = 1;
			}
			else if(system.uMultiKey[0] < (ckPWR+3))
			{
				system.usbp2_data.bSysPWRKey = 1;
				system.usbp2_data.in_report[0] = 0x05;			// System power Report ID.
				uReportNO = 2;
				system.usbp2_data.in_report[1] = SysPWRKey[system.uMultiKey[0]-ckPWR];
				system.usbp2_data.in_report[2] = 0;
				system.usbp2_data.uploading = 1;
			}
		}		
		if(system.usbp2_data.uploading)
		{
			system.usbp2_data.ready_to_uploading = 0;
			system.usbp2_data.uploading = 0;
			fifo_Write_main (EP_3, uReportNO, (UINT8 * )system.usbp2_data.in_report);
			memset(&system.usbp2_data.in_report[1], 0, 7);
			EP_RDY |= 0x08;
		}
	}
}


/***********************************************************
						end file
***********************************************************/