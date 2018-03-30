#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "usb_endp.h"

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

//uint8_t MAGBuf[500];
SHA1Context foo;
AES_KEY key;
uint8_t sha[60];
/**************************************************************************************
//	*** �� �� ��:	void MSR_SendData(void)
//	*** ���������� �ŵ����ݼ������ͺ���
//	*** ��    ��: 
//	*** �� �� ֵ: ����ĳ���  	 	
//	*** ģ����Ϣ: Ouyangweiquan 2012.04.24����
***************************************************************************************/
void MSR_SendData(void)
{
	uint8_t *ch = (uint8_t *)TrackBitFlow.Value, ivec[16];
	uint16_t len = 0x10,j;
	uint8_t lrc,bcc,block1,block2,block3;
		
	if(ENC_KEY.temp.level < 0x30 && ENC_KEY.temp.level > 0x34 )	//���ܼ���ʧЧ
	{
		goto ERRORDATA;											//��ԿʧЧ���ش���
	}
	if (1 == ENC_KEY.temp.status)								//���Ļ��ʹŵ�����
	{
		encryptdatastatus = 0xBF;								//���÷������ݵ�����
				
		/*���ȼ�84 = 11�����ݰ�ͷ + 60 ����ϣֵ + 10��KSN + 2��У���� + 1�������� */
		if(0x32 == ENC_KEY.temp.encway)							//���AES������ÿ��16�ֽ�
		{
			block1 = ceil((TK1len-1)/16.0);
			block2 = ceil((TK2len-1)/16.0);
			block3 = ceil((TK3len-1)/16.0);
			len = block1*16 + block2*16 + block3*16 + 84 ;		//���㷵�����ݳ���
		}
		else													//���DES������ÿ��8�ֽ�
		{
			block1 = ceil((TK1len-1)/8.0);
			block2 = ceil((TK2len-1)/8.0);
			block3 = ceil((TK3len-1)/8.0);
			len = block1*8 + block2*8 + block3*8 + 84 ;  		//���㷵�����ݳ���
		}
		
		if(!block1 && !block2 && !block3)						//������дŵ���Ϊ�գ�ˢ��ʧ��
			goto ERRORDATA;
		if(!TK1len)
		{												   	
			encryptdatastatus &= 0xF6;							//��һ�ŵ����ݷ���Ϊ��
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK1buf[1], TK1len-1);			//�����һ�ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha);
		}
		if(!TK2len)
		{
			encryptdatastatus &= 0xED;							//�ڶ��ŵ����ݷ���Ϊ��
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK2buf[1], TK2len-1);			//����ڶ��ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha+20);
		}
		if(!TK3len)
		{
		 	encryptdatastatus &= 0xDB;							//�����ŵ����ݷ���Ϊ��
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK3buf[1], TK3len-1);			//��������ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha+40);
		}		 
								
		memcpy(ch,"\xFF\x02\x00\x00\x80\x3F\x00\x00\x00\x00",10);//10���ֽ����ݰ�ͷ
		ch[2] = (uint8_t)(len-7);								 //���泤��
		ch[3] = ((len-7)>>8);
		if(TK1len)ch[6] = TK1len-1;
		if(!TK1len)ch[5] = 0x37;
		if(TK2len)ch[7] = TK2len-1;
		if(TK3len)ch[8] = TK3len-1;
		ch[10] = encryptdatastatus;								//������������
		
		if (0x31 == ENC_KEY.temp.encmode)				   		//DUKPT����
		{
			CalcCryptoKey();									//����DUKPT������Կ
		}
		else if (0x30 == ENC_KEY.temp.encmode)			 		//FIX����
		{
			memcpy(CryptoKey,ENC_KEY.temp.fix,16);				//����FIX��Կ
		}
		if( 0x30 == ENC_KEY.temp.encway)						//DES����
		{
			goto ERRORDATA;
		}
		else if(0x31 == ENC_KEY.temp.encway)					//3DES����
		{
			tri_des(TK1buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block1;j++)							//���ܵ�һ�ŵ�����
			{
				xor(TK1buf+1+j*8,TK1buf+j*8-7,8);
				tri_des(TK1buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11,TK1buf+1,block1*8);

			tri_des(TK2buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block2;j++)							//���ܵڶ��ŵ�����
			{
				xor(TK2buf+1+j*8,TK2buf+j*8-7,8);
				tri_des(TK2buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11+block1*8,TK2buf+1,block2*8);
			
			tri_des(TK3buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block3;j++)							//���ܵ����ŵ�����
			{
				xor(TK3buf+1+j*8,TK3buf+j*8-7,8);
				tri_des(TK3buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11+block1*8+block2*8,TK3buf+1,block3*8);
		}
		else if(0x32 == ENC_KEY.temp.encway)					//AES����
		{
			AES_set_encrypt_key(CryptoKey,128,&key);
			/* ���ܵ�һ�ŵ����� */
			if(block1)
			{
				memset(ivec,0,sizeof(ivec));
				memcpy(ch+11,TK1buf+1,block1*16);
				AES_cbc_encrypt(ch+11,ch+11,block1*16,&key,ivec,1);
			}
			/* ���ܵڶ��ŵ����� */
			if(block2)
			{
				memset(ivec,0,sizeof(ivec));
				memcpy(ch+11+block1*16,TK2buf+1,block2*16);
				AES_cbc_encrypt(ch+11+block1*16,ch+11+block1*16,block2*16,&key,ivec,1);
			}
			/* ���ܵ����ŵ����� */
			if(block3)
			{
				memset(ivec,0,sizeof(ivec));
				memcpy(ch+11+(block1+block2)*16,TK3buf+1,block3*16);
				AES_cbc_encrypt(ch+11+(block1+block2)*16,ch+11+(block1+block2)*16,block3*16,&key,ivec,1);
			}
		}
	 	else
		{
			goto ERRORDATA;
		}
		
		if(block3)
		{
			memcpy(ch+len-33,sha+40,20);						//��������ŵ����ݹ�ϣֵ
			if(block2)
			{
				memcpy(ch+len-53,sha+20,20);					//����ڶ��ŵ����ݹ�ϣֵ
				if (block1)
					memcpy(ch+len-73,sha,20);   				//�����һ�ŵ����ݹ�ϣֵ
			}
			else if (block1)
				memcpy(ch+len-53,sha,20);   					//�����һ�ŵ����ݹ�ϣֵ
		}		 
		else
		{
			if(block2)
			{
				memcpy(ch+len-33,sha+20,20);					//����ڶ��ŵ����ݹ�ϣֵ
				if (block1)
					memcpy(ch+len-53,sha,20);   				//�����һ�ŵ����ݹ�ϣֵ
			}
			else if (block1)
				memcpy(ch+len-33,sha,20);   					//�����һ�ŵ����ݹ�ϣֵ	
		}
				
		if((encryptdatastatus & 0x80) == 0x80)
			memcpy(ch+len-13,ENC_KEY.temp.ksn,10);				//����KSN����

		for(j = 4,lrc = 0,bcc = 0;j<len-3;j++)					//����У����
		{
			lrc ^= ch[j];
			bcc += ch[j];
		}
		ch[len-3] = lrc;
		ch[len-2] = bcc;
		ch[len-1] = 0x03;
	}
	else if(0 == ENC_KEY.temp.status)			  					//���Ļ�������
	{
		len = 1+TK3len+TK2len+TK1len;
		ch[0]=0xFF;
		if(TK3len)TK3buf[TK3len-1] = 0x0D;
		if(TK2len)TK2buf[TK2len-1] = 0x0D;
		if(TK1len)TK1buf[TK1len-1] = 0x0D;
		memcpy(ch+1,TK3buf,TK3len);
		memcpy(ch+1+TK3len,TK2buf,TK2len);
		memcpy(ch+1+TK3len+TK2len,TK1buf,TK1len);
	}
	else
	{
ERRORDATA:
		len = 10;
		memset(ch, 0xFF, len);					
	}
	
	UsbSendBuff(ch, len, 5000);
	dev_com_write(ch, len);
	
	return;
}

