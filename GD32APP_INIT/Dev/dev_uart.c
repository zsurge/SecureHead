/****************************************************************************
* �ļ�����dev_uart.c
* ��  �ܣ���������
* ˵  ����ʹ���ڲ������񣬸���stm32f10x.h�ļ����ã�HSI_VALUE=8MHz��
*         ͨѶ������115200��8λ����λ��1λֹͣλ������żУ�顣
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
    #ifdef UART_PRINT
	while (*s != '\0') {
		dev_com_write((unsigned char *)s, 1);
		s++;
	}
	#endif
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
	// TXD && RXD Reset
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);	
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);

    usart_transfer_config(USART0, USART_RTEN_DISABLE);
	usart_deinit(USART0);
		
	rec_end0 = rec_head0 = 0;
	return(0); 	
}

/*******************************************************************
��������:       int dev_com_read (char *buf, int len)
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
		while (usart_flag_get(USART0, USART_STAT_TC) == RESET) {
			if (t++ >= 0x100000)	//��ʱ
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
    dev_com_write((unsigned char *)string, length);  //д���ڳɹ�
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
