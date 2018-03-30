/******************************************************************************
 * @file    dev_timer.h
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
#ifndef __DEV_TIMER_H__
#define __DEV_TIMER_H__

#include "stm32f10x.h"

void TIM2_Cap_Init(u16 psc);
void TIM3_Cnt_Init(void);

#endif

