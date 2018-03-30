/********************************************************************************

 **** Copyright (C), 2017, Shenzhen Pay Full Science&Technology Co.,Ltd.                ****

 ********************************************************************************
 * File Name     : iap.c
 * Author        : surge
 * Date          : 2017-11-10
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2017-11-10
 *   Author      : surge
 *   Modification: Created file

*************************************************************************************************************/
#include "iap.h"
#include "ini.h"
#include <string.h>
#include "usb_endp.h"
#include "delay.h"
#include "dev_eprom.h"


unsigned char pBuff[1280] = {0};
#define PAGE_SIZE                         (0x400)    /* 1 Kbyte */

uint32_t FlashDestination = APP_LOADED_ADDR; /* Flash user program offset */


//void writeflash()
//{		


//    uint32_t prog_addr;

//    int i = 0;
//    char buff[70] = {0xaa,0xbb,0xcc,0xdd,0xee,0xa1,\
//    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,\
//    0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,\
//    0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,\
//    0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,\
//    0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,\
//    0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,\
//    0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,\
//    0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};
//    
//        prog_addr = ERASE_FLASH_BASE;	

//    for (i = 0; i < 70; i += 4) {
//        FLASH_ProgramWord(prog_addr, *(uint32_t *)(buff + 6 + i));
//        prog_addr += 4;
//    }				
//}

uint32_t FLASH_PagesMask(__IO uint32_t Size)
{
  uint32_t pagenumber = 0x0;
  uint32_t size = Size;

  if ((size % PAGE_SIZE) != 0)
  {
    pagenumber = (size / PAGE_SIZE) + 1;
  }
  else
  {
    pagenumber = size / PAGE_SIZE;
  }
  return pagenumber;

}

void iap_EraseFlash (void)
{
	uint32_t NbrOfPage = 0;
	uint32_t EraseCounter = 0x0;
	const uint16_t PageSize = PAGE_SIZE;
	FLASH_Status FLASHStatus = FLASH_COMPLETE;

	/* Erase the needed pages where the user application will be loaded */
	/* Define the number of page to be erased */
	NbrOfPage = FLASH_PagesMask(0xC800);//0X10000-0x3400-0x400=0xC800
//	printf("NbrOfPage is %d\r\n", NbrOfPage);

    FLASH_Unlock();
    
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 

	/* Erase the FLASH pages */
	for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
//		drv_WatchDogResetCounter();
		FLASHStatus = FLASH_ErasePage (FlashDestination + (PageSize * EraseCounter) );
	}
}


