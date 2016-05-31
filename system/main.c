//author:zjl
//time:2016-05-31


/***********************************************************
Copyright (C), 1998-2011, Esense Technology Co., Ltd.
FileName	: main.c
Author		:  
Date		:
Description	: 程序入口文件
Version		: v0.1
Cilent		: ChangHong
ProjectName	: 
Function List	: 
Compiler tool	: uVision4.0a,  C compiler v9.00.
;;-------------------------------------------------------------------
2014/06/27
(1). 2433 mode, IR_RELEASE_KEY_ADDR1地址0x1D改成0x1E，解决对码后较长的时间才可以收发数据
      原因:E2PROM_ClearSel(addr, len)的addr为奇数时会循环五次擦除
***********************************************************/

#include "Headfile\includes.h"
//-------------------------------------------------------
//Function: main
//Desc	: 主函数,程序入口
//Input	:
//Output: 
//Return: 
//Others: 
//Author: 
//Date	: 2011/03/01
//-------------------------------------------------------
int main(void)
{
	system_inital();
	system_check_workmode();
	DEG(("inter system !\n"));
	while(1)
	{
		switch(system.work_mode)
		{
			case SYSTEM_WORK:
				DEG(("inter work mode !\n"));
				system_work_mode();
				break;
			case SYSTEM_BIND:
				DEG(("inter bind mode !\n"));
				system_bind_mode();
				break;
			case SYSTEM_TEST:
				DEG(("inter test mode !\n"));
				system_test_mode();
				break;
			case SYSTEM_CODE:			// Write code.
				system_pc_mode();
				break;
			case SYSTEM_DEBUG:
				system_debug_mode();
				break;

			default:
				system.work_mode=SYSTEM_WORK;
				break;
		}
	}

	return 0;
}


/***********************************************************
						end file
***********************************************************/
