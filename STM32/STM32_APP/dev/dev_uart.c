/****************************************************************************
* �ļ�����dev_uart.c
* ��  �ܣ���������
* ˵  ����ʹ���ڲ������񣬸���stm32f10x.h�ļ����ã�HSI_VALUE=8MHz��
*         ͨѶ������115200��8λ����λ��1λֹͣλ������żУ�顣
****************************************************************************/
#include "stm32f10x.h"
#include "dev_uart.h"
#include <stdarg.h>
#include <stdio.h>

//volatile unsigned char rec_buf0[RXTEMPBUFLENMAX];
volatile unsigned short rec_head0;
volatile unsigned short rec_end0;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return ch;
}

/******************************************************************
*** �� �� ��:	void uart_printf()
*** ����������	����0����ַ���
*** ��    ��:  	����: Ҫ������ַ���
***            	���: ��
*** ����ģ��: 	API����
*** �� �� ֵ:   ��    	 	
*** ģ����Ϣ: 	Ouyang 2011.06.20����
******************************************************************/
void uart_puts(char *s)
{
  while (*s != '\0') {
	dev_com_write((unsigned char *)s, 1);
    s++;
  }
}
/******************************************************************
*** �� �� ��:	int dev_com_open(void)
*** ����������	�򿪴���0
*** ��    ��:  	����: ��
***            	���: ��
*** ����ģ��: 	API����
*** �� �� ֵ:   �ɹ�����0 ������-1    	 	
*** ģ����Ϣ: 	Ouyang 2011.06.20����
******************************************************************/
int dev_com_open(void)
{
	// Ĭ�ϲ�����Ϊ��115200
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// ��λ����ģ��
	USART_DeInit(USART1);
	
	// ��GPIO��Դ
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA |
								RCC_APB2Periph_AFIO |
								RCC_APB2Periph_USART1	//TXD/RXD1
								,
								ENABLE);
	
	// �򿪴���ʱ��
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// TXD���ܽ�PA2
	GPIO_InitStructure.GPIO_Pin = PinTXD1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	// RXD���ܽ�PA3
	GPIO_InitStructure.GPIO_Pin = PinRXD1;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure); 
	
	// �򿪴��ڽ����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);

	rec_end0 = rec_head0 = 0;

	return (0);
}

/******************************************************************
*** �� �� ��:	int dev_com_close(void)
*** ����������	�رմ���0
*** ��    ��:  	����: ��
***            	���: ��
*** ����ģ��: 
*** �� �� ֵ:	�ɹ�����0 ������-1     	 	
*** ģ����Ϣ: 	Ouyang 2011.06.20����
******************************************************************/
int dev_com_close(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// TXD && RXD Reset
	GPIO_InitStructure.GPIO_Pin = PinTXD1 | PinRXD1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_Cmd(USART1, DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
	
	rec_end0 = rec_head0 = 0;
	return(0); 	
}

/*******************************************************************
��������:       s32 dev_com_read (char *buf, int len)
��������:       ������0
��ڲ���:       buf ��Ҫ���봮�ڻ������е�����
                len ���ȡ������󳤶�
�� �� ֵ:       =-1 ��ʧ��
                >=0 ��������Ч���ĳ���
��    ע:       API����, 
                Ouyang 2011.06.20����
********************************************************************/
int dev_com_read(unsigned char *buf, int len)
{
	int i;

	if(len <= 0 || buf == NULL)
		return -1;
	
	i = 0;
	while (rec_head0 != rec_end0) {
		*buf = rec_buf0[rec_head0++];
		if(rec_head0 >= RXTEMPBUFLENMAX)
			rec_head0 = 0;
		buf++;
		i++;

		if(i >= len) {
			break;
		}
	}
	return (i);
}

/*******************************************************************
��������:       int dev_com_write(unsigned char *buf, int len)
��������:       �������յ��������봮�ڻ�����
��ڲ���:       buf д���ڵ���
                len ���ݵĳ���
�� �� ֵ:       = 0 д�ɹ�(д�ɹ��ֽڸ���)
                = -1 дʧ��
��    ע:       Ouyang 2011.06.20����
********************************************************************/
int dev_com_write(unsigned char *buf, int len)
{
	unsigned int t, i;

	if (buf == NULL || len <= 0) 
		return -1;
	i = 0;
	while (len != 0) {
		// �ȴ����ڷ������
		t = 0;
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
			if (t++ >= 0x100000)	//��ʱ
				return i;
		}
		USART_SendData(USART1, buf[i]);
		i++;
		len--;
	}
	return i;
}

void uart_printf(char *fmt,...)
{
    int length = 0;
    va_list ap;
    char string[256];
    char *pt;
    va_start(ap,fmt);
    vsprintf((char *)string,(const char *)fmt,ap);
    pt = &string[0];
    while(*pt!='\0')
    {
        length++;
        pt++;
    }
    dev_com_write((unsigned char *)string, length);  //д���ڳɹ�
    va_end(ap);
}
