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
			  2011/03/01  		0.1  		build this moudle 
***********************************************************/

#include "Headfile\includes.h"

#ifdef	CHIP_BK2535
FLASH_DATA XDATA Flash;
#endif
//-------------------------------------------------------
//Function: 
//Desc	: 两个缓存比较，相同返回 1 不相同返回0
//Input	:
//Output: 
//Return: 
//Others: 
//Author: joe  
//Date	: 2011/03/01
//-------------------------------------------------------
BOOL buf_compare(BYTE *buf1, BYTE *buf2,BYTE len)
{
	BYTE i,re = 1;
	for(i = 0; i<len;i++)
	{
		if(buf1[i] != buf2[i])
		{
			re = 0;
			break;
		}
	}
	return re;
}

//-------------------------------------------------------
//Function: 
//Desc	: 判断buf是否为0x00
//Input	:
//Output: 
//Return: 
//Others: 
//Author: joe  
//Date	: 2011/03/01
//-------------------------------------------------------
BOOL buf_is_null(BYTE *buf,BYTE len)
{
	BYTE i,re = 1;
	for(i = 0; i<len;i++)
	{
		if(buf[i] != 0x00)
		{
			re = 0;
			break;
		}
	}
	return re;
}
//-------------------------------------------------------
//Function: 
//Desc	:
//Input	:
//Output: 
//Return: 
//Others: 
//Author: joe  
//Date	: 2011/03/01
//-------------------------------------------------------
void buf_copy(BYTE *form, BYTE *to, BYTE len)
{
	BYTE i;
	for(i = 0; i<len; i++)
	{
		to[i] = form[i];
	}
}
//-------------------------------------------------------
//-------------------------------------------------------
#ifdef	CHIP_BK2535
void Sys_FlashEraseAll(void)
{
    UINT8 i, count;

    for(count = 0; count < 3; count++)
    {
        FlashEraseAll();
        for(i = 0; i < cMTP_LEN; i++)
        {
            if(FlashReadByte(i) != 0xff)
                break;
        }
        if(i >= cMTP_LEN)
            break;
    }
}

/*! \fn void application_flash_write_all(void)
    \brief The application interface that system reads the configuration in mtp to fill them into memory of running.

    \param void
    \return void
*/
void Sys_FlashWriteAll(void)
{
	if(Flash.flash_need_write)
	{
		Flash.flash_need_write = 0;
		mtp_unlock_set();
		Sys_FlashEraseAll();
		mtp_unlock_clr();
		FlashWriteBuffer(0, &Flash.mtp_pool[0], cMTP_LEN);
	}
}

/*! \fn BOOL application_flash_flag_read(UINT8 *mtp_data)
    \brief The application interface of system is whether configured before in mtp.

    There are 3 pieces of configuration flag. So it will read them and find the same two to overwrite the different one.
    \param mtp_data - used to save the flag, no less than 3 bytes 
    \return TRUE -configured before, FALSE - NOT configured before
*/
BOOL Sys_flash_dongle_flag_read(void)
{
    BOOL flag_paged = FALSE;

	if((Flash.mtp_pool[MTP_STATUS_ADDR1] == MTP_STORY_FLAG) || (Flash.mtp_pool[MTP_STATUS_ADDR2] == MTP_STORY_FLAG) || (Flash.mtp_pool[MTP_STATUS_ADDR3] == MTP_STORY_FLAG))
	{
		flag_paged = TRUE;
		//flag_usb_page_software_opened
		Flash.mtp_pool[MTP_STATUS_ADDR1] = MTP_STORY_FLAG;
		Flash.mtp_pool[MTP_STATUS_ADDR2] = MTP_STORY_FLAG;
		Flash.mtp_pool[MTP_STATUS_ADDR3] = MTP_STORY_FLAG;


		if(Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] == Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1])           // 1 2 same
		{
			if(Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] != Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2])       // 1 3 different
			{
				Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2] = Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];
				Flash.flash_need_write = 1;
			}
		}
		else if(Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] == Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2])   // 1 2 different, 1 3 same
		{
			Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1] = Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];
			Flash.flash_need_write = 1;
		}
		else if(Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1] == Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2])  // 1 2 different, 1 3 different, 2 3 same
		{
			Flash.mtp_pool[MTP_RECORD_FLAG_ADDR] = Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1];
			Flash.flash_need_write = 1;
		}
	}

	system.mtp_record.mtp[0] = ~Flash.mtp_pool[MTP_RECORD_FLAG_ADDR];
	system.mtp_record.mtp[1] = ~Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR1 + 1];
	system.mtp_record.mtp[2] = ~Flash.mtp_pool[MTP_02_COPY_FLAG_ADDR2 + 2];
    return flag_paged;
}

