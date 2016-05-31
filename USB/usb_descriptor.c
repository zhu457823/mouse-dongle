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
<author> 	<time> 	<version > 	<desc>
		  2011/03/01    0.1  		build this moudle 
***********************************************************/

#include "Headfile\includes.h"


/*code const*/ device_descriptor DEVICEDESC =
{
   18,                                 // bLength
   0x01,                               // bDescriptorType
   0x0002,	//0x1001,                             // bcdUSB
   0x00,                               // bDeviceClass
   0x00,                               // bDeviceSubClass
   0x00,                               // bDeviceProtocol
   EP0_PACKET_SIZE,                    // bMaxPacketSize0
   0x4570,	// 0x01AF, // 0xA724,	// 0x1604,	//0xA724, //0xA725,                             // idVendor = 24a7
   0x2018,	//0x0719,	// 0xE326, // 0x0225,	                          // idProduct = 2502
   0x0002,	//0x0110,                             // bcdDevice
   0x01,                               // iManufacturer
   0x02,	// 0x00,	//0x02,                               // iProduct
   0x03,		//0x00,                               // iSerialNumber
   0x01                                // bNumConfigurations
}; // end of DEVICEDESC

// From "USB Device Class Definition for Human Interface Devices (HID)".
// Section 7.1:
// "When a Get_Descriptor(Configuration) request is issued,
// it returns the Configuration descriptor, all Interface descriptors,
// all Endpoint descriptors, and the HID descriptor for each interface."
code const hid_configuration_descriptor_all HIDCONFIGDESC =
{
{ //hid_configuration_descriptor_all
   0x09,                               // Length
   0x02,                               // Type
   0x3b00,                             // Totallength (= 9+9+9+7+9+9+7)
   0x02,                               // NumInterfaces
   0x01,                               // bConfigurationValue
   0x00,                               // iConfiguration
   0x80,	//0xa0,                               // bmAttributes
   0x32                                // MaxPower (in 2mA units)
},

//  keyboard
{ // interface_descriptor hid_interface_descriptor
   0x09,                               // bLength
   0x04,                               // bDescriptorType
   0x00,                               // bInterfaceNumber
   0x00,                               // bAlternateSetting
   0x01,                               // bNumEndpoints
   0x03,                               // bInterfaceClass (3 = HID)
   0x01,                               // bInterfaceSubClass
   0x01,                               // bInterfaceProcotol
   0x00                                // iInterface
},
 
{ // class_descriptor hid_descriptor
   0x09,                               // bLength
   0x21,                               // bDescriptorType
   0x0101,                               // bcdHID
   0x00,                               // bCountryCode
   0x01,                               // bNumDescriptors
   0x22,                               // bDescriptorType
   HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE_LE  // wItemLength (tot. len. of report
                                       // descriptor)
},
 
// IN endpoint (mandatory for HID)
{ // endpoint_descriptor hid_endpoint_in_descriptor
   0x07,                               // bLength
   0x05,                               // bDescriptorType
   0x81,                               // bEndpointAddress
   0x03,                               // bmAttributes
   EP1_PACKET_SIZE_LE,                 // MaxPacketSize (LITTLE ENDIAN)
   10                                  // bInterval
},


// mouse media key
{ // interface_descriptor hid_interface_descriptor
   0x09,                               // bLength
   0x04,                               // bDescriptorType
   0x01,                               // bInterfaceNumber
   0x00,                               // bAlternateSetting
   0x01,                               // bNumEndpoints
   0x03,                               // bInterfaceClass (3 = HID)
   0x01,                               // bInterfaceSubClass
   0x02,                               // bInterfaceProcotol
   0x00                                // iInterface
},
 
{ // class_descriptor hid_descriptor
   0x09,                               // bLength
   0x21,                               // bDescriptorType
   0x0101,                               // bcdHID
   0x00,                               // bCountryCode
   0x01,                               // bNumDescriptors
   0x22,                               // bDescriptorType
   HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE_LE  //HID_MOUSE_REPORT_DESCRIPTOR_SIZE_LE wItemLength (tot. len. of report
                                       // descriptor)
},
 
// IN endpoint (mandatory for HID)
{ // endpoint_descriptor hid_endpoint_in_descriptor
   0x07,                               // bLength
   0x05,                               // bDescriptorType
   0x82,                               // bEndpointAddress
   0x03,                               // bmAttributes
   EP2_PACKET_SIZE_LE,     // MaxPacketSize (LITTLE ENDIAN)
   10                                  // bInterval
}

};

// HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE
code const hid_keyboard_report_descriptor KEYBOARDHIDREPORTDESC =
{
	0x05, 0x01,        // Usage Page (Generic Desktop),                    
	0x09, 0x06,        // Usage (Keyboard),                               
	0xA1, 0x01,        // Collection (Application),       
	0x85, 0x01,	// Report ID(x001)
	0x05, 0x07,        // Usage Page (Key Codes);                         
	0x19, 0xE0,        // Usage Minimum (224),                            
	0x29, 0xE7,        // Usage Maximum (231),                            
	0x15, 0x00,        // Logical Minimum (0),                            
	0x25, 0x01,        // Logical Maximum (1),                            
	0x75, 0x01,        // Report Size (1),                                
	0x95, 0x08,        // Report Count (8),                               
	0x81, 0x02,        // Input (Data, Variable, Absolute), ;Modifier byte
#if	0	
	0x95, 0x01,        // Report Count (1),                               
	0x75, 0x08,        // Report Size (8),                                
	0x81, 0x03,        // Input (Constant), ;Reserved byte   
	
	0x95, 0x05,        // Report Count (5),                               
	0x75, 0x01,        // Report Size (1),                                
	0x05, 0x08,        // Usage Page (Page# for LEDs),                    
	0x19, 0x01,        // Usage Minimum (1),                              
	0x29, 0x05,        // Usage Maximum (5),                              
	0x91, 0x02,        // Output (Data, Variable, Absolute), ;LED report  
	0x95, 0x01,        // Report Count (1),                               
	0x75, 0x03,        // Report Size (3),                                
	0x91, 0x03,        // Output (Constant), ;LED report padding
#endif	
	0x95, 0x06,        // Report Count (6),                               
	0x75, 0x08,        // Report Size (8),                                
	0x15, 0x00,        // Logical Minimum (0),                            
	0x25, 0xf1,        // Logical Maximum(101),                                                    
	0x19, 0x00,        // Usage Minimum (0),                              
	0x29, 0xf1,        // Usage Maximum (101),                            
	0x81, 0x00,        // Input (Data, Array), ;Key arrays (6 bytes)      
	0xC0,             // End Collection
	#if	0
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    	0x09, 0x02,                    // USAGE (Mouse)
    	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x02, 			   // Report ID (2)
    	0x09, 0x01,                    //   USAGE (Pointer)
    	0xa1, 0x00,                    //   COLLECTION (Physical)
    	0x05, 0x09,                    //     USAGE_PAGE (Button)
    	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1) 定义成19 00，鼠标按键电脑不响应
    	0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    	0x95, 0x03,                    //     REPORT_COUNT (3)
    	0x75, 0x01,                    //     REPORT_SIZE (1)
    	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    	0x75, 0x05,                    //     REPORT_SIZE (5)
    	0x95, 0x01,                    //     REPORT_COUNT (1)
    	0x81, 0x01,                    //     INPUT (Cnst,Var,Abs)
    	
    	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    	0x09, 0x30,                    //     USAGE (X)
    	0x09, 0x31,                    //     USAGE (Y)
    	0x09, 0x38,                    //     USAGE (Wheel)
  	0x15, 0x81, 			   //	  Logical Minimum (-127)
  	0x25, 0x7F, 			   //	  Logical Maximum (127) 
    	0x75, 0x08,                    //     REPORT_SIZE (8)
    	0x95, 0x03,                    //     REPORT_COUNT (3)    
    	0x81, 0x06,                    //     INPUT (Data,Var,Rel)

	0x09, 0x00,                    //     USAGE ()
	0x95, 0x0C,                    //     REPORT_COUNT (12)	
	0x81, 0x02,                    //     INPUT ()
    	0xc0,                          //   END_COLLECTION
    	0xc0,                           // END_COLLECTION
    	#endif
	#if	0
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    	0x09, 0x04,                    // USAGE (Joystick)
    	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x03, 			   // Report ID (3)
    	0x05, 0x09,                    //   USAGE (Gamepad)
    	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    	0x29, 0x08,                    //     USAGE_MAXIMUM (Button 8)
    	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    	0x35, 0x00,				// Physical minimum(0)
    	0x45, 0x01,				// Physical maximum(1).
    	0x75, 0x01,                    //     REPORT_SIZE (1)
    	0x95, 0x08,                    //     REPORT_COUNT (8)
    	0x81, 0x02,                    //     INPUT (Data,Var,Abs)

	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (X)
    	0x09, 0x31,                    //     USAGE (Y)
    	0x09, 0x32,                    //     USAGE (Z)
  	0x15, 0x00, 			   //	  Logical Minimum (0)
  	0x26, 0xFF, 0x00, 			   //	  Logical Maximum (0xff) 
    	0x75, 0x08,                    //     REPORT_SIZE (8)
    	0x95, 0x03,                    //     REPORT_COUNT (3)    
    	0x81, 0x02,                    //     INPUT (Data,Var,Rel)
    	0xc0,                          //   END_COLLECTION
    	#endif
