#include <stdlib.h> 
#include "app.h"
#include "usb_type.h"


union __ENC_KEY ENC_KEY;					//��Կ�������ݽṹ
uint8_t CryptoKey[16];						//DUKPT������Ĺ�����Կ
								  	
uint8_t random[8];							//�����
uint8_t macdata[8];							//��������

const char SHID[] = "PF SecureHeadReader V 1.00";
#ifdef FLASHKEY_SUPPORT
const char APPVERSION[] = "VPFASTMG171007001";
#else
const char APPVERSION[] = "VPFASTMS171007001";
#endif

volatile uint8_t WriteFlag = 0;				//������Կ��־��0�������棬1��ʹ�ܱ���
volatile uint8_t GetNextFlag = 0;			//��ȡ��һ��KSN��־��0������ȡ��һ����1��ʹ�ܻ�ȡ��һ�� 

volatile uint8_t macstate = 0x00;			//����״̬��0x30��δ���յ��������ݻ��������ʧ�ܣ�0x31����������OK
volatile uint8_t encryptdatastatus = 0x00;	//bit 1 ==1 ��ʾ1�ŵ��������ݴ���
											//bit 2 ==1 ��ʾ2�ŵ��������ݴ���
											//bit 3 ==1 ��ʾ3�ŵ��������ݴ���
											//bit 4 ==1 ��ʾ1�ŵ���ϣ���ݴ���
											//bit 5 ==1 ��ʾ2�ŵ���ϣ���ݴ���
											//bit 6 ==1 ��ʾ3�ŵ���ϣ���ݴ���
											//bit 7 ==1 ��ʾ�ỰID���ݴ���
											//bit 8 ==1 ��ʾKSN����

volatile uint8_t RxdStatus = 0;			 		//����״̬
volatile uint8_t SynHead = 0;				 	//���հ�ͷ����
volatile uint8_t RxdFrameStatus = 0;			//���հ�״̬
volatile uint8_t NowLen = 0;				 	//�����ֽ�ָ��
volatile uint8_t RxdTotalLen = 0;			 	//���հ����ݳ���
 uint8_t RxdBuf[MAX_RXD_BUF_LEN];			//���հ����ݻ���
 uint8_t SetKeyBuf[80];			    		//������Կ���ݻ���
//#define RxdBuf ((uint8_t *)TempTrackDirtData.Value)			//���հ����ݻ���
//#define SetKeyBuf ((uint8_t *)TempTrackData.Value)			    		//������Կ���ݻ���
volatile uint8_t SetKeyLen=0;			    //������Կ���ݳ���
volatile uint8_t SetKeyFlag=0;				//������Կ��־��0���������ã�1���������á�
volatile uint8_t Bcc;						//У���

//�ر������ж�
void NVIC_Clear_all(void)
{
	uint32_t i;
	for(i=0; i<3; i++)
		NVIC->ICER[i] = 0;
	for(i=0; i<3; i++)
		NVIC->ICPR[i] = 0;
}

#if 0
/**************************************************************************//**
 * @brief This function sets up the Cortex M-3 with a new SP and PC.
 *****************************************************************************/
#if defined ( __CC_ARM   )
__asm void BOOT_jump(uint32_t sp, uint32_t pc)
{
  /* Set new MSP, PSP based on SP (r0)*/
  msr msp, r0
  msr psp, r0

  /* Jump to PC (r1)*/
  //mov pc, r1
  BX r1;
}
#else
void BOOT_jump(uint32_t sp, uint32_t pc)
{
  (void) sp;
  (void) pc;
  /* Set new MSP, PSP based on SP (r0)*/
  __asm("msr msp, r0");
  __asm("msr psp, r0");

  /* Jump to PC (r1)*/
  __asm("mov pc, r1");
}
#endif

/**************************************************************************//**
 * @brief Boots the application
 *****************************************************************************/
