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
			2011/03/01  			0.1 			 build this moudle 
***********************************************************/

#ifndef _USB_DESCRIPTOR_H_
#define _USB_DESCRIPTOR_H_

#define	cConfigLen	0x3b	//0x9f	// 0x86+25 // 0x86	//0x85	//0x6c

typedef /*code*/ struct
{
   unsigned char bLength;              // Size of this Descriptor in Bytes
   unsigned char bDescriptorType;      // Descriptor Type (=1)
   WORD bcdUSB;                        // USB Spec Release Number in BCD
   unsigned char bDeviceClass;         // Device Class Code
   unsigned char bDeviceSubClass;      // Device Subclass Code
   unsigned char bDeviceProtocol;      // Device Protocol Code
   unsigned char bMaxPacketSize0;      // Maximum Packet Size for EP0
   WORD idVendor;                      // Vendor ID
   WORD idProduct;                     // Product ID
   WORD bcdDevice;                     // Device Release Number in BCD
   unsigned char iManufacturer;        // Index of String Desc for Manufacturer
   unsigned char iProduct;             // Index of String Desc for Product
   unsigned char iSerialNumber;        // Index of String Desc for SerNo
   unsigned char bNumConfigurations;   // Number of possible Configurations
} device_descriptor;                   // End of Device Descriptor Type

//--------------------------------------------------
// Standard Configuration Descriptor Type Definition
//--------------------------------------------------
typedef /*code*/ struct
{
   unsigned char bLength;              // Size of this Descriptor in Bytes
   unsigned char bDescriptorType;      // Descriptor Type (=2)
//   WORD wTotalLength;                  // Total Length of Data for this Conf
   unsigned char uLensL;
   unsigned char uLensH;
   
   unsigned char bNumInterfaces;       // No of Interfaces supported by this
                                       // Conf
   unsigned char bConfigurationValue;  // Designator Value for *this*
                                       // Configuration
   unsigned char iConfiguration;       // Index of String Desc for this Conf
   unsigned char bmAttributes;         // Configuration Characteristics (see below)
   unsigned char bMaxPower;            // Max. Power Consumption in this
                                       // Conf (*2mA)
} configuration_descriptor;            // End of Configuration Descriptor Type

//----------------------------------------------
// Standard Interface Descriptor Type Definition
//----------------------------------------------
typedef /*code*/ struct
{
   unsigned char bLength;              // Size of this Descriptor in Bytes
   unsigned char bDescriptorType;      // Descriptor Type (=4)
   unsigned char bInterfaceNumber;     // Number of *this* Interface (0..)
   unsigned char bAlternateSetting;    // Alternative for this Interface (if any)
   unsigned char bNumEndpoints;        // No of EPs used by this IF (excl. EP0)
   unsigned char bInterfaceClass;      // Interface Class Code
   unsigned char bInterfaceSubClass;   // Interface Subclass Code
   unsigned char bInterfaceProtocol;   // Interface Protocol Code
   unsigned char iInterface;           // Index of String Desc for this Interface
} interface_descriptor;                // End of Interface Descriptor Type

//------------------------------------------
// Standard Class Descriptor Type Definition
//------------------------------------------
typedef /*code */struct
{
   unsigned char bLength;               // Size of this Descriptor in Bytes (=9)
   unsigned char bDescriptorType;       // Descriptor Type (HID=0x21)
   WORD bcdHID;                         // HID Class Specification
                                        // release number (=1.01)
   unsigned char bCountryCode;          // Localized country code
   unsigned char bNumDescriptors;       // Number of class descriptors to follow
   unsigned char bReportDescriptorType; // Report descriptor type (HID=0x22)
   unsigned int wItemLength;            // Total length of report descriptor table
} class_descriptor;                     // End of Class Descriptor Type