//====================多媒体按键控制=======25========================
	0x05, 0x0c,                    // USAGE_PAGE (consumer)
	0x09, 0x01,                    //     USAGE ()
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x04, 			   // Report ID (4)
	#if	0
    	0x09, 0xe9,                    //     USAGE (Volume inc)
    	0x09, 0xea,                    //     USAGE (Volume dec)
    	0x09, 0xe2,                    //     USAGE (mute)
    	0x09, 0xB5,                    //     USAGE (Scan next track)
    	0x09, 0xB6,                    //     USAGE (scan previous track)
    	0x09, 0xB0,                    //     USAGE (Play)
    	0x09, 0xB1,                    //     USAGE (Pause)
    	0x09, 0xB7,                    //     USAGE (Stop)
    	0x09, 0xB3,				// Usage (fast forward)
    	0x09, 0xB4,				//  Usage (Rewind)
  	0x15, 0x00, 			   //	  Logical Minimum (0)
  	0x25, 0x01, 			   //	  Logical Maximum (0x01) 
    	0x75, 0x01,                    //     REPORT_SIZE (1)
    	0x95, 0x0A,                    //     REPORT_COUNT (10)    
    	0x81, 0x02,                    //     INPUT (Data,Var,Rel)
    	0x75, 0x06,                    //     REPORT_SIZE (6)
    	0x95, 0x01,                    //     REPORT_COUNT (1)
    	0x81, 0x01,                    //     INPUT (Cnst,Var,Abs)
    	#endif
	0x15, 0x00,		 // LOGICAL_MINIMUM (0)
	0x26, 0x80, 
	0x03, 0x19,  
	0x00, 0x2a, 
	0x80, 0x03,  
	0x75, 0x10, 	 	// REPORT_SIZE (0x10)
	0x95, 0x01, 		// REPORT_COUNT (1)
	0x81, 0x00, 	 	// Input (Data,Ary,Abs)
	#if	0
	0x15, 0x00,				 // LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,			// Logical Maximum (0xff) 
	0x19, 0x00, 				// USAGE_MINIMUM ( 0)
	0x2a, 0xff, 0x00,			//  USAGE_MAXIMUM ( 0xff)
	0x75, 0x08, 	 			// REPORT_SIZE (0x8)
	0x95, 0x01, 				 // REPORT_COUNT (1)
	0x81, 0x00, 	 			// Input (Data,Ary,Abs)
	#endif
    	0xc0,                           	// END_COLLECTION
    	
	#if	0
	0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x01,                    // USAGE (Vendor Usage 1)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x05,      			// Report ID(0x05)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x19, 0x00,                    //     USAGE_MINIMUM ( 1)
    	0x29, 0x18,                    //     USAGE_MAXIMUM ( 0x18)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x18,  				//   REPORT_COUNT (0x18 )	
	0x91, 0x00,                    //   OUTPUT (Data,Var,Abs)
	
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x19, 0x00,                    //     USAGE_MINIMUM ( 1)
    	0x29, 0x0F,                    //     USAGE_MAXIMUM ( 0x0F)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x0F,  				//   REPORT_COUNT (0xF )
	0x81, 0x00,                    //   INPUT (Data,Var,Abs)
	0xC0                           //   end Application Collection};
	#endif
	//====================电源控制======31==============================
    	0x05, 0x01, 	// Usage Page (Generic Desktop),
	0x09, 0x80,	 	// USAGE (3-D Digitizer)
	0xa1, 0x01,	 	// Collection (Application),
	0x85, 0x05, 	// Report ID (5)
	0x05, 0x01, 	// Usage Page (Generic Desktop),
	0x19, 0x81, 	// Usage Minimum (), 
	0x29, 0x83, 	// Usage Maximum (),
	0x15, 0x00, 	// Logical Minimum (0),
	0x25, 0x01, 	// Logical Maximum (1),
	0x95, 0x03, 	// Report Count (3),
	0x75, 0x01, 	// Report Size (1),
	0x81, 0x06, 	// Input (Data,Var,Rel)
	0x95, 0x01, 	// Report Count (1),  
	0x75, 0x05, 	// Report Size (5),	
	0x81, 0x01,		// Input (Const,Ary,Abs)
	0xc0,			// END_COLLECTION
	//====================beken============38======================
	0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x0e,                    // USAGE (Vendor Usage 1)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0xBA,      // Report ID
	0x95, 0x1f,  //   REPORT_COUNT ( )
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x09, 0x01,                    //   USAGE (Vendor Usage 1)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

	0x85, 0xBA,      // Report ID
	0x95, 0x1f,  //   REPORT_COUNT ( )
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x09, 0x01,                    //   USAGE (Vendor Usage 1)
	0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	0xC0                           //   end Application Collection};
};

