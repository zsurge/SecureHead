#ifndef _EPROM_H_
#define _EPROM_H_

#include "gd32f1x0.h"
#include "gd32f1x0_fmc.h"

void ReadBlockFlash(uint32_t ADDR ,uint8_t *Sourcebuf ,uint16_t len);
int CheckEarseFlash(uint8_t *Buf);
int EarseBlockFlash(uint32_t ADDR );
int WriteBlockFlash(uint32_t ADDR ,uint8_t *Sourcebuf ,uint16_t len);

#endif

