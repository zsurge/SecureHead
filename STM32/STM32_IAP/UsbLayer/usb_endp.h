#ifndef __USB_ENDP_H
#define __USB_ENDP_H

extern __IO char gUsbConnFlag;

void UsbRecvReset (void);

void UsbSetRespFlag(char flag);

unsigned char UsbRecvOne (unsigned char *Str);

unsigned int UsbRecvAtTime (unsigned char *Buff, unsigned int RecvSize, unsigned int ms);

unsigned int UsbSendBuff(const unsigned char *buff, unsigned int len, unsigned int ms);

char UsbCheckBuff(char *ExpectString);

int UsbReadTo(unsigned char *Buff, unsigned int BuffSize, unsigned char *EndString);

char UsbGetConn(void);

#endif 