code const hid_mouse_report_descriptor MOUSEHIDREPORTDESC =
{
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    	0x09, 0x02,                    // USAGE (Mouse)
    	0xa1, 0x01,                    // COLLECTION (Application)
//	0x85, 0x02, 			   // Report ID (2)
    	0x09, 0x01,                    //   USAGE (Pointer)
    	0xa1, 0x00,                    //   COLLECTION (Physical)
    	0x05, 0x09,                    //     USAGE_PAGE (Button)
    	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1) 定义成19 00，鼠标按键电脑不响应
    	0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    	0x95, 0x03,                    //     REPORT_COUNT (3)
    	0x75, 0x01,                    //     REPORT_SIZE (1)
    	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    	0x75, 0x05,                    //     REPORT_SIZE (5)
    	0x95, 0x01,                    //     REPORT_COUNT (1)
    	0x81, 0x01,                    //     INPUT (Cnst,Var,Abs)
    	
    	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    	0x09, 0x30,                    //     USAGE (X)
    	0x09, 0x31,                    //     USAGE (Y)
    	0x09, 0x38,                    //     USAGE (Wheel)
  	0x15, 0x81, 			   //	  Logical Minimum (-127)
  	0x25, 0x7F, 			   //	  Logical Maximum (127) 
    	0x75, 0x08,                    //     REPORT_SIZE (8)
    	0x95, 0x03,                    //     REPORT_COUNT (3)    
    	0x81, 0x06,                    //     INPUT (Data,Var,Rel)

	0x09, 0x00,                    //     USAGE ()
	0x95, 0x0C,                    //     REPORT_COUNT (12)	
	0x81, 0x02,                    //     INPUT ()
    	0xc0,                          //   END_COLLECTION
    	0xc0                           // END_COLLECTION
};

code const hid_media_key_report_descriptor MEDIAKEYHIDREPORTDESC =
{
//====================鼠标====75====================================
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x01, 				   // Report ID (1)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x05,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x05,                    //     REPORT_COUNT (5)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x03,                    //     REPORT_SIZE (3)
    0x81, 0x01,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
  	0x16, 0x01, 0xF8,			   //	  Logical Minimum (-2047)
  	0x26, 0xFF, 0x07,			   //	  Logical Maximum (2047) 
    0x75, 0x0C,                    //     REPORT_SIZE (12)
    0x95, 0x02,                    //     REPORT_COUNT (2)    
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)  
	0x05, 0x0c,					   //	  USAGE_PAGE(Consumer Devices)
	0x0a, 0x38,
	0x02,
	0x95, 0x01,					   //     REPORT_COUNT (1)	
	0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                           // END_COLLECTION
