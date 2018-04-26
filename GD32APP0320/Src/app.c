#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "gd32f1x0_wwdgt.h"
#include "usb_endp.h"
#include "ini.h"
#include "systick.h"
#include "dev_uart.h"


extern AES_KEY key;

union __ENC_KEY ENC_KEY;					//密钥保存数据结构
uint8_t CryptoKey[16];						//DUKPT计算出的过程密钥
								  	
uint8_t random[8];							//随机数
uint8_t macdata[8];							//鉴别数据

const char SHID[] = "PF SecureHeadReader V 1.02";
#ifdef FLASHKEY_SUPPORT
const char APPVERSION[] = "VPFASTMG180324003";
#else
const char APPVERSION[] = "VPFASTMS180324003";
#endif

volatile uint8_t WriteFlag = 0;				//保存密钥标志：0：不保存，1：使能保存
volatile uint8_t GetNextFlag = 0;			//获取下一个KSN标志：0：不获取下一个，1：使能获取下一个 

volatile uint8_t macstate = 0x00;			//鉴定状态：0x30：未接收到鉴定数据或鉴定数据失败；0x31：鉴定数据OK
volatile uint8_t encryptdatastatus = 0x00;	//bit 1 ==1 表示1磁道加密数据存在
											//bit 2 ==1 表示2磁道加密数据存在
											//bit 3 ==1 表示3磁道加密数据存在
											//bit 4 ==1 表示1磁道哈希数据存在
											//bit 5 ==1 表示2磁道哈希数据存在
											//bit 6 ==1 表示3磁道哈希数据存在
											//bit 7 ==1 表示会话ID数据存在
											//bit 8 ==1 表示KSN存在
//volatile uint16_t XORflag = 0x02;
volatile uint8_t RxdStatus = 0;			 		//接收状态
volatile uint8_t SynHead = 0;				 	//接收包头个数
volatile uint8_t RxdFrameStatus = 0;			//接收包状态
volatile uint8_t NowLen = 0;				 	//接收字节指针
volatile uint8_t RxdTotalLen = 0;			 	//接收包数据长度
// uint8_t RxdBuf[MAX_RXD_BUF_LEN];			//接收包数据缓存
// uint8_t SetKeyBuf[80];			    		//设置密钥数据缓存
#define RxdBuf ((uint8_t *)TempTrackDirtData.Value)			//接收包数据缓存
#define SetKeyBuf ((uint8_t *)TempTrackData.Value)			    		//设置密钥数据缓存
volatile uint8_t SetKeyLen=0;			    //设置密钥数据长度
volatile uint8_t SetKeyFlag=0;				//设置密钥标志，0：不能设置；1：允许设置。
volatile uint8_t Bcc;						//校验和

//关闭所有中断
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

void ResetSetting(void)
{
	SetKeyFlag = 0;
	memset(ENC_KEY.key,0x00,144);
	ENC_KEY.temp.level = 0x31;//加密等级为0x31
	ENC_KEY.temp.enabledevice = 0x31; //启用、禁止标志位
	ENC_KEY.temp.writesnflag = 0x30;  //写sn标志位
	ENC_KEY.temp.selecttrack = 0x30;    //选择磁道参数
	ENC_KEY.temp.Terminator = 0x0D;     //磁道结束符
	ENC_KEY.temp.setseparator = 0x00;   //写入分割符	
	ENC_KEY.temp.beepmode = 0x32;
	ENC_KEY.temp.settrack2format = 0x31;
	ENC_KEY.temp.status = 0;			//失能加密
	ENC_KEY.temp.encway = 0x00;			//默认DES加密
	macstate = 0x00;					//未接收到鉴定数据
	
	WriteFlag = 1;
	WriteENCKEY();	
	WriteFlag = 0;						
}

void Default_Settings(void)
{
	
	memset(ENC_KEY.key,0x00,sizeof(ENC_KEY.key));
	ENC_KEY.temp.level = 0x31;//加密等级为0x31
	ENC_KEY.temp.enabledevice = 0x31; //启用、禁止标志位
	ENC_KEY.temp.writesnflag = 0x30;  //写sn标志位
	ENC_KEY.temp.selecttrack = 0x30;    //选择磁道参数
	ENC_KEY.temp.Terminator = 0x0D;     //磁道结束符  ---对照文档
	ENC_KEY.temp.setseparator = 0x3b;   //写入数据分割符	
	ENC_KEY.temp.beepmode = 0x32;      //蜂鸣器模式
	ENC_KEY.temp.settrack2format = 0x31;//轨道2数据管理
	ENC_KEY.temp.status = 0;			//失能加密
	ENC_KEY.temp.encway = 0x30;			//默认DES加密
//	IDT_UpdateKSN(10,ENC_KEY.temp.ksn);
	memcpy(ENC_KEY.temp.ksn,"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x00",10);
	
	ENC_KEY.temp.Enhancedstatue=0x30;//强加密和普通加密状态
	
	ENC_KEY.temp.HASHSET=0x07;//哈希值的发送状态
//	ENC_KEY.temp.ksn[10]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00};
	macstate = 0x30;					//未接收到鉴定数据
	
	memcpy(ENC_KEY.temp.key,"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x00\x01\x02\x03\x04",16);
	
	ENC_KEY.temp.enabledevice = 0x31; //启用、禁止标志位
//	ENC_KEY.temp.Terminator = 0x0d;
	
	memset(ENC_KEY.temp.Preamble,0x00,sizeof(ENC_KEY.temp.Preamble)); //磁头起始符
	memset(ENC_KEY.temp.Postamble,0x00,sizeof(ENC_KEY.temp.Postamble));
	
	memset(ENC_KEY.temp.track1prefix,0x00,sizeof(ENC_KEY.temp.track1prefix));//磁头前缀
	memset(ENC_KEY.temp.track2prefix,0x00,sizeof(ENC_KEY.temp.track2prefix));
	memset(ENC_KEY.temp.track3prefix,0x00,sizeof(ENC_KEY.temp.track3prefix));
	
	memset(ENC_KEY.temp.track1suffix,0x00,sizeof(ENC_KEY.temp.track1suffix));//磁头后缀
	memset(ENC_KEY.temp.track1suffix,0x00,sizeof(ENC_KEY.temp.track1suffix));
	memset(ENC_KEY.temp.track1suffix,0x00,sizeof(ENC_KEY.temp.track1suffix));
	
//	ENC_KEY.temp.selecttrack =0x30;
//	ENC_KEY.temp.setseparator =0x0d;
	
//	ENC_KEY.temp.settrack2format=0x31;
	
	WriteFlag = 1;
	WriteENCKEY();	
	WriteFlag = 0;
}

