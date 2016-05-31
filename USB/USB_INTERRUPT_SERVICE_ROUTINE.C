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

//-----------------------------------------------------------------------------
// Support Routines
//-----------------------------------------------------------------------------

void handle_Control ( )
{
	unsigned int usb_cnt=0;
	if((EP_STATUS_OUT & 0x01)||(EP_STATUS_IN & 0x01))                                                                                          // 8 byte setup data received
	{     
		EP_STATUS_OUT = 0x01;                                                                                 // write 1 to clear
		EP_STATUS_IN = 0x01;

		EP_STATE[0] = EP_IDLE;    // force EP_STATE[0] to EP_IDLE
		system.usbp0_data.wait_out_report=0;

		if (CNT0 == 8)                // Make sure that EP 0 has an Out Packet of size 8 byte
		{                                
			// added on 2011.5.8 to fix usb set_report error.
			if (EP0_ADDR_DEF==0x21 && EP0_ADDR_DEF_1 == 0x09 )
			{
				USBINT0 = 0xc0;
				Set_Report();
				system.usbp0_data.report_id=EP0_ADDR_DEF_2;
				system.usbp0_data.report_type = EP0_ADDR_DEF_3;
		
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else if(EP0_ADDR_DEF==0x21 && EP0_ADDR_DEF_1 == 0x01 )
			{								// Fix SET_CUR request error
				SET_CUR();
			}
			else
			{
				fifo_Read (EP_0, 8, (UINT8 *) & setup);
				// Get setup Packet off of Fifo,
				// it is currently Big-Endian

				// Compiler Specific - these next three
				// statements swap the bytes of the
				// setup packet words to Big Endian so
				// they can be compared to other 16-bit
				// values elsewhere properly
//				USBINT0 = 0xc0;
//				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
				setup.wValue.i = setup.wValue.c[MSB] + ((int)setup.wValue.c[LSB] << 8);			// High byte and low byte exchange()
				setup.wIndex.i = setup.wIndex.c[MSB] + ( (int)setup.wIndex.c[LSB] << 8);
				setup.wLength.i = setup.wLength.c[MSB] + ( (int)setup.wLength.c[LSB] << 8);

				// Intercept HID class - specific requests
				// Class request.
//				if( (setup.bmRequestType & ~ 0x80) == DSC_HID) 
				if((setup.bmRequestType & cRequestType) == cClassReq)
				{
					#if	0
					switch (setup.bRequest) 
					{
						case GET_REPORT:
							Get_Report ( );
							break;
						case SET_REPORT:
							Set_Report();          
							break;
						case GET_IDLE:
							Get_Idle ( );
							break;
						case SET_IDLE:
							Set_Idle ( );
							break;
						case GET_PROTOCOL:
							Get_Protocol ( );
							break;
						case SET_PROTOCOL:
							Set_Protocol ( );
							break;
						default:
							force_Stall ( );      // Send stall to host if invalid
							break;                 // request
					}
					#endif
					switch(setup.bRequest)
					{
					// bmRequestType, bRequest, bChannelNum.(CN), bControlSelect(CS, include volume, mute etc.), bInterfaceNO, bTerminal/unit ID, wLength.
					// CTL: 21 01 00 02  00 05 02 00
					// DO:  00 00
						case cSET_CUR:
							if(setup.wIndex.c[1] >= 3)		// HID interface.
							{
								Get_Report();
							}
							else
								SET_CUR();
							break;

						case cSET_MIN:
							if(setup.wIndex.c[1] >= 3)		// HID interface.
							{
								Get_Idle();
							}
							else
								SET_MIN();
							break;

						case cSET_MAX:
							SET_MAX();
							break;

						case cSET_RES:
							SET_RES();
							break;

						case cSET_MEM:
							SET_MEM();
							break;

/*
						case GET_REPORT:
							Get_Report();
							break;
*/
						case SET_REPORT:
							Set_Report();          
							break;
/*								
						case GET_IDLE:
							Get_Idle ( );
							break;
*/	
						case SET_IDLE:
							Set_Idle ( );
							break;
								
						case cGET_CUR:
							GET_CUR();
							break;

						case cGET_MIN:
							GET_MIN();
							break;

						case cGET_MAX:
							GET_MAX();
							break;

						case cGET_RES:
							GET_RES();
							break;

						case cGET_MEM:
							GET_MEM();
							break;

						case cGET_STAT:
							GET_STAT();
							break;
							
						default:
							force_Stall ( );      // Send stall to host if invalid
							break;                 // request
					}
					
				} 
				else
				{
					// Standard request.
					switch (setup.bRequest)       // Call correct subroutine to handle
					{                             // each kind of standard request
						case GET_STATUS:
							Get_Status ( );
							break;
						case CLEAR_FEATURE:
							Clear_Feature ( );
							break;
						case SET_FEATURE:
							Set_Feature ( );
							break;
						case SET_ADDRESS:
							Set_Address ( );
							break;
						case GET_DESCRIPTOR:
							Get_Descriptor ( );
							break;
						case GET_CONFIGURATION:
							Get_Configuration ( );
							break;
						case SET_CONFIGURATION:
							Set_Configuration( );
							break;
						case GET_INTERFACE:
							Get_Interface ( );
							break;
						case SET_INTERFACE:		// 01 0b   00 00(wValue)   01 00(wIndex)   00 00
							Set_Interface ( );	// wValue:Interface alternate setting(0x0 is zero bandwith alternate setting, 0x01 is normal isochronous operate)
							break;				// wIndex: Interface number of one of the audiostreaming interface.
						default:
							force_Stall ( );                 // Send stall to host if invalid request
							break;
					}
				}
			}
		}      
		else 
		{
			force_Stall ( );                       // if rec setup data is not 8 byte , protacal stall
		}
	}   
	else if (EP_STATE[0] == EP_SET_ADDRESS)     // Handle Status Phase of Set Address
	{
		FUNCT_ADR = setup.wValue.c[LSB];         // set usb Address SFR
		EP_STATE[0] = EP_IDLE;


	}
	else if (EP_STATE[0] == EP_WAIT_STATUS)
	{
		EP_STATE[0] = EP_IDLE;

		wait_tx_status=0;
	}   
	else if (EP_STATE[0] == EP_RX)              // See if endpoint should transmit
	{  							// Out Token. PC->Device.
		if (DATASIZE >= EP0_PACKET_SIZE)
		{
			fifo_Read(EP_0, EP0_PACKET_SIZE, (unsigned char * )DATAPTR);
			// Advance data pointer
			DATAPTR  += EP0_PACKET_SIZE;
			// Decrement data size
			DATASIZE -= EP0_PACKET_SIZE;
			// Increment data sent counter
			DATASENT += EP0_PACKET_SIZE;            
		}
		else
		{
			// read bytes from FIFO
//			// Report type: 0x01 input, 0x02 output, 0x03 feature report.
			if( system.usbp0_data.wait_out_report && (system.usbp0_data.report_type==PC_SET_REPORT_2) && (system.usbp0_data.report_id==PC_SET_REPORT_1) )
			{
				system.usbp0_data.wait_out_report=0;
				DATAPTR = & EP0_ADDR_DEF;
			
				if(PC_SET_REPORT_1 == DATAPTR[0])
				{
					DATAPTR++;
					DATASIZE--;
				}

				for ( system.usbp0_data.report_cnt = 0;         // read  num = NO  fifo_data;   
					system.usbp0_data.report_cnt< DATASIZE;
					system.usbp0_data.report_cnt ++ )
				{
					system.usbp0_data.set_report_data[system.usbp0_data.report_cnt] = DATAPTR[system.usbp0_data.report_cnt];
				}
				system.usbp0_data.aceept = 1;  
				system.usbp0_data.reday_report_flag = 0;
				set_report_status_phace=1;
			}
			else
			{
				fifo_Read (EP_0, DATASIZE, (UINT8 * ) DATAPTR);
				// KEYBOARD_OUT_REPORT
				if (system.usbp0_data.wait_out_report)
				{
					numlock_sta = system.usbp0_data.out_report[0] & 0x01;
					system.usbp0_data.out_report_index = DATASIZE;
					system.usbp0_data.wait_out_report=0;
					set_report_status_phace=1;
				}

			}

			set_Wait_Status ( );                  // set Endpoint to EP_WAIT_STATUS
		}

		if ( (DATASENT == setup.wLength.i) && (set_report_status_phace==0) )
		{
			set_Wait_Status ( );
		}
		set_report_status_phace=0;
	}   
    
	if (EP_STATE[0] == EP_TX)                                        // See if endpoint should transmit
	{     									// In Token, device->PC

		if ((DATASIZE == 0))// || (DATASENT == setup.wLength.i))   // when all data has been sent over
		{

			set_Wait_Status ( );

		}
		else
		{   
			CFG_EP0_1 = 0xc0; 
			if (DATASIZE >= EP0_PACKET_SIZE)
			{
				// Break Data into multiple packets if larger than Max Packet
				fifo_Write (EP_0, EP0_PACKET_SIZE, (unsigned char*)DATAPTR);
				// Advance data pointer
				DATAPTR  += EP0_PACKET_SIZE;
				// Decrement data size
				DATASIZE -= EP0_PACKET_SIZE;
				// Increment data sent counter
				DATASENT += EP0_PACKET_SIZE;
			}

			else
			{

				// If data is less than Max Packet size or zero
				fifo_Write (EP_0, DATASIZE, (unsigned char*)DATAPTR);
				// Increment data sent counter
				DATASENT += DATASIZE;
				// Decrement data size
				DATASIZE = 0;
				USBINT0 = 0xc0;   
				EP_RDY = 0x01 ;

				// when usb_reset and send ok inttrupt (USBINT0&0x48)!=0 // when setup come (EP_STATUS & 0x01) will set
				 while(((USBINT0 & 0x4C) == 0) && ((EP_STATUS_OUT & 0x01) == 0));   //wait usb_reset, suspend or sending end interrupt  happend, wait setup come
				if((USBINT0&0x40) !=0) 
				{  
					CFG_EP0_1 =0x40;
					EP_RDY = 0x01 ;
					USBINT0 = 0xc0;
					EP_STATE[0]= EP_WAIT_STATUS;

				}
				wait_tx_status = 1; 
				system.usbp0_data.wait_out_report=0;
			} 
		}   
	}


	if (system.usbp0_data.wait_out_report==0 && wait_tx_status ==0)  
	{  
		USBINT0 = 0xc0;
		//   set_ep_rdy(EP_0);   // set ready to receive or send next packet
		EP_RDY = 0x01 ;  
	}
}




void handle_Out(void)  // Handle OUT endpoint, Packet received, read data from fifo
{ 
	 if(EP_STATUS_OUT & 0x80) // ep7
        EP_STATUS_OUT = 0x80;
    
	if(EP_STATUS_OUT & 0x40) // ep6
	    EP_STATUS_OUT = 0x40;

	if(EP_STATUS_OUT & 0x20) // ep5
	    EP_STATUS_OUT = 0x20;

	if(EP_STATUS_OUT & 0x10) // ep4  
	    EP_STATUS_OUT = 0x10; 

	if(EP_STATUS_OUT & 0x08) // ep3  
	    EP_STATUS_OUT = 0x08;    

	if(EP_STATUS_OUT & 0x04) // ep2  
	    EP_STATUS_OUT = 0x04; 

	if(EP_STATUS_OUT & 0x02) // ep1
	{
	    EP_STATUS_OUT = 0x02;
	}

	USBINT0 = 0x20;
}

void handle_In(void)
{

	if(EP_STATUS_IN & 0x80) // ep7
        EP_STATUS_IN = 0x80;
    
	if(EP_STATUS_IN & 0x40) // ep6
	    EP_STATUS_IN = 0x40;

	if(EP_STATUS_IN & 0x20) // ep5
	    EP_STATUS_IN = 0x20;

	if(EP_STATUS_IN & 0x10) // ep4  
	{
		EP_STATUS_IN = 0x10;
		CNT4 = 0;
		system.usbp4_data.ready_to_uploading = 1;
	}

	if(EP_STATUS_IN & 0x08) // ep3
	{
		EP_STATUS_IN = 0x08;
		CNT3 = 0;
		system.usbp2_data.ready_to_uploading = 1;
			// media
	}

	if(EP_STATUS_IN & 0x04) // ep2
	{ 
		EP_STATUS_IN = 0x04;
	}

	if(EP_STATUS_IN & 0x02) // ep1  
	{
//		CNT1 = 0;
//		CNT1_HBIT = 0;
		system.usbp1_data.ready_to_uploading = 1;
		EP_STATUS_IN = 0x02;
	} 

	USBINT0 = 0x10;
}

void handle_Reset (void)
{
	
	PCON2 |= 0x40;			// Enable 48MHZ.
	usb_suspend = 0;
	USB_PWR_CN &= ~0x02;   	// clr sus_mode  bit
	USB_PWR_CN |= 0x04;
    // debug_reset++;
	
	while(FUNCT_ADR != 0)
		FUNCT_ADR =  0;
	USB0_STATE = DEV_DEFAULT;
	EP_STATE[0] = EP_IDLE ;
	EP_STATE[1] = EP_STALL ;
	EP_STATE[2] = EP_STALL ;
	EP_STATE[3] = EP_STALL ;
	EP_STATE[4] = EP_STALL ;
	// P3 |= 0x02;
	wait_tx_status = 0;
	system.usbp0_data.wait_out_report = 0;
	USBINT0 = 0xc8;      // 这里有改动    0x08
}

void handle_Suspend (void)
{  
	USB_PWR_CN |= 0x02;  //usb suspend state
	
    	USBINT0 = 0x04;   
   	AIF &= ~ 0x04;         // clr mcu flag(External 4 interrupt flag(USB interrupt))  

//	PCON2 &= ~0x40;      	 //Disable USB
   	usb_suspend = 1;
}

void handle_Resume (void)
{
    PCON2 |= 0x40;			// Enable USB(48MHZ)

    usb_suspend = 0;
}


void handle_SOF (void)
{
#ifdef	CHIP_BK2535
//	system.usbp1_data.ready_to_uploading = 1;
	system.usbp1_data.bSOFTimer = 1;
#endif	
	USBINT0 = 0x01;		// Clear USB start of frame interrupt.
}


void handle_Unsupported_Token (void)
{
    USBINT1 = 0x80;
}


void handle_CRC_Err (void)
{
    USBINT1 = 0x40;
}


void handle_Overtime (void)
{
    USBINT1 = 0x20;
}


void handle_Data_Pid_Err (void)
{
    USBINT1 = 0x10;
}

//-----------------------------------------------------------------------------
// force_Stall
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Force a procedural stall to be sent to the host
//
//-----------------------------------------------------------------------------
void force_Stall (void)
{
     EP_STATE[0] = EP_STALL;                    // Put the endpoint in stall status
     EP_HALT |= 0x01;
//     DEG(("stal\n"));
}



void fifo_Read (UINT8 fifo_Index, UINT8 NO, UINT8 *p )
{
    unsigned char volatile xdata * fifo_p;
    UINT8 i;

    switch (fifo_Index)
    {
        case 0 :  fifo_p = & EP0_ADDR_DEF ;  break;
        case 1 :  fifo_p = & EP1_ADDR_DEF ;  break;
        case 2 :  fifo_p = & EP2_ADDR_DEF ;  break;
        case 3 :  fifo_p = & EP3_ADDR_DEF ;  break;
        case 4 :  fifo_p = & EP4_ADDR_DEF ;  break;
        default: ;
    }

    for ( i = 0; i < NO; i ++ )                 // read  num = NO  fifo_data;
    {
        p[i] = fifo_p[i];
    }
}

/*
void fifo_Read_main (UINT8 fifo_Index, UINT8 NO, UINT8 *p )
{
    unsigned char volatile xdata * fifo_p;
    UINT8 i;

    switch (fifo_Index)
    {
        case 0 :  fifo_p = & EP0_ADDR_DEF ;  break;
        case 1 :  fifo_p = & EP1_ADDR_DEF ;  break;
        case 2 :  fifo_p = & EP2_ADDR_DEF ;  break;
        case 3 :  fifo_p = & EP3_ADDR_DEF ;  break;
        case 4 :  fifo_p = & EP4_ADDR_DEF ;  break;
        default: ;
    }

    for ( i = 0; i < NO; i ++ )                 // read  num = NO  fifo_data;
    {
        p[i] = fifo_p[i];
    }
}
*/
void WriteEP1FIFO(UINT8 NO, UINT8 *p)
{
	unsigned char volatile xdata * fifo_p;
	unsigned char volatile xdata * cnt_p ;
	UINT8 i;
	fifo_p = & EP1_ADDR_DEF; 
	cnt_p  = & CNT1;
	
	for (i = 0; i < NO; i ++ )              // read  num= NO  fifo_data;
		* (fifo_p ++ ) = * (p ++ ) ;

	* cnt_p = NO;
}

void fifo_Write_main (UINT8 fifo_Index, UINT8 NO, UINT8 *p )
{
    unsigned char volatile xdata * fifo_p;
    unsigned char volatile xdata * cnt_p ;
    UINT8 i;
    
    switch (fifo_Index)
    {
        case 0 : { fifo_p = & EP0_ADDR_DEF ; cnt_p  = & CNT0; } break;
        case 1 : { fifo_p = & EP1_ADDR_DEF ; cnt_p  = & CNT1; } break;
        case 2 : { fifo_p = & EP2_ADDR_DEF ; cnt_p  = & CNT2; } break;
        case 3 : { fifo_p = & EP3_ADDR_DEF ; cnt_p  = & CNT3; } break;
        case 4 : { fifo_p = & EP4_ADDR_DEF ; cnt_p  = & CNT4; } break;
        default: ;
    }

    for (i = 0; i < NO; i ++ )              // read  num= NO  fifo_data;
        * (fifo_p ++ ) = * (p ++ ) ;
    
    * cnt_p = NO;   
    
}

void fifo_Write (UINT8 fifo_Index, UINT8 NO, UINT8 *p )
{
    unsigned char volatile xdata * fifo_p;
    unsigned char volatile xdata * cnt_p ;
    UINT8 i;
    
    switch (fifo_Index)
    {
        case 0 : { fifo_p = & EP0_ADDR_DEF ; cnt_p  = & CNT0; } break;
        case 1 : { fifo_p = & EP1_ADDR_DEF ; cnt_p  = & CNT1; } break;
        case 2 : { fifo_p = & EP2_ADDR_DEF ; cnt_p  = & CNT2; } break;
        case 3 : { fifo_p = & EP3_ADDR_DEF ; cnt_p  = & CNT3; } break;
        case 4 : { fifo_p = & EP4_ADDR_DEF ; cnt_p  = & CNT4; } break;
        default: ;
    }

    for (i = 0; i < NO; i ++ )              // read  num= NO  fifo_data;
        * (fifo_p ++ ) = * (p ++ ) ;
    
    * cnt_p = NO;   
    
}

/*
void fifo_Write_IN_ini (UINT8 fifo_Index, UINT8 NO, UINT8 *p )
{
    unsigned char volatile xdata * fifo_p;
    unsigned char volatile xdata * cnt_p ;
    UINT8 i;
    
    switch (fifo_Index)
    {
        case 0 : { fifo_p = & EP0_ADDR_DEF ; cnt_p  = & CNT0; } break;
        case 1 : { fifo_p = & EP1_ADDR_DEF ; cnt_p  = & CNT1; } break;
        case 2 : { fifo_p = & EP2_ADDR_DEF ; cnt_p  = & CNT2; } break;
        case 3 : { fifo_p = & EP3_ADDR_DEF ; cnt_p  = & CNT3; } break;
        case 4 : { fifo_p = & EP4_ADDR_DEF ; cnt_p  = & CNT4; } break;
        default: ;
    }

    for (i=0;i<NO;i++)                    // read  num= NO  fifo_data;
        * (fifo_p++) = * (p++) ;
    
    * cnt_p = NO;   
    
}
*/

/*
void set_Wait_Status (void)
{
      EP_STATE[0]= EP_WAIT_STATUS;
      set_ep0_dir ( ! (CFG_EP0_1 & 0x80) );  // EP0_DIR = ~EP0_DIR;
      CNT0 = 0;                              // status package has zero bytes to send or receive
}
*/
void set_Wait_Status (void)
{

//      set_ep0_dir ( ! (CFG_EP0_1 & 0x80) );  // EP0_DIR = ~EP0_DIR;
      if(CFG_EP0_1 & 0x80)
      {
        CFG_EP0_1 &= ~ 0x80;
      }
      else
      {
        CFG_EP0_1 |= 0x80;
      }
      EP_STATE[0]= EP_WAIT_STATUS;
      CNT0 = 0;                              // status package has zero bytes to send or receive
}

void set_Wait_Address (void)
{
      EP_STATE[0]= EP_SET_ADDRESS;
      set_ep0_dir ( ! (CFG_EP0_1 & 0x80) );  // EP0_DIR = ~EP0_DIR;
      CNT0=0;                                // status package has zero bytes to send or receive
}

void set_ep_rdy (UINT8 ep_index)             // set EP_RDY[ep_index] to 1;
{
     EP_RDY = (0x01 << ep_index);   
}

void set_ep0_dir(UINT8 i)                    // set ep0_dir with input number
{
    if (i)
        CFG_EP0_1 |= 0x80;
    else
        CFG_EP0_1 &= ~ 0x80;
    
}


/***********************************************************
						end file
***********************************************************/