//====================电源控制======31==============================
    0x05, 0x01, 	// Usage Page (Generic Desktop),
	0x09, 0x80,	 	// USAGE (3-D Digitizer)
	0xa1, 0x01,	 	// Collection (Application),
	0x85, 0x02, 	// Report ID (2)
	0x05, 0x01, 	// Usage Page (Generic Desktop),
	0x19, 0x81, 	// Usage Minimum (), 
	0x29, 0x83, 	// Usage Maximum (),
	0x15, 0x00, 	// Logical Minimum (0),
	0x25, 0x01, 	// Logical Maximum (1),
	0x95, 0x03, 	// Report Count (3),
	0x75, 0x01, 	// Report Size (1),
	0x81, 0x06, 	// Input (Data,Var,Rel)
	0x95, 0x01, 	// Report Count (1),  
	0x75, 0x05, 	// Report Size (5),	
	0x81, 0x01,		// Input (Const,Ary,Abs)
	0xc0,			// END_COLLECTION

//====================多媒体按键控制=======25========================
	0x05, 0x0c,		 // USAGE_PAGE (Consumer Devices)
	0x09, 0x01,		 // USAGE (Consumer Control)
	0xa1, 0x01,  	 // COLLECTION (Application)
	0x85, 0x03, 	 // Report ID (3)
	0x15, 0x00,		 // LOGICAL_MINIMUM (0)
	0x26, 0x80, 
	0x03, 0x19,  
	0x00, 0x2a, 
	0x80, 0x03,  
	0x75, 0x10, 	 // REPORT_SIZE (0x10)
	0x95, 0x01, 	 // REPORT_COUNT (1)
	0x81, 0x00, 	 // Input (Data,Ary,Abs)
	0xc0, 			 // END_COLLECTION

//====================MCE键盘控制=======26===========================
	0x06, 0xbc, 0xff, // USAGE_PAGE (Vendor Defined Page *)
	0x09, 0x88,   	  // USAGE(?)
	0xa1, 0x01, 	  // Collection (Application),
	0x85, 0x04, 	  // Report ID (4)
	0x19, 0x00, 	  // USAGE_MINIMUM (undefined)
	0x2a, 0xff, 0x00, 
	0x15, 0x00, 	  // Logical Minimum (0),
	0x26, 0xff, 0x00, 
	0x75, 0x08,  	  // REPORT_SIZE (8)
	0x95, 0x01,  	  // REPORT_COUNT (1)
	0x81, 0x00,  	  // Input (Data,Ary,Abs)
	0xc0,  			  // END_COLLECTION

//====================beken============38======================
    0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    0x09, 0x0e,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0xBA,      // Report ID
    0x95, 0x1f,  //   REPORT_COUNT ( )
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

    0x85, 0xBA,      // Report ID
    0x95, 0x1f,  //   REPORT_COUNT ( )
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xC0                           //   end Application Collection};
};

//============================================================
#ifdef	DEV_PHONE
code AudioClass_descriptor_USBPhone USBPHONE_DES =
{
// Config descriptor.
	{
		0x09,                               // Length
		0x02,                               // Type
//		0xC000,                             // Totallength 
		cConfigLen,			// Totallength 
		0x00,
		
		0x03,                               // NumInterfaces
		0x01,                               // bConfigurationValue
		0x00,                               // iConfiguration
		0x80,	//                               // bmAttributes
		0x32                                // MaxPower (in 2mA units)	
	},
// AC interface des.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x00,				// interface NO.
		0x00,				// bAlternatesetting
		0x00,				// bNumendpoint
		0x01,				// Audio interface class.
		0x01,				// Audio control interface subclass.
		0x00,
		0x00
	},
// AC interface header des.
	{
		0x0A,				// Len.
		0x24,				// Type
		0x01,				// Subtype
		0x0001,				// audio class 1.0 version
		0x4600,				// AC interface total lenght
		0x02,				// Number of streaming interface. 
		0x01,				// interface Num of the first audio streaming interface in the collection.
		0x02	// 0x01				// interface Num of the first audio streaming interface in the collection.
	},
// Input terminal des.
	{
		0x0c,				// Len
		0x24,				// Type
		0x02,				// Subtype
		0x01,				// ID
		0x0101,				// Terminal type(USB streaming)
		0x00,
		0x02,				// 
		0x0300,				// Channel config
		0x00,				// Channel name
		0x00
	},
// Feature unit des.
	{
		0x08,				// Len
		0x24,				// Type
		0x06,				// Subtype
		0x05,				// ID
		0x04,				// source ID(Microphone)
		0x01,				// control size
		0x03,				// bmaControls(B0:Mute, B1:Volume)
		0x00
	},
