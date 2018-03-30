/****************************************************************************
* 文件名：dev_uart.c
* 功  能：串口驱动
* 说  明：使用内部部晶振，根据stm32f10x.h文件配置，HSI_VALUE=8MHz；
*         通讯波特率115200，8位数据位，1位停止位，无奇偶校验。
****************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include "gd32f1x0.h"
#include "dev_uart.h"


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

#ifdef UART_PRINT
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	usart_data_transmit(USART0, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (usart_flag_get(USART0, USART_STAT_TC) == RESET);
	return ch;
}
#endif

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
    #ifdef UART_PRINT
	while (*s != '\0') {
		dev_com_write((unsigned char *)s, 1);
		s++;
	}
	#endif
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
	/* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200);
    usart_transfer_config(USART0, USART_RTEN_ENABLE);
	
	/* USART interrupt configuration */
    nvic_irq_enable(USART0_IRQn, 0, 0);
	usart_interrupt_enable(USART0, USART_INT_RBNEIE);
	
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
	// TXD && RXD Reset
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);	
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);

    usart_transfer_config(USART0, USART_RTEN_DISABLE);
	usart_deinit(USART0);
		
	rec_end0 = rec_head0 = 0;
	return(0); 	
}

/*******************************************************************
函数名称:       int dev_com_read (char *buf, int len)
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
		while (usart_flag_get(USART0, USART_STAT_TC) == RESET) {
			if (t++ >= 0x100000)	//超时
				return i;
		}
		usart_data_transmit(USART0, buf[i]);
		i++;
		len--;
	}
	return i;
}

void DBG_S(char *fmt,...)
{
    #ifdef UART_PRINT
    int length = 0;
    va_list ap;
    char string[256];
    char *pt;
    va_start(ap,fmt);
    vsprintf((char *)string,(const char *)fmt, ap);
    pt = &string[0];
    while(*pt!='\0')
    {
        length++;
        pt++;
    }
    dev_com_write((unsigned char *)string, length);  //写串口成功
    va_end(ap);

    #endif
}

/*****************************************************************************
 * Function      : DBG_H
 * Description   : print hex string
 * Input         : char *
                char *
                int
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20171113
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void DBG_H( char *title,char *buff, int len )
{

    #ifdef UART_PRINT
    int i = 0;
    if(len > 0)
    {    
    	printf("[%s]: length = %d\r\n  [ ", title,len);

    	for (i = 0; i < len; i++)
    	{
    		printf ("%02x ", buff[i]);
    	}
    	
    	printf ("] \r\n\r\n");	
    }

    #endif
}
