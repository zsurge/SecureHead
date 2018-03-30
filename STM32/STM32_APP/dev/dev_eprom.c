#include <stdlib.h>
#include <string.h>
#include "dev_eprom.h"

/*******************************************************************************
* Function Name  : ReadBlockFlash
* Description    : 读Flash的值
* Input          : ADDR为开始读出的地址,Sourcebuf为读入的数据，len表示读入的长度
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
* Description    : 擦除一个扇区的空间
* Input          : 为擦除开始的Flash的开始地址
* Output         : None
* Return         : 0：擦除成功；-1：擦除失败
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
* Description    : 写扇区函数
* Input          : 写的地址，*Sourcebuf写的数据,len 写的长度
* Output         : None
* Return         : 0：写成功；-1：写入失败
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
		/*写4字节*/
		FLASH_ProgramWord(ADDR, *form);
		for (j = 0; j < 4; j++) {
			d = *((u8 *)ADDR);
			/*  校验对错 */
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
* Description    : 检查是否要檫除flash
* Input          : 当前的Flash地址
* Output         : None
* Return         : 0：需要擦除；-1：不需要擦除
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