// Output terminal des.
	{
		0x09,				// Len
		0x24,				// Type
		0x03,				// Subtype
		0x02,				// ID
		0x0101,				// Terminal type(USB streaming)
		0x00,
		0x05,				// source ID.
		0x00
	},
// Feature unit des.
	{
		0x0A,				// Len
		0x24,				// Type
		0x06,				// Subtype
		0x06,				// ID
		0x01,				// source ID
		0x01,				// control size
		0x01,				// bmaControls(B0:Mute, B1:Volume)
		0x02,
		0x02,
		0x00
	},
// Output terminal des.
	{
		0x09,				// Len
		0x24,				// Type
		0x03,				// Subtype
		0x03,				// ID
		0x0103,				// Terminal type(Speaker)
		0x00,
		0x06,				// source ID.
		0x00
	},
// Input terminal des.
	{
		0x0c,				// Len
		0x24,				// Type
		0x02,				// Subtype
		0x04,				// ID
		0x0102,				// Terminal type(Microphone)
		0x00,
		0x01,				// Number channel
		0x0000,	//0x0100,				// Channel config
		0x00,				// Channel name
		0x00
	},
// AS interface0 des. Alternating 0.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x01,				// interface NO.
		0x00,				// bAlternatesetting
		0x00,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS interface0 des. Alternating 1.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x01,				// interface NO.
		0x01,				// bAlternatesetting
		0x01,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS class spec interface des.
	{
		0x07,
		0x24,
		0x01,
		0x02,			// The Terminal ID of the Terminal to which the endpoint of this interface is connected.
		0x01,
		0x0100			// PCM
	},
// AS format type des.
	{
		0x0b,
		0x24,			// type
		0x02,			// subtype
		0x01,			// formate type.
		0x01,			// number of channels
		0x02,			// subframe size.
		0x10,	//0x0A,			// bit resolution
		0x01,			// sample frequency type(1 sample frequency)
		0x40,
		0x1f,
		0x00	// 0x1f4000	//001f40	//401f00		// sample frequency(8KHZ)
	},
// Endpoint des.
	{
		0x09,
		0x05,
		0x81,			// in, endpoint ID 1.
		0x05, //0x01, //0x05,			// Asynchronous, Isochronous.
		0x1000, //0x2000,			// 32Bytes
		0x01,			// polling duty 1ms.
		0x00,
		0x00
	},
// AS Endpoint des.
	{
		0x07,
		0x25,
		0x01,			// 
		0x00,			// 
		0x00,			// 
		0x0000
	},

// AS interface1 des. Alternating 0.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x02,				// interface NO.
		0x00,				// bAlternatesetting
		0x00,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS interface1 des. Alternating 1.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x02,				// interface NO.
		0x01,				// bAlternatesetting
		0x01,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS class spec interface des.
	{
		0x07,
		0x24,
		0x01,
		0x01,			// The Terminal ID of the Terminal to which the endpoint of this interface is connected.
		0x01,
		0x0100			// PCM
	},
// AS format type des.
	{
		0x0b,
		0x24,			// type
		0x02,			// subtype
		0x01,			// formate type.
		0x02,			// number of channels
		0x02,			// subframe size.
		0x10,			// bit resolution
		0x01,			// sample frequency type(1 sample frequency)
		0x80,
		0x3e,
		0x00		// 3e8000//003E80	//803E00		// sample frequency(8KHZ)
	},
// Endpoint des.
	{
		0x09,
		0x05,
		0x02,			// out, endpoint ID 2.
		0x0D,			// synchronous, Isochronous.
		0x4000,			// 64Bytes
		0x01,			// polling duty 1ms.
		0x00,
		0x00
	},
// AS Endpoint des.
	{
		0x07,
		0x25,
		0x01,			// 
		0x80,			// Requirement for MaxPacketSize packet 
		0x00,			// 
		0x0000
	}
};
#endif
//============================================================
#ifdef	DEV_MIC
code AudioClass_descritport_MIC MIC_DES =
{
// Config descriptor.
	{
		0x09,                               // Length
		0x02,                               // Type
//		0x6c00,                          // Totallength 
		cConfigLen,			// Totallength 
		0x00,
		
		0x02,	//0x04,	     // NumInterfaces
		0x01,                               // bConfigurationValue
		0x00,                               // iConfiguration
		0x80,	//                               // bmAttributes
		0x32                                // MaxPower (in 2mA units)	
	},
	#if 0
// AC interface des.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x00,				// interface NO.
		0x00,				// bAlternatesetting
		0x00,				// bNumendpoint
		0x01,				// Audio interface class.
		0x01,				// Audio control interface subclass.
		0x00,
		0x00
	},
