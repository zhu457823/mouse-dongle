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
<author> 		<time>		 <version >		 <desc>
			2011/03/01  			0.1  			build this moudle 
***********************************************************/

#include "Headfile\includes.h"

//-----------------------------------------------------------------------------
// Support Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Get_Status
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change for custom HID designs.
//
// ----------------------------------------------------------------------------
void Get_Status (void)                 
// This routine returns a two byte status packet to the host
{                                       

     if (setup.wValue.c[MSB] || setup.wValue.c[LSB] ||                                                 
        setup.wLength.c[MSB]    || (setup.wLength.c[LSB] != 2))
	 // If non-zero return length or data length not Equal to 2
     // then send a stall indicating invalid request
     {                                   
         force_Stall ( );
     }

     switch(setup.bmRequestType)         
	 // Determine if recipient was device,interface, or EP
     {                                    
        case OUT_DEVICE:                   // If recipient was device
           if (setup.wIndex.c[MSB] || setup.wIndex.c[LSB])
           {
                force_Stall ( );            // Send stall if request is invalid
           }
           else
           {
              // Otherwise send 0x00, indicating bus power and no
              // remote wake-up supported
              if (Remote_Wakeup==1)
                  DATAPTR = (unsigned char*) & TWO_PACKET;
              else
                  DATAPTR = (unsigned char*) & ZERO_PACKET;

              DATASIZE = 2;
           }
           break;

        case OUT_INTERFACE:              // See if recipient was interface
           if ((USB0_STATE != DEV_CONFIGURED))
           {
               force_Stall ( );            // Otherwise send stall to host
           }
           else
           {
              // Status packet always returns 0x00
              DATAPTR = (unsigned char * ) & ZERO_PACKET;
              DATASIZE = 2;
           }
         break;

         case OUT_ENDPOINT:               // See if recipient was an endpoint
            if ((USB0_STATE != DEV_CONFIGURED) ||
            setup.wIndex.c[MSB])          
			// Make sure device is configured and index msb = 0x00
            {                             
			    // otherwise return stall to host
                force_Stall( );
            }
             else
             {
            // Handle case if request is directed to EP 1
            if (setup.wIndex.c[LSB] == IN_EP1)
            {
               if (EP_STATE[1] == EP_STALL)
               {           
                    // If endpoint is halted, return 0x01,0x00
                    DATAPTR = (unsigned char * ) & ONES_PACKET;
                    DATASIZE = 2;
               }
               else
               {
                    // Otherwise return 0x00,0x00 to indicate endpoint active
                    DATAPTR = (unsigned char * )&ZERO_PACKET;
                    DATASIZE = 2;
               }
            }
            else if (setup.wIndex.c[LSB] == IN_EP2)
            {
               if (EP_STATE[2] == EP_STALL)
               {                      
                    // If endpoint is halted, return 0x01,0x00
                    DATAPTR = ( unsigned char * ) & ONES_PACKET;
                    DATASIZE = 2;
               }
               else
               {
                    // Otherwise return 0x00,0x00 to indicate endpoint active
                    DATAPTR = ( unsigned char * ) & ZERO_PACKET;
                    DATASIZE = 2;
               }
            }
            else if (setup.wIndex.c[LSB] == IN_EP3)
            {
               if (EP_STATE[3] == EP_STALL)
               {                      
                    // If endpoint is halted, return 0x01,0x00
                    DATAPTR = ( unsigned char * ) & ONES_PACKET;
                    DATASIZE = 2;
               }
               else
               {
                    // Otherwise return 0x00,0x00 to indicate endpoint active
                    DATAPTR = ( unsigned char * ) & ZERO_PACKET;
                    DATASIZE = 2;
               }
            }
            else if (setup.wIndex.c[LSB] == OUT_EP4)
            {
               if (EP_STATE[4] == EP_STALL)
               {                      
                    // If endpoint is halted, return 0x01,0x00
                    DATAPTR = ( unsigned char * ) & ONES_PACKET;
                    DATASIZE = 2;
               }
               else
               {
                    // Otherwise return 0x00,0x00 to indicate endpoint active
                    DATAPTR = ( unsigned char * ) & ZERO_PACKET;
                    DATASIZE = 2;
               }
            }            
            else
            {
                 force_Stall ( );         // Send stall if unexpected data encountered
            }
         }
         break;

      default:
         force_Stall ( );
         break;
   }
   if (EP_STATE[0] != EP_STALL)
   {
      // Set serviced setup Packet, Endpoint 0 in transmit mode, and
      // reset DATASENT counter
      
      EP_STATE[0] = EP_TX;
      DATASENT = 0;
   }
}

