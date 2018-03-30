/******************************************************************************
 * @file    main.c
 *          
 * @author  Jery.Ouyang 
 *          
 * @date    2017-03-05
 *          
 * @brief   
 *          
 * @note    
 *          
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 * 2017-03-05   1.0.0.0  Jery.Ouyang  written
 *****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_endp.h"
#include "delay.h"
#include "dev_uart.h"
#include "ini.h"
#include "iap.h"

#define PinCPD  GPIO_Pin_2
#define PinOUT1 GPIO_Pin_7
#define PinOUT2 GPIO_Pin_0
#define PinOUT3 GPIO_Pin_1

extern ErrorStatus HSEStartUpStatus;


void RCC_Configuration(void);
void GPIO_Configuration(void);

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : 系统时钟设置
* Input          : None
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
//void RCC_Configuration(void)
//{
//	//将外设 RCC寄存器重设为缺省值
//	RCC_DeInit();

//	//使能内部晶振，内部晶振频率8MHz
//	RCC_HSICmd(ENABLE);
//  
//	//等待HSI晶振就绪
//	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
//	
//	//开启FLASH预取指功能
//	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//	
//	//FLASH时序控制
//	FLASH_SetLatency(FLASH_Latency_2);
//   
//	//设置HCLK（AHB时钟）=SYSCLK
//	RCC_HCLKConfig(RCC_SYSCLK_Div1);
//   
//	//PCLK2(APB2) = HCLK
//	RCC_PCLK2Config(RCC_HCLK_Div1);
//  
//	//PCLK1(APB1) = HCLK/2
//	RCC_PCLK1Config(RCC_HCLK_Div2);
//    
//	//设置PLL时钟源及倍频系数:8M * 9 = 72MHz
//	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9);   
//                
//	//使能PLL
//	RCC_PLLCmd(ENABLE);

//	//等待指定的 RCC 标志位设置成功 等待PLL初始化成功
//	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	

//	//设置系统时钟（SYSCLK） 设置PLL为系统时钟源
//	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//  
//	//等待PLL成功用作于系统时钟的时钟源
//	//  0x00：HSI 作为系统时钟 
//	//  0x04：HSE作为系统时钟 
//	//  0x08：PLL作为系统时钟  
//	while(RCC_GetSYSCLKSource() != 0x08);	
//}

void RCC_Configuration(void)
{

  /*将外设RCC寄存器重设为缺省值*/
  RCC_DeInit(); 

  /*设置外部高速晶振（HSE）*/
  RCC_HSEConfig(RCC_HSE_ON);   //RCC_HSE_ON——HSE晶振打开(ON) 

  /*等待HSE起振*/
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  if(HSEStartUpStatus == SUCCESS)        //SUCCESS：HSE晶振稳定且就绪
  {
    /*设置AHB时钟（HCLK）*/ 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  //RCC_SYSCLK_Div1——AHB时钟= 系统时钟 

    /* 设置高速AHB时钟（PCLK2）*/ 
    RCC_PCLK2Config(RCC_HCLK_Div1);   //RCC_HCLK_Div1——APB2时钟= HCLK 

    /*设置低速AHB时钟（PCLK1）*/    
    RCC_PCLK1Config(RCC_HCLK_Div2);   //RCC_HCLK_Div2——APB1时钟= HCLK / 2 

    /*设置FLASH存储器延时时钟周期数*/
    FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2延时周期   

    /*选择FLASH预取指缓存的模式*/  
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);       // 预取指缓存使能 

    /*设置PLL时钟源及倍频系数*/ 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     // PLL的输入时钟= HSE时钟频率；RCC_PLLMul_9——PLL输入时钟x 9   
    
    /*使能PLL */
    RCC_PLLCmd(ENABLE);  

    /*检查指定的RCC标志位(PLL准备好标志)设置与否*/   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)      
   {
    ;
   } 

    /*设置系统时钟（SYSCLK）*/ 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //RCC_SYSCLKSource_PLLCLK——选择PLL作为系统时钟 

    /* PLL返回用作系统时钟的时钟源*/
    while(RCC_GetSYSCLKSource() != 0x08)        //0x08：PLL作为系统时钟
   { 
        ;
   }

 } 

 /*使能或者失能APB2外设时钟*/
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE); 
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : NVIC设置
* Input          : None
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
}



