#ifndef __DEV_UART_H__
#define __DEV_UART_H__

#include <stdlib.h>
#include <string.h>
#include "magdecode.h"

#define RXTEMPBUFLENMAX        512 
#define UART_PRINT

//extern unsigned char rec_buf0[RXTEMPBUFLENMAX];
#define rec_buf0 ((uint8_t *)Track1TimeFlow.Value)			//节省空间共享缓存区
extern volatile unsigned short rec_head0;
extern volatile unsigned short rec_end0;

//接口函数
int dev_com_open(void);
int dev_com_close(void);
int dev_com_write(unsigned char *buf, int len);
int dev_com_read(unsigned char *buf, int len);
void uart_puts(char *s);
void DBG_S(char *fmt, ...);
void DBG_H( char *title,char *buff, int len );

#endif