void BOOT_boot(void)
{
	/* Clear all interrupts set. */
	NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICER[1] = 0xFFFFFFFF;

	/* Set new vector table */
	SCB->VTOR = (uint32_t) BOOT_ADDR;

	SCB->AIRCR = 0x05FA0004;

	/* Read new SP and PC from vector table */
	BOOT_jump(*((uint32_t *) BOOT_ADDR),*((uint32_t *) BOOT_ADDR + 1));
}

#endif


void init_serial_boot(void)
{
	RxdStatus = 0;
	SynHead = 0;
	RxdFrameStatus = SPACE;
}

/**************************************************************************************
	*** �� �� ��:	void WriteENCKEY(void)
	*** ����������	��ENCKEY���浽FLASH��
	*** ��    ��:  	����: ȫ�ֱ���ENC_KEY
					����: ENC_KEY�����ַ
				    �����NULL 
	*** �� �� ֵ:	NULL  	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void WriteENCKEY(void)
{
	#ifdef FLASHKEY_SUPPORT
	uint8_t i;
	uint8_t tempdata[64];
	memset(tempdata ,0, 64);
	if(WriteFlag==1)
	{
		memcpy(tempdata,ENC_KEY.key,62);
		memcpy(tempdata+62,"\x00\x00",2);
		for(i=0;i<62;i++)
		{
			tempdata[62] ^= tempdata[i];
			tempdata[63] += tempdata[i];
		}
 		for(i=0;i<8;i++)
 			tri_des(tempdata+i*8,(unsigned char *)SHID,(unsigned char *)SHID+8,0);	   //����Ҫ�洢����Կֵ
		__disable_irq();
		EarseBlockFlash(KEYADD);
		WriteBlockFlash(KEYADD ,tempdata, 64);
		__enable_irq();
		return ;
	}
	else
	{
		return ;
	}
	#endif
	
}

/**************************************************************************************
	*** �� �� ��:	void ReadENCKEY(void)
	*** ����������	��ȡ�����ENCKEY��RAM��
	*** ��    ��:  	����: ENC_KEY�����ַ
				    �����ȫ�ֱ���ENC_KEY 
	*** �� �� ֵ:	TRUE/FALSE   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
uint8_t ReadENCKEY(void)
{
	#ifdef FLASHKEY_SUPPORT
	uint8_t tempdata[64],i,lrc,bcc;
	memset(tempdata ,0, 64);
	ReadBlockFlash(KEYADD ,tempdata, 64);     			//����֮ǰ�������Կֵ
	for(i=0;i<8;i++)
		tri_des(tempdata+i*8,(unsigned char *)SHID,(unsigned char *)SHID+8,1);	   //���ܴ洢����Կֵ
	memcpy(ENC_KEY.key,tempdata,64);
	//У�鱣�����Կ
	for(lrc=bcc=i=0;i<62;i++)
	{
		lrc ^= tempdata[i];
		bcc += tempdata[i];
	}
	if(lrc == ENC_KEY.key[62] && bcc == ENC_KEY.key[63] )
		return TRUE;
	else
		return FALSE;
	#else
	return TRUE;
	#endif
}

/**************************************************************************************
	*** �� �� ��:	uint8_t AsciiToHex(uint8_t * pAscii, uint8_t * pHex, int nLen)
	*** ����������	��һ�� ASSC ���ʾ��ʮ�������ַ���ת����ʮ�����Ƶ��ֽڴ���
	*** ��    ��:  	����: pAscii -- Ҫת����ASCII���ʾ��ʮ�������ַ������׵�ַ��
						  nLen	 -- Ҫת����ASCII���ʾ��ʮ�������ַ����ĳ��ȣ��ֽ�������
				    �����pHex	 -- ת�����ʮ���������ֽڴ��׵�ַ��
	*** �� �� ֵ:	TRUE/FALSE   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
uint8_t AsciiToHex(uint8_t *pAscii, uint8_t *pHex, int nLen)
{
	unsigned char Nibble[2];
	int nHexLen,i,j;
	if (nLen%2)
		return FALSE;
	nHexLen = nLen/2;
	for (i = 0; i < nHexLen; i ++)
	{
		
		Nibble[0] = *pAscii++;
		Nibble[1] = *pAscii++;
		for (j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
					Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
					Nibble [j] = Nibble[j] - '0';
			else
				return FALSE;
		}	// for (int j = ...)
		pHex[i] = Nibble[0] << 4;	// Set the high nibble
		pHex[i] |= Nibble[1];		//Set the low nibble
	}	// for (int i = ...)
	return TRUE;
}

/**************************************************************************************
	*** �� �� ��:	void HexToAscii(unsigned char * pHex, unsigned char * pASSCHex, int nLen)
	*** ����������	��һ��ʮ�������ֽڴ�ת���� ASCII ���ʾ���ַ�����
	*** ��    ��:  	����: pHex 	   -- Ҫת����ʮ���������ֽڴ��׵�ַ��
						  nLen	   -- Ҫת����ʮ���������ֽڴ��ĳ��ȣ��ֽ�������
				    �����pASSCHex -- ת����� ASCII ���ʾ���ַ������׵�ַ��
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void HexToAscii(uint8_t *pHex, uint8_t *pASSCHex, int nLen)
{
	uint8_t Nibble[2];
	int i,j;
	for ( i = 0; i < nLen; i ++)
	{
		Nibble[0] = (pHex[i] & 0xF0) >> 4;	
		Nibble[1] = pHex[i] & 0x0F;
		for ( j = 0; j < 2; j ++)
		{
			if (Nibble[j] < 10)
				Nibble[j] += 0x30;
			else
			{
				if (Nibble[j] < 16)
					Nibble[j] = Nibble[j] - 10 + 'A';
			}
			*pASSCHex ++ = Nibble[j];
		}	// for (int j = ...)
	}	// for (int i = ...)
}

/**************************************************************************************
	*** �� �� ��:	void Random(void) 
	*** ����������	ȡ8���ֽڵ�16���Ƶ��������
	*** ��    ��:  	����: NULL��
				    �����8��ʮ�������������
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void Random(void) 
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		random[i] = rand() % 255;
	}
}

/**************************************************************************************
	*** �� �� ��:	uint8_t GetNextKSN(uint8_t* pBUserKSN) 
	*** ����������	ʹDUKPT�㷨����KSN�Լ�1��
	*** ��    ��:  	����: KSN��
				    �������һ��KSN��
	*** �� �� ֵ:	FALSE / TRUE   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.11.18����
***************************************************************************************/
uint8_t GetNextKSN(void)
{
	(*(ENC_KEY.temp.ksn + 9))++;
	if(	*(ENC_KEY.temp.ksn + 9) == 0x00)
	{
		(*(ENC_KEY.temp.ksn + 8))++;
		if(	*(ENC_KEY.temp.ksn + 8) == 0x00)
		{
			(*(ENC_KEY.temp.ksn + 7))++;
			if(	(*(ENC_KEY.temp.ksn + 7)) == 0x00)
			{
				(*(ENC_KEY.temp.ksn + 6))++;
				if(	*(ENC_KEY.temp.ksn + 6) == 0x00)
				{
					(*(ENC_KEY.temp.ksn + 5))++;
					if(	*(ENC_KEY.temp.ksn + 5) >= 0xFF)
					{
						return FALSE;
					}
				}
			}
		}
	}
	WriteFlag = 1;
	WriteENCKEY();							  //������º��KSN
//	{
//		WriteFlag = 0;
//		return TRUE;
//	}
	WriteFlag = 0;
	return TRUE;
}


