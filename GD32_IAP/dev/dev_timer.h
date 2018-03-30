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

#include "gd32f1x0.h"
#include "gd32f1x0_timer.h"

void TIM1_Cap_Init(uint16_t psc);
void TIM2_Cnt_Init(void);

#endif

