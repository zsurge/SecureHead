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
* Function Name  : TIM_Cap_Init
* Description    : 定时器2捕获计数初始化
* Input          : 预分频值
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void TIM2_Cap_Init(u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);	//使能 TIM2 和 TIM3时钟 
		
	//初始化 TIM 参数
	TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;							//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;								//预分频器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;						//TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;				//TIM 向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);								//初始化 TIMx

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);										//清除更新标志位 
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);								//清除TIM2等待中断更新中断标志位

	TIM_Cmd(TIM2, ENABLE);														//使能定时器
	
}  

/*******************************************************************************
* Function Name  : TIM3_Cnt_Init
* Description    : 定时器3定时初始化
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
void TIM3_Cnt_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 使能TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period        = 1499;								//设定的最大计数值，定时1.5秒
	TIM_TimeBaseStructure.TIM_Prescaler     = 35999;							//分频35999，at 1.00 Khz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;						//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;				//计数方向向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);										/*清除更新标志位*/ 
	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);								//清除TIM2等待中断更新中断标志位

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);									//使能TIM2的更新
	
	// 设定TIM3中断优先级
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
  
	TIM_Cmd(TIM3, DISABLE);														//TIM3 disable counter
}

