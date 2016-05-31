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
<author> <time> 		<version >		 <desc>
		2011/03/01  		0.1  			build this moudle 
***********************************************************/

#include "Headfile\includes.h"

#define	cKEYDB		3	// 5ms*4=20ms

BYTE XDATA uKeyDB = 0;
BYTE XDATA uKeyBak = 0;
//sbit bBindKeyPress = 0;
//-------------------------------------------------------
//Function: 
//Desc	: 
//Input	:
//Output: key press return 1, release return 0
//Return: 
//Others: 
//Author:  
//Date	: 2011/03/01
//-------------------------------------------------------
BYTE get_bindkey(void)
{
	BYTE DATA sta=0;

	if( !P_BindKey )
	{
		sta=1;
	}
		
	return sta;
}
//-------------------------------------------------------
//-------------------------------------------------------
void KeyScan(void)
{
	BYTE DATA uKeyTmp;
	uKeyTmp = get_bindkey();
	if(uKeyTmp != uKeyBak)
	{
		uKeyBak = uKeyTmp;
		uKeyDB = 0;
	}
	else if(++uKeyDB > cKEYDB)
	{
		uKeyDB = 0;
		if(uKeyTmp)
		{
			if(!system.Key.bKey.bBindKeyState)
			{
				system.Key.bKey.bBindKeyState = 1;
				system.Key.bKey.bBindKeyValid = 1;
			}
		}
		else
			system.Key.bKey.bBindKeyState = 0;			// Release

	}
}
/***********************************************************
						end file
***********************************************************/