//---------------------------------------------
// Standard Endpoint Descriptor Type Definition
//---------------------------------------------
typedef /*code*/ struct
{
   unsigned char bLength;              // Size of this Descriptor in Bytes
   unsigned char bDescriptorType;      // Descriptor Type (=5)
   unsigned char bEndpointAddress;     // Endpoint Address (Number + Direction)
   unsigned char bmAttributes;         // Endpoint Attributes (Transfer Type)
   WORD wMaxPacketSize;                // Max. Endpoint Packet Size
   unsigned char bInterval;            // Polling Interval (Interrupt) ms
} endpoint_descriptor;                 // End of Endpoint Descriptor Type
//================================================================
// USB Audio class descriptor. 
//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bInterfaceNO;
	unsigned char bAlternateSetting;
	unsigned char bNumEndpoint;
	unsigned char bInterfaceClass;			// Audio interface class.
	unsigned char bInterfaceSubClass;		// Audio streaming subclass code.
	unsigned char bInterfaceProtocol;
	unsigned char bInterface;				// Index of a string descriptor that describes this interface.
}StandardInterface_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef	struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;
	WORD wBCDADC;						// Revision of class spec.
	WORD wTotalLen;					// Total size of audio control interface. descriptor.
	unsigned char bInCollection;			// Number of streaming interface. 
	unsigned char baInterfaceNr1;			// interface Num of the first audio streaming interface in the collection.
}ACInterfaceHead_descriptor_1;
//---------------------------------------------
//---------------------------------------------
typedef	struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;
	WORD wBCDADC;						// Revision of class spec.
	WORD wTotalLen;					// Total size of audio control interface. descriptor.
	unsigned char bInCollection;			// Number of streaming interface. 
	unsigned char baInterfaceNr1;			// interface Num of the first audio streaming interface in the collection.
	unsigned char baInterfaceNr2;			// interface Num of the second audio streaming interface in the collection.
}ACInterfaceHead_descriptor_2;
//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// Input terminal subtype.
	unsigned char bTerminalID;			// ID of this terminal.
	WORD wTerminalType;
	unsigned char bAssocTerminal;			// identifying the Output Terminal to which this Input Terminal is associated.
	unsigned char bNrChannels;			// Channel Num.
	WORD wChannelConfig;
	unsigned char bChannelNames;
	unsigned char bTerminal;				// Index of string descriptor , describing the terminal.
}InputTerminal_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// Output terminal subtype.
	unsigned char bTerminalID;			// ID of this terminal.
	WORD wTerminalType;
	unsigned char bAssocTerminal;			// identifying the Input Terminal to which this Output Terminal is associated.
	unsigned char bSourceID;				// ID of the unit or terminal to which this feature unit is connected
	unsigned char bTerminal;				// Index of string descriptor , describing the terminal.
}OutputTerminal_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// Feature unit subtype.
	unsigned char bUnitID;					// ID of this unit.
	unsigned char bSourceID;
	unsigned char bControlSize;			// size in bytes of an element of the bmaControls(), array n. 该值决定bmaControlsN的长度.
	unsigned char bmaControls0;			// A bit set to 1 indicates that the mentioned Control is supported for master channel 0
	unsigned char bmaControls1;
	unsigned char bFeature;				// Index of string descriptor , describing the unit.
}FeatureUnit1CH_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// Feature unit subtype.
	unsigned char bUnitID;					// ID of this unit.
	unsigned char bSourceID;
	unsigned char bControlSize;			// size in bytes of an element of the bmaControls(), array n. 该值决定bmaControlsN的长度.
	unsigned char bmaControls0;			// A bit set to 1 indicates that the mentioned Control is supported for master channel 0
	unsigned char bmaControls1;
	unsigned char bmaControls2;
	unsigned char bFeature;				// Index of string descriptor , describing the unit.
}FeatureUnit2CH_descriptor;
//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// AS_GENERAL descriptor subtype.
	unsigned char bTerminalLink;			// The Terminal ID of the Terminal to which the endpoint of this interface is connected.
	unsigned char bDelay;
	WORD wFormatTag;					// Audio data format that has to be used to communicate with this interface.
}ClassSpecASInterface_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// Format type subtype.
	unsigned char bFormatType;
	unsigned char bNumChannel;
	unsigned char bSubFrameSize;
	unsigned char bBitReSolution;
	unsigned char bSamFreqType;
	unsigned char tSamFreq[3];
}ASFormatType_descriptor;
//---------------------------------------------
//---------------------------------------------

typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;				// Endpoint descriptor.
	unsigned char bEndpointAddress;		// Endpoint address..
	unsigned char bmAttributes;			// B3~2:Sync type. B1~0: Transfer type.
	WORD wMaxPacketSize;
	unsigned char bInterval;				// Interval for polling endpoint for data transfer expressed in ms(must set to 1).
	unsigned char bRefresh;
	unsigned char bSyncAddress;			// The address of the endpoint used to communicate sync information if required by this endpoint.
}StandardEndpoint_descriptor;

