/**
  ******************************************************************************
  * @file    SPI/SPI_FLASH/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "dev_uart.h"
#include "magdecode.h"

#define FILTERNUM 2				//过滤前后多少个波形
volatile uint16_t TM1ReadValue1 = 0, TM1ReadValue2 = 0;
volatile uint16_t TM2ReadValue1 = 0, TM2ReadValue2 = 0;
volatile uint16_t TM3ReadValue1 = 0, TM3ReadValue2 = 0;
volatile uint8_t TM1CaptureNumber = 0;
volatile uint8_t TM2CaptureNumber = 0;
volatile uint8_t TM3CaptureNumber = 0;

__IO unsigned int g1msTimer6 = 0;//for USB

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    if(g1msTimer6 > 0)g1msTimer6--;
}

/*******************************************************************************
* Function Name  : USART1_IRQ_svc
* Description    : 串口2中断服务函数
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/
#if 1
void USART1_IRQHandler(void)
{
	unsigned short ch;
	
	// 串口接收缓冲非空中断
	//if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	if (((USART1->CR1 & 0x20) != 0) && ((USART1->SR & 0x20) != 0) ) {
		//USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART1->SR = (u16)(~0x20);
		// if(USART_GetITStatus(USART1, USART_IT_ORE) != RESET)
		if ( ((USART1->CR3 & 1) != 0) && ((USART1->SR & 0x8) != 0)) {
			// 串口数据接收字符有丢失
			// ch = USART_ReceiveData(USART1);
			ch = (USART1->DR & (u16)0xFF);
			// USART_GetITStatus(USART1, USART_IT_ORE); // 清除ORE标记
			USART1->SR = (u16)(~0x8);
			rec_end0 = rec_head0;
		} else {
			ch = USART1->DR;
			//USART_SendData(USART1, ch);
			rec_buf0[rec_end0++] = (unsigned char)(ch&0xff);
			if (rec_end0 >= RXTEMPBUFLENMAX) {
				rec_end0 = 0;
			}

		}
	}

	/* If a Frame error is signaled by the card */
	// if(USART_GetITStatus(USART1, USART_IT_FE) != RESET)
	if( ((USART1->CR3 & 1) != 0) && 
		((USART1->SR & 0x2) != 0) )
	{
		/* Clear the USART1 Frame error pending bit */
		// USART_ClearITPendingBit(USART1, USART_IT_FE);
		USART1->SR = (u16)(~2);
		// USART_ReceiveData(USART1);
		ch = (USART1->DR & (u16)0xFF);
		/* Resend the byte that failed to be received (by the Smartcard) correctly */
		//SC_ParityErrorHandler();
	}

	/* If the USART1 detects a parity error */
	// if(USART_GetITStatus(USART1, USART_IT_PE) != RESET)
	if( ((USART1->CR1 & 0x100) != 0) && 
		((USART1->SR & 1) != 0) )
	{
		// while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		while((USART1->SR & USART_FLAG_RXNE) == 0)
		{
		}
		/* Clear the USART1 Parity error pending bit */
		// USART_ClearITPendingBit(USART1, USART_IT_PE);
		USART1->SR = (u16)(~1);
		// USART_ReceiveData(USART1);
		ch = (USART1->DR & (u16)0xFF);
	}
	/* If a Overrun error is signaled by the card */
	// if(USART_GetITStatus(USART1, USART_IT_ORE) != RESET)
	if( ((USART1->CR3 & 1) != 0) && 
		((USART1->SR & 0x8) != 0) )
	{
		/* Clear the USART1 Frame error pending bit */
		// USART_ClearITPendingBit(USART1, USART_IT_ORE);
		USART1->SR = (u16)(~0x8);
		// USART_ReceiveData(USART1);
		ch = (USART1->DR &(u16)0xFF);
	}
	/* If a Noise error is signaled by the card */
	// if(USART_GetITStatus(USART1, USART_IT_NE) != RESET)
	if( ((USART1->CR3 & 1) != 0) && 
		((USART1->SR & 0x4) != 0) )
	{
		/* Clear the USART1 Frame error pending bit */
		// USART_ClearITPendingBit(USART1, USART_IT_NE);
		USART1->SR = (u16)(~4);
		// USART_ReceiveData(USART1);
		ch = (USART1->DR &(u16)0xFF);
	}
}
#endif
/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External lines 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI2_IRQHandler(void)												/*刷卡中断响应函数*/
{
	if (EXTI_GetITStatus(EXTI_Line2) == SET) {							//刷卡中断来了
		EXTI_ClearITPendingBit(EXTI_Line2);								/*清除中断标记*/
		if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)) {			
			MSR_Check_Sync_Pattern();
			TIM_Cmd(TIM3, ENABLE);										//开启定时器
		} else {
			MSR_WaitForReady();											//刷卡完成
			TIM_Cmd(TIM3, DISABLE);	
		}
	}
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3_IRQ interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void TIM3_IRQHandler(void)												/*刷卡中断响应函数*/
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		MSR_WaitForReady();												//刷卡完成
		TIM_Cmd(TIM3, DISABLE);	
	}
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI0_IRQHandler(void)																		/*二磁道中断捕获响应*/
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		EXTI_ClearITPendingBit(EXTI_Line0);  													/*清除中断标记*/
		if (TM2CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
			/* Get the Input Capture value */
			TM2ReadValue1 = TIM2->CNT;															//第一次取值
			TM2CaptureNumber++;
		} else if (Track2TimeFlow.Length < TRACK2TIMEFLOWLENGTH ) {								//判断接收缓存是否满
			/* Get the Input Capture value */
			TM2ReadValue2 = TIM2->CNT;															//第二次取值

			/* Capture computation */
			#ifndef TIMERFLOW_12BIT
			if (TM2ReadValue2 > TM2ReadValue1) {
				//Track2TimeFlow.Value[Track2TimeFlow.Length++]  = (TM2ReadValue2 - TM2ReadValue1); 
				SetF2FInputBuffer(1, TM2ReadValue2 - TM2ReadValue1, 0);
			} else {
				//Track2TimeFlow.Value[Track2TimeFlow.Length++]  = ((0xFFFF - TM2ReadValue1) + TM2ReadValue2); 
				SetF2FInputBuffer(1, 0xFFFF - TM2ReadValue1 + TM2ReadValue2, 0);
			}
			#else
			_input_12bit_data(Track2TimeFlow.Value, Track2TimeFlow.Length, ((TM2ReadValue1 + 0x10000) - TM2ReadValue2) % (0x10000));
			Track2TimeFlow.Length++;
			#endif
			TM2ReadValue1 = TM2ReadValue2;
    	}
	}
}


