
/* Includes ------------------------------------------------------------------*/

#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_endp.h"
#include "usb_pwr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

__IO unsigned char RecvBuff[64+1];
__IO unsigned char SendBuff[64+1];
__IO unsigned char PrevXferComplete = 1;
__IO char gUsbConnFlag = 0;

#define USBMAXBUFFSIZE 1536

__IO unsigned char USBRecvBuf[USBMAXBUFFSIZE] = {0};
__IO unsigned int USBRecvTop = 0, USBRecvEnd = 0;

extern unsigned int g1msTimer6;

__IO char gUsbRespFlag = DISABLE; 

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
	
	if(p)
	{
	 	return 1;
	}
	else
	{
	 	return 0;
	}
}

char UsbGetConn(void)
{
	if(bDeviceState == CONFIGURED)
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
	//printf("%s : BytesToBeRead is %d\r\n", __func__, BytesToBeRead);
	
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
	//printf("%s : RecvLen is %d\r\n", __func__, RecvLen);
	return RecvLen;	
}

void PrintHexBuff_usb (unsigned char *title, unsigned char *buff, unsigned int len)
{
	#if 1
	int i = 0;
	printf ("%s|", title);

	for (i = 0; i < len; i++)
	{
		printf ("%02x ", buff[i]);
	}

	printf ("\r\n");
	printf ("\r\n");
	#endif
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
void EP1_OUT_Callback(void)
{
	unsigned int i = 0;
	unsigned int len = 0;
	unsigned char sum = 0;
	unsigned char respbuff[64] = {0};

	//RecvBuff
	//[0]    [1]    [2]    [3]    ...    [62]    [63]
	//01     len     d0    d1             d60     sum
	
	/* Read received data (2 bytes) */  
	USB_SIL_Read(EP1_OUT, (uint8_t *)RecvBuff);
	
	len = RecvBuff[1];
	sum = CalcSum((unsigned char *)RecvBuff, 63);

	if(RecvBuff[63] != sum)
	{	 
		SetEPRxStatus(ENDP1, EP_RX_VALID);
		 
		if (gUsbRespFlag == ENABLE)
		{	 
			respbuff[0] = 0x05;
			respbuff[1] = 1;
			respbuff[2] = 0xAA;
			respbuff[63] = 0xAE;
				
			USB_SIL_Write(EP1_IN, (unsigned char*)respbuff, 64);  
			SetEPTxValid(ENDP1);
			PrevXferComplete = 0;
		}

		return ;
	}

	for(i=2; i<2+len; i++)
	{
		if ( (USBRecvEnd == (USBRecvTop - 1) ) || ( (USBRecvTop == 0) && (USBRecvEnd == (USBMAXBUFFSIZE - 1) ) ) )
		{
			//缓冲溢出
			USBRecvTop = 0;
			USBRecvEnd = 0;

			//drv_BeepOnce(2);
		}
		else
		{
			USBRecvBuf[USBRecvEnd] = RecvBuff[i];
			USBRecvEnd++;

			if (USBRecvEnd >= USBMAXBUFFSIZE) USBRecvEnd = 0;
		}
	}
		
	//PrintHexBuff_usb((unsigned char *)__func__, RecvBuff, PACKAGE_SIZE);  	
	
	SetEPRxStatus(ENDP1, EP_RX_VALID);

	if (gUsbRespFlag == ENABLE)
	{
		respbuff[0] = 0x05;
		respbuff[1] = 1;
		respbuff[2] = 0xBB;
		respbuff[63] = 0xBF;
			
		USB_SIL_Write(EP1_IN, (unsigned char*)respbuff, 64);  
		SetEPTxValid(ENDP1);
		PrevXferComplete = 0;
	}
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

	//printf("%s : USBRecvEnd is %d, USBRecvTop is %d\r\n", __func__, USBRecvEnd, USBRecvTop);

	return 1;//read one
}

unsigned int UsbRecvAtTime (unsigned char *Buff, unsigned int RecvSize, unsigned int ms)
{
	unsigned int RecvLen = 0;
	unsigned char tmp[1] = {0};

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
}

unsigned int UsbSendBuff(const unsigned char *buff, unsigned int len, unsigned int ms)
{
	unsigned int sent = 0;		//已发送的数据长度
	unsigned int rest = len;	//未发送的数据长度
	unsigned int PACKET_LEN = 61;

	g1msTimer6 = ms;
	
	//SendBuff
	//[0]    [1]    [2]    [3]    ...    [62]    [63]
	//05     len     d0    d1             d60     sum
	PrevXferComplete = 1;

	while(1)
	{
		if(g1msTimer6 == 0)return sent;

		if(rest == 0)return len;

		if(PrevXferComplete == 0)continue;
		
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
		//4
		PrevXferComplete = 0;
		USB_SIL_Write(EP1_IN, (unsigned char*)SendBuff, 64);  
		SetEPTxValid(ENDP1);
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
	PrevXferComplete = 1;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

