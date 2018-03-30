/********************************************************************************

 **** Copyright (C), 2017, Shenzhen Pay Full Science&Technology Co.,Ltd.                ****

 ********************************************************************************
 * File Name     : usb_endp.c
 * Author        : surge
 * Date          : 2017-11-20
 * Description   : usb data process 
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2017-11-20
 *   Author      : surge
 *   Modification: Created file

*************************************************************************************************************/


#include "usb_endp.h"



#define USBMAXBUFFSIZE 1024

__IO unsigned char USBRecvBuf[USBMAXBUFFSIZE] = {0};
__IO unsigned int USBRecvTop = 0, USBRecvEnd = 0;
__IO char gUsbRespFlag = DISABLE; 

extern unsigned int g1msTimer6;

void UsbSetRespFlag(char flag)
{
	if(flag == DISABLE)
	{
		gUsbRespFlag = DISABLE;
	}
	else
	{
		gUsbRespFlag = ENABLE;
	}
}


char UsbCheckBuff(char *ExpectString)
{
	char *p = NULL;
	p = strstr((const char *)USBRecvBuf, ExpectString);
    DBG_S("%s usbrecvbuf = %s\t,expectstring = %s\r\n",__func__, USBRecvBuf,ExpectString);
	
	if(p)
	{
	 	return 1;
	}
	else
	{
	 	return 0;
	}
}

int UsbReadTo(unsigned char *Buff, unsigned int BuffSize, unsigned char *EndString)
{
	unsigned int RecvLen = 0;
	unsigned char tmp[1] = {0};
	unsigned char *p1 = NULL;
	unsigned char *p2 = NULL;
	unsigned int BytesToBeRead = 0;
	unsigned int TempRecvTop = USBRecvTop;
	
	p1 = (unsigned char *)(USBRecvBuf + TempRecvTop);
	if(p1 == NULL)
	{
		return -1;
	}
	
	p2 = (unsigned char *)strstr((const char *)p1, (const char *)EndString);
	if(p2 == NULL)
	{
		return -2;
	}
	
	p2 += strlen((const char *)EndString);
	
	BytesToBeRead = p2 - p1;
	DBG_S("%s : BytesToBeRead is %d\r\n", __func__, BytesToBeRead);
	
	while(BytesToBeRead)
	{
		if (UsbRecvOne (tmp) == 1)
		{
			Buff[RecvLen] = tmp[0];
			if(RecvLen+1 < BuffSize)
			{
				RecvLen++;
				BytesToBeRead--;
			}
		}
	}
	DBG_S("%s : RecvLen is %d\r\n", __func__, RecvLen);
	return RecvLen;	
}

unsigned char CalcSum(unsigned char *buff, unsigned int len)
{
	unsigned int i = 0;
	unsigned char sum = 0;

	for(i=0; i<len; i++)
	{
		sum ^= buff[i];		
	}

	return sum;
}

/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_OUT_Callback(unsigned char *RecvBuff)
{
	unsigned int i = 0;
	unsigned int len = 0;
	unsigned char sum = 0;
	unsigned char respbuff[64] = {0};

	//RecvBuff
	//[0]    [1]    [2]    [3]    ...    [62]    [63]
	//01     len     d0    d1             d60     sum

	
	len = RecvBuff[1];
	sum = CalcSum((unsigned char *)RecvBuff, 63);

	if(RecvBuff[63] != sum)
	{	
		if (gUsbRespFlag == ENABLE)
		{	 
			respbuff[0] = 0x05;
			respbuff[1] = 1;
			respbuff[2] = 0xAA;
			respbuff[63] = 0xAE;
				
      usbd_ep_tx (&usb_device_dev, CUSTOMHID_IN_EP, (uint8_t *)respbuff, 64);
			prev_receive_complete = 0;
		}
		
		return ;
	}

    //从第3位开始要去掉包头，因为长度是数据长度， 所以要加上01和长度，再去掉包尾和CRC
	//for(i=2+1; i<len+2-2; i++)
	for(i=2; i<len+2; i++)//为IAP修改
	{
		if ( (USBRecvEnd == (USBRecvTop - 1) ) || ( (USBRecvTop == 0) && (USBRecvEnd == (USBMAXBUFFSIZE - 1) ) ) )
		{
			//缓冲溢出
			USBRecvTop = 0;
			USBRecvEnd = 0;		
		}
		else
		{
			USBRecvBuf[USBRecvEnd] = RecvBuff[i];
			USBRecvEnd++;

			if (USBRecvEnd >= USBMAXBUFFSIZE) USBRecvEnd = 0;
		}
	}

	if (gUsbRespFlag == ENABLE)
	{
		respbuff[0] = 0x05;
		respbuff[1] = 1;
		respbuff[2] = 0xBB;
		respbuff[63] = 0xBF;
		
        usbd_ep_tx (&usb_device_dev, CUSTOMHID_IN_EP, (uint8_t *)respbuff, 64);
		prev_receive_complete = 0;
	}
	
	DBG_S("EP1_OUT_Callback USBRecvTop = %d,USBRecvEnd = %d\r\n",USBRecvTop,USBRecvEnd);

}

