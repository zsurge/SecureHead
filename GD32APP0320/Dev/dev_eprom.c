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
void ReadBlockFlash(uint32_t ADDR ,uint8_t *Sourcebuf ,uint16_t len)
{
	uint16_t i;

	/* Unlock the Flash Bank1 Program Erase controller */
  	fmc_unlock();

	for(i =0;i<len;i++)
	{
  		Sourcebuf[i] = *((uint8_t *)ADDR);
  		ADDR++;
  	}
	/* Lock the Flash Bank1 Program Erase controller */
  	fmc_lock();
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
	//volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
		
	/* Unlock the Flash Bank1 Program Erase controller */
  	fmc_unlock();
  	  	
	if ((ADDR % 0x0400) != 0) {
		fmc_lock();
		return 0;
	}
  	fmc_state = fmc_page_erase(ADDR);

  	if (fmc_state == FMC_READY) {
		fmc_lock();
		return 1;
	} else {
		fmc_lock();
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
int WriteBlockFlash(uint32_t ADDR, uint8_t *Sourcebuf, uint16_t len)
{
	uint16_t i;
	uint8_t d,j;
	uint32_t *form;
		
	/* Unlock the Flash Bank1 Program Erase controller */
  	fmc_unlock();

	if (len % 4 != 0) {
		fmc_lock();
		return 0;
	}
	
	form = (uint32_t *)Sourcebuf;
  	for (i = 0; i < len; i += 4) {
		/*写4字节*/
		fmc_word_program(ADDR, *form);
		for (j = 0; j < 4; j++) {
			d = *((uint8_t *)ADDR);
			/*  校验对错 */
			if (d != Sourcebuf[i+j]) {
				fmc_lock();
				return 0;
			}
			ADDR++;
		}
		form++;
	}
	fmc_lock();
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
int CheckEarseFlash(uint8_t *Buf)
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