//-----------------------------------------------------------------------------
// Clear_Feature
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Clear_Feature ( )                  
// This routine can clear Halt Endpoint features on endpoint 1
{                                       
   // Send procedural stall if device isn't configured
   if ( (USB0_STATE != DEV_CONFIGURED) ||
   // Or request is made to host(remote wakeup not supported)
   // (setup.bmRequestType == IN_DEVICE) ||
   // Or request is made to interface
   (setup.bmRequestType == IN_INTERFACE) ||
   // Or data length set to non-zero.
   setup.wLength.c[MSB] || setup.wLength.c[LSB])
   {
      force_Stall ( );
   }

   else
   {
      // Verify that packet was directed at an endpoint
      if ( (setup.bmRequestType == IN_DEVICE) && 
      // Remote_Wakeup feature is selected
      (setup.wValue.c[LSB] == DEVICE_REMOTE_WAKEUP )    )
      {
         Remote_Wakeup = 0;
      }
      
      
      else if ( (setup.bmRequestType == IN_ENDPOINT) 
	       && (setup.wValue.c[LSB] == ENDPOINT_HALT) )
      // The feature selected was HALT_ENDPOINT 
      {
         if (setup.wIndex.c[LSB] == IN_EP1)
         {
            EP_HALT &= ~ 0x02;
            EP_STATE[1] = EP_IDLE;    // Set endpoint 1 status back to idle
         }
         else if (setup.wIndex.c[LSB] == IN_EP2)
         {
            EP_HALT &= ~ 0x04;
            EP_STATE[2] = EP_IDLE;    // Set endpoint 1 status back to idle
         }
         else if (setup.wIndex.c[LSB] == IN_EP3)
         {
            EP_HALT &= ~ 0x08;
            EP_STATE[3] = EP_IDLE;    // Set endpoint 1 status back to idle
         }
         else if (setup.wIndex.c[LSB] == OUT_EP4)
         {
            EP_HALT &= ~ 0x10;
            EP_STATE[4] = EP_IDLE;    // Set endpoint 1 status back to idle
         }
      }
      else
      {
         force_Stall ( );               // Send procedural stall
      }
   }
   
   if (EP_STATE[0] != EP_STALL)
   {
      set_Wait_Status ( );              
	  // Set Serviced Out packet ready and 
	  // data end to indicate transaction is over
   }
}

//-----------------------------------------------------------------------------
// Set_Feature
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Set_Feature (void)                
// This routine will set the EP Halt feature for endpoint 1
{                                      
   // Make sure device is configured, setup data
   // is all valid and that request is directed at an endpoint
   if ((USB0_STATE != DEV_CONFIGURED) ||  
     (setup.bmRequestType == IN_INTERFACE) ||
      setup.wLength.c[MSB] || setup.wLength.c[LSB])
   {
      force_Stall ( );                  // Otherwise send stall to host
   }

   else
   {
        // Make sure endpoint exists and that halt
        if ( (setup.bmRequestType == IN_DEVICE) && 
        // Remote_Wakeup feature is selected
        (setup.wValue.c[LSB] == DEVICE_REMOTE_WAKEUP )    )
          {
            Remote_Wakeup = 1;
        }

          else if ( (setup.bmRequestType == IN_ENDPOINT) &&
        // endpoint feature is selected
        (setup.wValue.c[LSB] == ENDPOINT_HALT) )     
        {
                if (setup.wIndex.c[LSB] == IN_EP1)
                {
                    EP_HALT |= 0x02;
                    EP_STATE[1] = EP_STALL;
                 }
                else if (setup.wIndex.c[LSB] == IN_EP2)
                {
                    EP_HALT |= 0x04;
                    EP_STATE[2] = EP_STALL;
                }
                else if (setup.wIndex.c[LSB] == IN_EP3)
                {
                    EP_HALT |= 0x08;
                    EP_STATE[3] = EP_STALL;
                }
                else if (setup.wIndex.c[LSB] == OUT_EP4)
                {
                    EP_HALT |= 0x10;
                    EP_STATE[4] = EP_STALL;
                }

				              
         }
         else
         {
             force_Stall ( );               // Send procedural stall
         }
        
   }
   
   if (EP_STATE[0] != EP_STALL)
   {
      set_Wait_Status ( );
   }
}

