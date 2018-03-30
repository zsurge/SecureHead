/*!
    \file  gd32f1x0_it.c
    \brief interrupt service routines
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-01-15, V1.0.0, demo for GD32F1x0(x=3,5)
    2016-05-13, V2.0.0, demo for GD32F1x0(x=3,5)
*/
#include <stdio.h>
#include "gd32f1x0_it.h"
#include "systick.h"
#include "dev_uart.h"
#include "magdecode.h"


/* Private variables ---------------------------------------------------------*/
#define FILTERNUM 2				//过滤前后多少个波形
#define ENDTIMEOUT 30			//多少MS没有波形就启动解码
volatile uint16_t TM1ReadValue1 = 0, TM1ReadValue2 = 0;
volatile uint16_t TM2ReadValue1 = 0, TM2ReadValue2 = 0;
volatile uint16_t TM3ReadValue1 = 0, TM3ReadValue2 = 0;
volatile uint8_t TM1CaptureNumber = 0;
volatile uint8_t TM2CaptureNumber = 0;
volatile uint8_t TM3CaptureNumber = 0;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}

/*!
    \brief      this function handles USBD interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/

void  USBD_LP_IRQHandler (void)
{
    usbd_isr();
}


/*******************************************************************************
* Function Name  : USART0_IRQ_svc
* Description    : 串口0中断服务函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART0_IRQHandler(void)
{
	unsigned short ch;
	// 串口接收缓冲非空中断
	if (RESET != usart_interrupt_flag_get(USART0, USART_STAT_RBNE, USART_INT_RBNEIE)) {
        /* receive data */
		ch = usart_data_receive(USART0);
		//printf("%02X ", ch);
        rec_buf0[rec_end0++] = ch;
        if (rec_end0 >= RXTEMPBUFLENMAX) {
			rec_end0 = 0;
		}
    }
}

/**
  * @brief  This function handles TIMER1 interrupt request.
  * @param  None
  * @retval None
  */
void TIMER1_IRQHandler(void)
{
#if 0

    if (SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_CH1)) {
        /* clear channel 1 interrupt bit */
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH1);										/*清除中断标记*/

        if (TM1CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 1 capture value */
            TM1ReadValue1 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_1);		//第一次取值
            TM1CaptureNumber++;;
        } else if (Track1TimeFlow.Length < TRACK1TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 1 capture value */
            TM1ReadValue2 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_1);
			/* Capture computation */
            if (TM1ReadValue2 > TM1ReadValue1){
                SetF2FInputBuffer(0, TM1ReadValue2 - TM1ReadValue1, 0);
            } else {
                SetF2FInputBuffer(0, 0xFFFF - TM1ReadValue1 + TM1ReadValue2, 0); 
            }
			TM1ReadValue1 = TM1ReadValue2;
        }
    }
#endif

#if 0
	if (SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_CH2)) {
        /* clear channel 2 interrupt bit */
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH2);										/*清除中断标记*/

        if (TM2CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 2 capture value */
            TM2ReadValue1 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_2);		//第一次取值
            TM2CaptureNumber++;;
        } else if (Track2TimeFlow.Length < TRACK2TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 2 capture value */
            TM2ReadValue2 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_2);
			/* Capture computation */
			//printf("V1:%d, V2:%d\r\n", TM2ReadValue1, TM2ReadValue2);
            if (TM2ReadValue2 > TM2ReadValue1){
                SetF2FInputBuffer(1, TM2ReadValue2 - TM2ReadValue1, 0);
            } else {
                SetF2FInputBuffer(1, 0xFFFF - TM2ReadValue1 + TM2ReadValue2, 0); 
            }
			TM2ReadValue1 = TM2ReadValue2;
        }
    }
#endif

#if 0	
	if (SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_CH3)) {
        /* clear channel 3 interrupt bit */
        timer_interrupt_flag_clear(TIMER1,TIMER_INT_CH3);										/*清除中断标记*/

        if (TM3CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 3 capture value */
            TM3ReadValue1 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_3);		//第一次取值
            TM3CaptureNumber++;;
        } else if (Track3TimeFlow.Length < TRACK3TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 3 capture value */
            TM3ReadValue2 = timer_channel_capture_value_register_read(TIMER1, TIMER_CH_3);
			/* Capture computation */
            if (TM3ReadValue2 > TM3ReadValue1){
                SetF2FInputBuffer(2, TM3ReadValue2 - TM3ReadValue1, 0);
            } else {
                SetF2FInputBuffer(2, 0xFFFF - TM3ReadValue1 + TM3ReadValue2, 0); 
            }
			TM3ReadValue1 = TM3ReadValue2;
        }
    }
#endif
}


/**
  * @brief  This function handles TIMER2 interrupt request.
  * @param  None
  * @retval None
  */
void TIMER2_IRQHandler(void)
{
    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_UP)) {
		/* clear channel 3 interrupt bit */
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);										/*清除中断标记*/
		MSR_WaitForReady();																		//刷卡完成	
		timer_disable(TIMER2);																	//TIM2 disable counter
	}

	
}