//---------------------------------------------
//---------------------------------------------
typedef struct
{
	unsigned char bLen;
	unsigned char bDesType;
	unsigned char bDesSubType;			// AS_GENERAL descriptor subtype.
	unsigned char bmAttributes;
	unsigned char bLockDelayUnits;
	WORD wLockDelay;
}ClassSpecEndpoint_descriptor;
//================================================================
//---------------------------------------------
//---------------------------------------------
#ifdef	DEV_PHONE
typedef struct
{
	configuration_descriptor		USBPhoneConfig_des;
// Audio control interface.
	StandardInterface_descriptor	ACSubClassInterface_des;	// Audio control interface subclass.
	ACInterfaceHead_descriptor_2	ACInterfaceHead_des;
	InputTerminal_descriptor	ACInputTerminalUS_des;		// USB stream input terminal.
	FeatureUnit1CH_descriptor		ACFeatureUnitMIC_des;		// the Feature unit connect to MIC
	OutputTerminal_descriptor	ACOutputTerminalUS_des;	// USB stream output terminal.
	FeatureUnit2CH_descriptor		ACFeqtureUnitOutputUS_des;		// the feature unit connect to output terminal USB stream.
	OutputTerminal_descriptor	ACOutputTerminalSPK_des;	// speak output terminal.
	InputTerminal_descriptor	ACInputTermainalMIC_des;	// MIC input terminal.
// Audio streaming interface.
	StandardInterface_descriptor	ASSubClassInterface1Alter0_des;		// 0 Bandwidth
	StandardInterface_descriptor	ASSubClassInterface1Alter1_des;
	ClassSpecASInterface_descriptor	ClassSpecASInterface1_des;
	ASFormatType_descriptor		AS1FormatType_des;
	StandardEndpoint_descriptor		Endpoint1_des;
	ClassSpecEndpoint_descriptor	ASClassSpecEndpoint1_des;
// Aduio streaming interface.
	StandardInterface_descriptor	ASSubClassInterface2Alter0_des;		// 0 Bandwidth
	StandardInterface_descriptor	ASSubClassInterface2Alter1_des;
	ClassSpecASInterface_descriptor	ClassSpecASInterface2_des;
	ASFormatType_descriptor		AS2FormatType_des;
	StandardEndpoint_descriptor		Endpoint2_des;
	ClassSpecEndpoint_descriptor	ASClassSpecEndpoint2_des;
}AudioClass_descriptor_USBPhone;
#endif
//================================================
#ifdef	DEV_MIC
typedef struct{
	configuration_descriptor MICConfig_des;
#if 0
// Audio control interface.
	StandardInterface_descriptor ACSubClassInterface_des;	// Audio control interface subclass.
	ACInterfaceHead_descriptor_1 ACInterfaceHead_des;
	FeatureUnit1CH_descriptor ACFeatureUnitMIC_des;		// the Feature unit connect to MIC
	OutputTerminal_descriptor ACOutputTerminalUS_des;	// USB stream output terminal.
	InputTerminal_descriptor	ACInputTermainalMIC_des;	// MIC input terminal.
	
// Audio streaming interface.
	StandardInterface_descriptor	ASSubClassInterface1Alter0_des;		// 0 Bandwidth
	StandardInterface_descriptor	ASSubClassInterface1Alter1_des;
	ClassSpecASInterface_descriptor ClassSpecASInterface1_des;
	ASFormatType_descriptor AS1FormatType_des;
	StandardEndpoint_descriptor Endpoint1_des;
	ClassSpecEndpoint_descriptor	ASClassSpecEndpoint1_des;
#endif
// HID class interface.
	StandardInterface_descriptor KBInterface_des;
	class_descriptor KB_des;
	endpoint_descriptor KB_Endpoint_des;

	StandardInterface_descriptor MSInterface_des;
	class_descriptor MS_des;
	endpoint_descriptor MS_Endpoint_des;
}AudioClass_descritport_MIC;
#endif
//================================================
//---------------------------------------------
// HID Configuration Descriptor Type Definition
//---------------------------------------------
// From "USB Device Class Definition for Human Interface Devices (HID)".
// Section 7.1:
// "When a Get_Descriptor(Configuration) request is issued,
// it returns the Configuration descriptor, all Interface descriptors,
// all Endpoint descriptors, and the HID descriptor for each interface."
typedef  struct {
	configuration_descriptor 	hid_configuration_descriptor;
	interface_descriptor 		hid_keyboard_interface_descriptor;
	class_descriptor 			hid_keyboard_descriptor;
	endpoint_descriptor 		hid_keyboard_endpoint_in_descriptor;
	interface_descriptor 		hid_media_key_interface_descriptor;
	class_descriptor 			hid_media_key_descriptor;
	endpoint_descriptor 		hid_media_key_endpoint_in_descriptor;
}hid_configuration_descriptor_all;