//-----------------------------------------------------------------------------
// Set_Address
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Set_Address (void)                // Set new function address
{
   // Request must be directed to device
   if ((setup.bmRequestType != IN_DEVICE) ||
   setup.wIndex.c[MSB]  || setup.wIndex.c[LSB]||
   setup.wLength.c[MSB] || setup.wLength.c[LSB]||
   setup.wValue.c[MSB]  || (setup.wValue.c[LSB] & 0x80))
   {
     force_Stall ( );                   // Send stall if setup data invalid
   }

   if (setup.wValue.c[LSB] != 0)
   {
      USB0_STATE = DEV_ADDRESS;        
	  // Indicate that device state is now address
   }
   else
   {
      USB0_STATE = DEV_DEFAULT;        
	  // If new address was 0x00, return device to default state
   }                                   
   if (EP_STATE[0] != EP_STALL)
   {
      set_Wait_Address ( );
   }

//   DATASIZE=0;
//   EP_STATE[0] = EP_TX ;
}


//-----------------------------------------------------------------------------
// Get_Descriptor
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine sets the data pointer and size to correct 
// descriptor and sets the endpoint status to transmit
//
//-----------------------------------------------------------------------------

void Get_Descriptor (void)             
// This routine sets the data pointer and size 
//to correct descriptor and sets the endpoint status to transmit
{                                       
                                    
	switch(setup.wValue.c[MSB])         
	{                                    
		case DSC_DEVICE:                  // 0x80, 0x06, 0x00, 0x01
			DATAPTR = (unsigned char * ) &DEVICEDESC;
			DATASIZE = 18;
			break;

		case DSC_CONFIG:		// 0x80, 0x06, 0x00, 0x02
			DATAPTR = (unsigned char * ) & ConfigDesc;
			DATASIZE = cConfigLen;	//0xc0;
			break;

		case DSC_STRING:		// 0x80, 0x06, 0x02, 0x03
		// NOTE: if strings are added to this project, the hard-coded
		// value of 2 will need to be increased
			if (setup.wValue.c[LSB] > 3)//((setup.wValue.c[LSB] > 3)||(setup.wValue.c[LSB] == 2))   // If asking for string that's N/A
			{
				force_Stall( );
			}
			else
			{
				DATAPTR = STRINGDESCTABLE[setup.wValue.c[LSB]];
				// Can have a maximum of 255 strings
				DATASIZE = * DATAPTR;
			}
			break;



		case DSC_HID_REPORT:                // HID Specific (HID report descriptor) 0x81, 0x06, 0x00, 0x22, wIndex(Interface NO.)
			#ifdef	DEV_MIC
			if(setup.wIndex.i==0x03)//0x02)	// KB interface NO. = 2.
			{
				DATAPTR = (unsigned char*)&KEYBOARDHIDREPORTDESC;
				if(setup.wLength.i>HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE)
					setup.wLength.i =HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE;


				DATASIZE =  setup.wLength.i ;//HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE;
			}
			else if(setup.wIndex.i==0x04)		// MS interface NO. = 4.
			{
				DATAPTR = (unsigned char*)&MOUSEHIDREPORTDESC;
				if(setup.wLength.i>HID_MOUSE_REPORT_DESCRIPTOR_SIZE)
					setup.wLength.i =HID_MOUSE_REPORT_DESCRIPTOR_SIZE;


				DATASIZE =  setup.wLength.i ;//HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE;
			}
			#else
			if(setup.wIndex.i==0x02)	// KB interface NO. = 2.
			{
				DATAPTR = (unsigned char*)&KEYBOARDHIDREPORTDESC;
				if(setup.wLength.i>HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE)
					setup.wLength.i =HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE;


				DATASIZE =  setup.wLength.i ;//HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE;
			}
			else if(setup.wIndex.i==0x03)
			{
				DATAPTR = (unsigned char*)&MEDIAKEYHIDREPORTDESC;
				if(setup.wLength.i>HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE)
					setup.wLength.i=HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE;

				DATASIZE = setup.wLength.i ;// HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE;		
			}
			#endif
			break;


		case DSC_HID:                       // HID Specific (HID class descriptor)
			#ifdef	DEV_MIC
			if(setup.wIndex.i==0x03)//0x02)
			{	// KB interface NO. = 2.
				DATAPTR = (unsigned char*)&KeyHidDesc;
				DATASIZE = KeyHidDesc.bLength;
			}
			else if(setup.wIndex.i==0x04)//0x02)
			{	// KB interface NO. = 2.
				DATAPTR = (unsigned char*)&MouseHidDesc;
				DATASIZE = KeyHidDesc.bLength;
			}
			#else
			if(setup.wIndex.i==0x02){	// KB interface NO. = 2.
				DATAPTR = (unsigned char*)&KeyHidDesc;
				DATASIZE = KeyHidDesc.bLength;
			}
			else if(setup.wIndex.i==0x03)
			{
				DATAPTR = (unsigned char*)&MediaKeyHidDesc;
				DATASIZE = MediaKeyHidDesc.bLength;		
			}
			#endif
			break;

		case DSC_INTERFACE:		// Interface descriptor.
			#ifdef	DEV_MIC
			if ( setup.wValue.c[LSB] == 0x03)//0x02 )
			{ 
				DATAPTR = (unsigned char*) & KeyInterfaceDesc;
				DATASIZE = KeyInterfaceDesc.bLen;
			}
			else if ( setup.wValue.c[LSB] == 0x04)//0x02 )
			{ 
				DATAPTR = (unsigned char*) & MouseInterfaceDesc;
				DATASIZE = MouseInterfaceDesc.bLen;
			}
			#else
			if ( setup.wValue.c[LSB] == 0x02 )
			{ 
				DATAPTR = (unsigned char*) & KeyInterfaceDesc;
				DATASIZE = KeyInterfaceDesc.bLen;
			}
			else if ( setup.wValue.c[LSB] == 0x03 )
			{ 
				DATAPTR = (unsigned char*) & MediaKeyInterfaceDesc;
				DATASIZE = MediaKeyInterfaceDesc.bLength;
			}
			#endif
			break;


		default:
			force_Stall ( );               // Send Stall if unsupported request
			break;
	}

   // Verify that the requested descriptor is valid
   	if ((setup.wValue.c[MSB] == DSC_DEVICE )||
     		(setup.wValue.c[MSB] == DSC_CONFIG)     ||
     		(setup.wValue.c[MSB] == DSC_STRING  )   ||
     		(setup.wValue.c[MSB] == DSC_INTERFACE)  ||
     		(setup.wValue.c[MSB] == DSC_ENDPOINT) )
	{
		if (setup.wLength.i< DATASIZE)
		{
			DATASIZE = setup.wLength.i;  // Send only requested amount of data
		}
	}
	if (EP_STATE[0] != EP_STALL)           // Make sure endpoint not in stall mode
	{
		EP_STATE[0] = EP_TX;               // Put endpoint in transmit mode
		DATASENT = 0;                      // Reset Data Sent counter
	}
}