/*! \fn void application_flash_rf_address_read(UINT8 type)
    \brief The application interface of rf address reading stored in mtp.

    There are 3 pieces for each rf address, including mouse's and keyboard's. So it will read them and find the same two to overwrite the different one.
    \param type - MOUSE/KEYBOARD 
    \return void
*/
void Sys_flash_dongle_rf_address_read(UINT8 type)
{
    UINT8 *id_addr1, *id_addr2, *id_addr3, *rx_addr;

    if(type == MOUSE)
    {
        id_addr1 = &Flash.mtp_pool[RX0_ID_ADDR];
        id_addr2 = &Flash.mtp_pool[RX0_ID_COPY1_ADDR];
        id_addr3 = &Flash.mtp_pool[RX0_ID_COPY2_ADDR];
        rx_addr = RX0_Address;
    }
    else
    {
        id_addr1 = &Flash.mtp_pool[RX1_ID_ADDR];
        id_addr2 = &Flash.mtp_pool[RX1_ID_COPY1_ADDR];
        id_addr3 = &Flash.mtp_pool[RX1_ID_COPY2_ADDR];
        rx_addr = RX1_Address;
    }
    
    if(buf_compare(id_addr1, id_addr2, 5))              // 1 2 same
    {
        if(!buf_compare(id_addr2, id_addr3, 5))           // 1 2 same, 2 3 different
        {
            buf_copy(id_addr1, id_addr3, 5);          // 1->3
            Flash.flash_need_write = 1;
        }
    }
    else if(buf_compare(id_addr1,id_addr3, 5))          // 1 2 different, 1 3 same
    {
        buf_copy(id_addr1, id_addr2, 5);              // 1->2
        Flash.flash_need_write = 1;
    }
    else if(buf_compare(id_addr2, id_addr3, 5))         // 1 2 different, 1 3 different, 2 3 same
    {
        buf_copy(id_addr2, id_addr1, 5);              // 2->1
        Flash.flash_need_write = 1;
    }
    buf_copy(id_addr1, rx_addr, 5);
}


/*! \fn void application_flash_record_read(void)
    \brief The application interface that system reads the configuration in mtp to fill them into memory of running.

    \param void
    \return void
*/
void Sys_flash_dongle_record_read(void)
{
//	UINT8 i;
	BYTE temp[3];
	if(system.mtp_record.mtp_flag.vid_pid)      
	{
		buf_copy(&Flash.mtp_pool[VID_PID_ADDR], &system.vid_pid, VID_PID_LEN);
		DEVICEDESC.idVendor.c[0] = system.vid_pid[0];
		DEVICEDESC.idVendor.c[1] = system.vid_pid[1];
		DEVICEDESC.idProduct.c[0] = system.vid_pid[2];
		DEVICEDESC.idProduct.c[1] = system.vid_pid[3];
	}
	if(system.mtp_record.mtp_flag.usb_string)
	{
		buf_copy(&Flash.mtp_pool[USB_STRING_ADDR], FIFO_data, USB_STRING_LEN);
		temp[1] = 2;
		for(temp[0] = 0; temp[0] < USB_STRING_LEN; temp[0] = temp[0]+1)
		{
			if(FIFO_data[temp[0]] == 0x00)
			{
				break;
			}
			USB_STRING[temp[1] + temp[0]] = FIFO_data[temp[0]];
			USB_STRING[temp[1] + 1 + temp[0]] = 0x00;
			temp[1] = temp[0]+3;
		}
		USB_STRING[0] = (temp[0] << 1) + 2; //strlen * 2 + 2
		USB_STRING[1] = 0x03;
		STRINGDESCTABLE[2] = USB_STRING;   // 字符串TABLE指向设定字符串
	}
 	
    //mouse
	system.mouse_config.auto_down = system.mtp_record.mtp_flag.ms_au_down;

	if(system.mtp_record.mtp_flag.ms_type)          
		system.mouse_config.mouse_type = Flash.mtp_pool[MS_TYPE_ADDR];
	if(system.mtp_record.mtp_flag.mouse_bind) 
	{
		Sys_flash_dongle_rf_address_read(MOUSE);
	}

}

//-------------------------------------------------------
//-------------------------------------------------------
void system_read_MTPrecord(void)
{
	FlashReadBuffer(0, &Flash.mtp_pool[0], cMTP_LEN);
	if(Sys_flash_dongle_flag_read())
            Sys_flash_dongle_record_read();

	Sys_FlashWriteAll();
}
#endif
