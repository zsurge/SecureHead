#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "usb_endp.h"

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

//uint8_t MAGBuf[500];
SHA1Context foo;
AES_KEY key;
uint8_t sha[60];
/**************************************************************************************
//	*** 函 数 名:	void MSR_SendData(void)
//	*** 功能描述： 磁道数据加密上送函数
//	*** 参    数: 
//	*** 返 回 值: 解码的长度  	 	
//	*** 模块信息: Ouyangweiquan 2012.04.24创建
***************************************************************************************/
void MSR_SendData(void)
{
	uint8_t *ch = (uint8_t *)TrackBitFlow.Value, ivec[16];
	uint16_t len = 0x10,j;
	uint8_t lrc,bcc,block1,block2,block3;
		
	if(ENC_KEY.temp.level < 0x30 && ENC_KEY.temp.level > 0x34 )	//加密级别失效
	{
		goto ERRORDATA;											//密钥失效返回错误
	}
	if (1 == ENC_KEY.temp.status)								//密文回送磁道数据
	{
		encryptdatastatus = 0xBF;								//设置返回数据的类型
				
		/*长度加84 = 11个数据包头 + 60 个哈希值 + 10个KSN + 2个校验码 + 1个包结束 */
		if(0x32 == ENC_KEY.temp.encway)							//如果AES加密则每块16字节
		{
			block1 = ceil((TK1len-1)/16.0);
			block2 = ceil((TK2len-1)/16.0);
			block3 = ceil((TK3len-1)/16.0);
			len = block1*16 + block2*16 + block3*16 + 84 ;		//计算返回数据长度
		}
		else													//如果DES加密则每块8字节
		{
			block1 = ceil((TK1len-1)/8.0);
			block2 = ceil((TK2len-1)/8.0);
			block3 = ceil((TK3len-1)/8.0);
			len = block1*8 + block2*8 + block3*8 + 84 ;  		//计算返回数据长度
		}
		
		if(!block1 && !block2 && !block3)						//如果所有磁道数为空，刷卡失败
			goto ERRORDATA;
		if(!TK1len)
		{												   	
			encryptdatastatus &= 0xF6;							//第一磁道数据返回为空
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK1buf[1], TK1len-1);			//计算第一磁道数据哈希值
			SHA1Final (&foo, sha);
		}
		if(!TK2len)
		{
			encryptdatastatus &= 0xED;							//第二磁道数据返回为空
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK2buf[1], TK2len-1);			//计算第二磁道数据哈希值
			SHA1Final (&foo, sha+20);
		}
		if(!TK3len)
		{
		 	encryptdatastatus &= 0xDB;							//第三磁道数据返回为空
			len -= 20;
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK3buf[1], TK3len-1);			//计算第三磁道数据哈希值
			SHA1Final (&foo, sha+40);
		}		 
								
		memcpy(ch,"\xFF\x02\x00\x00\x80\x3F\x00\x00\x00\x00",10);//10个字节数据包头
		ch[2] = (uint8_t)(len-7);								 //保存长度
		ch[3] = ((len-7)>>8);
		if(TK1len)ch[6] = TK1len-1;
		if(!TK1len)ch[5] = 0x37;
		if(TK2len)ch[7] = TK2len-1;
		if(TK3len)ch[8] = TK3len-1;
		ch[10] = encryptdatastatus;								//返回数据类型
		
		if (0x31 == ENC_KEY.temp.encmode)				   		//DUKPT加密
		{
			CalcCryptoKey();									//计算DUKPT过程密钥
		}
		else if (0x30 == ENC_KEY.temp.encmode)			 		//FIX加密
		{
			memcpy(CryptoKey,ENC_KEY.temp.fix,16);				//拷贝FIX密钥
		}
		if( 0x30 == ENC_KEY.temp.encway)						//DES加密
		{
			goto ERRORDATA;
		}
		else if(0x31 == ENC_KEY.temp.encway)					//3DES加密
		{
			tri_des(TK1buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block1;j++)							//加密第一磁道数据
			{
				xor(TK1buf+1+j*8,TK1buf+j*8-7,8);
				tri_des(TK1buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11,TK1buf+1,block1*8);

			tri_des(TK2buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block2;j++)							//加密第二磁道数据
			{
				xor(TK2buf+1+j*8,TK2buf+j*8-7,8);
				tri_des(TK2buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11+block1*8,TK2buf+1,block2*8);
			
			tri_des(TK3buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block3;j++)							//加密第三磁道数据
			{
				xor(TK3buf+1+j*8,TK3buf+j*8-7,8);
				tri_des(TK3buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			memcpy(ch+11+block1*8+block2*8,TK3buf+1,block3*8);
		}
		else if(0x32 == ENC_KEY.temp.encway)					//AES加密
		{
			AES_set_encrypt_key(CryptoKey,128,&key);
			/* 加密第一磁道数据 */
			if(block1)
			{
				memset(ivec,0,sizeof(ivec));
				memcpy(ch+11,TK1buf+1,block1*16);
				AES_cbc_encrypt(ch+11,ch+11,block1*16,&key,ivec,1);
			}
			/* 加密第二磁道数据 */
			if(block2)
			{
				memset(ivec,0,sizeof(ivec));
				memcpy(ch+11+block1*16,TK2buf+1,block2*16);
				AES_cbc_encrypt(ch+11+block1*16,ch+11+block1*16,block2*16,&key,ivec,1);
			}
			/* 加密第三磁道数据 */
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
			memcpy(ch+len-33,sha+40,20);						//保存第三磁道数据哈希值
			if(block2)
			{
				memcpy(ch+len-53,sha+20,20);					//保存第二磁道数据哈希值
				if (block1)
					memcpy(ch+len-73,sha,20);   				//保存第一磁道数据哈希值
			}
			else if (block1)
				memcpy(ch+len-53,sha,20);   					//保存第一磁道数据哈希值
		}		 
		else
		{
			if(block2)
			{
				memcpy(ch+len-33,sha+20,20);					//保存第二磁道数据哈希值
				if (block1)
					memcpy(ch+len-53,sha,20);   				//保存第一磁道数据哈希值
			}
			else if (block1)
				memcpy(ch+len-33,sha,20);   					//保存第一磁道数据哈希值	
		}
				
		if((encryptdatastatus & 0x80) == 0x80)
			memcpy(ch+len-13,ENC_KEY.temp.ksn,10);				//拷贝KSN数据

		for(j = 4,lrc = 0,bcc = 0;j<len-3;j++)					//计算校验码
		{
			lrc ^= ch[j];
			bcc += ch[j];
		}
		ch[len-3] = lrc;
		ch[len-2] = bcc;
		ch[len-1] = 0x03;
	}
	else if(0 == ENC_KEY.temp.status)			  					//明文回送数据
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