void Get_Configuration (void)          
// This routine returns current configuration value
{                                       
   // This request must be directed to the device
   if ( (setup.bmRequestType != OUT_DEVICE)    ||
   // With value word set to zero
   setup.wValue.c[MSB]  || setup.wValue.c[LSB]||
   // And index set to zero
   setup.wIndex.c[MSB]  || setup.wIndex.c[LSB]||
   // And setup length set to one
   setup.wLength.c[MSB] || (setup.wLength.c[LSB] != 1) )
   {
      force_Stall ( );                  // Otherwise send a stall to host
   }

   else
   {
      if (USB0_STATE == DEV_CONFIGURED)  
	  // If the device is configured, then return value 0x01 
	  // since this software only supports one configuration
      {                                 
                                        
         DATAPTR = (unsigned char*) & ONES_PACKET;
         DATASIZE = 1;
      }
      if (USB0_STATE == DEV_ADDRESS)   
	  // If the device is in address state, it is not configured, so return 0x00
      {                                
         DATAPTR = (unsigned char*) & ZERO_PACKET;
         DATASIZE = 1;
      }
   }
   if (EP_STATE[0] != EP_STALL)
   {
      // Set Serviced Out Packet bit
      EP_STATE[0] = EP_TX;             // Put endpoint into transmit mode
      DATASENT = 0;                    // Reset Data Sent counter to zero
   }
}

