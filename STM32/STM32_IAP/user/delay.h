#ifndef __DELAY_H
#define __DELAY_H

#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"

void delay_init(u8 SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t Nus);

#endif
