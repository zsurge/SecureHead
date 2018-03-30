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

#define	FLASHKEY_SUPPORT		//ouyangweiquan	2012.08.20 add ������Կд��Flash�ĵ���
//#undef	FLASHKEY_SUPPORT


typedef void (*function)(void);

#define STX								0x02	/* frame head */
#define ETX		    					0x03	/* text end */
#define CMDSUCC	    					0x06	/* command success */
#define CMDERRO	    					0x15	/* command error */

#define REQUEST_DOWN					0x55	/* request download */
#define READ_VERSION					0x28 	/* read application ersion */

#define RESETHEAD						0x38	/* reset secureheadreader */
#define	SETKEY							0x46	/* setting key commands */
#define READCMD							0x52	/* read status commands */
#define SETTINGCMD						0x53	/* setting commands */

#define	SETKEYHEAD					  	0xFF	/* setting Dukpt key commands head */
#define	SETKEYVALUE						0x0A	/* setting Dukpt key value commands */
#define	SETKEYCOMMU						0x13	/* setting Dukpt key communications commands */

#define READID							0x22	/* read secureheadreader ID */
#define SETDECODEWAY					0x1D	/* set decoding in both directions */
#define MSRSETTINGS						0x1A	/* MSR Reading Settings */
#define SETDEFAULT						0x18	/* set default configuration */
#define SETENCMODE						0x58	/* set encryption mode */
#define GETCHALLENGE					0x74	/* get encrypt challenge */
#define SENDAUTHDATA					0x74	/* send authentication data */
#define GETSECURITYLEVEL				0x7E	/* get security level */
#define SETDEVICEKEY					0x76	/* set device key command */		 
#define SETTHREETRACKS					0x84	/* set all three tracks */
#define ASKTHREETRACKS					0x85	/* ask all three tracks */
#define REVIEWKSN						0x51	/* review KSN (DUKPT key management only) */
#define REVIEWSN						0x4E	/* review serial number */
#define SETSID							0x54	/* set Session ID */
#define SETENCWAY						0x4C	/* set encryption way */
#define SETDEFWAY1						0x34	/* set default way 1 */
#define SETDEFWAY2						0x35	/* set default way 2 */
#define SETDEFWAY3						0x36	/* set default way 3 */
//#define 

//#define DDATAOK							0x20	//�ش���֡��ȷ

#define SPACE		        			0x00
#define FINISH		       	 			0x55


//#define BOOT_ADDR						0x00
//#define APP_ADDR						0x2000		

#define MAX_RXD_BUF_LEN        			100
#define MAX_TXD_BUF_LEN					100

#define KEYADD							0x800F800		  //��Կ�洢��ַ
#define KEYADDBAK						0x800E400		  //������Կ�洢��ַ


union __ENC_KEY
{
	uint8_t key[64];
	struct{
	uint8_t status;							//����״̬��0��ʧ�ܼ��ܣ�1��ʹ�ܼ���
	uint8_t level;							//���ܼ���0x30����ԿʧЧ��0x31�����ģ�0x32���Ѿ�ע����Կ��0x33��ʹ��DUPUT���ܣ�0x34��δʹ��
	uint8_t encmode;						//���ܷ�ʽ��0x30��FIX���ܣ�0x31��DUPUT����
	uint8_t encway;							//�������ͣ�0x30��DES���ܣ�0x31��3DES���ܣ�0x32��AES����
	uint8_t fix[16];						//�̶���Կ��ֵ
	uint8_t key[16];						//������Կ��ֵ
	uint8_t ksn[10];						//KSN��ֵ
	uint8_t sid[8];							//�ỰID
	uint8_t sn[8];							//��ͷ���к�
	uint8_t lrc;							//����
	uint8_t bcc;							//�ۼӺ�
	}temp;
};

extern union __ENC_KEY ENC_KEY;				//��Կ�������ݽṹ
extern uint8_t CryptoKey[16];				//DUKPT������Ĺ�����Կ 
extern uint8_t random[8];					//�����
extern uint8_t macdata[8];					//��������

extern volatile uint8_t WriteFlag;			//������Կ��־��0�������棬1��ʹ�ܱ��� 
extern volatile uint8_t GetNextFlag;		//��ȡ��һ��KSN��־��0������ȡ��һ����1��ʹ�ܻ�ȡ��һ�� 

extern volatile uint8_t macstate;			//����״̬��0x30��δ���յ��������ݻ��������ʧ�ܣ�0x31����������OK
extern volatile uint8_t encryptdatastatus;	//bit 1 ==1 ��ʾ1�ŵ��������ݴ���
                							//bit 2 ==1 ��ʾ2�ŵ��������ݴ���
                							//bit 3 ==1 ��ʾ3�ŵ��������ݴ���
											//bit 4 ==1 ��ʾ1�ŵ���ϣ���ݴ���
		                					//bit 5 ==1 ��ʾ2�ŵ���ϣ���ݴ���
		                					//bit 6 ==1 ��ʾ3�ŵ���ϣ���ݴ���
											//bit 7 ==1 ��ʾ�ỰID���ݴ���
		                					//bit 8 ==1 ��ʾKSN���ݴ���

void init_serial_boot(void);
void DealRxData(void);
void DealSerialParse(void);
uint8_t ReadENCKEY(void);
void WriteENCKEY(void);
uint8_t AsciiToHex(uint8_t * pAscii, uint8_t * pHex, int nLen);
uint8_t GetNextKSN(void);
void CalcCryptoKey(void);

#endif /* __APP_H */

