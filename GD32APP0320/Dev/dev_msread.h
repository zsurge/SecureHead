#ifndef __DEV_MSREAD_H__
#define __DEV_MSREAD_H__

void MSR_SendData(void);

#undef TK1buf
#define TK1buf ((uint8_t *)Track1Data.Value)					//��һ�ŵ����ݻ���
#undef TK2buf
#define TK2buf ((uint8_t *)Track2Data.Value)					//�ڶ��ŵ����ݻ���
#undef TK3buf
#define TK3buf ((uint8_t *)Track3Data.Value)					//�����ŵ����ݻ���

#undef TK1len
#define TK1len Track1Data.Length								//��һ�ŵ����ݳ���
#undef TK2len
#define TK2len Track2Data.Length								//�ڶ��ŵ����ݳ���
#undef TK3len
#define TK3len Track3Data.Length								//�����ŵ����ݳ���

#endif
 

