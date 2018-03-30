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
* Description    : ϵͳʱ������
* Input          : None
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void RCC_Configuration(void)
//{
//	//������ RCC�Ĵ�������Ϊȱʡֵ
//	RCC_DeInit();

//	//ʹ���ڲ������ڲ�����Ƶ��8MHz
//	RCC_HSICmd(ENABLE);
//  
//	//�ȴ�HSI�������
//	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
//	
//	//����FLASHԤȡָ����
//	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//	
//	//FLASHʱ�����
//	FLASH_SetLatency(FLASH_Latency_2);
//   
//	//����HCLK��AHBʱ�ӣ�=SYSCLK
//	RCC_HCLKConfig(RCC_SYSCLK_Div1);
//   
//	//PCLK2(APB2) = HCLK
//	RCC_PCLK2Config(RCC_HCLK_Div1);
//  
//	//PCLK1(APB1) = HCLK/2
//	RCC_PCLK1Config(RCC_HCLK_Div2);
//    
//	//����PLLʱ��Դ����Ƶϵ��:8M * 9 = 72MHz
//	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9);   
//                
//	//ʹ��PLL
//	RCC_PLLCmd(ENABLE);

//	//�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
//	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	

//	//����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ
//	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//  
//	//�ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ
//	//  0x00��HSI ��Ϊϵͳʱ�� 
//	//  0x04��HSE��Ϊϵͳʱ�� 
//	//  0x08��PLL��Ϊϵͳʱ��  
//	while(RCC_GetSYSCLKSource() != 0x08);	
//}
{

  /*������RCC�Ĵ�������Ϊȱʡֵ*/
  RCC_DeInit(); 

  /*�����ⲿ���پ���HSE��*/
  RCC_HSEConfig(RCC_HSE_ON);   //RCC_HSE_ON����HSE�����(ON) 

  /*�ȴ�HSE����*/
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  if(HSEStartUpStatus == SUCCESS)        //SUCCESS��HSE�����ȶ��Ҿ���
  {
    /*����AHBʱ�ӣ�HCLK��*/ 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  //RCC_SYSCLK_Div1����AHBʱ��= ϵͳʱ�� 

    /* ���ø���AHBʱ�ӣ�PCLK2��*/ 
    RCC_PCLK2Config(RCC_HCLK_Div1);   //RCC_HCLK_Div1����APB2ʱ��= HCLK 

    /*���õ���AHBʱ�ӣ�PCLK1��*/    
    RCC_PCLK1Config(RCC_HCLK_Div2);   //RCC_HCLK_Div2����APB1ʱ��= HCLK / 2 

    /*����FLASH�洢����ʱʱ��������*/
    FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2��ʱ����   

    /*ѡ��FLASHԤȡָ�����ģʽ*/  
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);       // Ԥȡָ����ʹ�� 

    /*����PLLʱ��Դ����Ƶϵ��*/ 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     // PLL������ʱ��= HSEʱ��Ƶ�ʣ�RCC_PLLMul_9����PLL����ʱ��x 9   
    
    /*ʹ��PLL */
    RCC_PLLCmd(ENABLE);  

    /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)      
   {
    ;
   } 

    /*����ϵͳʱ�ӣ�SYSCLK��*/ 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //RCC_SYSCLKSource_PLLCLK����ѡ��PLL��Ϊϵͳʱ�� 

    /* PLL��������ϵͳʱ�ӵ�ʱ��Դ*/
    while(RCC_GetSYSCLKSource() != 0x08)        //0x08��PLL��Ϊϵͳʱ��
   { 
        ;
   }

 } 

 /*ʹ�ܻ���ʧ��APB2����ʱ��*/
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE); 
}
/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : NVIC����
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

