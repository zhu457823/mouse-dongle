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
<author> 		<time> 		<version > 		<desc>
				2011/03/01  		0.1  			build this moudle 
***********************************************************/

#ifndef _USB_INTERRUPT_SERVICE_ROUTINE_H_
#define _USB_INTERRUPT_SERVICE_ROUTINE_H_

void handle_Control ( );
void handle_Out(void);
void handle_In(void);
void handle_Reset (void);
void handle_Suspend (void);
void handle_Resume (void);
void handle_SOF (void);
void handle_Unsupported_Token (void);
void handle_CRC_Err (void);
void handle_Overtime (void);
void handle_Data_Pid_Err (void);
void force_Stall (void);
void fifo_Read (UINT8 fifo_Index, UINT8 NO, UINT8 *p );
void WriteEP1FIFO(UINT8 NO, UINT8 *p);
//void fifo_Read_main (UINT8 fifo_Index, UINT8 NO, UINT8 *p );
void fifo_Write (UINT8 fifo_Index, UINT8 NO, UINT8 *p );
void fifo_Write_main (UINT8 fifo_Index, UINT8 NO, UINT8 *p );
//void fifo_Write_IN_ini (UINT8 fifo_Index, UINT8 NO, UINT8 *p );
void set_Wait_Status (void);
void set_Wait_Address (void);
void set_ep_rdy (UINT8 ep_index) ;
void set_ep0_dir(UINT8 i) ;

#endif

/***********************************************************
						end file
***********************************************************/