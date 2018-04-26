#ifndef __APP_H
#define __APP_H

#include "magdecode.h"
#include "dev_eprom.h"	
#include "dev_uart.h"
#include "dev_timer.h"
#include "dev_msread.h"
#include "des.h"
#include "sha1.h"
#include "aes.h"
#include "dukpt.h"
#include "utilities.h"

#define	FLASHKEY_SUPPORT		//ouyangweiquan	2012.08.20 add 增加密钥写入Flash的调试
//#undef	FLASHKEY_SUPPORT


typedef void (*function)(void);

#define STX								0x02	/* frame head */
#define ETX		    					0x03	/* text end */
#define CMDSUCC	    					0x06	/* command success */
#define CMDERRO	    					0x15	/* command error */

#define REQUEST_DOWN					0x55	/* request download */
#define READ_VERSION					0x28 	/* read application ersion */

#define RESETHEAD						0xF8	/* reset secureheadreader */


#define	SETKEY							0x46	/* setting key commands */
#define READCMD							0x52	/* read status commands */
#define SETTINGCMD						0x53	/* setting commands */

#define	SETKEYHEAD					  	0xFF	/* setting Dukpt key commands head */
#define	SETKEYVALUE						0x0A	/* setting Dukpt key value commands */


#define	SETKEYCOMMU						0xF3	/* setting Dukpt key communications commands */

#define SETBEEP                         0x11    /* Beep Setting */
#define READID							  0x22	/* read secureheadreader ID */
#define SETDECODEWAY					0x1D	/* Decoding Method Settings */
#define MSRSETTINGS						0x1A	/* MSR Reading Settings */
#define SETDEFAULT						0x18	/* set default configuration */
#define SETENCMODE						0x58	/* set encryption mode */
#define GETCHALLENGE					0x74	/* get encrypt challenge */
#define SENDAUTHDATA					0x74	/* send authentication data */
#define GETSECURITYLEVEL			0x7E	/* get security level */
#define SETDEVICEKEY					0x76	/* set device key command */	

#define SETENCRYPTIONOPTION				0x84	/* Encryption Option Setting */
#define SETENCRYPTIONFORMAT				0x85	/* Encryption Output Format Setting*/

#define REVIEWKSN						0x51	/* review KSN (DUKPT key management only) */
#define REVIEWSN						0x4E	/* review serial number */
#define SETSID							0x54	/* set Session ID */
#define SETENCWAY						0x4C	/* set encryption way */
#define HASHOPTION					0x5C	/* Hash Option 
Setting */
#define MASKOPTION          0x86

//#define DDATAOK							0x20	//回传上帧正确

#define SPACE		        			  0x00
#define FINISH		       	 			0x55

//add for zd
#define SETTERMINATOR                    0x21   /*设置结束符*/
#define SETPREAMBLE                      0xD2   /*设置起始字符串*/
#define SETPOSTAMBLE                     0xD3   /*设置结束字符串*/

#define SETTRACK1PREFIX                  0X34   /*设置磁道1开头数据,最大6字节*/
#define SETTRACK2PREFIX                  0X35   /*设置磁道2开头数据,最大6字节*/
#define SETTRACK3PREFIX                  0X36   /*设置磁道3开头数据,最大6字节*/
#define SETTRACK1SUFFIX                  0X37   /*设置磁道1结束数据，最大6字节*/
#define SETTRACK2SUFFIX                  0X38   /*设置磁道2结束数据，最大6字节*/
#define SETTRACK3SUFFIX                  0X39   /*设置磁道3结束数据，最大6字节*/
#define SETSELECTTRACK                   0X13   /*设置选择读的轨道*/

#define SETTRACKSEPARATOR                0x17   /*设置轨道分割符*/
#define SETTRACK2                        0x19   /*设置轨道2数据上送格式*/

#define MAX_RXD_BUF_LEN        			100
#define MAX_TXD_BUF_LEN					100

#define REVIEWSET					               0x1F   /*主要是激活设置命令  */
#define ENCRYPTEXTERNAL					               0x41   /*主要是激活设置命令  */
#define ACTIVATEAUTHEN            0x80  //加密等级4的时候，认证模式

