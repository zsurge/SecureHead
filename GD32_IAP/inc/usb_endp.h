#ifndef __USB_ENDP_H
#define __USB_ENDP_H


#include <string.h>
#include "dev_uart.h"
#include "usbd_int.h"
#include "usbd_core.h"

void UsbRecvReset (void);

unsigned char UsbRecvOne (unsigned char *Str);

unsigned int UsbRecvAtTime (unsigned char *Buff, unsigned int RecvSize, unsigned int ms);

unsigned int UsbSendBuff(usbd_core_handle_struct *pudev,unsigned char *buff, unsigned int len, unsigned int ms);

//是否需要自动应答
void UsbSetRespFlag(char flag);


char UsbCheckBuff(char *ExpectString);

int UsbReadTo(unsigned char *Buff, unsigned int BuffSize, unsigned char *EndString);


#endif 


