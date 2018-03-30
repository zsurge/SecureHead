/******************************************************************************
 * @file    dev_timer.c
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
#include "dev_timer.h"

/*******************************************************************************
* Function Name  : TIM1_Cap_Init
* Description    : 定时器1捕获计数初始化
* Input          : 预分频值
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void TIM1_Cap_Init(uint16_t psc)
{
	/* TIMER1 configuration: input capture mode -------------------
    the external signal is connected to TIMER1 CH1 pin (PA7)\CH2 pin (PB0)\CH3 pin (PB1)
    the rising edge is used as active edge
    the TIMER1 CH0CV is used to compute the frequency value
    ------------------------------------------------------------ */
//    timer_ic_parameter_struct timer_icinitpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);

    timer_deinit(TIMER1);

    /* TIMER1 configuration */
    timer_initpara.timer_prescaler         = psc;
    timer_initpara.timer_alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.timer_counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.timer_period            = 65535;
    timer_initpara.timer_clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.timer_repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);
#if 1
	timer_interrupt_flag_clear(TIMER1, TIMER_INT_UP);
#else
    /* TIMER1  configuration */
    /* TIMER1 CH1\CH2\CH3 input capture configuration */
    timer_icinitpara.timer_icpolarity  = TIMER_IC_POLARITY_BOTH_EDGE;
    timer_icinitpara.timer_icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.timer_icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.timer_icfilter    = 0x0;
    timer_input_capture_config(TIMER1, TIMER_CH_1, &timer_icinitpara);
	timer_input_capture_config(TIMER1, TIMER_CH_2, &timer_icinitpara);
	timer_input_capture_config(TIMER1, TIMER_CH_3, &timer_icinitpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
    /* clear channel 1\2\3 interrupt bit */
    timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH1);
	timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH2);
	timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH3);
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
	nvic_irq_enable(TIMER1_IRQn, 1, 1);
	
	/* channel 1\2\3 interrupt enable */
    timer_interrupt_enable(TIMER1, TIMER_INT_CH1IE);
	timer_interrupt_enable(TIMER1, TIMER_INT_CH2IE);
	timer_interrupt_enable(TIMER1, TIMER_INT_CH3IE);
#endif
    /* TIMER1 counter enable */
    timer_enable(TIMER1);
	
}  

/*******************************************************************************
* Function Name  : TIM2_Cnt_Init
* Description    : 定时器2定时初始化
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
void TIM2_Cnt_Init(void)
{
	timer_parameter_struct timer_initpara;

	// 使能TIM2时钟
	/* TIMERS clock enable */
	rcu_periph_clock_enable(RCU_TIMER2);

	timer_deinit(TIMER2);

    /* TIMER0 configuration */
    timer_initpara.timer_prescaler         = 2199;
    timer_initpara.timer_alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.timer_counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.timer_period            = 35999;
    timer_initpara.timer_clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.timer_repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);
	
	/* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);									//使能TIM2的更新

	timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);							/*清除更新标志位*/ 
	
	// 设定TIM3中断优先级
    /* set the priority group */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
	nvic_irq_enable(TIMER2_IRQn, 0, 1);
	
	timer_interrupt_enable(TIMER2, TIMER_INT_UP);
	timer_disable(TIMER2);														//TIM3 disable counter
}