// AC interface header des.
	{
		0x09,				// Len.
		0x24,				// Type
		0x01,				// Subtype
		0x0001,				// audio class 1.0 version
		0x2600, //0x4600,				// AC interface total lenght
		0x01,				// Number of streaming interface. 
		0x01				// interface Num of the first audio streaming interface in the collection.
//		0x02	// 0x01				// interface Num of the first audio streaming interface in the collection.
	},
// Feature unit des.
	{
		0x09,	//0x08,				// Len
		0x24,				// Type
		0x06,				// Subtype
		0x05,				// ID
		0x04,				// source ID(Microphone)
		0x01,				// control size
		0x03,				// bmaControls(B0:Mute, B1:Volume)
		0x00,
		0x00
	},
// Output terminal des.
	{
		0x09,				// Len
		0x24,				// Type
		0x03,				// Subtype
		0x02,				// ID
		0x0101,				// Terminal type(USB streaming)
		0x00,
		0x05,				// source ID.
		0x00
	},
// Input terminal des.
	{
		0x0c,				// Len
		0x24,				// Type
		0x02,				// Subtype
		0x04,				// ID
		0x0102,				// Terminal type(Microphone)
		0x00,
		0x01,				// Number channel
		0x0000,	//0x0100,				// Channel config
		0x00,				// Channel name
		0x00
	},
// AS interface0 des. Alternating 0.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x01,				// interface NO.
		0x00,				// bAlternatesetting
		0x00,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS interface0 des. Alternating 1.
	{
		0x09,				// Len.
		0x04,				// Type.
		0x01,				// interface NO.
		0x01,				// bAlternatesetting
		0x01,				// bNumendpoint
		0x01,				// Audio interface class.
		0x02,				// Audio streaming interface subclass.
		0x00,
		0x00
	},
// AS class spec interface des.
	{
		0x07,
		0x24,
		0x01,
		0x02,			// The Terminal ID of the Terminal to which the endpoint of this interface is connected.
		0x01,
		0x0100			// PCM
	},
// AS format type des.
	{
		0x0b,
		0x24,			// type
		0x02,			// subtype
		0x01,			// formate type.
		0x01,			// number of channels
		0x02,			// subframe size.
		0x10,	//0x0A,			// bit resolution
		0x01,			// sample frequency type(1 sample frequency)
#ifdef	SAMPLERATE_8KHZ
		0x40,
		0x1f,
		0x00		//0x001f40			// sample frequency(8KHZ)
#endif
#ifdef	SAMPLERATE_12KHZ
		0xE0,
		0x2E,
		0x00	// 0x002EE0 sample frequency(12KHZ)
#endif
#ifdef	SAMPLERATE_16KHZ
		0x80,
		0x3E,
		0x00	// 0x003E80 sample frequency(16KHZ)
#endif
	},
// Standand AS isochrounous audio data Endpoint des.
	{
		0x09,
		0x05,
		0x81,			// in, endpoint ID 1.
// B1~B0: transfer type, 01: isochronous;
// B3~B2: Synchronization Type, 00:no sync, 01:Asynchronous, 10:Adaptive, 11:Synchronous;
// B5~B4: usage type: 00:data endpoint, 01:feedback endpoint;
		0x05,	//0x01, //0x01, //0x05,			// Asynchronous, Isochronous. 
		EP1_PACKET_SIZE_LE,	//0x2000,	//0x1000, // 16Bytes //0x2000,			// 32Bytes
		0x01,			// polling duty 1ms.
		0x00,
		0x00
	},
// Class spec AS isochrounous audio data Endpoint des(isochronous).
	{
		0x07,
		0x25,
		0x01,			// EP_GENERAL descriptor subtype
		0x00,			// 
		0x00,			// 
		0x0000
	},
	#endif
// HID interface descriptor(keyboard).
	{ 
		0x09,                               // bLength
		0x04,                               // bDescriptorType
		0x03,	//0x02,             // interface NO.
		0x00,                               // bAlternateSetting
		0x01,                               // bNumEndpoints
		0x03,                               // bInterfaceClass (3 = HID)
		0x01,                               // bInterfaceSubClass
		0x01,                               // bInterfaceProcotol(keyboard)
		0x00                                // iInterface
	},
