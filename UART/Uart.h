/***********************************************************
Copyright (C),Tech Esense Co., Ltd.
FileName		: Uart.h
Author			: joe
Date			: 2010-11-03
Description		: 
Version			: 1.0bate
Function List	: 
--
History			: 
<author> <time>	<version> <desc>
************************************************************/

#ifndef _UART_H_
#define _UART_H_

#ifdef DEBUG
	void UartOpen(void);
	#define DEG(x) printf x
#else
    #define DEG(x)
#endif

#endif

/***********************************************************
						end Uart.h
************************************************************/