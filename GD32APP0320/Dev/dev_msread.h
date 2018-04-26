#ifndef __DEV_MSREAD_H__
#define __DEV_MSREAD_H__

void MSR_SendData(void);

#undef TK1buf
#define TK1buf ((uint8_t *)Track1Data.Value)					//第一磁道数据缓存
#undef TK2buf
#define TK2buf ((uint8_t *)Track2Data.Value)					//第二磁道数据缓存
#undef TK3buf
#define TK3buf ((uint8_t *)Track3Data.Value)					//第三磁道数据缓存

#undef TK1len
#define TK1len Track1Data.Length								//第一磁道数据长度
#undef TK2len
#define TK2len Track2Data.Length								//第二磁道数据长度
#undef TK3len
#define TK3len Track3Data.Length								//第三磁道数据长度

#endif
 