/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI1_IRQHandler(void)																	/*三磁道中断捕获响应*/
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);  /*清除中断标记*/
		if (TM3CaptureNumber <= FILTERNUM) {
			/* Get the Input Capture value */
			TM3ReadValue1 = TIM2->CNT;															//第一次取值
			TM3CaptureNumber++;
		} else if (Track3TimeFlow.Length < TRACK3TIMEFLOWLENGTH ) {								//判断接收缓存是否满
			/* Get the Input Capture value */
			TM3ReadValue2 = TIM2->CNT;															//第二次取值

			/* Capture computation */
			#ifndef TIMERFLOW_12BIT
			if (TM3ReadValue2 > TM3ReadValue1) {
				//Track3TimeFlow.Value[Track3TimeFlow.Length++]  = (TM3ReadValue2 - TM3ReadValue1); 
				SetF2FInputBuffer(2, TM3ReadValue2 - TM3ReadValue1, 0);
			} else {
				//Track3TimeFlow.Value[Track3TimeFlow.Length++]  = ((0xFFFF - TM3ReadValue1) + TM3ReadValue2); 
				SetF2FInputBuffer(2, 0xFFFF - TM3ReadValue1 + TM3ReadValue2, 0);
			}
			#else
			_input_12bit_data(Track3TimeFlow.Value, Track3TimeFlow.Length, ((TM3ReadValue1 + 0x10000) - TM3ReadValue2) % (0x10000));
			Track3TimeFlow.Length++;
			#endif
			
			TM3ReadValue1 = TM3ReadValue2;
    	}
	}
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI9_5_IRQHandler(void)	//PA7																	/*一磁道中断捕获响应*/
{
	if(EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);  /*清除中断标记*/
		if (TM1CaptureNumber <= FILTERNUM) {
			/* Get the Input Capture value */
			TM1ReadValue1 = TIM2->CNT;																//第一次取值
			TM1CaptureNumber++;
		} else if (Track1TimeFlow.Length < TRACK1TIMEFLOWLENGTH ) {									//判断接收缓存是否满
			/* Get the Input Capture value */
			TM1ReadValue2 = TIM2->CNT;																//第二次取值

			/* Capture computation */
			#ifndef TIMERFLOW_12BIT
			if (TM1ReadValue2 > TM1ReadValue1) {
				//Track1TimeFlow.Value[Track1TimeFlow.Length++]  = (TM1ReadValue2 - TM1ReadValue1); 
				SetF2FInputBuffer(0, TM1ReadValue2 - TM1ReadValue1, 0);
			} else {
				//Track1TimeFlow.Value[Track1TimeFlow.Length++]  = ((0xFFFF - TM1ReadValue1) + TM1ReadValue2); 
				SetF2FInputBuffer(0, (0xFFFF - TM1ReadValue1) + TM1ReadValue2, 0);
			}
			#else
			_input_12bit_data(Track1TimeFlow.Value, Track1TimeFlow.Length, ((TM1ReadValue1 + 0x10000) - TM1ReadValue2) % (0x10000));
			Track1TimeFlow.Length++;
			#endif
			
			TM1ReadValue1 = TM1ReadValue2;
    	}
	}
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{

  if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
  {
	/* Clear EXTI line17 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line17);

    /* Check if the Wake-Up flag is set */
    if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
    {
      /* Clear Wake Up flag */
      PWR_ClearFlag(PWR_FLAG_WU);
    }

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();   
    /* Clear RTC Alarm interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_ALR);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }


}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
