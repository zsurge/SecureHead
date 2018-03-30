#include <string.h>
#include <stdio.h>
#define AFX_MAG_DECODE_VARIABLES
#include "magdecode.h"
#undef AFX_MAG_DECODE_VARIABLES

#define BSYNC				4							//同步计数器个数
#define CURNC				8							//平滑计算位周期个数
#define TRACKERRORLENGTH	0

volatile char MSR_fCardDataReady = 0;
#ifdef TIMERFLOW_12BIT
/*****************************************************************************
**| 0x123 | 0x456 |  0x789 |  ...... |  0x123 | 0x456
**|————————————————————————————————————————————————————————————————————————--|
**|  0 |  1  |  2 |  3  |  4 |...... | n-2  | n-1  |  n														 
**|————————————————————————————————————————————————————————————————————————--|
**| 23 | 14  | 56 | 89     7x ...... |  23  |  14  |  56
**|————————————————————————————————————————————————————————————————————————--|
**|1字节+高半字节|HSB        LSB|   ......     |HSB        LSB|低半字节+1字节| 																  
**|————————————————————————————————————————————————————————————————————————--|
**|    偶数据	  |    奇数据    |   ...........................				  | 																  
**|————————————————————————————————————————————————————————————————————————--|
第一个数据为0x0123, 第二个数据为0x0456,则压成12bit后保存的时间流为0x23 0x14 0x56,反转后为0x56 0x14 0x23
数据量为奇数个数,补成偶数个
*****************************************************************************/
static void _input_12bit_data(uint8_t *src, uint16_t timeflowcnt, uint16_t value)
{
    uint16_t offset;
    
    offset = (timeflowcnt * 3) >> 1;
    if (timeflowcnt & 0x01) {
        src[offset] |= (value >> 8) & 0x0f;    //高4bit放在第一字节低四位
        src[offset + 1] = value & 0xff;      //低8bit放在第二字节
    } else {
		src[offset] = value & 0xff;              //低8bit放在第一字节
		src[offset + 1] = (value >> 4) & 0xf0;     //高4bit放在第二字节高四位
	}
}
/*****************************************************************************
*****************************************************************************/
static uint16_t _output_12bit_data(uint8_t *src, uint16_t timeflowcnt)
{
    uint16_t value;
    uint16_t offset;
    
    offset = (timeflowcnt * 3) >> 1;
    if (timeflowcnt & 0x01) { 
		value = ((((uint16_t)src[offset]) << 8) & 0x0f00) + src[(offset) + 1];
    } else {
		value = ((((uint16_t)src[(offset) + 1]) << 4)& 0xf00) + src[offset];
    }
    return value;
}
#endif

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static void SetBit(uint8_t *lpByte,uint8_t nBit)
{
    *lpByte |= (0x01<<nBit);
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static void ClearBit(uint8_t *lpByte,uint8_t nBit)
{
    *lpByte &= ~(0x01<<nBit);
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static void CplBit(uint8_t *lpByte,uint8_t nBit)
{
	*lpByte ^= (0x01<<nBit);
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static uint8_t CheckLrcEvenParity(uint8_t *lpIn,uint16_t nLen,uint8_t nBitPos)
{
	uint16_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i <nLen; i++)
	{
		if(((lpIn[i] >> nBitPos) & 0x01) == 0x01)
		{
			BitCnt ++;
		}
	}
	if((BitCnt % 2) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static uint16_t CheckLrcDirtOnlyOne(uint16_t *lpOutDirtPos,uint8_t *lpIn,uint16_t nLen,uint8_t nBitPos)
{
	uint16_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i <nLen; i++)
	{
		if(((lpIn[i] >> nBitPos) & 0x01) == 0x01)
		{
			*lpOutDirtPos = i;
			BitCnt ++;
		}
	}
	if(BitCnt == 1)								//只有一位可疑位
	{
		return 1;								//返回唯一一位污染
	}
	else
	{
		return 0;								//返回没有污染
	}	
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static const uint8_t PARITY_TAB[16] = {0, 1, 1, 2, 1, 2, 2, 3,
                                       1, 2, 2, 3, 2, 3, 3, 4};
static uint8_t CheckOddParity(uint8_t nByte)
{
    return (PARITY_TAB[nByte&0x0f]+PARITY_TAB[(nByte>>4)&0x0f])&0x01;
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static uint8_t CheckDirtOnlyOne(uint8_t nByte)
{
	uint8_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i < 8; i++)
	{
		if((nByte & 0x01) == 0x01)
		{
			BitCnt ++;
		}
		nByte >>= 1;
	}
	if(BitCnt == 1)								//只有一位可疑位
	{
		return 1;						
	}
	else
	{
		return 0;
	}	
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注: 
********************************************************************/
static uint16_t GetDelta(uint16_t FirstData,uint16_t SecondData)
{
	if(FirstData > SecondData)
	{
		return FirstData - SecondData;
	}
	else
	{
		return SecondData - FirstData; 
	}
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 
返 回 值: 
备	  注:
********************************************************************/
static uint16_t PllSmooth(uint16_t *lpIn,uint16_t nLen)
{
	uint32_t i,average = 0;

	if(nLen >= CURNC)
	{
		for(i = 1; i <= CURNC; i++)
		{
			average += lpIn[nLen-i];
		}
		average /= CURNC;
	}
	else
	{
		for(i = 0; i < nLen; i++)
		{
			average += lpIn[i];
		}
		average /= nLen;
	}
	return (uint16_t)average;
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 
入口参数: 高4位：1: 一轨解码, 2: 二轨解码, 3: 三轨解码
          低4位：5: 5Bit编码, 6: 6Bit编码, 7: 7Bit编码, 8: 8Bit编码
返 回 值: 
备	  注: 
********************************************************************/
static void ResortMagData( uint8_t  type)
{
  #ifndef TIMERFLOW_12BIT  
	uint16_t lpInTimeFlowLength,*lpInTimeFlowValue;
	uint16_t i,nLoopCount = 0,uData;
	type = type >> 4;
	if (1 == type)
	{
		lpInTimeFlowLength = Track1TimeFlow.Length;
		lpInTimeFlowValue = Track1TimeFlow.Value;
	}
	else if (2 == type)
	{
		lpInTimeFlowLength = Track2TimeFlow.Length;
		lpInTimeFlowValue = Track2TimeFlow.Value;
	}
	else if (3== type)
	{
		lpInTimeFlowLength = Track3TimeFlow.Length;
		lpInTimeFlowValue = Track3TimeFlow.Value;
	}
	else
	{
		return ;
	}
	nLoopCount = lpInTimeFlowLength / 2;
	
	for ( i = 0; i < nLoopCount; i ++ )
	{
		uData = lpInTimeFlowValue[i];
		lpInTimeFlowValue[i] = lpInTimeFlowValue[lpInTimeFlowLength-i-1];
		lpInTimeFlowValue[lpInTimeFlowLength-i-1] = uData;
	}
  #else
	uint16_t lpInTimeFlowLength;
    uint8_t  *lpInTimeFlowValue;
	uint16_t i,nLoopCount = 0;
    uint8_t uData;

	type = type >> 4;
	if (1 == type)
	{
        Track1TimeFlow.Length = (Track1TimeFlow.Length+1)&0xfffe;
		lpInTimeFlowLength = Track1TimeFlow.Length;
		lpInTimeFlowValue = Track1TimeFlow.Value;
	}
	else if (2 == type)
	{
        Track2TimeFlow.Length = (Track2TimeFlow.Length+1)&0xfffe;
		lpInTimeFlowLength = Track2TimeFlow.Length;
		lpInTimeFlowValue = Track2TimeFlow.Value;
	}
	else if (3== type)
	{
        Track3TimeFlow.Length = (Track3TimeFlow.Length+1)&0xfffe;
		lpInTimeFlowLength = Track3TimeFlow.Length;
		lpInTimeFlowValue = Track3TimeFlow.Value;
	}
	else
	{
		return ;
	}
    lpInTimeFlowLength = (lpInTimeFlowLength*3)>>1;
	nLoopCount = lpInTimeFlowLength / 2;
	
	for ( i = 0; i < nLoopCount; i ++ )
	{
		uData = lpInTimeFlowValue[i];
		lpInTimeFlowValue[i] = lpInTimeFlowValue[lpInTimeFlowLength-i-1];
		lpInTimeFlowValue[lpInTimeFlowLength-i-1] = uData;
	}
    //把保存高位字节的高4bit和低4bit对调
    for(i=1; i< lpInTimeFlowLength; i+=3) 
    {
        lpInTimeFlowValue[i] = ((lpInTimeFlowValue[i]<<4)&0xF0)|((lpInTimeFlowValue[i]>>4)&0X0F);
    }
  #endif
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 所有的位都需要计算精确的加速度出来
入口参数: 高4位：1: 一轨解码, 2: 二轨解码, 3: 三轨解码
          低4位：5: 5Bit编码, 6: 6Bit编码, 7: 7Bit编码, 8: 8Bit编码
返 回 值: 
备	  注: 1.考虑当前滑动周期(平均和可疑位取值).  
		  2.考虑加速度和减速取值区间问题
          3.******考虑丢位,目前可以考虑插位  
		  4.丢位引起最大误差为3Nibble~6Nibble.
		  5.如果丢位超过6Nibble，可以认为失败。
		  6.在120%模糊地带，有个问题，就是会把本来是1的前半部分考虑为0，导致多位，后面
		    全部会混乱，解决这个问题可以考虑当前是加速度还是减速度渗入区间来界定。
		  7.在出现连续丢位情况下，我们要计算合理加速度.
		  8.示波器上显示，3磁道数据刷的越慢，误差更大+/-20%，越快，误差越小+/-10%
		    可以通过当前周期值判断现在刷卡数据，同步误差比例,比如用误差值而不是百分比?.
		  9.****出现可疑位,我们用纠错算法,如果未出现可疑位,我们用传统纠一位算法实现丢一位正确位情况 
		  10.****考虑最后不稳定位是否应该直接丢弃
		  11.时间流也要考虑正解和反解
********************************************************************/
uint8_t DecodeTimeToBit(uint8_t type)
{
	uint8_t  bSync = 0,bFlag,bCompensate = 0;
	uint8_t  ProbePulse = 0,ProbeDirt = 0;
	uint16_t SyncCnt = 0,CurTimeFlowCnt = 0,CurPercent = 0;
	uint32_t i,j;
	uint16_t CurPllCycle = 0,CurPllCycleTemp[CURNC] = {0},curnclen = 0;
	int ProbeTotalTime = 0;
	uint16_t lpInTimeFlowLength;
	#ifndef TIMERFLOW_12BIT
    uint16_t *lpInTimeFlowValue;
	#else
	uint8_t *lpInTimeFlowValue;
	#endif
    uint16_t ltmpu16, ltmpu16_next;

	type = type >> 4;
	if (1 == type)
	{
		lpInTimeFlowLength = Track1TimeFlow.Length;
		lpInTimeFlowValue = Track1TimeFlow.Value;
	}
	else if (2 == type)
	{
		lpInTimeFlowLength = Track2TimeFlow.Length;
		lpInTimeFlowValue = Track2TimeFlow.Value;
	}
	else if (3== type)
	{
		lpInTimeFlowLength = Track3TimeFlow.Length;
		lpInTimeFlowValue = Track3TimeFlow.Value;
	}
	else
	{
		return 3;
	}
	memset((uint8_t*)&TrackBitFlow,0,sizeof(TRACKBITFLOW));
    
	for(CurTimeFlowCnt = 0; CurTimeFlowCnt < lpInTimeFlowLength; CurTimeFlowCnt++)
	{
		if(!bSync)																								//磁道数据未同步上,需要继续同步
		{
			#ifndef TIMERFLOW_12BIT  
            if((lpInTimeFlowValue[CurTimeFlowCnt] == 0) || (lpInTimeFlowValue[CurTimeFlowCnt] > 30000))		//防止除数为零								//过滤干扰周期,按2磁道最慢速度10cm/s计算,最慢1位周期不能小于3333us.
			#else  
			ltmpu16  = _output_12bit_data(lpInTimeFlowValue, CurTimeFlowCnt);
            if((0 == ltmpu16) || (30000 < ltmpu16))
			#endif
            {
				continue;
			}
          #ifndef TIMERFLOW_12BIT 
			i = GetDelta(CurPllCycle,lpInTimeFlowValue[CurTimeFlowCnt]);
			i = (i*100) /lpInTimeFlowValue[CurTimeFlowCnt];
			CurPllCycle = lpInTimeFlowValue[CurTimeFlowCnt];
          #else
			i = GetDelta(CurPllCycle,ltmpu16);
			i = (i*100) /ltmpu16;
			CurPllCycle = ltmpu16;
		  #endif	
			if(i > 30)																							//同步头连续误差不应该超过20%,可以考虑更科学同步方法,冒泡控制10位总误差不能超过20%                  
			{
				SyncCnt = 0;
			}
			else
			{
				SyncCnt ++;
				if(SyncCnt >= CURNC)															//同步上了
				{
					bSync = 1;
					ProbeDirt = 0;
					ProbePulse = 0;
					ProbeTotalTime = 0;
					TrackBitFlow.Length = 0;
					curnclen = 0;
					for(i = 0; i < (uint32_t)CurTimeFlowCnt+1; i ++)
					{
						//TrackBitFlow.Value[i] = 0xff;
                      #ifndef TIMERFLOW_12BIT 
						CurPllCycleTemp[i%CURNC] = lpInTimeFlowValue[i];
                      #else
                        CurPllCycleTemp[i%CURNC] = _output_12bit_data(lpInTimeFlowValue, i);
                      #endif
					}
					curnclen = CurTimeFlowCnt+1;
				}
			}
		}
		else
		{
			#ifndef TIMERFLOW_12BIT
			ltmpu16  = lpInTimeFlowValue[CurTimeFlowCnt];
			#else
			ltmpu16  = _output_12bit_data(lpInTimeFlowValue, CurTimeFlowCnt);
			#endif
            ProbeTotalTime += ltmpu16;
			CurPllCycle = PllSmooth(CurPllCycleTemp,CURNC);
			CurPercent = (ProbeTotalTime * 100) / CurPllCycle;
			i = (ltmpu16*100) / CurPllCycle; 
			if(i >= 20 && i < 33)															//非稳态区域											
			{
				ProbeDirt = 1;
			}
			if(CurPercent >= 33 && CurPercent < 70)											//稳定半周期，抗两端尖峰干扰
			{
				if(i < 20)
				{
					ProbeDirt = 1;															//中间尖峰干扰
				}
				ProbePulse ++;																//跳变加加
			}
			else if(CurPercent >= 70 && CurPercent < 130)									//稳定全周期 幅度不能收窄,否则有些卡过不去
			{             
				bFlag = 0;
				#ifndef TIMERFLOW_12BIT
				ltmpu16_next = lpInTimeFlowValue[CurTimeFlowCnt + 1];
				#else
                ltmpu16_next = _output_12bit_data(lpInTimeFlowValue, CurTimeFlowCnt + 1);
				#endif
				if((!(CurPercent >= 90 && CurPercent < 110)) && ((CurTimeFlowCnt+1) < lpInTimeFlowLength))
				{
					if(((ltmpu16_next !=0 ) && (((ltmpu16_next * 100) / CurPllCycle) < 33)) 
						&& ((((ProbeTotalTime+ltmpu16_next) * 100) / CurPllCycle) < 110))	//累加超过20%，会导致MARK位增加
					{
						bFlag = 1;
						bCompensate ++;
					}
				}
				if(bFlag == 0)
				{
					if(bCompensate == 0)													//没有实施补偿
					{
						if(ProbePulse == 1 && ((ltmpu16*100) / CurPllCycle) < 20)
						{
							ProbePulse = 0;													//防止边沿干扰,控制+20大于70%边
						}
					}
					if(CurPllCycle > ProbeTotalTime)
					{
						i = CurPllCycle - ProbeTotalTime;
						if((i * 100 / CurPllCycle) < 35)
						{
							CurPllCycleTemp[curnclen%CURNC] = ProbeTotalTime;curnclen++;
							ProbeTotalTime = 0;
						}
						else
						{
							j = (7 * i) / 8;
							CurPllCycleTemp[curnclen%CURNC] = ProbeTotalTime + j;curnclen++;
							ProbeTotalTime = CurPllCycle - (ProbeTotalTime + j);
						}
					}
					else
					{
						i = ProbeTotalTime - CurPllCycle;
						if((i * 100 / CurPllCycle) < 35)
						{
							CurPllCycleTemp[curnclen%CURNC] = ProbeTotalTime;curnclen++;
							ProbeTotalTime = 0;
						}
						else
						{
							j = (1 * i) / 8;
							CurPllCycleTemp[curnclen%CURNC] = ProbeTotalTime - j;curnclen++;
							ProbeTotalTime = j;
						}
					}
					if(ProbeDirt == 1)
					{
						if (TrackBitFlow.Length < TRACKBITFLOWLENGTH)
							TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
						else
							break;
					}
					else 
					{
						if(ProbePulse > 0)			
						{
							if (TrackBitFlow.Length < TRACKBITFLOWLENGTH)
								TrackBitFlow.Value[TrackBitFlow.Length++] = 1;
							else
								break;
						}
						else
						{
							if (TrackBitFlow.Length < TRACKBITFLOWLENGTH)
								TrackBitFlow.Value[TrackBitFlow.Length++] = 0;
							else
								break;
						}
					}
					bCompensate = 0;
					ProbePulse = 0;
					ProbeDirt = 0;
				}
			}
			else if(CurPercent >= 130)																			//非稳态
			{
				j = 0; 
				while(ProbeTotalTime >= CurPllCycle) 
				{
					j ++;
					if (j>10)
						break;
					CurPllCycleTemp[curnclen%CURNC] = CurPllCycle;curnclen++;
					ProbeTotalTime -= CurPllCycle;
					CurPllCycle = PllSmooth(CurPllCycleTemp,CURNC);
					if (TrackBitFlow.Length < TRACKBITFLOWLENGTH)
						TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
					else
						break;
				}
				ProbeDirt = 0;
				ProbePulse = 0;
				bCompensate = 0;
				i = (ProbeTotalTime*100)/CurPllCycle;	
				if(i < 40)											//if((j <= 1 && i <= 25) || ((j > 1 && i <= 33))) 幅度尽量放开,1号卡就遇到过不去情况																			
				{
					CurPllCycleTemp[(curnclen-1)%CURNC] += ProbeTotalTime;
					ProbeTotalTime = 0;
				}
				else if(i >= 70)
				{
					CurPllCycleTemp[curnclen%CURNC] = ProbeTotalTime;curnclen++;
					if (TrackBitFlow.Length < TRACKBITFLOWLENGTH)
						TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
					else
						break;
					ProbeTotalTime = 0;	
				}
				else
				{
					ProbeDirt = 1;
					ProbePulse = 1;
				}
			}
		}
	}
	//解码结束
	if(!bSync)
	{
		memset((uint8_t*)&TrackBitFlow, 0, sizeof(TRACKBITFLOW));
		return 0;
	}
	else
	{
		return 1;
	}
}


/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 将Bit信息解码成字符信息
入口参数: 高4位：1: 一轨解码, 2: 二轨解码, 3: 三轨解码
          低4位：5: 5Bit编码, 6: 6Bit编码, 7: 7Bit编码, 8: 8Bit编码
返 回 值: 0: 解码成功，1: 解码错,   2: 解码空 
备	  注: 
********************************************************************/
uint8_t DecodeTrackData(uint8_t type)
{
	TRACKDATA *lpOutTrackData;
	uint16_t i,j,k,m,FirstBitCnt,SndBitCnt,FirstOkByteCnt,SndOkByteCnt;
	uint8_t BitCnt = 0,SyncStep,bFlag,bData;
	uint8_t bSyncHead,bCorrectDirt,bCheckOk,DecodeTimes,bFinalSucc,bFinalCorrect;
	uint8_t bEachCorrected;			//中间只要有纠错或者2地方,放弃纠错
		
	if (0x15 == type|| 0x16 == type || 0x17 == type || 0x18 == type)
	{
		lpOutTrackData = &Track1Data;
	}
	else if (0x25 == type)
	{
		lpOutTrackData = &Track2Data;
	}
	else if (0x35 == type || 0x36 == type || 0x37 == type)
	{
		lpOutTrackData = &Track3Data;
	}
	else
		return 2;

	memset((uint8_t*)lpOutTrackData,0,sizeof(TRACKDATA));
	if (!TrackBitFlow.Length)
		return 2;
	
	FirstBitCnt = 0;
	SndBitCnt = 0;
	FirstOkByteCnt = 0;
	SndOkByteCnt = 0;
	bFinalSucc = 0;

	for(DecodeTimes = 0; DecodeTimes < 2; DecodeTimes ++)				//正反双向解码
	{
		bSyncHead = 0;
		SyncStep = 0;
		bFinalCorrect = 0;
		bEachCorrected = 0;
		
		for(k = 0; k < TrackBitFlow.Length; k ++)
		{
			if(DecodeTimes == 0)									    //正向解
			{
				i = k;
			}
			else														//反向解
			{
				i = TrackBitFlow.Length - (k + 1);
			}
			bData = TrackBitFlow.Value[i];
			if(bData == 2)												//缺省全部转换为零解
			{
				bData = 0;
			}
			if(!bSyncHead)												//找同步头
			{
				if (7 == (type & 0x0F))
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 0)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 1)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 0)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 0)
							{
								SyncStep = 6;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 6:
							if(bData == 1)							//同步上了
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0x45;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(5 == (type & 0x0F))
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 1)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 0)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 1)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)											//同步上了
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0x0B;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(6 == (type & 0x0F))											//CADMV标准
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							} else {
								SyncStep = 0;
							}
							break;
						case 1:
							if(bData == 0)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							memset((uint8_t*)&TempTrackDirtData, 0, sizeof(TempTrackDirtData));
							memset((uint8_t*)&TempTrackData, 0, sizeof(TempTrackData));
							if(bData == 1 && 0x16 == type)							//一磁道 Start Sentinel is % (05H)
							{
								TempTrackData.Value[0] = 0x05;
								SyncStep = 3;
							}
							else if(bData == 0 && 0x36 == type)						//三磁道 Start Sentinel is ! (01H)
							{
								TempTrackData.Value[0] = 0x01;
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 0)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 0)											//同步上了
							{
								bSyncHead = 1;
								BitCnt = 0;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(8 == (type & 0x0F))											//JIS2标准
				{
					switch(SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 1)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 1)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 1)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 1)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 1)
							{
								SyncStep = 6;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 6:
							if(bData == 1)
							{
								SyncStep = 7;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 7:
							if(bData == 1)							//同步上了
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0xff; //JIS2为0Xff
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
			}
			else
			{
				if(TrackBitFlow.Value[i] == 0)
				{
					ClearBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);		
				}
				else if(TrackBitFlow.Value[i] == 1)
				{
					SetBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);
				}
				else //if(TrackBitFlow.Value[i] == 2)
				{
					ClearBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);
					SetBit(&TempTrackDirtData.Value[TempTrackDirtData.Length],BitCnt);
				}
				BitCnt ++;
				if (7 == (type & 0x0F))
				{
					BitCnt %= 7;
				}
				else if(5 == (type & 0x0F))
				{
					BitCnt %= 5;
				}
				else if(6 == (type & 0x0F))
				{
					BitCnt %= 6;
				}
				else if(8 == (type & 0x0F))
				{
					BitCnt %= 8;
				}
				
				if(BitCnt == 0)																//BitCnt位一个字节			
				{
					if (TempTrackData.Length < TRACKDATALENGTH-1  )
					{
						TempTrackData.Length ++;
						TempTrackDirtData.Length ++;
					}
					else
					{
						break;
					}
				}
			}
		}

		type &= 0x0F;																		//取磁道数据编码位数
		if(bSyncHead)																		//同步上了,校验数据
		{
			if(DecodeTimes == 0)
			{
				if (7 == type)
				{
					FirstBitCnt = TempTrackData.Length * 7;
				}
				else if(5 == type)
				{
					FirstBitCnt = TempTrackData.Length * 5;
				}
				else if(6 == type)
				{
					FirstBitCnt = TempTrackData.Length * 6;
				}
				else if(8 == type)
				{
					FirstBitCnt = TempTrackData.Length * 5;
				}
			}
			else
			{
				if (7 == type)
				{
					SndBitCnt = TempTrackData.Length * 7;
				}
				else if (5 == type)
				{
					SndBitCnt = TempTrackData.Length * 5;
				}
				else if (6 == type)
				{
					SndBitCnt = TempTrackData.Length * 6;
				}
				else if (8 == type)
				{
					SndBitCnt = TempTrackData.Length * 8;
				}
			}
			bFlag = 0;
			for(j = 0; (bFlag == 0) && (j < 2); j++)										//查找结束符
			{
				for(i = 1; i < TempTrackData.Length; i ++)
				{
					
					if (7 == type)
					{
						bData = 0x7F;
					}
					else if (6 == type)
					{
						bData = 0x3F;
					}
					else if (5 == type)
					{
						bData = 0x1F;
					}
					else if (8 == type)
					{
						bData = 0xFF;
					}
					if(
					((8 != type)&&((TempTrackData.Value[i] & bData) == 0x1F)) ||
					((8 == type)&&((TempTrackData.Value[i] & bData) == 0xFF))
					)																			//找到结束符
					{
						TempTrackData.Length = i + 2;											//提前结束
						TempTrackDirtData.Length = i + 2;
						bFlag = 1;
						break;
					}
				}
				if(bFlag == 0 && j == 0 && 6 != type)											//CADMV标准无字符校验	
				{
					for(i = 0; i < TempTrackData.Length; i ++)									//横向纠错
					{
						if(!CheckOddParity(TempTrackData.Value[i]))								//奇校验字节OK
						{
							if(CheckDirtOnlyOne(TempTrackDirtData.Value[i]))
							{
								TempTrackData.Value[i] ^= TempTrackDirtData.Value[i]; 
								if (7 == type)
								{
									bData = 0x7F;
								}
								else if(5 == type)
								{
									bData = 0x1F;
								}
								else if(8 == type)
								{
									bData = 0xFF;
								}
								
								if(
								((8 != type)&&((TempTrackData.Value[i] & bData) == 0x1F)) ||
								((8 == type)&&((TempTrackData.Value[i] & 0xFF) == 0xFF))
								)						//是结束符
								{
									bEachCorrected++;
									TempTrackDirtData.Value[i] = 0x00;							//直接纠正,有个案例就错3位，但同时会引入上送错误卡号风险
									bFinalCorrect = 1;	
									break;
								}
								else
								{
									TempTrackData.Value[i] ^= TempTrackDirtData.Value[i];		//异或回去
								}
							}
						}
					}
				}
			}
			if(bFlag == 1 && 6 != type)															//校验纠错
			{
				do
				{
					bCheckOk = 1;
					bCorrectDirt = 0;
					for(i = 0; i < TempTrackData.Length; i ++)									//横向纠错
					{
						if(!CheckOddParity(TempTrackData.Value[i]))								//奇校验字节OK
						{
							if(DecodeTimes == 0)
							{
								if(FirstOkByteCnt < 8)							
								{
									FirstOkByteCnt = 0;
								}
							}
							else
							{
								if(SndOkByteCnt < 8)
								{
									SndOkByteCnt = 0;
								}
							}
							bCheckOk = 0;
							if(CheckDirtOnlyOne(TempTrackDirtData.Value[i]))
							{
								bEachCorrected++;
								TempTrackData.Value[i] ^= TempTrackDirtData.Value[i];
								TempTrackDirtData.Value[i] = 0x00;
								bCorrectDirt = 1;
								bFinalCorrect = 1;
							}
						}
						else																	//必须要连续错8BYTE才认为正确磁卡数据
						{
							if(DecodeTimes == 0)
							{
								FirstOkByteCnt++;
							}
							else
							{
								SndOkByteCnt++;
							}
						}
					}
					if (7 == type)
					{
						bData = 6;
					}
					else if (5 == type)
					{
						bData = 4;
					}
					else if( 8 == type)
					{
						bData = 7;
					}
					for(i = 0; i < bData; i ++)
					{
						if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)i))					//纵向校验错
						{
							bCheckOk = 0;
							if(CheckLrcDirtOnlyOne(&j,TempTrackDirtData.Value,TempTrackDirtData.Length,(uint8_t)i))	//有唯一的污染位
							{
								bEachCorrected++;
								CplBit(&TempTrackData.Value[j],(uint8_t)i);
								ClearBit(&TempTrackDirtData.Value[j],(uint8_t)i);
								bCorrectDirt = 1;
								bFinalCorrect = 1;
							}
						}
					}
				}while(bCorrectDirt);
				if(!bCheckOk)																					//校验通过
				{
					do																						//交叉校验 
					{
						bCheckOk = 1;
						bCorrectDirt = 0;
						k = 0;
						m = 0;
						for(i = 0; i < TempTrackData.Length; i ++)									//横向纠错
						{
							if(!CheckOddParity(TempTrackData.Value[i]))								//奇校验字节OK
							{
								bCheckOk = 0;
								k++;
								m = i;
								if (7 == type)
								{
									bData = 6;
								}
								else if (5 == type)
								{
									bData = 4;
								}
								else if (8 == type)
								{
									bData = 7;
								}
								
								for(j = 0; j < bData; j ++)
								{
									if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))					//纵向校验错
									{
										bEachCorrected++;
										CplBit(&TempTrackData.Value[i],(uint8_t)j);
										bCorrectDirt = 1;
										bFinalCorrect = 1;
										break;
									}
								}
							}
						}
						if(k == 1 && bCorrectDirt == 0)										//纵向校验正确，横向错在校验位，且只有一位
						{
							if (7 == type)
							{
								bData = 6;
							}
							else if (5 == type)
							{
								bData = 4;
							}
							else if (8 == type)
							{
								bData = 7;
							}
							bEachCorrected++;
							CplBit(&TempTrackData.Value[m],bData);
							bCorrectDirt = 1;
							bFinalCorrect = 1;
						}
						if (7 == type)
						{
							bData = 6;
						}
						else if (5 == type)
						{
							bData = 4;
						}
						else if (8 == type)
						{
							bData = 7;
						}
						
						for(j = 0; j < bData; j ++)
						{
							if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))					//纵向校验错
							{
								bCheckOk = 0;
								break;
							}
						}
					}while(bCorrectDirt);
				}
				
				if(bCheckOk && (bEachCorrected <= ((type == 5) ? 3 * ERRLEVEL: ERRLEVEL)))					//校验通过，控制容错率
				{
					if(TempTrackData.Length >= 3)
					{
						bFlag = 0;
						for(i = 1; i < (TempTrackData.Length-2); i ++)										//去掉结束位和起始位
						{
							if (5 == type)
								TempTrackData.Value[i] &= 0x0F;
							else
								break;
							if(bFinalCorrect == 1)															//过滤纠错后的乱码
							{
								if(!((TempTrackData.Value[i] <= 0x09) || TempTrackData.Value[i] == 0x0E  || TempTrackData.Value[i] == 0x0D  || TempTrackData.Value[i] == 0x0C))
								{
									bFlag = 1;
								}
							}
						}
						if(bFlag == 0)
						{
							if(DecodeTimes == 0)															   //第一次解码拷贝到返回数据
							{
								for(i = 0; i < TempTrackData.Length; i++)										//转换成ASCII字符
								{
									if (7 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x3F) + 0x20;
									}
									else if (5 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x0F) + 0x30;
									}
									else if (8 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x7F);
									}
								}
								lpOutTrackData->Length = TempTrackData.Length+1; 	
							}
							else
							{
								if(TempTrackData.Length > lpOutTrackData->Length)
								{
									for(i = 0; i < TempTrackData.Length; i++)										//转换成ASCII字符
									{
										if (7 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x3F) + 0x20;
										}
										else if( 5 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x0F) + 0x30;
										}
										else if( 8 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x7F);
										}
									}
									lpOutTrackData->Length = TempTrackData.Length+1;
								}									
							}
							bFinalSucc = 1;
						}
					}
				}
			} else if (bFlag == 1 && 6 == type) {
				bData = 6;
				bCheckOk = 0;
				for(j = 0; j < bData; j ++)
				{
					if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))		//纵向校验错
					{
						bCheckOk = 1;
						break;
					}
				}
				
				if (0 == bCheckOk) {																	//LRC校验通过
					if(DecodeTimes == 0)															   //第一次解码拷贝到返回数据
					{
						for(i = 0; i < TempTrackData.Length; i++)										//转换成ASCII字符
						{
							lpOutTrackData->Value[i+1] = TempTrackData.Value[i] + 0x20;
						}
						lpOutTrackData->Length = TempTrackData.Length+1;
					}
					else
					{
						if(TempTrackData.Length > lpOutTrackData->Length)
						{
							for(i = 0; i < TempTrackData.Length; i++)										//转换成ASCII字符
							{
								lpOutTrackData->Value[i+1] = TempTrackData.Value[i] + 0x20;
							}
							lpOutTrackData->Length = TempTrackData.Length+1;
						}									
					}
					bFinalSucc = 1;
				}
			}
		}
	}
	if(bFinalSucc == 1)
	{
		if(lpOutTrackData->Length < 4 )
		{
			return 2;										//数据长度为零，解码为空	
		}
		else
		{
			return 0;										//刷卡成功
		}
	}
	else
	{
		if(((FirstOkByteCnt >= 8 && FirstBitCnt >= 100) || (SndOkByteCnt >= 8 && SndBitCnt >= 100)))
		{
			return 1;									//刷卡失败
		}
		else
		{
			return 2;									//刷卡空
		}
	}
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 初始化参数
入口参数: 
返 回 值: 
备	  注: 
********************************************************************/
void InitMagDecode(void)
{
	memset((uint8_t*)&Track1TimeFlow, 0, sizeof(Track1TimeFlow));
	memset((uint8_t*)&Track2TimeFlow, 0, sizeof(Track2TimeFlow));
	memset((uint8_t*)&Track3TimeFlow, 0, sizeof(Track3TimeFlow));
	
	memset((uint8_t*)&TrackBitFlow, 0, sizeof(TrackBitFlow));

	memset((uint8_t*)&Track1Data, 0, sizeof(Track1Data));
	memset((uint8_t*)&Track2Data, 0, sizeof(Track2Data));
	memset((uint8_t*)&Track3Data, 0, sizeof(Track3Data));
}