#define HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE 0x0085	// 0x00c1	// 0x00eb	// 0x00e0	// 0x00e2	//0x00D8	//0x0029	//0x003f
#define HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE_LE 0x8500	// 0xc100	//0xeb00	// 0xe000	// 0xe200	//0xD800	//0x2900	//0x3f00

#define HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE 0x00C3
#define HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE_LE 0xC300

#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE 0x003a		// 0x00C3
#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE_LE 0x3a00	// 0xC300

typedef code unsigned char hid_keyboard_report_descriptor[HID_KEYBOARD_REPORT_DESCRIPTOR_SIZE];
typedef code unsigned char hid_mouse_report_descriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE];
typedef code unsigned char hid_media_key_report_descriptor[ HID_MEDIA_KEY_REPORT_DESCRIPTOR_SIZE];

//-----------------------------
// SETUP Packet Type Definition
//-----------------------------
typedef struct
{
/*
B7: DataTransfer Direction, 0:Host to Device 1:Device to Host.
B6~5: Type, 0: Standard, 1: Class, 2: Vendor, 3: Reserved.
B4~0: Recipient, 0: Device, 1: Interface, 2: endpoint, 3: Other, 4:~31: Reserved.
*/
   unsigned char bmRequestType;        // Request recipient, type, and dir.
   unsigned char bRequest;             // Specific standard request number
   WORD wValue;                        // varies according to request
   WORD wIndex;                        // varies according to request
   WORD wLength;                       // Number of bytes to transfer, USB format: Low byte, High byte.
} setup_buffer;                        // End of SETUP Packet Type

extern xdata setup_buffer setup; 

extern /*code const*/ device_descriptor DEVICEDESC;
extern code const hid_configuration_descriptor_all HIDCONFIGDESC;
extern code const hid_keyboard_report_descriptor KEYBOARDHIDREPORTDESC;
extern code const hid_mouse_report_descriptor MOUSEHIDREPORTDESC;
extern code const hid_media_key_report_descriptor MEDIAKEYHIDREPORTDESC;

#ifdef	DEV_PHONE
extern code AudioClass_descriptor_USBPhone USBPHONE_DES;
#endif

#ifdef	DEV_MIC
extern code  AudioClass_descritport_MIC MIC_DES;
#endif

#define STR0LEN 4
#define STR1LEN sizeof ("Tmall.com")*2	//("KonkaUsbTouchPad") * 2
#define STR2LEN sizeof ("2.4G Wireless Air Mouse") * 2
#define STR3LEN sizeof ("Belon SmartMouse")*2		//("KonkaUsbTouchPad") * 2

extern code const unsigned char String0Desc [STR0LEN];
extern code const unsigned char String1Desc [STR1LEN];
extern code const unsigned char String2Desc [STR2LEN];
extern code const unsigned char String3Desc [STR3LEN];
extern unsigned char *  STRINGDESCTABLE [];


#ifdef	DEV_PHONE
#define ConfigDesc	         (USBPHONE_DES.USBPhoneConfig_des)//(HIDCONFIGDESC.hid_configuration_descriptor)
#endif

#ifdef	DEV_MIC
#define ConfigDesc	         (MIC_DES.MICConfig_des)
#endif

#define KeyInterfaceDesc	   (MIC_DES.KBInterface_des)	//(HIDCONFIGDESC.hid_keyboard_interface_descriptor)
#define KeyHidDesc	         (MIC_DES.KB_des)	//(HIDCONFIGDESC.hid_keyboard_descriptor)
#define KeyEndpiontDesc	     (MIC_DES.KB_Endpoint_des) //(HIDCONFIGDESC.hid_keyboard_endpoint_in_descriptor)

#define MouseInterfaceDesc	   (MIC_DES.MSInterface_des)
#define MouseHidDesc			(MIC_DES.MS_des)
#define MouseEndpiontDesc	     (MIC_DES.MS_Endpoint_des) 

#define MediaKeyInterfaceDesc (HIDCONFIGDESC.hid_media_key_interface_descriptor)
#define MediaKeyHidDesc	      (HIDCONFIGDESC.hid_media_key_descriptor)
#define KeyEndpiontInDesc	  (HIDCONFIGDESC.hid_media_key_endpoint_in_descriptor)



#endif


/***********************************************************
						end file
***********************************************************/