// HID class descriptor.
	{ 
		0x09,                               // bLength
		0x21,                               // bDescriptorType
		0x0101,                            // bcdHID
		0x00,                               // bCountryCode
		0x01,                               // bNumDescriptors
		0x22,                               // bDescriptorType
		HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE_LE  // wItemLength (tot. len. of report descriptor)
	},
 
// Endpoint descriptor(interrupt in).
	{ 
		0x07,                               // bLength
		0x05,                               // bDescriptorType
		0x83,                               // bEndpointAddress
		0x03,                               // bmAttributes
		EP3_PACKET_SIZE_LE,                 // MaxPacketSize (LITTLE ENDIAN)
		0x0a	// 0x01	//10                                  // bInterval
	},

// HID interface descriptor(Mouse).
	{ 
		0x09,                               // bLength
		0x04,                               // bDescriptorType
		0x04,	//0x02,                               // interface NO.
		0x00,                               // bAlternateSetting
		0x01,                               // bNumEndpoints
		0x03,                               // bInterfaceClass (3 = HID)
		0x01,                               // bInterfaceSubClass
		0x02,                               // bInterfaceProcotol(Mouse)
		0x00                                // iInterface
	},
// HID class descriptor.
	{ 
		0x09,                               // bLength
		0x21,                               // bDescriptorType
		0x0101,                            // bcdHID
		0x00,                               // bCountryCode
		0x01,                               // bNumDescriptors
		0x22,                               // bDescriptorType
		HID_MOUSE_REPORT_DESCRIPTOR_SIZE_LE  // wItemLength (tot. len. of report descriptor)
	},
 
// Endpoint descriptor(interrupt in).
	{ 
		0x07,                               // bLength
		0x05,                               // bDescriptorType
		0x84,                               // bEndpointAddress
		0x03,                               // bmAttributes
		EP4_PACKET_SIZE_LE,                 // MaxPacketSize (LITTLE ENDIAN)
		0x0a	// 0x01	//10                                  // bInterval
	}
};
#endif
//============================================================

code const unsigned char String0Desc [STR0LEN] =
{
   STR0LEN, 0x03, 0x09, 0x04
}; 
// End of String0Desc

//#define STR1LEN sizeof ("2.4G") * 2

code const unsigned char String1Desc [STR1LEN] =
{
   STR1LEN, 0x03,
#if	0
	'K', 0,
	'o', 0,
	'n', 0,
	'k', 0,
	'a', 0,
	'U', 0,
	's', 0,
	'b', 0,
	'T', 0,
	'o', 0,
	'u', 0,
	'c', 0,
	'h', 0,
	'P', 0,
	'a', 0,
	'd', 0
#endif
	'T', 0,
	'm', 0,
	'a', 0,
	'l', 0,
	'l', 0,
	'.', 0,
	'c', 0,
	'0', 0,
	'm', 0
}; 
// End of String1Desc

//#define STR2LEN sizeof ("2.4G Wireless Microphone") * 2

code const unsigned char String2Desc [STR2LEN] =
{
   STR2LEN, 0x03,
   '2', 0,
   '.', 0,
   '4', 0,
   'G', 0,
   ' ', 0,
   'W', 0,
   'i', 0,
   'r', 0,
   'e', 0,
   'l', 0,
   'e', 0,
   's', 0,
   's', 0,
   ' ', 0,
	'A', 0,
	'i', 0,
	'r', 0,
	' ', 0,
	'M', 0,
	'o', 0,
	'u', 0,
	's', 0,
	'e', 0
}; // End of String2Desc
code const unsigned char String3Desc[STR3LEN] = {
	STR3LEN, 0x03,
	'B', 0,	// 'K', 0,
	'e', 0,	// 'o', 0,
	'l', 0,
	'o', 0,
	'n', 0,
	' ', 0,
	'S', 0,
	'm', 0,
	'a', 0,
	'r', 0,
	't', 0,
	'M', 0,
	'o', 0,
	'u', 0,
	's', 0,
	'e', 0
};

unsigned char *  STRINGDESCTABLE [] =
{
   String0Desc,
   String1Desc,
   String2Desc,
   String3Desc
};

xdata setup_buffer setup; 

/***********************************************************
						end file
***********************************************************/