/*******************************************************************
作	 者 : 欧阳伟权
版	 权 : 
函数功能: 解码
入口参数: 高4位：1: 一轨解码, 2: 二轨解码, 3: 三轨解码
          低4位：5: 5Bit编码, 6: 6Bit编码, 7: 7Bit编码, 8: 8Bit编码
返 回 值: 0: 解码成功，1: 解码错,   2: 解码空 
********************************************************************/
uint8_t MagDecodeTrack(uint8_t type)
{
	uint8_t DecodeTimes, bFlag, bBrushError = 0;
	for(DecodeTimes = 0; DecodeTimes < 2; DecodeTimes++)
	{
		if(DecodeTimes == 1)
		{
			ResortMagData(type);						//反解		
		}
		if(DecodeTimeToBit(type))
		{
			bFlag = DecodeTrackData(type);
			if(bFlag == 0)
			{
				return 0;
			}
			else if(bFlag == 1)
			{
				bBrushError = 1;
			}
		}
	}
	if(bBrushError == 1)
	{
		return 1;
	}
	return 2;
}



/*******************************************************************************
* Function Name  : FlushBuffer_Init
* Description    : The MCU invokes this function to store 3 tracks of F2F signa 
level on magnetic strip card by TmrCnt of timer count capture to input buffer 
of TrNo from external input pin.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void FlushBuffer_Init (void)
{
	InitMagDecode();
	MSR_Check_Sync_Pattern();
}



/*******************************************************************************
* Function Name  : SetF2FInputBuffer
* Description    : The MCU invokes this function to flush buffer of MSR to a 
default value and pointer of Write/Read buffer to a start address.
* Input          : TrNo,This parameter indicate track number of 3 tracks of F2F signal.
                        0 = track1.
                        1 = track2.
                        2 = track3.
                   TmrCnt,This parameter indicate count value by timer captured.
                   level,This parameter indicate a input pin of 3 tracks of F2F signal level.
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level)
{
	//if (MSR_fCardDataReady == 0) {
		switch (TrNo) {
			case 0:Track1TimeFlow.Value[Track1TimeFlow.Length++] = TmrCnt; break;
			case 1:Track2TimeFlow.Value[Track2TimeFlow.Length++] = TmrCnt; break;
			case 2:Track3TimeFlow.Value[Track3TimeFlow.Length++] = TmrCnt; break;
		}
	//}
}


/*******************************************************************************
* Function Name  : MSR_Check_Sync_Pattern
* Description    : The MCU invokes this function to check first pattern of 
synchronize and wait for 3 tracks of F2F signal finish.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void MSR_Check_Sync_Pattern (void)
{
	MSR_fCardDataReady = 0;
	return;
}


/*******************************************************************************
* Function Name  : MSR_F2F_Decoder
* Description    : The MCU invokes this function to translate 3 tracks of F2F 
signal to a bit data by Weltrend algorithm.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void MSR_F2F_Decoder (void)
{
	return;
}


/*******************************************************************************
* Function Name  : MSR_Character_Decoder
* Description    : The MCU invokes this function to translate 3 tracks of F2F 
bit data to a character of ISO or JIS format.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void MSR_Character_Decoder (void)
{
	if (Track1TimeFlow.Length > 20) {			//至少前后有10个前导0才去解码
		MagDecodeTrack(1);						//第一磁道数据7Bit解码
	}
	
	if (Track2TimeFlow.Length > 20) {			//至少前后有10个前导0才去解码
		MagDecodeTrack(2);						//第二磁道数据5Bit解码
	}
	
	if (Track3TimeFlow.Length > 20) {			//至少前后有10个前导0才去解码
		MagDecodeTrack(3);						//第三磁道数据5Bit解码
	}
	return;
}


/*******************************************************************************
* Function Name  : GetMSR_CardDataForUART
* Description    : The MCU invokes this function to get 3 tracks of MSR character 
data sequentially from 1'st track to 3'rd track with byte format.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG unsigned char GetMSR_CardDataForUART (void)
{
	int i;
	if (Track1Data.Length > 2) {
		printf("TK1:");
		for (i = 2; i < Track1Data.Length - 2; i++) {
			printf("%c", Track1Data.Value[i]);
		}
		printf("\r\n");
	}
	
	if (Track2Data.Length > 2) {
		printf("TK2:");
		for (i = 2; i < Track2Data.Length - 2; i++) {
			printf("%c", Track2Data.Value[i]);
		}
		printf("\r\n");
	}
	
	if (Track3Data.Length > 2) {
		printf("TK3:");
		for (i = 2; i < Track3Data.Length - 2; i++) {
			printf("%c", Track3Data.Value[i]);
		}
		printf("\r\n");
	}
	
	return NULL;
}


/*******************************************************************************
* Function Name  : MSR_WaitForReady
* Description    : The MCU invokes this function to wait for 3 tracks of character 
data to fetch complete, sequentially. When you have call function of 
GetMSR_CardDataForUART to send out data by UART.
* Input          : None
* Output         : None
* Return         : None
* Author		 : Jery Ouyang
* Date			 : 2017-03-08
*******************************************************************************/
EXTERNMAG void MSR_WaitForReady (void)
{
	MSR_fCardDataReady = 1;
}