/**************************************************************************************
	*** 函 数 名:	void WriteENCKEY(void)
	*** 功能描述：	讲ENCKEY保存到FLASH中
	*** 参    数:  	输入: 全局变量ENC_KEY
					输入: ENC_KEY保存地址
				    输出：NULL 
	*** 返 回 值:	NULL  	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
***************************************************************************************/
void WriteENCKEY(void)
{
	#ifdef FLASHKEY_SUPPORT
	uint8_t i;
	uint8_t tempdata[144];
	memset(tempdata ,0, sizeof(tempdata));
	if(WriteFlag==1)
	{
		memcpy(tempdata,ENC_KEY.key,142);
		memcpy(tempdata+142,"\x00\x00",2);
		for(i=0;i<142;i++)
		{
			tempdata[142] ^= tempdata[i];
			tempdata[143] += tempdata[i];
		}
 		for(i=0;i<8;i++)
 			tri_des(tempdata+i*8,(unsigned char *)SHID,(unsigned char *)SHID+8,0);	   //加密要存储的密钥值
		__disable_irq();
		EarseBlockFlash(KEYADD);
		WriteBlockFlash(KEYADD ,tempdata, 144);
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
	*** 函 数 名:	void ReadENCKEY(void)
	*** 功能描述：	读取保存的ENCKEY到RAM中
	*** 参    数:  	输入: ENC_KEY保存地址
				    输出：全局变量ENC_KEY 
	*** 返 回 值:	TRUE/FALSE   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
***************************************************************************************/
uint8_t ReadENCKEY(void)
{
	#ifdef FLASHKEY_SUPPORT
	uint8_t tempdata[144],i,lrc,bcc;
	memset(tempdata ,0, 144);
	ReadBlockFlash(KEYADD ,tempdata, 144);     			//读出之前保存的密钥值
	for(i=0;i<8;i++)
		tri_des(tempdata+i*8,(unsigned char *)SHID,(unsigned char *)SHID+8,1);	   //解密存储的密钥值
	memcpy(ENC_KEY.key,tempdata,144);
	//校验保存的密钥
	for(lrc=bcc=i=0;i<142;i++)
	{
		lrc ^= tempdata[i];
		bcc += tempdata[i];
	}
	if(lrc == ENC_KEY.key[142] && bcc == ENC_KEY.key[143] )
		return TRUE;
	else
		return FALSE;
	#else
	return TRUE;
	#endif
}

/**************************************************************************************
	*** 函 数 名:	uint8_t AsciiToHex(uint8_t * pAscii, uint8_t * pHex, int nLen)
	*** 功能描述：	将一个 ASSC 码表示的十六进制字符串转换成十六进制的字节串；
	*** 参    数:  	输入: pAscii -- 要转换的ASCII码表示的十六进制字符串的首地址；
						  nLen	 -- 要转换的ASCII码表示的十六进制字符串的长度（字节数）；
				    输出：pHex	 -- 转换后的十六进制数字节串首地址；
	*** 返 回 值:	TRUE/FALSE   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
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
	*** 函 数 名:	void HexToAscii(unsigned char * pHex, unsigned char * pASSCHex, int nLen)
	*** 功能描述：	将一个十六进制字节串转换成 ASCII 码表示的字符串；
	*** 参    数:  	输入: pHex 	   -- 要转换的十六进制数字节串首地址；
						  nLen	   -- 要转换的十六进制数字节串的长度（字节数）；
				    输出：pASSCHex -- 转换后的 ASCII 码表示的字符串的首地址；
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
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
	*** 函 数 名:	void Random(void) 
	*** 功能描述：	取8个字节的16进制的随机数；
	*** 参    数:  	输入: NULL；
				    输出：8个十六进制随机数；
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
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
	*** 函 数 名:	uint8_t GetNextKSN(uint8_t* pBUserKSN) 
	*** 功能描述：	使DUKPT算法因子KSN自加1；
	*** 参    数:  	输入: KSN；
				    输出：下一个KSN；
	*** 返 回 值:	FALSE / TRUE   	 	
	*** 模块信息: 	Ouyangweiquan 2011.11.18创建
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
	WriteENCKEY();							  //保存更新后的KSN
//	{
//		WriteFlag = 0;
//		return TRUE;
//	}
	WriteFlag = 0;
	return TRUE;
}


/**************************************************************************************
	*** 函 数 名:	void CalcCryptoKey(void) 
	*** 功能描述：	根据当前更新后的KSN和KEY计算出过程密钥；
	*** 参    数:  	输入: KSN和KEY；
				    输出：过程密钥；
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.11.18创建
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

/*  


异或函数


*/

 int CalcXOR(char *datas, int len,int sl)
{
		int i = 0;
		int CheckSum = 0x02;

		for (i = sl; i < len; i++)
		{
				CheckSum ^= datas[i];
		}

		return CheckSum;
}

/**************************************************************************************
	*** 函 数 名:	void send_frame(uint8_t frame_type)
	*** 功能描述：	返回对命令的响应；
	*** 参    数:  	输入: frame_type -- 响应命令的参数；
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
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
		case REVIEWSET:
		i=0;
		TxdBuf[i++]=0x06;//   其实帧包头
		TxdBuf[i++]=0x02;
		
		bcc = 0x02;
		
		TxdBuf[i++]=0x4c;		
		TxdBuf[i++]=0x01;		
		TxdBuf[i++]=ENC_KEY.temp.encway;
		
		
		TxdBuf[i++]=0x4e;//ksn		
		TxdBuf[i++]=0x0a;
		for(j=0;j<10;j++)
		{
		  TxdBuf[i++]=ENC_KEY.temp.sn[j];
		}
		
		TxdBuf[i++]=0x1a;	/* MSR Reading Settings*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.enabledevice;
		
		
		TxdBuf[i++]=0x1d;	/* Decoding Method Setting*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=0x31;
		
		TxdBuf[i++]=0x21;	/* Decoding Method Setting*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.Terminator;
		
		TxdBuf[i++]=0x21;	/* Preamble Setting*/
		TxdBuf[i++]=strlen(ENC_KEY.temp.Preamble);
		i+=1;
		memcpy(TxdBuf+i,ENC_KEY.temp.Preamble,strlen(ENC_KEY.temp.Preamble));
		i+=strlen(ENC_KEY.temp.Preamble);
		
		TxdBuf[i++]=0xd3;	/* Postamble Setting*/
		TxdBuf[i++]=strlen(ENC_KEY.temp.Postamble);
		i+=1;
		memcpy(TxdBuf+i,ENC_KEY.temp.Postamble,strlen(ENC_KEY.temp.Postamble));
		i+=strlen(ENC_KEY.temp.Postamble);
		
		TxdBuf[i++]=0x34;	/* Track n Prefix Setting   n= 34 35 36*/
		TxdBuf[i++]=strlen(ENC_KEY.temp.track1prefix);
		i+=1;
		memcpy(TxdBuf+i,ENC_KEY.temp.track1prefix,strlen(ENC_KEY.temp.track1prefix));
		i+=strlen(ENC_KEY.temp.track1prefix);
		
		TxdBuf[i++]=0x35;	/* Track n Prefix Setting   n= 34 35 36*/
		TxdBuf[i++]=strlen(ENC_KEY.temp.track2prefix);
		i+=1;
		memcpy(TxdBuf+i,ENC_KEY.temp.track1prefix,strlen(ENC_KEY.temp.track2prefix));
		i+=strlen(ENC_KEY.temp.track2prefix);
		
		TxdBuf[i++]=0x36;	/* Track n Prefix Setting   n= 34 35 36*/
		TxdBuf[i++]=strlen(ENC_KEY.temp.track3prefix);
		i+=1;
		memcpy(TxdBuf+i,ENC_KEY.temp.track1prefix,strlen(ENC_KEY.temp.track3prefix));
		i+=strlen(ENC_KEY.temp.track3prefix);
		
	  TxdBuf[i++]=0x13;	/* Track Selection Setting*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.selecttrack;
		
		TxdBuf[i++]=0x17;	/* Track Separator Selection*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.setseparator;
		
		TxdBuf[i++]=0x19;	/* Start/End Sentinel and Track 2 Account Number Only*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.settrack2format;

    TxdBuf[i++]=0x58;	/* Select Key Management Type*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.encmode;
		
		TxdBuf[i++]=0x4c;	/* Encryption Settings*/
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.encway;
		
		
		TxdBuf[i++]=0x51;	/* Encryption Settings*/
		TxdBuf[i++]=0x0a;
		memcpy(TxdBuf+i,ENC_KEY.temp.ksn,10);
		TxdBuf[i++]=ENC_KEY.temp.encway;
		
		TxdBuf[i++]=0x7e;     /*   加密等级     */
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.level;
			
		TxdBuf[i++]=0x5c;          /* Hash Option Setting */
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.HASHSET;
		
		TxdBuf[i++]=0x85;          /* Encryption Output Format Setting */
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.Enhancedstatue;
		
		TxdBuf[i++]=0x86;          /* Mask Option Setting */
		TxdBuf[i++]=0x01;
		TxdBuf[i++]=ENC_KEY.temp.MaskSetting;
		
		TxdBuf[i++]=ETX;
		
		TxdBuf[i++]=CalcXOR(TxdBuf,i,2);
		
		break;
		
		
		case ENCRYPTEXTERNAL://外部认证模式  只有在加密等级4的时候才使用
			i=0;
		  TxdBuf[i++]=0x06;
		  TxdBuf[i++]=0x02;
		  
		
		
		
       break;
    case REQUEST_DOWN:   				/* request download */
            i = 0;						    //请求下载
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
			i = 0;						   //加密磁头协议
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
//				printf("op[]\r\n");
				break;
			}
			init_serial_boot();	
			break;
		case GETCHALLENGE:
//			 printf("RxdBuf--AS %x\r\n",RxdBuf[2]);
			if(RxdBuf[2] == GETCHALLENGE) 
			{
				i = 0;
				TxdBuf[i++] = 0x06; 			// 06
				TxdBuf[i++] = RxdBuf[0]; 		// 02
				bcc = RxdBuf[0];
				for(j=0; j<8; j++)  //拷贝随机数、计算异或和
				{
					random[j] = rand()%127; //random[j];

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
				for(j=0; j<strlen(SHID); j++)  //拷贝安全磁头ID、计算异或和
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
				
//				printf("456\r\n");
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
				
				for(j=0; j< 10; j++)  			//拷贝KSN、计算异或和
				{
					TxdBuf[i++] = ENC_KEY.temp.ksn[j];
					printf("ENC_KEY.temp.ksn[j] %x\r\n",ENC_KEY.temp.ksn[j]);
					bcc ^= ENC_KEY.temp.ksn[j];
				}
				TxdBuf[i++] = ETX;
	            bcc ^= ETX;
	            TxdBuf[i++] = bcc;
//				printf("TxdBuf %x\r\n",TxdBuf[i-1]);
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
				TxdBuf[i++] = 0x0B;				// 0B
				bcc ^= 0x0B;
				TxdBuf[i++] = 0x0A;				// 0A
				bcc ^= 0x0A;
				
				for(j=0; j<0x0A; j++)  			//拷贝SN、计算异或和
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
				
				for(j=0; j< 8; j++)  			//拷贝SID、计算异或和
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
		case SETTERMINATOR:
		{
			i = 0;
			memset(TxdBuf,0x00,sizeof(TxdBuf));
		  TxdBuf[i++] = 0x06; 
			
			printf("ff\r\n");
			
			
		}break;
		
        default:
        	init_serial_boot();
			return;
    }
	dev_com_write(TxdBuf, i);
	UsbSendBuff(TxdBuf, i, 3000);

	//发送命令的响应
//	printf("Send:");
//	for (bcc = 0; bcc < i; bcc++)
//		printf("%02X ", TxdBuf[bcc]);
//	printf("\r\n");
}


/**************************************************************************************
	*** 函 数 名:	void DealSerialParse(void)
	*** 功能描述：	将收到的数据解析成数据包；
	*** 参    数:  	NULL
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
***************************************************************************************/
void DealSerialParse(void)
{
	uint8_t i = 0;
	while(1)
	{	
		if(UsbRecvOne(&i) != 1)  //读取USB数据
		{
		    return;
		}	
		
		switch (RxdStatus)
		{ /*接收数据状态*/
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
				break;				/*接收包头*/
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
	*** 函 数 名:	void DealRxData(void)
	*** 功能描述：	解析收到的完整数据包，并响应数据包；
	*** 参    数:  	NULL
	*** 返 回 值:	NULL   	 	
	*** 模块信息: 	Ouyangweiquan 2011.09.20创建
***************************************************************************************/
char firstflag=0,secondflag=0,countflag=0,firstkeybuff[16],secondkeybuff[16];
void DealRxData(void)
{
	uint16_t i,j,loop;
	uint8_t bcc = 0,setseparatorflag=0,EnyBuff[]={0},ivec[16];
    
	if (FINISH == RxdFrameStatus)
	{
		//spi_send(RxdBuf,RxdTotalLen);
		//打印一条接收到的命令
//		printf("CMD:");
//		for (i = 0; i < RxdTotalLen; i++)
//			printf("%02X ", RxdBuf[i]);
//		printf("\r\n");

//    DBG_H("CMD", RxdBuf, RxdTotalLen);
		
		
		wwdgt_counter_update(0);
		
		if(RxdBuf[0]==0x01) //LOADKEY  导入密钥
		{
		if(RxdBuf[5]==0x01)
			{
				if(firstflag!=RxdBuf[5])
				{
					firstflag=RxdBuf[5];
					if(countflag==0)
					{					
						countflag+=1;
						memset(firstkeybuff,0x00,sizeof(firstkeybuff));
						memcpy(firstkeybuff,&RxdBuf[6],16);				
					}
					if(countflag==1)
					{
						countflag=0;
						firstflag=0;
						memset(secondkeybuff,0x00,sizeof(secondkeybuff));
						memcpy(secondkeybuff,&RxdBuf[6],16);
						
						xor(firstkeybuff,secondkeybuff,16);	
						memset(ENC_KEY.temp.key,0x00,sizeof(ENC_KEY.temp.key));
						memcpy(ENC_KEY.temp.key,firstkeybuff,16);
						memset(firstkeybuff,0x00,sizeof(firstkeybuff));
						memset(secondkeybuff,0x00,sizeof(secondkeybuff));
						
						send_frame(CMDSUCC);
					}
			}
		}
			if(RxdBuf[5]==0x02)
			{
				if(secondflag!=RxdBuf[5])
				{
					secondflag=RxdBuf[5];
				if(countflag==0)
				{					
					countflag+=1;
					memset(firstkeybuff,0x00,sizeof(firstkeybuff));
				  memcpy(firstkeybuff,&RxdBuf[6],16);				
			  }
				if(countflag==1)
				{
					countflag=0;
					secondflag=0;
					memset(secondkeybuff,0x00,sizeof(secondkeybuff));
				  memcpy(secondkeybuff,&RxdBuf[6],16);
          xor(firstkeybuff,secondkeybuff,16);	
          memset(ENC_KEY.temp.key,0x00,sizeof(ENC_KEY.temp.key));//清理key数组
          memcpy(ENC_KEY.temp.key,firstkeybuff,16);
					memset(firstkeybuff,0x00,sizeof(firstkeybuff));
					memset(secondkeybuff,0x00,sizeof(secondkeybuff));	
          send_frame(CMDSUCC);					
				}
			}
				
			}							
	}
		
		if(RxdBuf[0] == STX)										//解析02数据包
		{
			if (REQUEST_DOWN == RxdBuf[1])							//0x55	/* request download */
			{
				send_frame(CMDSUCC);
																	//重启
				init_serial_boot();
				
				WriteUpgradeFlag();
				NVIC_SystemReset();
				delay_1ms(10000); 		
			    while(1);
			    
			}
			else if(ENCRYPTEXTERNAL == RxdBuf[1])//解密外部数据
			{
				memcpy(EnyBuff,&RxdBuf[4],RxdBuf[3]);
				loop=RxdBuf[3]/8;
				if((RxdBuf[3]%8)!=0) loop+=1;
				
				memset(ivec,0,sizeof(ivec));
				if((ENC_KEY.temp.level==0x32)||(ENC_KEY.temp.level==0x33))
				{					
					if(0x31 == ENC_KEY.temp.encmode)//是dukpt加密方式  则返回ksn
					{
						CalcCryptoKey();//DUKPT加密方式获取密钥
					}				
					if(0x30 == ENC_KEY.temp.encmode)//是fix加密方式  则返回sn
					{
						memcpy(CryptoKey,ENC_KEY.temp.fix,16);				//拷贝FIX密钥						
					}
					if (0x31 == ENC_KEY.temp.encmode)				   		//DUKPT加密
					{
						tri_des(EnyBuff,CryptoKey,CryptoKey+8,0);
						for(j = 1;j< loop;j++)							//加密第一磁道数据
						{
							xor(EnyBuff+j*8,EnyBuff+j*8-7,8);
							tri_des(EnyBuff+1+j*8,CryptoKey,CryptoKey+8,0);
						}
						
					}
					if (0x32 == ENC_KEY.temp.encmode)				   		////AES加密加密
					{
						AES_set_encrypt_key(CryptoKey,128,&key);
						AES_cbc_encrypt(EnyBuff,EnyBuff,loop*16,&key,ivec,1);
					}
					if(ENC_KEY.temp.level==0x33) //加密等级4
					{
						loop=RxdBuf[3];
						memcpy(EnyBuff,ENC_KEY.temp.sid,loop);					
					}
					if(0x31 == ENC_KEY.temp.encmode)//是dukpt加密方式  则返回ksn
					{
						memcpy(EnyBuff+loop,ENC_KEY.temp.ksn,10);
            loop+=10;						
					}
					if(0x30 == ENC_KEY.temp.encmode)
					{
						memcpy(EnyBuff+loop,ENC_KEY.temp.sn,10);//FIX KEY加密
						loop+=10;
					}
					UsbSendBuff(EnyBuff, loop, 3000);
					send_frame(ENCRYPTEXTERNAL);
				}
				else 
				{
					send_frame(CMDERRO);
					
				}
				init_serial_boot();
//				break;
			}
			else if (READ_VERSION == RxdBuf[1])						//0x28	/* read application ersion */
			{
				send_frame(READ_VERSION);
				init_serial_boot();
			}
			else if (RESETHEAD == RxdBuf[1])						//0xF8	/* reset secureheadreader */
			{
//				SetKeyFlag = 0;
//				memset(ENC_KEY.key,0x00,136);
//				ENC_KEY.temp.level = 0x31;
//				ENC_KEY.temp.enabledevice = 0x31;
//				ENC_KEY.temp.writesnflag = 0x30;
//				ENC_KEY.temp.selecttrack = 0x30;
//				ENC_KEY.temp.Terminator = 0x0D;
//				WriteFlag = 1;
//				WriteENCKEY();
//				send_frame(CMDSUCC);
//				WriteFlag = 0;

//            	SetKeyFlag = 0;
//            	memset(ENC_KEY.key,0x00,136);
//            	ENC_KEY.temp.level = 0x31;
//            	ENC_KEY.temp.enabledevice = 0x31;
//            	ENC_KEY.temp.writesnflag = 0x30;
//            	ENC_KEY.temp.selecttrack = 0x30;
//            	ENC_KEY.temp.Terminator = 0x0D;            	
//            	ENC_KEY.temp.status = 0;			//失能加密
//            	ENC_KEY.temp.encway = 0x00;			//默认DES加密   
//            	
//            	WriteFlag = 1;
//            	WriteENCKEY();	
//            	send_frame(CMDSUCC);
//            	WriteFlag = 0;	
//                printf("00002\r\n");
                ResetSetting();
                send_frame(CMDSUCC);
				init_serial_boot();
			}
			else if (SETKEY == RxdBuf[1] && SETKEY == RxdBuf[2])	//0x46	/* set key commands  */
			{
				memset(SetKeyBuf,0,sizeof(SetKeyBuf));
				SetKeyLen = from64tobits(SetKeyBuf,&RxdBuf[3],RxdTotalLen-7);
//				DBG_H("SetKeyBuf is",SetKeyBuf,RxdTotalLen-7);
				if(SetKeyBuf[0] == SETKEYHEAD)
				{
					bcc = 0;	
					for(i = 0; i < SetKeyLen-1; i++)
						bcc ^= SetKeyBuf[i];
					if (bcc == SetKeyBuf[SetKeyLen -1])			   	//校验
					{
						SetKeyLen =  SetKeyBuf[2];					//拷贝密钥数据长度
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

			
			else if (READCMD == RxdBuf[1])					//0x52	/* read status commands */  读取状态命令
			{
				switch (RxdBuf[2])
				{
					case REVIEWSET:
						send_frame(REVIEWSET);
						RxdFrameStatus = SPACE;
                		break;
						
					case ACTIVATEAUTHEN:
						if(ENC_KEY.temp.level==0x33)//加密等级4
						{
						if(RxdBuf[3]==0x80)
						{
							if(RxdBuf[4]==0x02)
							{
								j=0;loop=0;i=0;
								
								memcpy(EnyBuff+j,ENC_KEY.temp.ksn,10);
								for(loop=0;loop<2;loop++)
								{
									for(i=0;i<6;i++)
									EnyBuff[j++]=rand()%127;
									if(i==5)
									{
										EnyBuff[j++]=ENC_KEY.temp.ksn[9];
										EnyBuff[j++]=ENC_KEY.temp.ksn[10];
									}
								}
							}
							
						}send_frame(CMDSUCC);
					}
					else
					{
						send_frame(CMDERRO);
					}RxdFrameStatus = SPACE;
					
					break;
					case READID:						    //0x22	/* read secureheadreader ID */
						send_frame(READID);
						RxdFrameStatus = SPACE;
                		break;
					case GETCHALLENGE:						//0x74	/* get encrypt challenge */
//						printf("ccs\r\n");
						send_frame(GETCHALLENGE);
						RxdFrameStatus = SPACE;
                		break;
					case GETSECURITYLEVEL:					//0x7E	/* get security level */
						send_frame(GETSECURITYLEVEL);
						RxdFrameStatus = SPACE;
                		break;
					case REVIEWKSN:							//0x51	/* review KSN (DUKPT key management only) */
//						printf("002ggh\r\n");
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
					case MASKOPTION: //MaskSetting  数据掩码设置
						if(RxdBuf[3]==0x01)   //
						{
								if(RxdBuf[4]==0x01)
									ENC_KEY.temp.MaskSetting=RxdBuf[4];
							
							send_frame(CMDSUCC);
						}
						else
						{
							send_frame(CMDERRO);
						}RxdFrameStatus = SPACE;
							break;
					case HASHOPTION:
						if(RxdBuf[2]==0x5C)
						{
							if(RxdBuf[3]==0x01)
							{
								if(RxdBuf[4]==0x01)//轨道1哈希值发送标记
								ENC_KEY.temp.HASHSET=RxdBuf[4];
								
								if(RxdBuf[4]==0x02)//轨道2哈希值发送标记
								ENC_KEY.temp.HASHSET=RxdBuf[4];
								
								if(RxdBuf[4]==0x04)//轨道3哈希值发送标记
								ENC_KEY.temp.HASHSET=RxdBuf[4];
								
								if(RxdBuf[4]==0x07)//全部轨道哈希值发送标记
								ENC_KEY.temp.HASHSET=RxdBuf[4];
								send_frame(CMDSUCC);
						   
							}
							
						}
						else
						{
							send_frame(CMDERRO);
						}RxdFrameStatus = SPACE;
							break;		
					case SETDEFAULT:						//0x18	/* set default configuration */
						ENC_KEY.temp.status = 0;			//失能加密
						ENC_KEY.temp.level = 0x31;			//加密级别为1
						ENC_KEY.temp.encway = 0x00;			//默认DES加密
						macstate = 0x00;					//未接收到鉴定数据
						WriteFlag = 1;
//					  ResetSetting();
						WriteENCKEY();						//保存更新后的KEY
						WriteFlag = 0;	
					  
            Default_Settings();					
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
//					  printf("ffddQQ\r\n");
                		break;
					case SETBEEP:
						if(RxdBuf[3] == 0x01)
						{	
							if(0x30 <= RxdBuf[4] && 0x34 > RxdBuf[4])		 //匹配命令的参数
							{
								ENC_KEY.temp.beepmode = RxdBuf[4];	//读取设置的加密方式							
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的KEY
								WriteFlag = 0;
								
								send_frame(CMDSUCC);
							}
							else
							{
								send_frame(CMDERRO);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
        case SETSELECTTRACK :  /*设置选择读的轨道*/
//					printf("RxdBufdf %x\r\n",RxdBuf[4]);
            if(RxdBuf[3] == 0x01)
						{	
							if(0x30 <= RxdBuf[4] && 0x39 >= RxdBuf[4])		 //匹配命令的参数
							{
								ENC_KEY.temp.selecttrack = RxdBuf[4];	//读取设置的加密方式	
//                printf("ENC_KEY.temp.selecttrack %d\r\n",ENC_KEY.temp.selecttrack);	
//                printf("RxdBuf0 %x\r\n",RxdBuf[4]);									
                								
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的参数
								WriteFlag = 0;
								
								send_frame(CMDSUCC);
							}
							else
							{
								send_frame(CMDERRO);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                	    break;
						
         case SETTRACKSEPARATOR:   /*设置轨道分割符*/
					   
            if(RxdBuf[3] == 0x01)
						{	
							if(0 <= RxdBuf[4] && 127 >= RxdBuf[4])		 //匹配命令的参数
							{
								setseparatorflag=RxdBuf[4];
								printf("RxdBuf %x\r\n",RxdBuf[4]);
								ENC_KEY.temp.setseparator = setseparatorflag;	//写入分割符	
                printf("ENC_KEY.temp.setseparator %d\r\n",ENC_KEY.temp.setseparator);								
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的参数
								WriteFlag = 0;
								
								send_frame(CMDSUCC);
							}
							else
							{
								send_frame(CMDERRO);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;            	    
            	    break;
           case SETTRACK2:   /*设置轨道2数据上送格式*/
           if(RxdBuf[3] == 0x01)
						{	
							if(0x30 <= RxdBuf[4] && 0x34 > RxdBuf[4])		 //匹配命令的参数
							{
								ENC_KEY.temp.settrack2format = RxdBuf[4];	//读取设置的加密方式							
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的参数
								WriteFlag = 0;								
								send_frame(CMDSUCC);
							}
							else
							{
								send_frame(CMDERRO);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;            	    
            	        break;
					case SETDECODEWAY:						//0x1D	/* set decoding in both directions */	
					    //这里还未完成，待补充
						send_frame(CMDSUCC);
						RxdFrameStatus = SPACE;
                		break;
					case SETENCMODE:						//0x58	/* set encryption mode */		
//            printf("SETENCMODE\r\n");						
						if(RxdBuf[3]==0x01)
						{	
							if(0x30==RxdBuf[4]|| 0x31==RxdBuf[4])
							{
								ENC_KEY.temp.encmode = RxdBuf[4];	//读取设置的加密方式
								if(0x30 == RxdBuf[4])
									ENC_KEY.temp.level = 0x32;
								else
									ENC_KEY.temp.level = 0x33;	
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的KEY
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

//				    DBG_H("randomf",random,8);
						tri_des(random,ENC_KEY.temp.fix,ENC_KEY.temp.fix+8,0);
				    
						if(memcmp(random,&RxdBuf[4],RxdBuf[3]) == 0)
						{
//							DBG_H("ENC_KEY.temp.fix",ENC_KEY.temp.fix,16);							
							macstate = 0x31;				//鉴定数据OK
							memset(random,0x00,8);			//清空随机数
							send_frame(CMDSUCC);	
						}
						else
						{
							macstate = 0x30;				//鉴定数据失败
							memset(random,0x00,8);			//清空随机数
							send_frame(CMDERRO);	
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETENCWAY:							//0x4C	/* set encryption way */
                        
						if(RxdBuf[3]==0x01)
						{	
							if( 0x31 == RxdBuf[4] || 0x32 == RxdBuf[4])
							{
								ENC_KEY.temp.encway = RxdBuf[4];//读取设置的加密类型   
								ENC_KEY.temp.status = 1;	//使能加密
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的KEY
								WriteFlag = 0;
								send_frame(CMDSUCC);
							}
							if(0x30 == RxdBuf[4])
							{
								ENC_KEY.temp.encway = RxdBuf[4];//读取设置的加密类型   
								ENC_KEY.temp.status = 0;	//使能加密
//								printf("ddffc\r\n");
//								printf("ENC_KEY.temp.encwayccf %d\r\n",ENC_KEY.temp.encway);
								WriteFlag = 1;
								WriteENCKEY();				//保存更新后的KEY
								WriteFlag = 0;
								send_frame(CMDSUCC);
								
							}
//							else
//								send_frame(CMDERRO);
						}
						else
						{
							ENC_KEY.temp.status = 0;		//失能加密
							WriteFlag = 1;
							WriteENCKEY();					//保存更新后的KEY
							WriteFlag = 0;
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETENCRYPTIONOPTION:					//0x84	/* Encryption Option Setting*/
						if(RxdBuf[3]==0x01)
						{	
							if(0x01 == RxdBuf[4])		    //轨道1强制加密
							{
								ENC_KEY.temp.Enhancedoption=RxdBuf[4];
								send_frame(CMDSUCC);
							}
							if(0x02 == RxdBuf[4])		    //轨道3强制加密
							{
								ENC_KEY.temp.Enhancedoption=RxdBuf[4];
								send_frame(CMDSUCC);
							}
							if(0x04 == RxdBuf[4])		    //轨道3强制加密
							{
								ENC_KEY.temp.Enhancedoption=RxdBuf[4];
								send_frame(CMDSUCC);
							}
							if(0x08 == RxdBuf[4])		    //轨道3强制加密
							{
								ENC_KEY.temp.Enhancedoption=RxdBuf[4];
								send_frame(CMDSUCC);
							}
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETENCRYPTIONFORMAT:					 //0x85	/* Encryption Output Format Setting */
						if(RxdBuf[3] == 0x01)
						{	
							if(0x31 == RxdBuf[4])		 //匹配命令的参数
							{
								ENC_KEY.temp.Enhancedstatue=RxdBuf[4];
								send_frame(CMDSUCC);
							}
							else if(0x30 == RxdBuf[4])	
							{
								ENC_KEY.temp.Enhancedstatue=RxdBuf[4];
								send_frame(CMDSUCC);							
							}
						}
						else if(RxdBuf[3] == 0x00)
						{
//							ENC_KEY.temp.Enhancedstatue=RxdBuf[4];
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                		break;
					case SETDEVICEKEY:						//0x76	/* set device key command */
						if(RxdBuf[3]==0x10 && 0x31 == macstate)
						{
							memcpy(ENC_KEY.temp.fix,&RxdBuf[4],RxdBuf[3]);
							ENC_KEY.temp.level = 0x32;
							WriteFlag = 1;
							WriteENCKEY();					//保存更新后的KEY
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
							WriteENCKEY();					//保存会话ID
							WriteFlag = 0; 								
							send_frame(CMDSUCC);
						}
						else
							send_frame(CMDERRO);	
						  RxdFrameStatus = SPACE;
                		break;
					case REVIEWSN:							//0x4E	/* review serial number */
						if(RxdBuf[3]==0x0A)
						{
						    if(ENC_KEY.temp.writesnflag == 0x30)
						    {
    							memcpy(ENC_KEY.temp.sn,&RxdBuf[4],10);
    							ENC_KEY.temp.writesnflag = 0x31;
    							WriteFlag = 1;
    							WriteENCKEY();					//保存序列号
    							WriteFlag = 0; 								
    							send_frame(CMDSUCC);
							}
							else
							{
							    send_frame(CMDERRO);  //只能写一次
							}
						}
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
                		break;
					case MSRSETTINGS:						//0x1A	/* MSR Reading Settings */							
						if(RxdBuf[3]==0x01)
						{
						    if(RxdBuf[4] == 0x30) //add 20180205 level=0 dissable dev
							{							    
								ENC_KEY.temp.enabledevice = 0x30;
    							WriteFlag = 1;
    							WriteENCKEY();					
    							WriteFlag = 0; 		
    							send_frame(CMDSUCC);    							
							}
							else
							{
    							ENC_KEY.temp.enabledevice = RxdBuf[4];
    							WriteFlag = 1;
    							WriteENCKEY();					
    							WriteFlag = 0; 		
    							send_frame(CMDSUCC);
							}
						}	
						else
							send_frame(CMDERRO);	
						RxdFrameStatus = SPACE;
		            break;
						
        case SETTERMINATOR: /*设置结束符*/
//					printf("oo---\r\n");
            if(RxdBuf[3]==0x01)
						{	
							ENC_KEY.temp.Terminator = RxdBuf[4];
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0;
              send_frame(SETTERMINATOR);							
//							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
                        break;
				case SETPREAMBLE:
						if(RxdBuf[3] <= 0x0F && RxdBuf[3] >= 0)
						{
              if(RxdBuf[3]>0x01)RxdBuf[3]=0x01;							
							memset(ENC_KEY.temp.Preamble,0x00,sizeof(ENC_KEY.temp.Preamble));
							memcpy(ENC_KEY.temp.Preamble,&RxdBuf[4],RxdBuf[3]);
							
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;
					    break;					
				case SETPOSTAMBLE:
						if(RxdBuf[3] <= 0x0F && RxdBuf[3] >= 0)
						{								
							memset(ENC_KEY.temp.Postamble,0x00,sizeof(ENC_KEY.temp.Postamble));
							memcpy(ENC_KEY.temp.Postamble,&RxdBuf[5],RxdBuf[3]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;                    
						break;
				case SETTRACK1PREFIX:
						if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{	
							memset(ENC_KEY.temp.track1prefix,0x00,sizeof(ENC_KEY.temp.track1prefix));
							memcpy(ENC_KEY.temp.track1prefix,&RxdBuf[4],RxdBuf[3]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;                     
						break;
				case SETTRACK2PREFIX:
						if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{	
							memset(ENC_KEY.temp.track2prefix,0x00,sizeof(ENC_KEY.temp.track2prefix));
							memcpy(ENC_KEY.temp.track2prefix,&RxdBuf[4],RxdBuf[3]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;  
						break;
        case SETTRACK3PREFIX:
            if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{	
							memset(ENC_KEY.temp.track3prefix,0x00,sizeof(ENC_KEY.temp.track3prefix));
							memcpy(ENC_KEY.temp.track3prefix,&RxdBuf[4],RxdBuf[3]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;  
						break;
				case SETTRACK1SUFFIX:
						if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{	
							memset(ENC_KEY.temp.track1suffix,0x00,sizeof(ENC_KEY.temp.track1suffix));
							memcpy(ENC_KEY.temp.track1suffix,&RxdBuf[4],RxdBuf[3]);
//							printf("ENC_KEY.temp.track1suffix0 %x\r\n",ENC_KEY.temp.track1suffix[0]);
//							printf("ENC_KEY.temp.track1suffix1 %x\r\n",ENC_KEY.temp.track1suffix[1]);
//							printf("ENC_KEY.temp.track1suffix2 %x\r\n",ENC_KEY.temp.track1suffix[2]);
//							printf("ENC_KEY.temp.track1suffix3 %x\r\n",ENC_KEY.temp.track1suffix[3]);
//							printf("ENC_KEY.temp.track1suffix4 %x\r\n",ENC_KEY.temp.track1suffix[4]);
//							printf("ENC_KEY.temp.track1suffix5 %x\r\n",ENC_KEY.temp.track1suffix[5]);
							
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;                      
						break;
				case SETTRACK2SUFFIX:
						if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{	
							memset(ENC_KEY.temp.track2suffix,0x00,sizeof(ENC_KEY.temp.track2suffix));
							memcpy(ENC_KEY.temp.track2suffix,&RxdBuf[4],RxdBuf[3]);
//							printf("ENC_KEY.temp.track1suffix0--- %x\r\n",ENC_KEY.temp.track2suffix[0]);
//							printf("ENC_KEY.temp.track1suffix1--- %x\r\n",ENC_KEY.temp.track2suffix[1]);
//							printf("ENC_KEY.temp.track1suffix2--- %x\r\n",ENC_KEY.temp.track2suffix[2]);
//							printf("ENC_KEY.temp.track1suffix3--- %x\r\n",ENC_KEY.temp.track2suffix[3]);
//							printf("ENC_KEY.temp.track1suffix4--- %x\r\n",ENC_KEY.temp.track2suffix[4]);
//							printf("ENC_KEY.temp.track1suffix5--- %x\r\n",ENC_KEY.temp.track2suffix[5]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
						RxdFrameStatus = SPACE;  
						break;
            case SETTRACK3SUFFIX:
            if(RxdBuf[3] <= 0x06 && RxdBuf[3] >= 0)
						{								
					    memset(ENC_KEY.temp.track3suffix,0x00,sizeof(ENC_KEY.temp.track3suffix));
							memcpy(ENC_KEY.temp.track3suffix,&RxdBuf[4],RxdBuf[3]);
							WriteFlag = 1;
							WriteENCKEY();					
							WriteFlag = 0; 		
							send_frame(CMDSUCC);   
						}
						else
						{
							send_frame(CMDERRO);
						}
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
}