/*****************************************************************************
 * Function      : UsbUpdata
 * Description   : usb update
 * Input         : void
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20171115
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void UsbUpdata( void )
{
	char step = 0;
	unsigned long total = 0;
	unsigned long sent = 0;
	unsigned long rest = 0;

	unsigned char calc_sum = 0;
	unsigned char get_sum = 0;

	unsigned int pos = 0, DATAS_LENGTH = PAGE_SIZE;
	uint32_t RamSource = 0;
    uint32_t j = 0;

    char temp = 0;

	while (1)
	{
		switch (step)
		{
			case 0:
			    delay_ms(1000);                
                iap_EraseFlash();
                
				memset (pBuff, 0, sizeof (pBuff) );
				UsbRecvReset();
				step = 0;
				total = 0;
				sent = 0;
				rest = 0;

				calc_sum = 0;
				get_sum = 0;

				pos = 0;
				DATAS_LENGTH = PAGE_SIZE;

				step++;
				break;

			case 1:
				if (UsbCheckBuff ("Checksum:") == 1)
				{
					memset (pBuff, 0, sizeof (pBuff) );
					UsbReadTo (pBuff, sizeof (pBuff), "Checksum:");

					memset (pBuff, 0, sizeof (pBuff) );
					UsbReadTo (pBuff, sizeof (pBuff), "\r\n");

					get_sum = atoi ( (const char *) pBuff);	
					
					step++;
					memset (pBuff, 0, sizeof (pBuff) );
				}

				break;

			case 2:
				if (UsbCheckBuff ("Content-Length:") == 1)
				{
					memset (pBuff, 0, sizeof (pBuff) );
					UsbReadTo (pBuff, sizeof (pBuff), "Content-Length:");

					memset (pBuff, 0, sizeof (pBuff) );
					UsbReadTo (pBuff, sizeof (pBuff), "\r\n\r\n");

					total = atoi ( (const char *) pBuff);
					rest = total;


					step++;
					memset (pBuff, 0, sizeof (pBuff) );
				}

				break;

			case 3:
				while(step == 3)
				{				    
					if (rest == 0)
					{
						step++;
						break;
					}

					if (UsbRecvOne (pBuff + pos) == 1)
					{
						calc_sum ^= * (pBuff + pos);

						pos++;
					}


					if (pos < DATAS_LENGTH) continue;

					//write to flash
                    RamSource = (uint32_t) pBuff;

					for (j = 0; (j < DATAS_LENGTH) && (FlashDestination <  (APP_LOADED_ADDR + total) ); j += 4)
					{
						/* Program the data received into  Flash */			
						temp = FLASH_ProgramWord(FlashDestination, *(uint32_t *)RamSource);


						if (* (uint32_t*) FlashDestination != * (uint32_t*) RamSource)
						{
						    
	                        //写升级成功标志位
                            WriteUpgradeCompleFlag();
                            /* lock the internal flash */
                            FLASH_Lock();
                            /* generate system reset to allow jumping to the user code */
                            NVIC_SystemReset();
                            delay_ms(10000); 	
						}

						FlashDestination += 4;
						RamSource += 4;
					}				
					//--write flash end-----------------------------------------------------------------------------------------------------------------------------

					sent += DATAS_LENGTH;
					rest -= DATAS_LENGTH;


					if (rest >= PAGE_SIZE) DATAS_LENGTH = PAGE_SIZE;
					else DATAS_LENGTH = rest;

					pos = 0;
					memset (pBuff, 0, sizeof (pBuff) );
				}

				break;

			case 4:
				if (calc_sum == get_sum)
				{
                    
                    //写升级成功标志位
                    WriteUpgradeCompleFlag();
                    /* lock the internal flash */
                    FLASH_Lock();
                    /* generate system reset to allow jumping to the user code */
                    NVIC_SystemReset();
                    delay_ms(10000); 	
    			}
				step++;
				break;

			case 5:
				UsbSetRespFlag (DISABLE);

                //发送数据失败提示
				NVIC_SystemReset();
				delay_ms (10000);
				break;

			default:
				break;

		}
	}
}



#if 0
void UsbUpdata( void )
{
    unsigned char tmp[64] = {0};
    int i = 0;
    if(0x01 == report_buf[0])
    {
        //01 len 02 xx
        switch(report_buf[3])
        {
            case 0x55:
                WriteUpgradeFlag();
				NVIC_SystemReset();
				delay_ms(10000); 		
			    while(1);
			case 0x38:
			    UsbRecvAtTime(tmp,10,1000);
			    custom_hid_report_send (&usb_device_dev, tmp, 10);
			    memset(report_buf,0x00,sizeof(report_buf));
			    break;
			case 0x39:
			    memset(tmp,0x00,sizeof(tmp));
			    UsbRecvAtTime(tmp,2,1000);
			    custom_hid_report_send (&usb_device_dev, tmp, 2);
			    memset(report_buf,0x00,sizeof(report_buf));
			    break;			    
			case 0x52:			
   			    custom_hid_report_send (&usb_device_dev, "\x04\x31\x32\x33\x34", 5);
   			    memset(report_buf,0x00,sizeof(report_buf));
			    break;
		    case 0x53:
		        FLASH_Unlock();	
            	//擦除APP空间
            	for(i = 0; i < 50; i++)
            	{
            		fmc_page_erase(ERASE_FLASH_BASE + (i * 1024));//擦除一页
            	} 	
            	
                memset(report_buf,0x00,sizeof(report_buf));
                break;
            case 0x54:
			    writeflash();
			    FLASH_Lock();
			    memset(report_buf,0x00,sizeof(report_buf));			    
		        break;
		    default:
		        custom_hid_report_send (&usb_device_dev, "\xff\xff\xff\xff", 4);
			    memset(report_buf,0x00,sizeof(report_buf));
		        break;
		        
        }        
    }  
    
}

#endif


