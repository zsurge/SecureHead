/***********************************************************************************
 * �� �� ��   : ini.c
 * �� �� ��   : �Ŷ�
 * ��������   : 2017��10��25��
 * �ļ�����   : �ն˲�����д
 * ��Ȩ˵��   : Copyright (c) 2008-2017   ���ڱ긻�Ƽ����޹�˾
 * ��    ��   : 
 * �޸���־   : 
***********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ini.h"


T_MagCardParam gMagCardParam;				//������־λ

char ReadUpgradeFlag()
{ 
    ClearMagCardParam();
    uint8_t tempdata[64];
	memset(tempdata ,0x00, 64);
    
	ReadBlockFlash(PARAM_START_ADD ,tempdata, 4);
    memcpy(gMagCardParam.UpgradeFlag,tempdata,4);

    //DBG_H("iap upgrade flag", gMagCardParam.UpgradeFlag, 4);

    if(gMagCardParam.UpgradeFlag[0] == 0xAA \
        &&gMagCardParam.UpgradeFlag[1] == 0xBB\
        &&gMagCardParam.UpgradeFlag[2] == 0XAA\
        &&gMagCardParam.UpgradeFlag[3] == 0XBB)
        {  
            return UPGRADE;
        }
    return NOTUPGRADE;    
	
}

void WriteUpgradeFlag()
{    	
    unsigned char flag[4] = {0xAA,0xBB,0xAA,0xBB};
    
	__disable_irq();
	EarseBlockFlash(PARAM_START_ADD);
	WriteBlockFlash(PARAM_START_ADD ,flag, 4);
	__enable_irq();
	return ;	
}

void WriteUpgradeCompleFlag()
{    	
    unsigned char flag[4] = {0x55,0xaa,0x55,0xaa};
    
	__disable_irq();
	EarseBlockFlash(PARAM_START_ADD);
	WriteBlockFlash(PARAM_START_ADD ,flag, 4);
	__enable_irq();
	return ;	
}

void ClearMagCardParam()
{
	memset(&gMagCardParam,0x00,sizeof(gMagCardParam));
}


