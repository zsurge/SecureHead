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

#define USB_PULLUP                      GPIOA
#define USB_PULLUP_PIN                  GPIO_PIN_5
#define RCC_AHBPeriph_GPIO_PULLUP       RCU_GPIOA


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
* Description	 : goio����
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

    /* USB wakeup EXTI line configuration */
    exti_interrupt_flag_clear(EXTI_18);
    exti_init(EXTI_18, EXTI_INTERRUPT, EXTI_TRIG_RISING);
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

    /* enable the power clock */
    rcu_periph_clock_enable(RCU_PMU);

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

    /* enable the USB Wake-up interrupt */
    nvic_irq_enable(USBDWakeUp_IRQChannel, 0, 0);
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
	/********************configure the clock****************************/
	//set sysclock 72MHZ, clocksource = PLL, enable HSI
	rcu_deinit();
	
	RCU_CTL0 |= 1;		//enable HIS
	while(!(RCU_CTL0 & (1 << 1)));

	rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
	rcu_pll_config(RCU_PLLSRC_IRC8M_DIV2, ((1<<27)|(1<<18)));

	RCU_CTL0 |= (1 << 24);
	while(!(RCU_CTL0 & (1 << 25)));
	/******************************************************************/


    /* SYSTICK configuration */
    systick_config();

    /* system clocks configuration */
    rcu_config();

	/* Configure EXTI Line to generate an interrupt on falling edge */
	EXTI_Configuration();

	/* Configure external signal is connected to TIMER1 CHn pin  */
	gpio_configuration();

	nvic_vector_table_set(0x08000000, 0x00003400 );
    __enable_irq();
    USBD_REG_SET(USBD_DADDR, ~DADDR_USBEN);
    
    
    /* USART initialize */
	dev_com_open();
	uart_puts("APP OK...\r\n");

	//�򿪶�ʱ����ʱ
	TIM1_Cap_Init(36 - 1);										//�� 1Mhz ��Ƶ�ʼ���
	TIM2_Cnt_Init();											//��ʱ1.3s��ʼ��������ˢ�����


	/* USB device configuration */
    usbd_core_init(&usb_device_dev);
    uart_puts("1.usbd_core_init...\r\n");

    /* NVIC configuration */
    nvic_config();
    uart_puts("2.nvic_config...\r\n");

    /* enabled USB pull-up */
    gpio_bit_set(USB_PULLUP, USB_PULLUP_PIN);
    uart_puts("3.gpio_bit_set...\r\n");

    /* now the usb device is connected */
    usb_device_dev.status = USBD_CONNECTED;   
    uart_puts("4.usb_device_dev.status...\r\n");

    UsbRecvReset();

//    while(1)
//    {
//        delay_1ms(3000);
//        uart_puts("main while\r\n");
//    }

    
    #if 1
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
		
		//ι��
		//IWDG_ReloadCounter();
		
		//����Э�����ݴ���
		DealSerialParse();
		DealRxData();

		if (MSR_fCardDataReady && 0 == get_tick()) {
			MSR_Character_Decoder();
						
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