//-----------------------------------------------------------------------------
// Set_Configuration
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Set_Configuration (void)          
// This routine allows host to change current device configuration value
{                                      

   	// Device must be addressed before configured
	if ((USB0_STATE == DEV_DEFAULT) ||
  	 // and request recipient must be the device
  	 (setup.bmRequestType != IN_DEVICE) ||
   	// the index and length words must be zero
   	setup.wIndex.c[MSB]  || setup.wIndex.c[LSB]||
   	setup.wLength.c[MSB] || setup.wLength.c[LSB] ||
   	setup.wValue.c[MSB]  || (setup.wValue.c[LSB] > 1))
   	// This software only supports config = 0,1
	{
		force_Stall ( );                  // Send stall if setup data is invalid
	}

   	else
	{
		if (setup.wValue.c[LSB] > 0)     
		// Any positive configuration request results in configuration being set to 1
		{                                 
		                        
			USB0_STATE = DEV_CONFIGURED;
			EP_STATE[1] = EP_IDLE;       // Set endpoint status to idle (enabled)
			EP_STATE[2] = EP_IDLE;       // Set endpoint status to idle (enabled)         
			EP_STATE[3] = EP_IDLE;       // Set endpoint status to idle (enabled)
			EP_STATE[4] = EP_IDLE;       // Set endpoint status to idle (enabled)         
			/*
			POLL_WRITE_BYTE (INDEX, 1);   // Change index to endpoint 1
			// Set DIRSEL to indicate endpoint 1 is IN/OUT
			POLL_WRITE_BYTE (EINCSR2, rbInSPLIT);
			POLL_WRITE_BYTE (INDEX, 0);   // Set index back to endpoint 0

			Handle_In1( );
			*/
		}
		else
		{
			USB0_STATE = DEV_ADDRESS;     // Unconfigures device by setting state
			EP_STATE[1] = EP_STALL;       // to address, and changing endpoint
			EP_STATE[2] = EP_STALL;       // 1 and 2
			EP_STATE[3] = EP_STALL;       // to address, and changing endpoint
			EP_STATE[4] = EP_STALL;       // 1 and 2
		}
	}
	if (EP_STATE[0] != EP_STALL)
	{
		set_Wait_Status ( );
	}
}

//-----------------------------------------------------------------------------
// Get_Interface
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - Non
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Get_Interface (void)              
// This routine returns 0x00, since no alternate interface is supported by this firmware
{                                                                             
   // If device is not configured
   if ((USB0_STATE != DEV_CONFIGURED) ||
   // or recipient is not an interface
   (setup.bmRequestType != OUT_INTERFACE) ||
   // or non-zero value or index fields
   setup.wValue.c[MSB]  ||setup.wValue.c[LSB] ||
   // or data length not equal to one
   setup.wIndex.c[MSB]  ||setup.wIndex.c[LSB] ||
   setup.wLength.c[MSB] ||(setup.wLength.c[LSB] != 1))
   {
      force_Stall ( );                  // Then return stall due to invalid request
   }
   else
   {
     // Otherwise, return 0x00 to host
      DATAPTR = (unsigned char*) & ZERO_PACKET;
      DATASIZE = 1;
   }
   if (EP_STATE[0] != EP_STALL)
   {
     // Set Serviced setup packet, put endpoint in transmit mode and reset
     // Data sent counter
      EP_STATE[0] = EP_TX;
      DATASENT = 0;
   }
}

