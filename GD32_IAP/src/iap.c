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
#include "systick.h"
#include "usbd_std.h"
#include "custom_hid_core.h"
#include <string.h>
#include "dev_uart.h"
#include "usb_endp.h"

#define DELAY_COUNTER 0xFFFE
unsigned char pBuff[1280] = {0};
#define PAGE_SIZE                         (0x400)    /* 1 Kbyte */

uint32_t FlashDestination = APP_LOADED_ADDR; /* Flash user program offset */


/*****************************************************************************
 * Function      : IapProcess
 * Description   : update process
 * Input         : void
 * Output        : None
 * Return        : char
 * Others        : 
 * Record
 * 1.Date        : 20171110
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
//char IapProcess( void )
//{
//	int i = 0;
//	 //01 len 02 xx
//    if((0x01 == report_buf[0]) && ((0x0 != report_buf[2])||(0x0 != report_buf[3])||(0x0 != report_buf[4])||(0x0 != report_buf[5])))
//    {
//        if(0xFF == report_buf[3])
//        {
//    		WriteUpgradeCompleFlag();
//    		NVIC_SystemReset();
//    		delay_1ms(10000); 		
//    			while(1);
//        }
//        else if (0xFE==report_buf[3])
//        {
//            fmc_unlock();	
//            DBG_S("CLEAR FLASH START\r\n");
//        	//擦除APP空间
//        	for(i = 0; i < 50; i++)
//        	{
//        		fmc_page_erase(ERASE_FLASH_BASE + (i * 1024));//擦除一页
//        	} 	
//            DBG_S("CLEAR FLASH END\r\n");
//            memset(report_buf,0x00,sizeof(report_buf));
//        } if(0xEE == report_buf[3])
//        {
//           writeflash(); 
//        }
//        else
//        {
//            custom_hid_report_send (&usb_device_dev, report_buf, 4);     
//            memset(report_buf,0x00,sizeof(report_buf));
//        }
//    }
//	return 0;
//}

//void writeflash()
//{		
//    uint32_t counter;
//    uint32_t prog_word;
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
//        fmc_word_program(prog_addr, *(uint32_t *)(buff + 6 + i));
//        prog_addr += 4;
//    }				
//}


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

	while (1)
	{
		switch (step)
		{
			case 0:
			    delay_1ms(1000);
                DBG_S("step 0---------------------\r\n"); 
                fmc_unlock();	                                       
    			//擦除APP空间
    			for(pos = 0; pos < 50; pos++)
    			{
    				fmc_page_erase(ERASE_FLASH_BASE + (pos * 1024));//擦除一页
    			} 	
    			
                step++;                        
                DBG_S(">>>>>step1 end step<<<< = %d\r\n",step);

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
			    DBG_S("step 1---------------------\r\n"); 
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
			    DBG_S("step 1---------------------\r\n"); 
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
			    DBG_S("step 3---------------------\r\n"); 
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
						fmc_word_program(FlashDestination, *(uint32_t *)RamSource);

						if (* (uint32_t*) FlashDestination != * (uint32_t*) RamSource)
						{
	                        //写升级成功标志位
                            WriteUpgradeCompleFlag();
                            /* lock the internal flash */
                            fmc_lock();
                            /* generate system reset to allow jumping to the user code */
                            NVIC_SystemReset();
                            delay_1ms(10000); 	
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
                    DBG_S("step 3---------------------\r\n");
                    
                    //写升级成功标志位
                    WriteUpgradeCompleFlag();
                    /* lock the internal flash */
                    fmc_lock();
                    /* generate system reset to allow jumping to the user code */
                    NVIC_SystemReset();
                    delay_1ms(10000); 	
    			}
				step++;
				break;

			case 5:
				UsbSetRespFlag (DISABLE);

                //发送数据失败提示
				NVIC_SystemReset();
				delay_1ms (10000);
				break;

			default:
				break;

		}
	}
}