/**************************************************************************************
	*** �� �� ��:	void CalcCryptoKey(void) 
	*** ����������	���ݵ�ǰ���º��KSN��KEY�����������Կ��
	*** ��    ��:  	����: KSN��KEY��
				    �����������Կ��
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.11.18����
***************************************************************************************/
void CalcCryptoKey(void) 
{
	int counter;
	uint8_t k=1;
	//GetNextKSN();
	GetNextFlag = 1;
	IDT_LoadInitKey(1,ENC_KEY.temp.key,ENC_KEY.temp.ksn);
	counter = ENC_KEY.temp.ksn[9] | (ENC_KEY.temp.ksn[8] << 8) | ((ENC_KEY.temp.ksn[7] & 0x1f) << 16);
	do
	{	       
		IDT_EncryptPIN(1,IDT_ChangeCounter(counter, k),ENC_KEY.temp.ksn,CryptoKey,0); 
		k++;
	}while(k <= IDT_GetNumOfOnes(counter));
}

/**************************************************************************************
	*** �� �� ��:	void send_frame(uint8_t frame_type)
	*** ����������	���ض��������Ӧ��
	*** ��    ��:  	����: frame_type -- ��Ӧ����Ĳ�����
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void send_frame(uint8_t frame_type)
{
    uint8_t i = 0, j, bcc;
	uint8_t TxdBuf[MAX_TXD_BUF_LEN];
	uint8_t TempBuf[20];
	uint8_t pBKCV[6];
	uint8_t bpSEncod[10]={0xFF,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        
    switch (frame_type) 
	{
        case REQUEST_DOWN:   				/* request download */
            i = 0;						    //��������
			TxdBuf[i++] = frame_type;
			break;

		case READ_VERSION:					/* read application ersion */
			i = 0;
			TxdBuf[i++] = 0x06; 			// 06
			TxdBuf[i++] = RxdBuf[0]; 		// 02
			bcc = RxdBuf[0];
			TxdBuf[i++] = strlen(APPVERSION);
			bcc ^= strlen(APPVERSION);
			for(j = 0; j < strlen(APPVERSION); j++)
			{
				TxdBuf[i++] = APPVERSION[j];
            	bcc ^= APPVERSION[j];	
			}
			TxdBuf[i++] = ETX;
			bcc ^= ETX;
	        TxdBuf[i++] = bcc;
			break;
        			 
		case CMDSUCC:
		case CMDERRO:
			i = 0;						   //���ܴ�ͷЭ��
			TxdBuf[i++] = frame_type;
			break;
		case GETSECURITYLEVEL:					//0x7E	/* get security level */
			if(RxdBuf[2] == GETSECURITYLEVEL) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				TxdBuf[i++] = GETSECURITYLEVEL;
	            bcc ^= GETSECURITYLEVEL;
				TxdBuf[i++] = 0x01;
	            bcc ^= 0x01;
				//ReadENCKEY();
				TxdBuf[i++] = ENC_KEY.temp.level;
	            bcc ^= ENC_KEY.temp.level; 				
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();	
			break;
		case GETCHALLENGE:
			if(RxdBuf[2] == GETCHALLENGE) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				for(j=0; j<8; j++)  //�������������������
				{
					TxdBuf[i++] = random[j];
					bcc ^= random[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();			
			break;			
		case READID:
			if(RxdBuf[2] == READID) 
			{
				i = 0;
				//TxdBuf[i++] = 0xFF; 			// FF
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				for(j=0; j<strlen(SHID); j++)  //������ȫ��ͷID����������
				{
					TxdBuf[i++] = SHID[j];
					bcc ^= SHID[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();
			break;
		case REVIEWKSN:
			if(RxdBuf[2] == REVIEWKSN) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				TxdBuf[i++] = RxdBuf[2];		// 51
				bcc ^= RxdBuf[2];
				TxdBuf[i++] = 0x0B;				// 0B
				bcc ^= 0x0B;
				TxdBuf[i++] = 0x0A;				// 0A
				bcc ^= 0x0A;
				
				for(j=0; j< 10; j++)  			//����KSN����������
				{
					TxdBuf[i++] = ENC_KEY.temp.ksn[j];
					bcc ^= ENC_KEY.temp.ksn[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();
			break;
		case REVIEWSN:							//0x4E	/* review serial number */
			if(RxdBuf[2] == REVIEWSN) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				TxdBuf[i++] = RxdBuf[2];		// 4E
				bcc ^= RxdBuf[2];
				TxdBuf[i++] = 0x09;				// 09
				bcc ^= 0x09;
				TxdBuf[i++] = 0x08;				// 08
				bcc ^= 0x08;
				
				for(j=0; j< 8; j++)  			//����SN����������
				{
					TxdBuf[i++] = ENC_KEY.temp.sn[j];
					bcc ^= ENC_KEY.temp.sn[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();
			break;
		case SETSID:							//0x54	/* set Session ID */
			if(RxdBuf[2] == SETSID) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				TxdBuf[i++] = RxdBuf[2];		// 54
				bcc ^= RxdBuf[2];
				TxdBuf[i++] = 0x09;				// 09
				bcc ^= 0x09;
				TxdBuf[i++] = 0x08;				// 08
				bcc ^= 0x08;
				
				for(j=0; j< 8; j++)  			//����SID����������
				{
					TxdBuf[i++] = ENC_KEY.temp.sid[j];
					bcc ^= ENC_KEY.temp.sid[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
				break;
			}
			init_serial_boot();
			break;
		case SETKEYCOMMU:
			{
				i = 0;
				if(0 == SetKeyFlag)
				{
					memcpy(TxdBuf,"\x06\x02\x46\x46\x00\x00\x00\x00\x00\x00\x00\x00\x0D\x0A\x03\x00",16);
					to64frombits(TempBuf,"\xFF\x00\x01\x04\xFA",5);
					memcpy(&TxdBuf[4],TempBuf,8);
					for(bcc = 0, i = 2; i < 15; i++)
						bcc ^= TxdBuf[i];
					TxdBuf[i++] = bcc;
				}
			}
			break;
		case SETKEYVALUE:
			{
				i = 0;
				if(1 == SetKeyFlag)
				{
					memcpy(TxdBuf,"\x06\x02\x46\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0D\x0A\x03\x00",23);
					GetKeyCkeckValue(ENC_KEY.temp.ksn,pBKCV,8,ET_DES_MS);
					HexToAscii(pBKCV, bpSEncod+3, 3);
					for(bcc = 0, i = 0; i < 9; i++)
						bcc ^= bpSEncod[i];
					bpSEncod[i] = bcc;
					to64frombits(TempBuf,bpSEncod,10);
					memcpy(&TxdBuf[4],TempBuf,15);					
					for(bcc = 0, i = 2; i < 22; i++)
						bcc ^= TxdBuf[i];
					TxdBuf[i++] = bcc;
				}
				else if(2 == SetKeyFlag)
				{
					memcpy(TxdBuf,"\x06\x02\x46\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0D\x0A\x03\x00",23);
					GetKeyCkeckValue(ENC_KEY.temp.key,pBKCV,16,ET_DES_MS);
					HexToAscii(pBKCV, bpSEncod+3, 3);
					for(bcc = 0, i = 0; i < 9; i++)
						bcc ^= bpSEncod[i];
					bpSEncod[i] = bcc;
					to64frombits(TempBuf,bpSEncod,10);
					memcpy(&TxdBuf[4],TempBuf,15);
					for(bcc = 0, i = 2; i < 22; i++)
						bcc ^= TxdBuf[i];
					TxdBuf[i++] = bcc;
				}
			}
			break;
        default:
        	init_serial_boot();
			return;
    }
	//dev_com_write(TxdBuf, i);
	UsbSendBuff(TxdBuf, i, 3000);

	//�����������Ӧ
//	printf("Send:");
//	for (bcc = 0; bcc < i; bcc++)
//		printf("%02X ", TxdBuf[bcc]);
//	printf("\r\n");
}


/**************************************************************************************
	*** �� �� ��:	void DealSerialParse(void)
	*** ����������	���յ������ݽ��������ݰ���
	*** ��    ��:  	NULL
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void DealSerialParse(void)
{
	uint8_t i = 0;
	while(1)
	{	
		if(UsbRecvOne(&i) != 1)  //��ȡUSB����
		{
		    return;
		}	
		
		switch (RxdStatus)
		{ /*��������״̬*/
			case 0:
				if(STX == i)
				{
					RxdBuf[0] = i;
					Bcc = i;
					NowLen = 1;
					RxdStatus = 25;
				}
				else 
				{
					SynHead = 0;
				}
				break;				/*���հ�ͷ*/
			case 25:
				if (i == ETX) 
				{
					RxdStatus = 26;
				}
				RxdBuf[NowLen++] = i;
				Bcc ^= i;
				break;
			case 26:
				if(i == Bcc || (i ^ 0x02) == Bcc)
				{
					RxdBuf[NowLen++] = i;
					RxdTotalLen = NowLen;
					RxdFrameStatus = FINISH;					
					RxdStatus = 0;
					SynHead = 0;
					break;
				}
				else
				{
					RxdBuf[NowLen++] = i;
					Bcc ^= i;
					RxdStatus = 25;
				}
				break;
			default:
				if (RxdFrameStatus == SPACE) 
				{
					RxdStatus = 0;
					SynHead = 0;
				}
			break;
		 }
	}
}

/**************************************************************************************
	*** �� �� ��:	void DealRxData(void)
	*** ����������	�����յ����������ݰ�������Ӧ���ݰ���
	*** ��    ��:  	NULL
	*** �� �� ֵ:	NULL   	 	
	*** ģ����Ϣ: 	Ouyangweiquan 2011.09.20����
***************************************************************************************/
void DealRxData(void)
{
	uint16_t i;
	uint8_t bcc = 0;
    
	if (FINISH == RxdFrameStatus)
	{
		//spi_send(RxdBuf,RxdTotalLen);
		//��ӡһ�����յ�������
//		printf("CMD:");
//		for (i = 0; i < RxdTotalLen; i++)
//			printf("%02X ", RxdBuf[i]);
//		printf("\r\n");

//    DBG_H("CMD", RxdBuf, RxdTotalLen);
		
//		wwdgt_counter_update(0);
		if(RxdBuf[0] == STX)										//����02���ݰ�
		{
			if (REQUEST_DOWN == RxdBuf[1])							//0x55	/* request download */
			{
				send_frame(CMDSUCC);
																	//����
				init_serial_boot();
				
				WriteUpgradeFlag();
				NVIC_SystemReset();
				delay_1ms(10000); 		
			    while(1);
			    
			}
			else if (READ_VERSION == RxdBuf[1])						//0x28	/* read application ersion */
			{
				send_frame(READ_VERSION);
				init_serial_boot();
			}
			else if (RESETHEAD == RxdBuf[1])						//0x38	/* reset secureheadreader */
			{
				SetKeyFlag = 0;
				memset(ENC_KEY.key,0x00,64);
				ENC_KEY.temp.level = 0x31;
				WriteFlag = 1;
				WriteENCKEY();
				send_frame(CMDSUCC);
				WriteFlag = 0;
				init_serial_boot();
			}
			else if (SETKEY == RxdBuf[1] && SETKEY == RxdBuf[2])	//0x46	/* set key commands  */
			{
				memset(SetKeyBuf,0,sizeof(SetKeyBuf));
				SetKeyLen = from64tobits(SetKeyBuf,&RxdBuf[3],RxdTotalLen-7);
				if(SetKeyBuf[0] == SETKEYHEAD)
				{
					bcc = 0;	
					for(i = 0; i < SetKeyLen-1; i++)
						bcc ^= SetKeyBuf[i];
					if (bcc == SetKeyBuf[SetKeyLen -1])			   	//У��
					{
						SetKeyLen =  SetKeyBuf[2];					//������Կ���ݳ���
						switch (SetKeyBuf[1])
						{
							case SETKEYCOMMU:						//0x13	/* setting key communications commands */
								if(0x01 == SetKeyLen && 0x02 == SetKeyBuf[3])
								{
									send_frame(SETKEYCOMMU);
									SetKeyFlag = 1;
								}
								else
								{
									send_frame(CMDERRO);
									SetKeyFlag = 0;
								}
								init_serial_boot();
								break;
							case SETKEYVALUE:						//0x0A	/* setting key value commands */
								if(SetKeyFlag > 0)
								{
									if(0x11 == SetKeyLen && 0x32==SetKeyBuf[3])			/* setting ksn value commands */
									{
										AsciiToHex(&SetKeyBuf[4],ENC_KEY.temp.ksn,SetKeyLen-1);
										if(GetNextKSN())
										{
											send_frame(SETKEYVALUE);
											SetKeyFlag = 2;
										}	
										else
											send_frame(CMDERRO);
										//WriteFlag = 0;
									}
									else if(0x21 == SetKeyLen && 0x33==SetKeyBuf[3])	   /* setting key value commands */
									{
										AsciiToHex(&SetKeyBuf[4],ENC_KEY.temp.key,SetKeyLen-1);
										ENC_KEY.temp.encmode = 0x31;
										ENC_KEY.temp.level = 0x33; 
										WriteFlag = 1;
										WriteENCKEY();
										send_frame(SETKEYVALUE);
										SetKeyFlag = 0;
//											}	
//											else
//												send_frame(CMDERRO);
										WriteFlag = 0;
									}										
								}
								else
									send_frame(CMDERRO);
								init_serial_boot();
								break;
							default:
    	           				init_serial_boot();
        	    				break; 
						}
					}
				}
				
			}				
			else if (READCMD == RxdBuf[1])					//0x52	/* read status commands */
			{
				switch (RxdBuf[2])
				{
					case READID:						    //0x22	/* read secureheadreader ID */
						send_frame(READID);
						RxdFrameStatus = SPACE;
                		break;
					case GETCHALLENGE:						//0x74	/* get encrypt challenge */
						Random();							//���������
						send_frame(GETCHALLENGE);
						RxdFrameStatus = SPACE;
                		break;
					case GETSECURITYLEVEL:					//0x7E	/* get security level */
						send_frame(GETSECURITYLEVEL);
						RxdFrameStatus = SPACE;
                		break;
					case REVIEWKSN:							//0x51	/* review KSN (DUKPT key management only) */
						send_frame(REVIEWKSN);
						RxdFrameStatus = SPACE;
                		break;
					case REVIEWSN:							//0x4E	/* review serial number */
						send_frame(REVIEWSN);
						RxdFrameStatus = SPACE;
                		break;
					case SETSID:							//0x54	/* set Session ID */
						send_frame(SETSID);
						RxdFrameStatus = SPACE;
                		break;					
	           		default:
    	           		init_serial_boot();
        	    		break;
        		}
			}
			else if (SETTINGCMD == RxdBuf[1])				//0x53	/* setting commands */
			{
				switch (RxdBuf[2])
				{
					case SETDEFAULT:						//0x18	/* set default configuration */
						ENC_KEY.temp.status = 0;			//ʧ�ܼ���
						ENC_KEY.temp.level = 0x31;			//���ܼ���Ϊ1
						ENC_KEY.temp.encway = 0x00;			//Ĭ��DES����
						macstate = 0x00;					//δ���յ���������
						WriteFlag = 1;
						WriteENCKEY();						//������º��KEY
						WriteFlag = 0;							
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETDECODEWAY:						//0x1D	/* set decoding in both directions */							
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETENCMODE:						//0x58	/* set encryption mode */							
						if(RxdBuf[3]==0x01)
						{	
							if(0x30==RxdBuf[4]|| 0x31==RxdBuf[4])
							{
								ENC_KEY.temp.encmode = RxdBuf[4];	//��ȡ���õļ��ܷ�ʽ
								if(0x30 == RxdBuf[4])
									ENC_KEY.temp.level = 0x32;
								else
									ENC_KEY.temp.level = 0x33;	
								WriteFlag = 1;
								WriteENCKEY();				//������º��KEY
								WriteFlag = 0;
								send_frame(CMDSUCC);
							}
							else
								send_frame(CMDERRO);
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SENDAUTHDATA:						//0x74	/* send authentication data */
						//memcpy(random,"\x17\xCB\x4E\xCE\xC8\x64\xBB\x3C",8);		//debug
						tri_des(random,ENC_KEY.temp.fix,ENC_KEY.temp.fix+8,0);
						if(memcmp(random,&RxdBuf[4],RxdBuf[3]) == 0)
						{
							macstate = 0x31;				//��������OK
							memset(random,0x00,8);			//��������
							send_frame(CMDSUCC);	
						}
						else
						{
							macstate = 0x30;				//��������ʧ��
							memset(random,0x00,8);			//��������
							send_frame(CMDERRO);	
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETENCWAY:							//0x4C	/* set encryption way */
						if(RxdBuf[3]==0x01)
						{	
							if(0x30 == RxdBuf[4] || 0x31 == RxdBuf[4] || 0x32 == RxdBuf[4])
							{
								ENC_KEY.temp.encway = RxdBuf[4];//��ȡ���õļ�������
								ENC_KEY.temp.status = 1;	//ʹ�ܼ���
								WriteFlag = 1;
								WriteENCKEY();				//������º��KEY
								WriteFlag = 0;
								send_frame(CMDSUCC);
							}
							else
								send_frame(CMDERRO);
						}
						else
						{
							ENC_KEY.temp.status = 0;		//ʧ�ܼ���
							WriteFlag = 1;
							WriteENCKEY();					//������º��KEY
							WriteFlag = 0;
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETTHREETRACKS:					//0x84	/* set all three tracks */
						if(RxdBuf[3]==0x01)
						{	
							if(0x0F == RxdBuf[4])		    //ƥ������Ĳ���
							{
								send_frame(CMDSUCC);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case ASKTHREETRACKS:					 //0x85	/* ask all three tracks */
						if(RxdBuf[3])
						{	
							if(0x31 == RxdBuf[4]);			 //ƥ������Ĳ���
								send_frame(CMDSUCC);
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETDEFWAY1:						//0x34	/* set default way 1 */
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETDEFWAY2:						//0x35	/* set default way 2 */
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETDEFWAY3:						//0x36	/* set default way 3 */
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETDEVICEKEY:						//0x76	/* set device key command */
						if(RxdBuf[3]==0x10 && 0x31 == macstate)
						{
							memcpy(ENC_KEY.temp.fix,&RxdBuf[4],RxdBuf[3]);
							ENC_KEY.temp.level = 0x32;
							WriteFlag = 1;
							WriteENCKEY();					//������º��KEY
							WriteFlag = 0; 								
							send_frame(CMDSUCC);
						}
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
                		break;
					case SETSID:							//0x54	/* set Session ID */
						if(RxdBuf[3]==0x08)
						{
							memcpy(ENC_KEY.temp.sid,&RxdBuf[4],8);
							WriteFlag = 1;
							WriteENCKEY();					//����ỰID
							WriteFlag = 0; 								
							send_frame(CMDSUCC);
						}
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
                		break;
					case REVIEWSN:							//0x4E	/* review serial number */
						if(RxdBuf[3]==0x08)
						{
							memcpy(ENC_KEY.temp.sn,&RxdBuf[4],8);
							WriteFlag = 1;
							WriteENCKEY();					//�������к�
							WriteFlag = 0; 								
							send_frame(CMDSUCC);
						}
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
                		break;
					case MSRSETTINGS:						//0x1A	/* MSR Reading Settings */							
						if(RxdBuf[3]==0x01)
						{
							ENC_KEY.temp.level = RxdBuf[4];
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 								
							send_frame(CMDSUCC);
						}
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
		            break;
	    	        default:
	        	       init_serial_boot();
	            	break;
	            }
			}
			else
			{
				init_serial_boot();
			}
		}
		else
		{
			init_serial_boot();
		}
	}
//	else
//	{
//		init_serial_boot();
//	}
}