//-----------------------------------------------------------------------------
// Set_Interface
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Standard request that should not change in custom HID designs.
//
//-----------------------------------------------------------------------------
void Set_Interface (void)
{
   // Make sure request is directed at interface
   // and all other packet values are set to zero
   if ((setup.bmRequestType != IN_INTERFACE)  ||
      setup.wLength.c[MSB] ||setup.wLength.c[LSB]||
      setup.wValue.c[MSB]  ||/*setup.wValue.c[LSB] ||*/
      setup.wIndex.c[MSB]  /*||setup.wIndex.c[LSB]*/)
   {
	force_Stall ( );                  // Othewise send a stall to host
   }
   else
   {
	if(setup.wIndex.c[LSB] == 1)		// Microphone audio streaming interface Num.
  	{
		if(setup.wValue.c[LSB])
			USBPhone.uMICInterfaceAlter = 1;
		else
			USBPhone.uMICInterfaceAlter = 0;
  	}
	else if(setup.wIndex.c[LSB] == 2)	// KB interface Num.
  	{
  		#if	0
		if(setup.wValue.c[LSB])
			USBPhone.uSPKInterfaceAlter = 1;	// Normal isochronous operation. 
		else
			USBPhone.uSPKInterfaceAlter = 0;	// zero bindwidth alternate setting.
		#endif
  	}

   }
   
   if (EP_STATE[0] != EP_STALL)
   {
	set_Wait_Status ( );              
	// Indicate setup packet has been serviced
                                       
   }
}

