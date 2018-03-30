#ifndef _EPROM_H_
#define _EPROM_H_

#include "stm32f10x.h"

void ReadBlockFlash(uint32_t ADDR ,u8 *Sourcebuf ,u16 len);
int CheckEarseFlash(u8 *Buf);
int EarseBlockFlash(uint32_t ADDR );
int WriteBlockFlash(uint32_t ADDR ,u8 *Sourcebuf ,u16 len);

#endif

