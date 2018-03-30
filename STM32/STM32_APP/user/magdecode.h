#ifndef __MAG_DECODE_H
#define __MAG_DECODE_H

#include <stdint.h>

#ifdef AFX_MAG_DECODE_VARIABLES
    #define EXTERNMAG 
#else
    #define EXTERNMAG extern 
#endif

#define ERRLEVEL 1					//�ݴ�ļ���ȡֵ��Χ0��1��2

#ifndef	AAMVA_SUPPORT
	#define AAMVA_SUPPORT			//AAMVA��׼��֧��
#endif
#ifndef	CADMV_SUPPORT
	#define CADMV_SUPPORT			//CADMV��׼��֧��
#endif
#ifndef	JIS_SUPPORT
	#define JIS_SUPPORT				//JIS��׼��֧��
#endif

#define TRACK1TIMEFLOWLENGTH 800
#define TRACK2TIMEFLOWLENGTH 500
#define TRACK3TIMEFLOWLENGTH 1050
#define TRACKBITFLOWLENGTH 800
#define TRACKDATALENGTH 110

typedef struct _TRACKTIMEFLOW 
{
	uint16_t Value[TRACK1TIMEFLOWLENGTH];
	uint16_t Length;
}TRACK1TIMEFLOW;

typedef struct _TRACK2TIMEFLOW 
{
	uint16_t Value[TRACK2TIMEFLOWLENGTH];
	uint16_t Length;
}TRACK2TIMEFLOW;

typedef struct _TRACK3TIMEFLOW 
{
	uint16_t Value[TRACK3TIMEFLOWLENGTH];
	uint16_t Length;
}TRACK3TIMEFLOW;

typedef struct _TRACKBITFLOW 
{
	uint8_t  Value[TRACKBITFLOWLENGTH];
	uint16_t Length;
}TRACKBITFLOW;

typedef struct _TRACKDATA 
{
	uint8_t Value[TRACKDATALENGTH];
	uint8_t Length;
}TRACKDATA;

EXTERNMAG TRACK1TIMEFLOW Track1TimeFlow;				//һ�ŵ���ԭʼ�ź�
EXTERNMAG TRACK2TIMEFLOW Track2TimeFlow;				//���ŵ���ԭʼ�ź�
EXTERNMAG TRACK3TIMEFLOW Track3TimeFlow;				//���ŵ���ԭʼ�ź�

EXTERNMAG TRACKBITFLOW TrackBitFlow;					//������Bit��Ϣ

EXTERNMAG TRACKDATA TempTrackDirtData,TempTrackData;	//��ʱ��������������ͷ��������
EXTERNMAG TRACKDATA Track1Data,Track2Data,Track3Data;	//�������ַ���Ϣ

//==============================================================================
/*******************************************************************************
* Function Name  : MagDecodeTrack
* Description    : �ŵ��������ݽ���
* Input          : ��4λ��1: һ�����, 2: �������, 3: �������
                   ��4λ��5: 5Bit����, 6: 6Bit����, 7: 7Bit����, 8: 8Bit����
* Output         : None
* Return         : 0: ����ɹ���1: �����,   2: ����� 
* Author		 : Jery Ouyang
* Date			 : 2017-03-23
*******************************************************************************/
EXTERNMAG uint8_t MagDecodeTrack(uint8_t type);

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
EXTERNMAG void FlushBuffer_Init (void);


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
EXTERNMAG void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level);

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
EXTERNMAG void MSR_Check_Sync_Pattern (void);

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
EXTERNMAG void MSR_F2F_Decoder (void);

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
EXTERNMAG void MSR_Character_Decoder (void);

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
EXTERNMAG unsigned char GetMSR_CardDataForUART (void);

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
EXTERNMAG void MSR_WaitForReady (void);

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
EXTERNMAG int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length);


#endif