void UsbRecvReset (void)
{
	USBRecvTop = 0;
	USBRecvEnd = 0;

	memset((void *)USBRecvBuf, 0, USBMAXBUFFSIZE); 
}

unsigned char UsbRecvOne (unsigned char *Str)
{
	if (USBRecvTop == USBRecvEnd) return 0;//read nothing

	*Str = USBRecvBuf[USBRecvTop];
	USBRecvTop++;

	if (USBRecvTop >= USBMAXBUFFSIZE) USBRecvTop = 0;


	return 1;//read one
}

unsigned int UsbRecvAtTime (unsigned char *Buff, unsigned int RecvSize, unsigned int ms)
{
	unsigned int RecvLen = 0;
	unsigned char tmp[1] = {0};

    DBG_S("1.UsbRecvAtTime USBRecvTop = %d,USBRecvEnd = %d\r\n",USBRecvTop,USBRecvEnd);
	
	g1msTimer6 = ms;

	if (RecvSize == 0) return 0;

	while (1)
	{
		if (g1msTimer6 == 0) return RecvLen;

		if (UsbRecvOne (tmp) == 1) 
		{
			Buff[RecvLen++] = tmp[0];
		}

		if (RecvLen >= RecvSize) return RecvLen;
	}

	DBG_S("2.UsbRecvAtTime USBRecvTop = %d,USBRecvEnd = %d\r\n",USBRecvTop,USBRecvEnd);

}

unsigned int UsbSendBuff(usbd_core_handle_struct *pudev,unsigned char *buff, unsigned int len, unsigned int ms)
{
	unsigned int sent = 0;		//已发送的数据长度
	unsigned int rest = len;	//未发送的数据长度
	unsigned int PACKET_LEN = 61;
	unsigned char SendBuff[64+1]= {0};
	
	//SendBuff
	//[0]    [1]    [2]    [3]    ...    [62]    [63]
	//05     len     d0    d1             d60     sum

    prev_receive_complete = 1;
	while(1)
	{
		if(rest == 0)return len;	

		if(prev_receive_complete == 0)continue;
		
		if (rest >= 61)PACKET_LEN = 61;
		else PACKET_LEN = rest;

		memset((unsigned char*)SendBuff, 0, sizeof(SendBuff));	
		//1
		SendBuff[0] = 0x05;							//REPORTID
		SendBuff[1] = PACKET_LEN;					//len
		//2
		memcpy((unsigned char*)(SendBuff+2), (buff+sent), PACKET_LEN);	//61 bytes
		//3
		SendBuff[63] = CalcSum((unsigned char*)SendBuff, 63);
		
		prev_receive_complete = 0;
		
    usbd_ep_tx (pudev, CUSTOMHID_IN_EP, (uint8_t *)SendBuff, 64);
		//5
		sent += PACKET_LEN;
		rest -= PACKET_LEN;
	}
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback.
* Description    : EP1 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
	prev_receive_complete = 1;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



