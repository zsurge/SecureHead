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
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "systick.h"
#include "dev_eprom.h"
#include "dev_uart.h"
#include "app.h"
#include "usbd_std.h"
#include "custom_hid_core.h"
#include "usb_endp.h"
#include "dev_msread.h"

#define USB_PULLUP                      GPIOA
#define USB_PULLUP_PIN                  GPIO_PIN_5
#define RCC_AHBPeriph_GPIO_PULLUP       RCU_GPIOA


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
	/* enable the key clock */
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_CFGCMP);
#if 0
	/* configure CPD pin as input */
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);

	/* enable and set CPD EXTI interrupt to the lowest priority */
	nvic_irq_enable(EXTI0_1_IRQn, 2, 0);

	/* connect key CPD line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);

	/* configure key CPD line */
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	exti_interrupt_flag_clear(EXTI_0);
#endif
	/* configure F2F1 pin as input */
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_7);

	/* enable and set F2F2 EXTI interrupt to the lowest priority */
	nvic_irq_enable(EXTI4_15_IRQn, 2, 0);

	/* connect F2F1 EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN7);

	/* configure F2F2 EXTI line */
	exti_init(EXTI_7, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	exti_interrupt_flag_clear(EXTI_7);

	/* configure F2F2 pin as input */
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);

	/* enable and set F2F2 EXTI interrupt to the lowest priority */
	nvic_irq_enable(EXTI0_1_IRQn, 2, 0);

	/* connect F2F2 EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN0);

	/* configure F2F2 EXTI line */
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	exti_interrupt_flag_clear(EXTI_0);


	/* configure F2F3 pin as input */
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_1);

	/* enable and set F2F3 EXTI interrupt to the lowest priority */
	nvic_irq_enable(EXTI0_1_IRQn, 2, 0);

	/* connect F2F3 EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN1);

	/* configure F2F3 EXTI line */
	exti_init(EXTI_1, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	exti_interrupt_flag_clear(EXTI_1);
}


/*******************************************************************************
* Function Name  : gpio_configuration
* Description	 : goio设置
* Input 		 : None
* Output		 : None
* Return		 : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void gpio_configuration(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);

    /*configure PA7 (TIMER1 CH1) as alternate function*/
//    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
//    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

//    gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_7);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_7);

	/*configure PB0 (TIMER1 CH2) as alternate function*/
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_0);

	/*configure PB1 (TIMER1 CH3) as alternate function*/
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);

    gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_1);

    /* configure usb pull-up pin */
    gpio_mode_set(USB_PULLUP, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, USB_PULLUP_PIN);
    gpio_output_options_set(USB_PULLUP, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, USB_PULLUP_PIN);

}

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable USB pull-up pin clock */ 
    rcu_periph_clock_enable(RCC_AHBPeriph_GPIO_PULLUP);

    /* configure USB model clock from PLL clock */
    rcu_usbd_clock_config(RCU_USBD_CKPLL_DIV1_5);

    /* enable USB APB1 clock */
    rcu_periph_clock_enable(RCU_USBD);
}

/*!
    \brief      configure interrupt priority
    \param[in]  none
    \param[out] none
    \retval     none
*/
void nvic_config(void)
{
    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);

    /* enable the USB low priority interrupt */
    nvic_irq_enable(USBD_LP_IRQn, 1, 0);
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

__IO uint8_t uartflag=0;