static u8  fac_us=0;							//us��ʱ������
static u16 fac_ms=0;							//ms��ʱ������
/*******************************************************************************
* Function Name  : delay_init
* Description    : ��ʼ���ӳٺ�����ʹ��SysTick����ͨ����ģʽ���ӳٽ��й��� 
* Input          : ϵͳʱ��Ƶ��(Mhx)
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;//ѡ���ڲ�ʱ�� HCLK/8
	fac_us = SYSCLK / 8;      
	fac_ms = fac_us * 1000;
}            

/*******************************************************************************
* Function Name  : delay_init
* Description    : ��ʱNms��Nms <= 0xffffff * 8 / SYSCLK����72M������,Nms <= 1864
* Input          : ��ʱNms
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_ms(uint16_t nms)
{         
	uint32_t temp;     
	SysTick->LOAD = nms * fac_ms;				//ʱ�����
	SysTick->VAL  = 0x00;						//��ռ�����
	SysTick->CTRL = 0x01;						//��ʼ����  
	do {
		temp=SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL = 0x00;       				//�رռ�����
	SysTick->VAL  = 0X00;       				//��ռ�����        
}
 
/*******************************************************************************
* Function Name  : delay_us
* Description    : ��ʱNus
* Input          : ��ʱNus
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_us(uint32_t Nus)
{  
	uint32_t temp;       
	SysTick->LOAD = Nus * fac_us;				//ʱ�����      
	SysTick->VAL  = 0x00;						//��ռ�����
	SysTick->CTRL = 0x01;						//��ʼ����   
	do {
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL = 0x00;       				//�رռ�����
	SysTick->VAL  = 0X00;       				//��ռ�����     
}

/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description	 : EXTI����
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
	
	//�����ⲿ�ж��¼�
	/*�ⲿ�ж�ʹ��PB2*/												//��ʼ�� PB2		CPD
	GPIO_InitStructure.GPIO_Pin	  = PinCPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//����ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//��ռʽ���ȼ�������Ϊ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI2_IRQn;				//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//ָ����Ӧ���ȼ���0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);		//PA4��Ϊ�ⲿ�ж�ͨ��
	EXTI_InitStructure.EXTI_Line    = EXTI_Line2;					//�ⲿ�ж�ͨ��4
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//�ⲿ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//ʹ��
	EXTI_Init(&EXTI_InitStructure);

	//�����ⲿ�ж��¼�
	/*�ⲿ�ж�ʹ��PA7*/											//��ʼ�� PA7		F2F1
	GPIO_InitStructure.GPIO_Pin	  = PinOUT1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//����ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//��ռʽ���ȼ�������Ϊ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI9_5_IRQn;			//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//ָ����Ӧ���ȼ���0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);	//PA10��Ϊ�ⲿ�ж�ͨ��
	EXTI_InitStructure.EXTI_Line    = EXTI_Line7;					//�ⲿ�ж�ͨ��10
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//�ⲿ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//ʹ��
	EXTI_Init(&EXTI_InitStructure);

	//�����ⲿ�ж��¼�
	/*�ⲿ�ж�ʹ��PB0*/												//��ʼ�� PB0		F2F2
	GPIO_InitStructure.GPIO_Pin	  = PinOUT2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//����ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//��ռʽ���ȼ�������Ϊ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI0_IRQn;				//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//ָ����Ӧ���ȼ���0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);		//PA0��Ϊ�ⲿ�ж�ͨ��
	EXTI_InitStructure.EXTI_Line    = EXTI_Line0;					//�ⲿ�ж�ͨ��0
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//�ⲿ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//ʹ��
	EXTI_Init(&EXTI_InitStructure);

	//�����ⲿ�ж��¼�
	/*�ⲿ�ж�ʹ��PB4*/												//��ʼ�� PB1		F2F3
	GPIO_InitStructure.GPIO_Pin	  = PinOUT3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			//����ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);					//��ռʽ���ȼ�������Ϊ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel    = EXTI1_IRQn;			//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//ָ����Ӧ���ȼ���0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);		//PA6��Ϊ�ⲿ�ж�ͨ��
	EXTI_InitStructure.EXTI_Line    = EXTI_Line1;					//�ⲿ�ж�ͨ��6
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;			//�ⲿ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//ʹ��
	EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description	 : RTC����
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
* Description	 : IWDG����
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
#define DEV_WDG_PR      IWDG_Prescaler_64       //ʱ�ӷ�Ƶ
#define DEV_WDG_RELOAD  1000   					//ι��ʱ��
void IWDG_Configuration(void)
{
	/* д��0x5555,�����������Ĵ���д�빦�� */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
 
	/* ����ʱ�ӷ�Ƶ, 40K / 64 = 625HZ (1.6ms)*/
	IWDG_SetPrescaler(DEV_WDG_PR);
 
	/* ι��ʱ�� 1.6s / 1.6MS = 1000 .ע�ⲻ�ܴ���0xfff*/
	IWDG_SetReload(DEV_WDG_RELOAD);
 
	/* ι��*/
	IWDG_ReloadCounter();
 
	/* ʹ�ܹ���*/
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
	//ʹ���ڲ������ڲ�����Ƶ��8MHz
	RCC_HSICmd(ENABLE);
  
	//�ȴ�HSI�������
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	
	//ʹ��PLL
	RCC_PLLCmd(ENABLE);

	//�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	

	//����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
	//�ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ
	//  0x00��HSI ��Ϊϵͳʱ�� 
	//  0x04��HSE��Ϊϵͳʱ�� 
	//  0x08��PLL��Ϊϵͳʱ��  
	while(RCC_GetSYSCLKSource() != 0x08);
}

/*******************************************************************************
* Function Name  : main
* Description    : ������
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

//	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET) {			//����ϴ��ǿ��Ź�����ĸ�λ
//		RCC_ClearFlag();
//	}
    
	
	delay_init(72);

	//�򿪴���
	dev_com_open();		
	uart_puts("APP Start...\r\n");

	#endif

	//USB INIT
	UsbAllInit();	
	UsbRecvReset();

#if 1	
	
	//�򿪶�ʱ����ʱ
	TIM2_Cap_Init(72 - 1);										//�� 1Mhz ��Ƶ�ʼ���
	TIM3_Cnt_Init();											//��ʱ1.3s��ʼ��������ˢ�����

	//��λ���ܴ�ͷ����KEY
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

		//ι��
//		IWDG_ReloadCounter();
		
		//����Э�����ݴ���
		DealSerialParse();
		DealRxData();
		
		if (1 == GPIO_ReadInputDataBit(GPIOB, PinCPD) && MSR_fCardDataReady) {

			ret = MSR_GetCharacterDataOn(0, Buf, sizeof(Buf));	//һ�ŵ�����

//			if (0 == ret) {	
//				printf("TK1:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK1 ret:%d\r\n", ret);
//			}

			ret = MSR_GetCharacterDataOn(1, Buf, sizeof(Buf));	//���ŵ�����

//			if (0 == ret) {	
//				printf("TK2:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK2 ret:%d\r\n", ret);
//			}

			ret = MSR_GetCharacterDataOn(2, Buf, sizeof(Buf));	//���ŵ�����

//			if (0 == ret) {	
//				printf("TK3:%s\r\n", (char *)Buf);
//			} else {
//				printf("TK3 ret:%d\r\n", ret);
//			}
			
			MSR_SendData();
			if (GetNextFlag) {									//������һ��KSN
			
				GetNextKSN();
				GetNextFlag = 0;
			}

			//���³�ʼ��
			FlushBuffer_Init();
			TM1CaptureNumber = 0;
			TM2CaptureNumber = 0;
			TM3CaptureNumber = 0;
		}
	}
	#endif

}

