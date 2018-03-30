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
#include "app.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_endp.h"




#define PinCPD  GPIO_Pin_2
#define PinOUT1 GPIO_Pin_7
#define PinOUT2 GPIO_Pin_0
#define PinOUT3 GPIO_Pin_1

extern ErrorStatus HSEStartUpStatus;
void RCC_Configuration(void);
void GPIO_Configuration(void);
void delay_ms(uint16_t nms);
void delay_us(uint32_t Nus);
/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : 系统时钟设置
* Input          : None
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void RCC_Configuration(void)
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
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3400);
}

static u8  fac_us=0;							//us延时倍乘数
static u16 fac_ms=0;							//ms延时倍乘数
/*******************************************************************************
* Function Name  : delay_init
* Description    : 初始化延迟函数，使用SysTick的普通计数模式对延迟进行管理 
* Input          : 系统时钟频率(Mhx)
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;//选择内部时钟 HCLK/8
	fac_us = SYSCLK / 8;      
	fac_ms = fac_us * 1000;
}            

/*******************************************************************************
* Function Name  : delay_init
* Description    : 延时Nms，Nms <= 0xffffff * 8 / SYSCLK，对72M条件下,Nms <= 1864
* Input          : 延时Nms
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_ms(uint16_t nms)
{         
	uint32_t temp;     
	SysTick->LOAD = nms * fac_ms;				//时间加载
	SysTick->VAL  = 0x00;						//清空计数器
	SysTick->CTRL = 0x01;						//开始倒数  
	do {
		temp=SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//等待时间到达   
	SysTick->CTRL = 0x00;       				//关闭计数器
	SysTick->VAL  = 0X00;       				//清空计数器        
}
 
/*******************************************************************************
* Function Name  : delay_us
* Description    : 延时Nus
* Input          : 延时Nus
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_us(uint32_t Nus)
{  
	uint32_t temp;       
	SysTick->LOAD = Nus * fac_us;				//时间加载      
	SysTick->VAL  = 0x00;						//清空计数器
	SysTick->CTRL = 0x01;						//开始倒数   
	do {
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//等待时间到达   
	SysTick->CTRL = 0x00;       				//关闭计数器
	SysTick->VAL  = 0X00;       				//清空计数器     
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
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
	//配置外部中断事件
	/*外部中断使用PB2*/												//初始化 PB2		CPD
	GPIO_InitStructure.GPIO_Pin	  = PinCPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//输入模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//抢占式优先级别设置为无抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI2_IRQn;				//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//指定响应优先级别0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);		//PA4作为外部中断通道
	EXTI_InitStructure.EXTI_Line    = EXTI_Line2;					//外部中断通道4
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//外部中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//使能
	EXTI_Init(&EXTI_InitStructure);

	//配置外部中断事件
	/*外部中断使用PA7*/											//初始化 PA7		F2F1
	GPIO_InitStructure.GPIO_Pin	  = PinOUT1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//抢占式优先级别设置为无抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI9_5_IRQn;			//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//指定响应优先级别0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);	//PA10作为外部中断通道
	EXTI_InitStructure.EXTI_Line    = EXTI_Line7;					//外部中断通道10
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//外部中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//使能
	EXTI_Init(&EXTI_InitStructure);

	//配置外部中断事件
	/*外部中断使用PB0*/												//初始化 PB0		F2F2
	GPIO_InitStructure.GPIO_Pin	  = PinOUT2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//输入模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//抢占式优先级别设置为无抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI0_IRQn;				//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//指定响应优先级别0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);		//PA0作为外部中断通道
	EXTI_InitStructure.EXTI_Line    = EXTI_Line0;					//外部中断通道0
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//外部中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//使能
	EXTI_Init(&EXTI_InitStructure);

	//配置外部中断事件
	/*外部中断使用PB4*/												//初始化 PB1		F2F3
	GPIO_InitStructure.GPIO_Pin	  = PinOUT3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//输入模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//抢占式优先级别设置为无抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI1_IRQn;			//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//指定响应优先级别0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);		//PA6作为外部中断通道
	EXTI_InitStructure.EXTI_Line    = EXTI_Line1;					//外部中断通道6
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//外部中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//使能
	EXTI_Init(&EXTI_InitStructure);
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

/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
extern volatile char MSR_fCardDataReady;
extern __IO uint8_t TM1CaptureNumber;
extern __IO uint8_t TM2CaptureNumber;
extern __IO uint8_t TM3CaptureNumber;
int main(void)
{
    #if 1
	int ret;
	uint8_t Buf[110];
	
	RCC_Configuration();
	
	/* Configure EXTI Line to generate an interrupt on falling edge */
	EXTI_Configuration();

	/* NVIC configuration */
//	NVIC_Configuration();
    
//	IWDG_Configuration();

//	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET) {			//如果上次是看门狗引起的复位
//		RCC_ClearFlag();
//	}
    
	
	delay_init(72);

	//打开串口
	dev_com_open();		
	uart_puts("APP Start...\r\n");

	#endif

	//USB INIT
	UsbAllInit();	
	UsbRecvReset();

#if 1	
	
	//打开定时器计时
	TIM2_Cap_Init(72 - 1);										//以 1Mhz 的频率计数
	TIM3_Cnt_Init();											//定时1.3s初始化，用于刷卡完成

	//复位加密磁头加密KEY
	#ifdef FLASHKEY_SUPPORT
	if(!ReadENCKEY())
	{
		memset(ENC_KEY.key, 0x00, sizeof(ENC_KEY.key));
		ENC_KEY.temp.level = 0x31;
		WriteFlag = 1;	
	}
	#else
	memset(ENC_KEY.key, 0x00, sizeof(ENC_KEY.key));
	ENC_KEY.temp.level = 0x31;
	#endif

	while (1) {													/* main loop */

//	uart_puts(" main loop...\r\n");

		//喂狗
//		IWDG_ReloadCounter();
		
		//串口协议数据处理
		DealSerialParse();
		DealRxData();
		
		if (1 == GPIO_ReadInputDataBit(GPIOB, PinCPD) && MSR_fCardDataReady) {

			ret = MSR_GetCharacterDataOn(0, Buf, sizeof(Buf));	//一磁道解码

//			if (0 == ret) {	
//				printf("TK1:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK1 ret:%d\r\n", ret);
//			}

			ret = MSR_GetCharacterDataOn(1, Buf, sizeof(Buf));	//二磁道解码

//			if (0 == ret) {	
//				printf("TK2:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK2 ret:%d\r\n", ret);
//			}

			ret = MSR_GetCharacterDataOn(2, Buf, sizeof(Buf));	//三磁道解码

//			if (0 == ret) {	
//				printf("TK3:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK3 ret:%d\r\n", ret);
//			}
			
			MSR_SendData();
			if (GetNextFlag) {									//计算下一个KSN
			
				GetNextKSN();
				GetNextFlag = 0;
			}

			//重新初始化
			FlushBuffer_Init();
			TM1CaptureNumber = 0;
			TM2CaptureNumber = 0;
			TM3CaptureNumber = 0;
		}
	}
	#endif

}

