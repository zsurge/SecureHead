/***********************************************************************************
 * 文 件 名   : ini.c
 * 负 责 人   : 张舵
 * 创建日期   : 2017年10月25日
 * 文件描述   : 终端参数读写
 * 版权说明   : Copyright (c) 2008-2017   深圳标富科技有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ini.h"


T_MagCardParam gMagCardParam;				//升级标志位

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


