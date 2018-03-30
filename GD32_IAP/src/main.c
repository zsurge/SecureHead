/*!
    \file  main.c
    \brief construct a USB custom HID device
*/

/*
    Copyright (C) 2016 GigaDevice

    2014-09-06, V1.0.0, firmware for GD32F150
    2016-01-15, V1.0.1, firmware for GD32F150
    2016-04-30, V3.0.0, firmware update for GD32F150
*/

#include <string.h>
#include "usbd_std.h"
#include "custom_hid_core.h"
#include "systick.h"
#include "iap.h"
#include "ini.h"
#include "dev_uart.h"
#include "usb_endp.h"


#define USB_PULLUP                      GPIOA
#define USB_PULLUP_PIN                  GPIO_PIN_5 
#define RCC_AHBPeriph_GPIO_PULLUP       RCU_GPIOA

char (*CurProc) (void);


typedef void (*pAppFunction)(void);
pAppFunction application;
uint32_t app_address;



void rcu_config(void);
void gpio_config(void);
void nvic_config(void);

char JumpToApplication(void)
{
    /* test if user code is programmed starting from address 0x8004000 */
    if (((*(__IO uint32_t*)APP_LOADED_ADDR) & 0x2FFE0000) == 0x20000000) {

//        usbd_core_deinit();
        
        app_address = *(__IO uint32_t*) (APP_LOADED_ADDR + 4);
        application = (pAppFunction) app_address;

        /* initialize user application's stack pointer */
        __set_MSP(*(__IO uint32_t*) APP_LOADED_ADDR);        
		__disable_irq();     //PRIMASK=1,关全局中断   
		
        /* jump to user application */
        application();
		while(1);
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
 * Function      : InitUsbAll
 * Description   : initial usb
 * Input         : void
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20171110
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void ApplicationInit( void )
{
    /* SYSTICK configuration */
    systick_config();
    
    /* system clocks configuration */
    rcu_config();

    /* Configure EXTI Line to generate an interrupt on falling edge */
//	EXTI_Configuration();

    /* GPIO configuration */
    gpio_config();

    #ifdef UART_PRINT
    /* USART initialize */
	dev_com_open();
	DBG_S("IAP Start...\r\n");
	#endif
    
    /* USB device configuration */
    usbd_core_init(&usb_device_dev);
    
    UsbRecvReset();
    UsbSetRespFlag (ENABLE);

    /* NVIC configuration */
    nvic_config();

    /* enabled USB pull-up */
    gpio_bit_set(USB_PULLUP, USB_PULLUP_PIN);

    /* now the usb device is connected */
    usb_device_dev.status = USBD_CONNECTED;  
    
}

/*!
    \brief      main routine
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{    
    uint32_t counterup=0;
    ApplicationInit();

    if(ReadUpgradeFlag() != UPGRADE)
    {        
        DBG_S("Jump To Application\r\n");
	
        gpio_bit_reset(GPIOA, USB_PULLUP_PIN); 

      while(counterup != 0xfFFFE)
    	{
    		counterup++;
    	}
        
        JumpToApplication(); 

        counterup = 0;
      while(counterup != 0xfFFFE)
    	{
    		counterup++;
    	}        
    }
    else
    {      
        uart_puts("iap is start\r\n");

        counterup = 0;

        while(counterup != 0xfFFFE)
    	{
    		counterup++;
    	}

        while(1)
        {
            UsbUpdata();
//            IapProcess();
        }   
       
    }

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
    \brief      configure the gpio peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_config(void)
{
    /* configure usb pull-up pin */
    gpio_mode_set(USB_PULLUP, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, USB_PULLUP_PIN);
    gpio_output_options_set(USB_PULLUP, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, USB_PULLUP_PIN);
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

