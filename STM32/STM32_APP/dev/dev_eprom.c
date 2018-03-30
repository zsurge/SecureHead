#include <stdlib.h>
#include <string.h>
#include "dev_eprom.h"

/*******************************************************************************
* Function Name  : ReadBlockFlash
* Description    : ��Flash��ֵ
* Input          : ADDRΪ��ʼ�����ĵ�ַ,SourcebufΪ��������ݣ�len��ʾ����ĳ���
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-15
*******************************************************************************/
void ReadBlockFlash(uint32_t ADDR ,u8 *Sourcebuf ,u16 len)
{
	u16 i;

	/* Unlock the Flash Bank1 Program Erase controller */
  	//FLASH_Unlock();

	for(i =0;i<len;i++)
	{
  		Sourcebuf[i] = *((u8 *)ADDR);
  		ADDR++;
  	}
	/* Lock the Flash Bank1 Program Erase controller */
  	//FLASH_Lock();
}

/*******************************************************************************
* Function Name  : EarseBlockFlash
* Description    : ����һ�������Ŀռ�
* Input          : Ϊ������ʼ��Flash�Ŀ�ʼ��ַ
* Output         : None
* Return         : 0�������ɹ���-1������ʧ��
* Author         : Jery Ouyang
* Date           : 2017-03-15
*******************************************************************************/
int EarseBlockFlash(uint32_t ADDR )
{
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
		
	/* Unlock the Flash Bank1 Program Erase controller */
  	FLASH_Unlock();
  	  	
	if ((ADDR % 0x0400) != 0) {
		FLASH_Lock();
		return 0;
	}
  	FLASHStatus = FLASH_ErasePage(ADDR);

  	if (FLASHStatus == FLASH_COMPLETE) {
		FLASH_Lock();
		return 1;
	} else {
		FLASH_Lock();
		return 0;
	}
}	

/*******************************************************************************
* Function Name  : WriteBlockFlash
* Description    : д��������
* Input          : д�ĵ�ַ��*Sourcebufд������,len д�ĳ���
* Output         : None
* Return         : 0��д�ɹ���-1��д��ʧ��
* Author         : Jery Ouyang
* Date           : 2017-03-15
*******************************************************************************/
int WriteBlockFlash(uint32_t ADDR, u8 *Sourcebuf, u16 len)
{
	u16 i;
	u8 d,j;
	u32 *form;
		
	/* Unlock the Flash Bank1 Program Erase controller */
  	FLASH_Unlock();

	if (len % 4 != 0) {
		FLASH_Lock();
		return 0;
	}
	
	form = (u32 *)Sourcebuf;
  	for (i = 0; i < len; i += 4) {
		/*д4�ֽ�*/
		FLASH_ProgramWord(ADDR, *form);
		for (j = 0; j < 4; j++) {
			d = *((u8 *)ADDR);
			/*  У��Դ� */
			if (d != Sourcebuf[i+j]) {
				FLASH_Lock();
				return 0;
			}
			ADDR++;
		}
		form++;
	}
	FLASH_Lock();
	return	1;
}

/*******************************************************************************
* Function Name  : CheckEarseFlash
* Description    : ����Ƿ�Ҫ�߳�flash
* Input          : ��ǰ��Flash��ַ
* Output         : None
* Return         : 0����Ҫ������-1������Ҫ����
* Author		 : Jery Ouyang
* Date			 : 2017-03-15
*******************************************************************************/
int CheckEarseFlash(u8 *Buf)
{
	int i;
	for (i = 0; i < 4; i++) {
		if (Buf[i] != 0xff)
			break;
	}
	if (i == 4) {
		return -1;
	} else {
		return 0;
	}
}