/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description	 : EXTI设置
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI_Configuration(void)
{

}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description	 : RTC设置
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void RTC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	
	/* Reset Backup Domain */
	BKP_DeInit();
	
	/* Enable LSI OSC */
	RCC_LSICmd(ENABLE);

	/* Wait till LSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
	
	/* Select LSI as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Set the RTC time base to 1s */
	RTC_SetPrescaler(40000); 
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	
	/* Enable the RTC Alarm interrupt */
	RTC_ITConfig(RTC_IT_ALR, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  
	/* Enable the RTCAlarm_IRQn Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : IWDG_Configuration
* Description	 : IWDG设置
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
#define DEV_WDG_PR      IWDG_Prescaler_64       //时钟分频
#define DEV_WDG_RELOAD  1000   					//喂狗时间
void IWDG_Configuration(void)
{
	/* 写入0x5555,用于允许狗狗寄存器写入功能 */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
 
	/* 狗狗时钟分频, 40K / 64 = 625HZ (1.6ms)*/
	IWDG_SetPrescaler(DEV_WDG_PR);
 
	/* 喂狗时间 1.6s / 1.6MS = 1000 .注意不能大于0xfff*/
	IWDG_SetReload(DEV_WDG_RELOAD);
 
	/* 喂狗*/
	IWDG_ReloadCounter();
 
	/* 使能狗狗*/
	IWDG_Enable();
}

/*******************************************************************************
* Function Name  : SYSCLKConfig_STOP
* Description    : Configures system clock after wake-up from STOP: enable HSI, PLL
*                  and select PLL as system clock source.
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void SYSCLKConfig_STOP(void)
{
	//使能内部晶振，内部晶振频率8MHz
	RCC_HSICmd(ENABLE);
  
	//等待HSI晶振就绪
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	
	//使能PLL
	RCC_PLLCmd(ENABLE);

	//等待指定的 RCC 标志位设置成功 等待PLL初始化成功
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	

	//设置系统时钟（SYSCLK） 设置PLL为系统时钟源
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
	//等待PLL成功用作于系统时钟的时钟源
	//  0x00：HSI 作为系统时钟 
	//  0x04：HSE作为系统时钟 
	//  0x08：PLL作为系统时钟  
	while(RCC_GetSYSCLKSource() != 0x08);
}

#define UserApplicationAddress 0x8003400

typedef void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;

char iap_StartApp (void)
{
    if ( ( (* (__IO uint32_t*) UserApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    {
//		__disable_irq();
//		__disable_fault_irq();
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);   		
//		TIM_Cmd (TIM2, DISABLE);
//		iap_delay(0xFFFF);
	 
		/* Jump to user application */
		JumpAddress = *(__IO uint32_t*) (UserApplicationAddress + 4);
		Jump_To_Application = (pFunction) JumpAddress;

		/* Initialize user application's Stack Pointer */
		__set_PSP(*(__IO uint32_t*) UserApplicationAddress);
		__set_CONTROL(0);
		__set_MSP(*(__IO uint32_t*) UserApplicationAddress);
		
		Jump_To_Application();				
		while(1);
    }
	else
	{
		return 0;
	}
}

/*****************************************************************************
 * Function      : ApplicationInit
 * Description   : init dev
 * Input         : void
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20180111
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void ApplicationInit( void )
{  
	RCC_Configuration();
	
	/* Configure EXTI Line to generate an interrupt on falling edge */
	EXTI_Configuration();

	/* NVIC configuration */
	NVIC_Configuration();
    
//	IWDG_Configuration();

//	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET) {			//如果上次是看门狗引起的复位
//		RCC_ClearFlag();
//	}    
//	
	delay_init(72);

	//打开串口
	dev_com_open();		
	uart_puts("iap init...\r\n");  

	//USB INIT
	UsbAllInit();	
	UsbSetRespFlag (ENABLE);
	UsbRecvReset();


}

/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
//extern volatile char MSR_fCardDataReady;
//extern __IO uint8_t TM1CaptureNumber;
//extern __IO uint8_t TM2CaptureNumber;
//extern __IO uint8_t TM3CaptureNumber;
int main(void)
{
	ApplicationInit();

	if(ReadUpgradeFlag() != UPGRADE)
    {        
        uart_puts("Jump To Application\r\n");	        
        iap_StartApp();       
    }
    else
    {      
        uart_puts("iap is start\r\n");

        while(1)
        {
           UsbUpdata();
        }   
       
    }
}

