/*!
    \file  systick.c
    \brief the systick configuration file
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-01-15, V1.0.0, demo for GD32F1x0(x=3,5)
    2016-05-13, V2.0.0, demo for GD32F1x0(x=3,5)
*/

#include "gd32f1x0.h"
#include "systick.h"

static uint32_t delay;

__IO unsigned int g1msTimer6 = 0;//for USB

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000)){
        /* capture error */
        while (1);
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00);
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
    delay = count;

    while(0 != delay);
}


void set_tick(uint32_t tick)
{
     delay = tick;
}


uint32_t get_tick(void)
{
    return delay;
}


/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    if (0 != delay){ 
        delay--;
    }
    if(g1msTimer6 > 0)g1msTimer6--;
}