/*******************************************************************************
* Function Name  : EXTI0_1_IRQHandler
* Description    : This function handles External lines 0 & 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI0_1_IRQHandler(void)											/*刷卡中断响应函数*/
{
	#if 0
	if (RESET != exti_interrupt_flag_get(EXTI_0)) {
		printf("mag cpd\r\n");
        exti_interrupt_flag_clear(EXTI_0);
		if (0 == gpio_input_bit_get(GPIOA, GPIO_PIN_0)) {			
			MSR_Check_Sync_Pattern();
			timer_enable(TIMER2);										//开启定时器
		} else {
			MSR_WaitForReady();											//刷卡完成
			timer_disable(TIMER2);
		}
    }
	#else
	set_tick(ENDTIMEOUT);
	MSR_WaitForReady();
	if (RESET != exti_interrupt_flag_get(EXTI_0)) {
		/* clear channel 2 interrupt bit */
        exti_interrupt_flag_clear(EXTI_0);										/*清除中断标记*/

        if (TM2CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 2 capture value */
            TM2ReadValue1 = TIMER_CNT(TIMER1);		//第一次取值
            TM2CaptureNumber++;;
        } else if (Track2TimeFlow.Length < TRACK2TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 2 capture value */
            TM2ReadValue2 = TIMER_CNT(TIMER1);
			/* Capture computation */
			//printf("V1:%d, V2:%d\r\n", TM2ReadValue1, TM2ReadValue2);
            if (TM2ReadValue2 > TM2ReadValue1){
                SetF2FInputBuffer(1, TM2ReadValue2 - TM2ReadValue1, 0);
            } else {
                SetF2FInputBuffer(1, 0xFFFF - TM2ReadValue1 + TM2ReadValue2, 0); 
            }
			TM2ReadValue1 = TM2ReadValue2;
        }
    }
	#endif
	
	if (RESET != exti_interrupt_flag_get(EXTI_1)) {
		/* clear channel 3 interrupt bit */
        exti_interrupt_flag_clear(EXTI_1);										/*清除中断标记*/

        if (TM3CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 3 capture value */
            TM3ReadValue1 = TIMER_CNT(TIMER1);		//第一次取值
            TM3CaptureNumber++;;
        } else if (Track3TimeFlow.Length < TRACK3TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 3 capture value */
            TM3ReadValue2 = TIMER_CNT(TIMER1);
			/* Capture computation */
            if (TM3ReadValue2 > TM3ReadValue1){
                SetF2FInputBuffer(2, TM3ReadValue2 - TM3ReadValue1, 0);
            } else {
                SetF2FInputBuffer(2, 0xFFFF - TM3ReadValue1 + TM3ReadValue2, 0); 
            }
			TM3ReadValue1 = TM3ReadValue2;
        }
    }
}

/*******************************************************************************
* Function Name  : EXTI4_15_IRQHandler
* Description    : This function handles External lines 0 & 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void EXTI4_15_IRQHandler(void)											/*刷卡中断响应函数*/
{
	set_tick(ENDTIMEOUT);
	MSR_WaitForReady();
	if (RESET != exti_interrupt_flag_get(EXTI_7)) {
		/* clear channel 1 interrupt bit */
        exti_interrupt_flag_clear(EXTI_7);										/*清除中断标记*/

        if (TM1CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 1 capture value */
            TM1ReadValue1 = TIMER_CNT(TIMER1);		//第一次取值
            TM1CaptureNumber++;;
        } else if (Track1TimeFlow.Length < TRACK1TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 1 capture value */
            TM1ReadValue2 = TIMER_CNT(TIMER1);
			/* Capture computation */
			//printf("V1:%d, V2:%d\r\n", TM2ReadValue1, TM2ReadValue2);
            if (TM1ReadValue2 > TM1ReadValue1){
                SetF2FInputBuffer(0, TM1ReadValue2 - TM1ReadValue1, 0);
            } else {
                SetF2FInputBuffer(0, 0xFFFF - TM1ReadValue1 + TM1ReadValue2, 0); 
            }
			TM1ReadValue1 = TM1ReadValue2;
        }
    }
	#if 0
	if (RESET != exti_interrupt_flag_get(EXTI_15)) {
		/* clear channel 2 interrupt bit */
        exti_interrupt_flag_clear(EXTI_15);										/*清除中断标记*/

        if (TM2CaptureNumber <= FILTERNUM) {													//过滤前面的干扰
            /* read channel 2 capture value */
            TM2ReadValue1 = TIMER_CNT(TIMER1);		//第一次取值
            TM2CaptureNumber++;;
        } else if (Track2TimeFlow.Length < TRACK2TIMEFLOWLENGTH) {								//判断接收缓存是否满
            /* read channel 2 capture value */
            TM2ReadValue2 = TIMER_CNT(TIMER1);
			/* Capture computation */
			//printf("V1:%d, V2:%d\r\n", TM2ReadValue1, TM2ReadValue2);
            if (TM2ReadValue2 > TM2ReadValue1){
                SetF2FInputBuffer(1, TM2ReadValue2 - TM2ReadValue1, 0);
            } else {
                SetF2FInputBuffer(1, 0xFFFF - TM2ReadValue1 + TM2ReadValue2, 0); 
            }
			TM2ReadValue1 = TM2ReadValue2;
        }
    }
	#endif
}

#ifdef USBD_LOWPWR_MODE_ENABLE

/*!
    \brief      this function handles USBD wakeup interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  USBDWakeUp_IRQHandler (void)
{
    exti_int_flag_clear(EXTI_18);
}

#endif /* USBD_LOWPWR_MODE_ENABLE */

