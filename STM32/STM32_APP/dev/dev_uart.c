/****************************************************************************
* 文件名：dev_uart.c
* 功  能：串口驱动
* 说  明：使用内部部晶振，根据stm32f10x.h文件配置，HSI_VALUE=8MHz；
*         通讯波特率115200，8位数据位，1位停止位，无奇偶校验。
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
*** 函 数 名:	void uart_printf()
*** 功能描述：	串口0输出字符串
*** 参    数:  	输入: 要输出的字符串
***            	输出: 无
*** 功能模块: 	API函数
*** 返 回 值:   无    	 	
*** 模块信息: 	Ouyang 2011.06.20创建
******************************************************************/
void uart_puts(char *s)
{
  while (*s != '\0') {
	dev_com_write((unsigned char *)s, 1);
    s++;
  }
}
/******************************************************************
*** 函 数 名:	int dev_com_open(void)
*** 功能描述：	打开串口0
*** 参    数:  	输入: 无
***            	输出: 无
*** 功能模块: 	API函数
*** 返 回 值:   成功返回0 ，否则-1    	 	
*** 模块信息: 	Ouyang 2011.06.20创建
******************************************************************/
int dev_com_open(void)
{
	// 默认波特率为：115200
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 复位串口模块
	USART_DeInit(USART1);
	
	// 打开GPIO电源
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA |
								RCC_APB2Periph_AFIO |
								RCC_APB2Periph_USART1	//TXD/RXD1
								,
								ENABLE);
	
	// 打开串口时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// TXD，管脚PA2
	GPIO_InitStructure.GPIO_Pin = PinTXD1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	// RXD，管脚PA3
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
	
	// 打开串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);

	rec_end0 = rec_head0 = 0;

	return (0);
}

/******************************************************************
*** 函 数 名:	int dev_com_close(void)
*** 功能描述：	关闭串口0
*** 参    数:  	输入: 无
***            	输出: 无
*** 功能模块: 
*** 返 回 值:	成功返回0 ，否则-1     	 	
*** 模块信息: 	Ouyang 2011.06.20创建
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
函数名称:       s32 dev_com_read (char *buf, int len)
函数功能:       读串口0
入口参数:       buf 需要推入串口缓冲区中的数据
                len 需读取数据最大长度
返 回 值:       =-1 读失败
                >=0 读到的有效报文长度
备    注:       API函数, 
                Ouyang 2011.06.20创建
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
函数名称:       int dev_com_write(unsigned char *buf, int len)
函数功能:       将串口收到的数推入串口缓冲区
入口参数:       buf 写串口的数
                len 数据的长度
返 回 值:       = 0 写成功(写成功字节个数)
                = -1 写失败
备    注:       Ouyang 2011.06.20创建
********************************************************************/
int dev_com_write(unsigned char *buf, int len)
{
	unsigned int t, i;

	if (buf == NULL || len <= 0) 
		return -1;
	i = 0;
	while (len != 0) {
		// 等待串口发送完毕
		t = 0;
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
			if (t++ >= 0x100000)	//超时
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
    dev_com_write((unsigned char *)string, length);  //写串口成功
    va_end(ap);
}