/*******************************************************************************
* Function Name  : MSR_GetCharacterDataOn
* Description    : The MCU invokes this function to get 3 tracks of character 
data by TrNo to a buffer pointer of *pBuf, the buffer size is limited by length.
* Input          : TrNo,This parameter indicate track number of 3 tracks of F2F signal.
                        0 = track1.
                        1 = track2.
                        2 = track3.
                   pBuf,This parameter indicate a buffer pointer, the character data well copy to here.
                   length,This parameter indicate a buffer size.
* Output         : None
* Return         : 0: success.  -1: error.  -2: none.  -3: parameter error.
* Author		 : Jery Ouyang
* Date			 : 2017-03-23
*******************************************************************************/
EXTERNMAG int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length)
{
	int ret = 0;
	if (pBuf == NULL) {
		return -3;
	}
	memset(pBuf, 0, length);
	switch (TrNo) {
		case 0:
			if (Track1TimeFlow.Length > 20) {					//捕获到了一磁道数据，至少前后有10个前导位才解码
				ret = MagDecodeTrack(0x17);						//第一磁道数据7Bit解码
				if (0 != ret) {									//ISO标准解码失败
				#ifdef JIS_SUPPORT
					if (0 != ret) {
						ret = MagDecodeTrack(0x18);				//第一磁道数据8Bit解码
					}
				#endif

				#ifdef CADMV_SUPPORT
					if (0 != ret) {
						ret = MagDecodeTrack(0x16);				//第一磁道数据6Bit解码
					}
				#endif
				}
				if (0 == ret) {									//解码成功
					Track1Data.Value[0] = 0x2B;					//一磁道数据开始分隔符
					Track1Data.Length -= 2;						//拷贝数据去掉第一个字节分隔符和最后一个字节的校验
					memcpy(pBuf, &Track1Data.Value[1], (Track1Data.Length - length < 0) ? Track1Data.Length : length);
					Track1Data.Length += 2;						//恢复长度
				}
			} else {
				ret = 2;
			}
			break;
		case 1:
			if (Track2TimeFlow.Length > 20) {					//捕获到了二磁道数据，至少前后有10个前导位才解码
				ret = MagDecodeTrack(0x25);						//第二磁道数据5Bit解码
				if (0 == ret) {									//解码成功
					Track2Data.Value[0] = 0x2C;					//二磁道数据开始分隔符
					Track2Data.Length -= 2;						//拷贝数据去掉第一个字节分隔符和最后一个字节的校验
					memcpy(pBuf, &Track2Data.Value[1], (Track2Data.Length - length < 0) ? Track2Data.Length : length);
					Track2Data.Length += 2;						//恢复长度
				}
			} else {
				ret = 2;
			}
			break;
		case 2:
			if (Track3TimeFlow.Length > 20) {					//捕获到了三磁道数据，至少前后有10个前导位才解码
				ret = MagDecodeTrack(0x35);						//第三磁道数据5Bit解码
				if (0 != ret) {									//ISO标准解码失败
				#ifdef AAMVA_SUPPORT
					if (0 != ret) {
						ret = MagDecodeTrack(0x37);				//第三磁道数据7Bit解码
					}
				#endif
				#ifdef CADMV_SUPPORT
					if (0 != ret) {
						ret = MagDecodeTrack(0x36);				//第三磁道数据6Bit解码
					}
				#endif
				}
				if (0 == ret) {									//解码成功
					Track3Data.Value[0] = 0x2D;					//三磁道数据开始分隔符
					Track3Data.Length -= 2;						//拷贝数据去掉第一个字节分隔符和最后一个字节的校验
					memcpy(pBuf, &Track3Data.Value[1], (Track3Data.Length - length < 0) ? Track3Data.Length : length);
					Track3Data.Length += 2;						//恢复长度
				}
			} else {
				ret = 2;
			}
			break;
		default:
			ret = 3;
			break;
	}
	return (0 - ret);
}