int main(void)
{
//	uint8_t  sbuff[24]={0};
//	uint8_t  sobuff[18]={0x45,0x21,0x3e,0x30,0x56,0x90,0x65,0x12,0x85,0x96,0x74,0x32,0x85,0x52,0x95,0x96,0x98,0x99};
//	uint8_t  fsbuff[16]={0x45,0x21,0x3e,0x30,0x56,0x90,0x65,0x12,0x85,0x96,0x74,0x32,0x85,0x52,0x95,0x96};
//	uint8_t  dsbuff[9]={0x45,0x21,0x3e,0x30,0x56,0x90,0x65,0x12,0x85};
//	uint8_t  lsbuff[8]={0x45,0x21,0x3e,0x30,0x56,0x90,0x65,0x12};
//	uint8_t  key[16]={0x45,0x21,0x3e,0x30,0x96,0x74,0x32,0x85,0x52,0x95,0x96,0x98,0x99,0x56,0x90,0x65};
//	uint8_t  loop=0,j,i;
//	
//	memcpy(sbuff,sobuff,18);
    /* SYSTICK configuration */
    systick_config();

    /* system clocks configuration */
    rcu_config();

	/* Configure EXTI Line to generate an interrupt on falling edge */
	EXTI_Configuration();

	/* Configure external signal is connected to TIMER1 CHn pin  */
	gpio_configuration();

	nvic_vector_table_set(0x08000000, 0x00003400 );
//	nvic_vector_table_set(0x08000000, 0x00000000 );
    __enable_irq();
    USBD_REG_SET(USBD_DADDR, ~DADDR_USBEN);
    
    
    /* USART initialize */
    #ifdef UART_PRINT
	dev_com_open();
//	uart_puts("APP Start...\r\n");
	#endif



	//打开定时器计时
	TIM1_Cap_Init(36 - 1);										//以 1Mhz 的频率计数
	TIM2_Cnt_Init();											//定时1.3s初始化，用于刷卡完成

    

	/* USB device configuration */
    usbd_core_init(&usb_device_dev);
//    uart_puts("1.usbd_core_init...\r\n");

    /* NVIC configuration */
    nvic_config();
//    uart_puts("2.nvic_config...\r\n");

    /* enabled USB pull-up */
    gpio_bit_set(USB_PULLUP, USB_PULLUP_PIN);
//    uart_puts("3.gpio_bit_set...\r\n");

    /* now the usb device is connected */
    usb_device_dev.status = USBD_CONNECTED;   
    uart_puts("4.usb_device_dev.status...\r\n");

    UsbRecvReset();

    ReadENCKEY();

//    loop = 3;
//		
//		DBG_S("loo= = %d\r\n",loop);
//		
//    tri_des(sbuff,key,key+8,0);
//		
//			for(j = 1;j< loop;j++)							//加密第一磁道数据
//			{
//				DBG_H("1 sbuff",sbuff,8);
//				
//				DBG_H("2 sbuff",sbuff+j*8,8);
//				
//				xor(sbuff+j*8,sbuff+j*8-8,8);
//				
//				DBG_H("3 sbuff",sbuff+j*8,8);			
//				
//				tri_des(sbuff+j*8,key,key+8,0);
//				DBG_H("4 sbuff",sbuff+j*8,8);	
//				
//			}
//		DBG_H("sbuff",sbuff,24);
    #if 1
	//复位加密磁头加密KEY
//	#ifdef FLASHKEY_SUPPORT	
//	if(!ReadENCKEY())
//	{
//		memset(ENC_KEY.key, 0x00, sizeof(ENC_KEY.key));
//		ENC_KEY.temp.level = 0x31;
//		WriteFlag = 1;	
//	}
//	#else
//	memset(ENC_KEY.key, 0x00, sizeof(ENC_KEY.key));
//	ENC_KEY.temp.level = 0x31;
//	#endif
//	  GetNextKSN();
//   memcpy(ENC_KEY.temp.sid,"\x01\x02\x03\x04\x05\x06\x07\x08",8);
//	 memcpy(ENC_KEY.temp.ksn,"\x01\x02\x03\x04\x05\x06\x07\x08\xaa\xbb",10);
//	 memcpy(ENC_KEY.temp.sn,"\x09\x08\x07\x06\x05\x04\x03\x02\x01\xdd",10);
//	 memcpy(ENC_KEY.temp.fix,"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\xaa\xbb\xcc\xdd\xee",16);
//	 ENC_KEY.temp.level=0x33;
    memset(TK3buf,0x00,sizeof(TK3buf));
		memset(TK2buf,0x00,sizeof(TK2buf));
		memset(TK1buf,0x00,sizeof(TK1buf));
    while (1) {													/* main loop */
		
			if(uartflag==97)
			{
				
				
				uartflag=0;
				
				
			}
		//喂狗
		//IWDG_ReloadCounter();
		
		//串口协议数据处理
		DealSerialParse();
		DealRxData();

		if (MSR_fCardDataReady && 0 == get_tick()) {
			MSR_Character_Decoder();
//			printf("1111\r\n");			
			MSR_SendData();//
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

