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
* Description    : ��ʱ��2���������ʼ��
* Input          : Ԥ��Ƶֵ
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-05
*******************************************************************************/
void TIM2_Cap_Init(u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);	//ʹ�� TIM2 �� TIM3ʱ�� 
		
	//��ʼ�� TIM ����
	TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;							//�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;								//Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;						//TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;				//TIM ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);								//��ʼ�� TIMx

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);										//������±�־λ 
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);								//���TIM2�ȴ��жϸ����жϱ�־λ

	TIM_Cmd(TIM2, ENABLE);														//ʹ�ܶ�ʱ��
	
}  

/*******************************************************************************
* Function Name  : TIM3_Cnt_Init
* Description    : ��ʱ��3��ʱ��ʼ��
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

	// ʹ��TIM3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period        = 1499;								//�趨��������ֵ����ʱ1.5��
	TIM_TimeBaseStructure.TIM_Prescaler     = 35999;							//��Ƶ35999��at 1.00 Khz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;						//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;				//�����������ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);										/*������±�־λ*/ 
	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);								//���TIM2�ȴ��жϸ����жϱ�־λ

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);									//ʹ��TIM2�ĸ���
	
	// �趨TIM3�ж����ȼ�
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
  
	TIM_Cmd(TIM3, DISABLE);														//TIM3 disable counter
}

