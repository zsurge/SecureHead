#ifndef __IAP_H
#define __IAP_H



#define ERASE_FLASH_BASE            ((uint32_t)0x08003400)         
#define APP_LOADED_ADDR 			((uint32_t)0x08003400) 
#define BOOTLOADER_ADDR				((uint32_t)0x08000000) 

//char IapProcess(void);
void UsbUpdata( void );
void iap_EraseFlash (void);
//void writeflash(void);

#endif