#define LOADKEY            0x13  //导入密钥 key

#define KEYADD							0x800F800		  //密钥存储地址
#define KEYADDBAK						0x800E400		  //备份密钥存储地址



union __ENC_KEY
{
	//uint8_t key[64];
	uint8_t key[144];                        //添加磁道前后缀
	struct{
	uint8_t zhangwei;                       //站位
	uint8_t beepmode;                       //beep mode
	uint8_t enabledevice;                   //使用磁头 for zd
	uint8_t writesnflag;                    //是否已经写过SN for zd
	uint8_t Terminator;                     //线束符 for zd
	uint8_t selecttrack;                    //要选择的轨道  for zd
	uint8_t setseparator;                   //设置轨道分割符 for zd
	uint8_t settrack2format;                //设置轨道2数据上送格式 for zd
	uint8_t status;							//加密状态：0：失能加密；1：使能加密
	uint8_t level;							//加密级别：0x30：密钥失效；0x31：明文；0x32：已经注入密钥；0x33：使能DUPUT加密：0x34：未使用
	uint8_t encmode;						//加密方式：0x30：FIX加密；0x31：DUPUT加密
	uint8_t encway;							//加密类型：0x30：DES加密；0x31：3DES加密；0x32：AES加密
	uint8_t fix[16];						//固定密钥的值
	uint8_t key[16];						//加密密钥的值
	uint8_t ksn[10];						//KSN的值
	uint8_t sid[8];							//会话ID
	uint8_t sn[10];							//磁头序列号
	uint8_t Preamble[15];                   //起始字符串，最大15字节 for zd
	uint8_t Postamble[15];                  //结束字符串，最大15字节 for zd
	uint8_t track1prefix[6];                //磁道1前缀，最大6字节 for zd
	uint8_t track2prefix[6];                //磁道2前缀，最大6字节 for zd
	uint8_t track3prefix[6];                //磁道3前缀，最大6字节 for zd
	uint8_t track1suffix[6];                //磁道1后缀，最大6字节 for zd
	uint8_t track2suffix[6];                //磁道1后缀，最大6字节 for zd
	uint8_t track3suffix[6];                //磁道1后缀，最大6字节 for zd
  
	uint8_t Enhancedstatue;
	uint8_t Enhancedoption;
	uint8_t HASHSET;
	uint8_t MaskSetting;
	
	uint8_t lrc;							//异或和
	uint8_t bcc;							//累加和
	}temp;
};

extern union __ENC_KEY ENC_KEY;				//密钥保存数据结构
extern uint8_t CryptoKey[16];				//DUKPT计算出的过程密钥 
extern uint8_t random[8];					//随机数
extern uint8_t macdata[8];					//鉴别数据

extern volatile uint8_t WriteFlag;			//保存密钥标志：0：不保存，1：使能保存 
extern volatile uint8_t GetNextFlag;		//获取下一个KSN标志：0：不获取下一个，1：使能获取下一个 

extern volatile uint8_t macstate;			//鉴定状态：0x30：未接收到鉴定数据或鉴定数据失败；0x31：鉴定数据OK
extern volatile uint8_t encryptdatastatus;	//bit 1 ==1 表示1磁道加密数据存在
                							//bit 2 ==1 表示2磁道加密数据存在
                							//bit 3 ==1 表示3磁道加密数据存在
											//bit 4 ==1 表示1磁道哈希数据存在
		                					//bit 5 ==1 表示2磁道哈希数据存在
		                					//bit 6 ==1 表示3磁道哈希数据存在
											//bit 7 ==1 表示会话ID数据存在
		                					//bit 8 ==1 表示KSN数据存在

void init_serial_boot(void);
void DealRxData(void);
void DealSerialParse(void);
uint8_t ReadENCKEY(void);
void WriteENCKEY(void);
uint8_t AsciiToHex(uint8_t * pAscii, uint8_t * pHex, int nLen);
uint8_t GetNextKSN(void);
void CalcCryptoKey(void);
void ResetSetting(void);

void Default_Settings(void);//恢复最初设置

#endif /* __APP_H */