//-----------------------------------------------------------------------------
// Get_Idle
//-----------------------------------------------------------------------------
// Not supported.
//
//-----------------------------------------------------------------------------
void Get_Idle(void) 
{
      // Otherwise, return 0x00 to host
      DATAPTR = (unsigned char*) & idle_rate;
      DATASIZE = 1;

      if (EP_STATE[0] != EP_STALL)
      {
         // Set Serviced setup packet, put endpoint in transmit mode 
	     // and reset Data sent counter
         EP_STATE[0] = EP_TX;
         DATASENT = 0;
      }
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Get_Protocol
//-----------------------------------------------------------------------------
// Not supported.
//
//-----------------------------------------------------------------------------
/*
void Get_Protocol(void) 
{ 
    set_Wait_Status ( );
}
*/
void Get_Protocol(void) 
{ 
	 DATAPTR = (unsigned char*) & set_protocol_status;
       DATASIZE = 1;

	   EP_STATE[0] = EP_TX ;        // Endpoint 0 in transmit mode
        DATASENT = 0; 
}

//-----------------------------------------------------------------------------
// Set_Protocol
//-----------------------------------------------------------------------------
// Not supported.
//
//-----------------------------------------------------------------------------
/*void Set_Protocol (void) 
{ 
    set_Wait_Status ( );
}*/
void Set_Protocol (void) 
{ 
	set_protocol_status=setup.wValue.c[LSB];
    set_Wait_Status ( );
}


//-----------------------------------------------------------------------------
// Set_Idle( )
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Description: Sets the idle feature on interrupt in endpoint.
//-----------------------------------------------------------------------------
void Set_Idle (void)
{ 
    idle_rate = setup.wValue.c[MSB];
    set_Wait_Status ( );
}

//-----------------------------------------------------------------------------
// Get_Report( )
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Description: Sends a given report type to the host.
//
//-----------------------------------------------------------------------------

void Get_Report (void)
{
   // set DATAPTR to buffer used inside Control Endpoint
   
   DATAPTR = (unsigned char*) & ZERO_PACKET;
 //  DATASIZE = 1;
   DATASIZE = EP0_ADDR_DEF_6;

   if( (setup.wValue.c[MSB]==PC_GET_REPORT_2) && (setup.wValue.c[LSB]==PC_GET_REPORT_1) )
	{


		if(system.usbp0_data.reday_report_flag)   // ok
		{
			system.usbp0_data.reday_report_flag = 0;
	 
			system.usbp0_data.get_report_data[0] = PC_GET_DATA;	
		}
		else					// no data
		{
			system.usbp0_data.get_report_data[0] = PC_GET_NONDATA;	

		}
		DATAPTR = (unsigned char*) & system.usbp0_data.get_report_data;

	}

   if (EP_STATE[0] != EP_STALL)
   {
        // Set serviced setup Packet
        EP_STATE[0] = EP_TX ;        // Endpoint 0 in transmit mode
        DATASENT = 0;                // Reset DATASENT counter       
   }
}

//-----------------------------------------------------------------------------
// Set_Report( )
//-----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// Description: Receives a report sent from the host.
//
//-----------------------------------------------------------------------------
void Set_Report ()
{
   // prepare buffer for OUT packet   
   // set DATAPTR to buffer
   DATAPTR  = system.usbp0_data.out_report;
   //   DATASIZE = setup.wLength.i;
   DATASIZE = EP0_ADDR_DEF_6;
   
   system.usbp0_data.wait_out_report=1;
   if (EP_STATE[0] != EP_STALL)
   {
      // Set serviced setup Packet
      EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode
     
      DATASENT = 0;                    // Reset DATASENT counter
   }
}
//===========================================================
// USB Audio class request.
//===========================================================
void AudioInit(void)
{
#ifdef	DEV_MIC
	USBPhone.uMICMute = 0;		// 1
	USBPhone.wMICVolume.i = 0;
	USBPhone.wMICMaxVolume.i = 1;
	USBPhone.wMICMinVolume.i = 0;
	USBPhone.wMICRes.i = 0x01;
	USBPhone.uMICInterfaceAlter = 0;	// 0x0, Zero bandwidth alternate setting. 0x01, normal isochronous operation.
#endif

#ifdef	DEV_PHONE
	USBPhone.uMICMute = 0;
	USBPhone.uSPKMute = 1;
	USBPhone.wMICVolume.i = 0;
	USBPhone.wSPKVolume.i = 0;
	USBPhone.wMICMaxVolume.i = 1;
	USBPhone.wMICMinVolume.i = 0;
	USBPhone.wSPKMaxVolume.i = 0;
	USBPhone.wSPKMinVolume.i = 0;
	USBPhone.wSPKRes.i = 0x01;
	USBPhone.wMICRes.i = 0x01;

	USBPhone.uMICInterfaceAlter = 0;	// 0x0, Zero bandwidth alternate setting. 0x01, normal isochronous operation.
	USBPhone.uSPKInterfaceAlter = 0;
#endif
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void SET_CUR(void)
{
#ifdef	DEV_PHONE
	if(EP0_ADDR_DEF_4 == 0)		// Audio control interface is 0
	{								// Feature unit control.
		if(EP0_ADDR_DEF_3 == cMuteCtrl_CS)
		{
			if(EP0_ADDR_DEF_5 == 0x06)		// Feature UNIT ID
			{						
				USBINT0 = 0xc0;
				DATAPTR = &(USBPhone.uSPKMute);
				DATASIZE = 1;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else if(EP0_ADDR_DEF_5 == 0x05)	// Feature UNIT ID
			{
				USBINT0 = 0xc0;
				DATAPTR = &(USBPhone.uMICMute);
				DATASIZE = 1;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else
				force_Stall();
		}
		else if(EP0_ADDR_DEF_3 == cVolumeCtrl_CS)
		{
			if(EP0_ADDR_DEF_5 == 0x06)		// Feature UNIT ID
			{			
				USBINT0 = 0xc0;

				DATAPTR = &(USBPhone.wSPKVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
				
			}
			else if(EP0_ADDR_DEF_5== 0x05)	// Feature UNIT ID
			{
				USBINT0 = 0xc0;
				DATAPTR = &(USBPhone.wMICVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else
				force_Stall();
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif

#ifdef	DEV_MIC
	if(EP0_ADDR_DEF_4 == 0)		// Audio control interface is 0
	{								// Feature unit control.
		if(EP0_ADDR_DEF_3 == cMuteCtrl_CS)
		{
			if(EP0_ADDR_DEF_5 == 0x05)	// Feature UNIT ID
			{
				USBINT0 = 0xc0;
				DATAPTR = &(USBPhone.uMICMute);
				DATASIZE = 1;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else
				force_Stall();
		}
		else if(EP0_ADDR_DEF_3 == cVolumeCtrl_CS)
		{
			if(EP0_ADDR_DEF_5== 0x05)	// Feature UNIT ID
			{
				USBINT0 = 0xc0;
				DATAPTR = &(USBPhone.wMICVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_RX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
				set_ep_rdy(EP_0);			// 1:Endpoint 0 ready for transfer USB data.
			}
			else
				force_Stall();
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
void SET_MIN(void)
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
void SET_MAX(void)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void SET_RES(void)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void SET_MEM(void)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_CUR(void)
{
#ifdef	DEV_PHONE
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.
		if(setup.wValue.c[MSB] == cMuteCtrl_CS)
		{
			if(setup.wIndex.c[MSB] == 0x06)		// Feature UNIT ID
			{						
				DATAPTR = &(USBPhone.uSPKMute);
				DATASIZE = 1;
 
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
			{
				DATAPTR = &(USBPhone.uMICMute);
				DATASIZE = 1;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else
				force_Stall();
		}
		else if(setup.wValue.c[MSB] == cVolumeCtrl_CS)
		{
			if(setup.wIndex.c[MSB] == 0x06)		// Feature UNIT ID
			{						
				DATAPTR = &(USBPhone.wSPKVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
			{
				DATAPTR = &(USBPhone.wMICVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else
				force_Stall();
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif

#ifdef	DEV_MIC
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.
		if(setup.wValue.c[MSB] == cMuteCtrl_CS)
		{
			if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
			{
				DATAPTR = &(USBPhone.uMICMute);
				DATASIZE = 1;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else
				force_Stall();
		}
		else if(setup.wValue.c[MSB] == cVolumeCtrl_CS)
		{
			if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
			{
				DATAPTR = &(USBPhone.wMICVolume.c[MSB]);
				DATASIZE = 2;
   
				if (EP_STATE[0] != EP_STALL)
				{
					// Set serviced setup Packet
					EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

					DATASENT = 0;                    // Reset DATASENT counter
				}
			}
			else
				force_Stall();
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_MIN(void)
{
#ifdef	DEV_PHONE
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.

		if(setup.wIndex.c[MSB] == 0x06)		// Feature UNIT ID
		{						
			DATAPTR = &(USBPhone.wSPKMinVolume.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
		{
			DATAPTR = &(USBPhone.wMICMinVolume.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif

#ifdef	DEV_MIC
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.

		if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
		{
			DATAPTR = &(USBPhone.wMICMinVolume.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else
			force_Stall();
	}
	else
	{
		force_Stall();
	}
#endif
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_MAX(void)
{
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.
#ifdef	DEV_PHONE
		if(setup.wIndex.c[MSB] == 0x06)		// Feature UNIT ID
		{						
			DATAPTR = &(USBPhone.wSPKMaxVolume.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
		{
			DATAPTR = &(USBPhone.wMICMaxVolume.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else
			force_Stall();
#endif

#ifdef	DEV_MIC
	if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
	{
		DATAPTR = &(USBPhone.wMICMaxVolume.c[MSB]);
		DATASIZE = 2;

		if (EP_STATE[0] != EP_STALL)
		{
			// Set serviced setup Packet
			EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

			DATASENT = 0;                    // Reset DATASENT counter
		}
	}
	else
		force_Stall();
#endif
	}
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_RES(void)
{
	if(setup.wIndex.c[LSB] == 0)		// Audio control interface is 0
	{								// Feature unit control.
#ifdef	DEV_PHONE
		if(setup.wIndex.c[MSB] == 0x06)		// Feature UNIT ID
		{						
			DATAPTR = &(USBPhone.wSPKRes.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
		{
			DATAPTR = &(USBPhone.wMICRes.c[MSB]);
			DATASIZE = 2;

			if (EP_STATE[0] != EP_STALL)
			{
				// Set serviced setup Packet
				EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

				DATASENT = 0;                    // Reset DATASENT counter
			}
		}
		else
			force_Stall();
#endif

#ifdef	DEV_MIC
	 if(setup.wIndex.c[MSB] == 0x05)	// Feature UNIT ID
	{
		DATAPTR = &(USBPhone.wMICRes.c[MSB]);
		DATASIZE = 2;

		if (EP_STATE[0] != EP_STALL)
		{
			// Set serviced setup Packet
			EP_STATE[0] = EP_TX ;            // Endpoint 0 in transmit mode

			DATASENT = 0;                    // Reset DATASENT counter
		}
	}
	else
		force_Stall();
#endif
	}
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_MEM(void)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void GET_STAT(void)
{

}
/***********************************************************
						end file
***********************************************************/
