#line 1 "..\\dev\\stm32f10x_it.c"





















  

 
#line 1 "..\\dev\\stm32f10x_it.h"



















  

 



 
#line 1 "..\\core_cm3\\stm32f10x.h"







































 



 



 
    






  


 
  


 

#line 75 "..\\core_cm3\\stm32f10x.h"


















 





#line 107 "..\\core_cm3\\stm32f10x.h"







            
#line 122 "..\\core_cm3\\stm32f10x.h"





 






 
#line 143 "..\\core_cm3\\stm32f10x.h"



 



 



 
#line 162 "..\\core_cm3\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 221 "..\\core_cm3\\stm32f10x.h"

#line 242 "..\\core_cm3\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42         


#line 296 "..\\core_cm3\\stm32f10x.h"

#line 341 "..\\core_cm3\\stm32f10x.h"

#line 381 "..\\core_cm3\\stm32f10x.h"

#line 426 "..\\core_cm3\\stm32f10x.h"

#line 472 "..\\core_cm3\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"
 







 

























 
























 




 


 

 













#line 110 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"


 







#line 145 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"
 
 





 










#line 26 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 197 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"

     







     










     











#line 261 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"



 



#line 147 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cmInstr.h"
 







 

























 






 



 


 









 







 







 






 








 







 







 









 









 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 










 











 









 









 









 











 











 











 







 










 










 









 





#line 684 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cmInstr.h"

   

#line 148 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cmFunc.h"
 







 

























 






 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 







 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1);
}




#line 307 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cmFunc.h"


#line 634 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cmFunc.h"

 

#line 149 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"








 
#line 179 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"

 






 
#line 195 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"

 












 


 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 




#line 422 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"

 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     



       uint32_t RESERVED1[1];

} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
       uint32_t RESERVED3[29];
  volatile  uint32_t IWR;                      
  volatile const  uint32_t IRR;                      
  volatile uint32_t IMCR;                     
       uint32_t RESERVED4[43];
  volatile  uint32_t LAR;                      
  volatile const  uint32_t LSR;                      
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                     
  volatile const  uint32_t PID5;                     
  volatile const  uint32_t PID6;                     
  volatile const  uint32_t PID7;                     
  volatile const  uint32_t PID0;                     
  volatile const  uint32_t PID1;                     
  volatile const  uint32_t PID2;                     
  volatile const  uint32_t PID3;                     
  volatile const  uint32_t CID0;                     
  volatile const  uint32_t CID1;                     
  volatile const  uint32_t CID2;                     
  volatile const  uint32_t CID3;                     
} ITM_Type;

 



 



























 



 



 



 









   






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t CYCCNT;                   
  volatile uint32_t CPICNT;                   
  volatile uint32_t EXCCNT;                   
  volatile uint32_t SLEEPCNT;                 
  volatile uint32_t LSUCNT;                   
  volatile uint32_t FOLDCNT;                  
  volatile const  uint32_t PCSR;                     
  volatile uint32_t COMP0;                    
  volatile uint32_t MASK0;                    
  volatile uint32_t FUNCTION0;                
       uint32_t RESERVED0[1];
  volatile uint32_t COMP1;                    
  volatile uint32_t MASK1;                    
  volatile uint32_t FUNCTION1;                
       uint32_t RESERVED1[1];
  volatile uint32_t COMP2;                    
  volatile uint32_t MASK2;                    
  volatile uint32_t FUNCTION2;                
       uint32_t RESERVED2[1];
  volatile uint32_t COMP3;                    
  volatile uint32_t MASK3;                    
  volatile uint32_t FUNCTION3;                
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   






 


 
typedef struct
{
  volatile uint32_t SSPSR;                    
  volatile uint32_t CSPSR;                    
       uint32_t RESERVED0[2];
  volatile uint32_t ACPR;                     
       uint32_t RESERVED1[55];
  volatile uint32_t SPPR;                     
       uint32_t RESERVED2[131];
  volatile const  uint32_t FFSR;                     
  volatile uint32_t FFCR;                     
  volatile const  uint32_t FSCR;                     
       uint32_t RESERVED3[759];
  volatile const  uint32_t TRIGGER;                  
  volatile const  uint32_t FIFO0;                    
  volatile const  uint32_t ITATBCTR2;                
       uint32_t RESERVED4[1];
  volatile const  uint32_t ITATBCTR0;                
  volatile const  uint32_t FIFO1;                    
  volatile uint32_t ITCTRL;                   
       uint32_t RESERVED5[39];
  volatile uint32_t CLAIMSET;                 
  volatile uint32_t CLAIMCLR;                 
       uint32_t RESERVED7[8];
  volatile const  uint32_t DEVID;                    
  volatile const  uint32_t DEVTYPE;                  
} TPI_Type;

 



 



 












 






 



 





















 



 





















 



 



 


















 






   


#line 1133 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"






 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 






 

 
#line 1253 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 1262 "D:\\Keil\\ARM\\CMSIS\\Include\\core_cm3.h"






 










 

 



 




 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}







 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}







 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}











 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}







 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}










 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}












 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}













 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}













 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 




 

















 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0))  return (1);       

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = ticks - 1;                                   
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 




 

extern volatile int32_t ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}








 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}








 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 479 "..\\core_cm3\\stm32f10x.h"
#line 1 "..\\core_cm3\\system_stm32f10x.h"



















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 480 "..\\core_cm3\\stm32f10x.h"
#line 481 "..\\core_cm3\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
#line 920 "..\\core_cm3\\stm32f10x.h"
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1312 "..\\core_cm3\\stm32f10x.h"

#line 1335 "..\\core_cm3\\stm32f10x.h"



#line 1354 "..\\core_cm3\\stm32f10x.h"




















 
  


   

#line 1454 "..\\core_cm3\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1515 "..\\core_cm3\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1691 "..\\core_cm3\\stm32f10x.h"

#line 1698 "..\\core_cm3\\stm32f10x.h"

 
 








 








 






#line 1734 "..\\core_cm3\\stm32f10x.h"

 











 











 













 






#line 1850 "..\\core_cm3\\stm32f10x.h"




#line 1870 "..\\core_cm3\\stm32f10x.h"

 





#line 1883 "..\\core_cm3\\stm32f10x.h"

 
#line 1902 "..\\core_cm3\\stm32f10x.h"

#line 1911 "..\\core_cm3\\stm32f10x.h"

 
#line 1919 "..\\core_cm3\\stm32f10x.h"



















#line 1944 "..\\core_cm3\\stm32f10x.h"












 













#line 1976 "..\\core_cm3\\stm32f10x.h"





#line 1990 "..\\core_cm3\\stm32f10x.h"

#line 1997 "..\\core_cm3\\stm32f10x.h"

#line 2007 "..\\core_cm3\\stm32f10x.h"











 


















#line 2043 "..\\core_cm3\\stm32f10x.h"

 
#line 2051 "..\\core_cm3\\stm32f10x.h"



















#line 2076 "..\\core_cm3\\stm32f10x.h"












 













#line 2108 "..\\core_cm3\\stm32f10x.h"





#line 2122 "..\\core_cm3\\stm32f10x.h"

#line 2129 "..\\core_cm3\\stm32f10x.h"

#line 2139 "..\\core_cm3\\stm32f10x.h"











 








 








   
#line 2178 "..\\core_cm3\\stm32f10x.h"

#line 2273 "..\\core_cm3\\stm32f10x.h"

#line 2300 "..\\core_cm3\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2462 "..\\core_cm3\\stm32f10x.h"

 
#line 2480 "..\\core_cm3\\stm32f10x.h"

 
#line 2498 "..\\core_cm3\\stm32f10x.h"

#line 2515 "..\\core_cm3\\stm32f10x.h"

 
#line 2533 "..\\core_cm3\\stm32f10x.h"

 
#line 2552 "..\\core_cm3\\stm32f10x.h"

 

 






 
#line 2579 "..\\core_cm3\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2654 "..\\core_cm3\\stm32f10x.h"

 










#line 2685 "..\\core_cm3\\stm32f10x.h"

 





 
#line 2700 "..\\core_cm3\\stm32f10x.h"

 
#line 2709 "..\\core_cm3\\stm32f10x.h"

   
#line 2718 "..\\core_cm3\\stm32f10x.h"

 
#line 2727 "..\\core_cm3\\stm32f10x.h"

 





 
#line 2742 "..\\core_cm3\\stm32f10x.h"

 
#line 2751 "..\\core_cm3\\stm32f10x.h"

   
#line 2760 "..\\core_cm3\\stm32f10x.h"

 
#line 2769 "..\\core_cm3\\stm32f10x.h"

 





 
#line 2784 "..\\core_cm3\\stm32f10x.h"

 
#line 2793 "..\\core_cm3\\stm32f10x.h"

   
#line 2802 "..\\core_cm3\\stm32f10x.h"

 
#line 2811 "..\\core_cm3\\stm32f10x.h"

 





 
#line 2826 "..\\core_cm3\\stm32f10x.h"

 
#line 2835 "..\\core_cm3\\stm32f10x.h"

   
#line 2844 "..\\core_cm3\\stm32f10x.h"

 
#line 2853 "..\\core_cm3\\stm32f10x.h"

#line 2862 "..\\core_cm3\\stm32f10x.h"

#line 2871 "..\\core_cm3\\stm32f10x.h"

#line 2881 "..\\core_cm3\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2945 "..\\core_cm3\\stm32f10x.h"

 
#line 2980 "..\\core_cm3\\stm32f10x.h"

 
#line 3015 "..\\core_cm3\\stm32f10x.h"

 
#line 3050 "..\\core_cm3\\stm32f10x.h"

 
#line 3085 "..\\core_cm3\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3152 "..\\core_cm3\\stm32f10x.h"

 



 









 
#line 3176 "..\\core_cm3\\stm32f10x.h"




 




 
#line 3192 "..\\core_cm3\\stm32f10x.h"

 





 
#line 3214 "..\\core_cm3\\stm32f10x.h"

 
 





 
#line 3229 "..\\core_cm3\\stm32f10x.h"
 
#line 3236 "..\\core_cm3\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3285 "..\\core_cm3\\stm32f10x.h"

 
#line 3307 "..\\core_cm3\\stm32f10x.h"

 
#line 3329 "..\\core_cm3\\stm32f10x.h"

 
#line 3351 "..\\core_cm3\\stm32f10x.h"

 
#line 3373 "..\\core_cm3\\stm32f10x.h"

 
#line 3395 "..\\core_cm3\\stm32f10x.h"

 
 
 
 
 

 
#line 3431 "..\\core_cm3\\stm32f10x.h"

 
#line 3461 "..\\core_cm3\\stm32f10x.h"

 
#line 3471 "..\\core_cm3\\stm32f10x.h"















 
#line 3495 "..\\core_cm3\\stm32f10x.h"















 
#line 3519 "..\\core_cm3\\stm32f10x.h"















 
#line 3543 "..\\core_cm3\\stm32f10x.h"















 
#line 3567 "..\\core_cm3\\stm32f10x.h"















 
#line 3591 "..\\core_cm3\\stm32f10x.h"















 
#line 3615 "..\\core_cm3\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3716 "..\\core_cm3\\stm32f10x.h"

#line 3725 "..\\core_cm3\\stm32f10x.h"















  
 
#line 3748 "..\\core_cm3\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3883 "..\\core_cm3\\stm32f10x.h"

#line 3890 "..\\core_cm3\\stm32f10x.h"

#line 3897 "..\\core_cm3\\stm32f10x.h"

#line 3904 "..\\core_cm3\\stm32f10x.h"







 
#line 3918 "..\\core_cm3\\stm32f10x.h"

#line 3925 "..\\core_cm3\\stm32f10x.h"

#line 3932 "..\\core_cm3\\stm32f10x.h"

#line 3939 "..\\core_cm3\\stm32f10x.h"

#line 3946 "..\\core_cm3\\stm32f10x.h"

#line 3953 "..\\core_cm3\\stm32f10x.h"

 
#line 3961 "..\\core_cm3\\stm32f10x.h"

#line 3968 "..\\core_cm3\\stm32f10x.h"

#line 3975 "..\\core_cm3\\stm32f10x.h"

#line 3982 "..\\core_cm3\\stm32f10x.h"

#line 3989 "..\\core_cm3\\stm32f10x.h"

#line 3996 "..\\core_cm3\\stm32f10x.h"

 
#line 4004 "..\\core_cm3\\stm32f10x.h"

#line 4011 "..\\core_cm3\\stm32f10x.h"

#line 4018 "..\\core_cm3\\stm32f10x.h"

#line 4025 "..\\core_cm3\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4167 "..\\core_cm3\\stm32f10x.h"

 
#line 4177 "..\\core_cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4225 "..\\core_cm3\\stm32f10x.h"

 

























 
#line 4268 "..\\core_cm3\\stm32f10x.h"

 
#line 4282 "..\\core_cm3\\stm32f10x.h"

 
#line 4292 "..\\core_cm3\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4411 "..\\core_cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4446 "..\\core_cm3\\stm32f10x.h"





#line 4457 "..\\core_cm3\\stm32f10x.h"

 
#line 4465 "..\\core_cm3\\stm32f10x.h"

#line 4472 "..\\core_cm3\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4494 "..\\core_cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4556 "..\\core_cm3\\stm32f10x.h"



 
#line 4568 "..\\core_cm3\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4606 "..\\core_cm3\\stm32f10x.h"

 











#line 4629 "..\\core_cm3\\stm32f10x.h"

 











#line 4652 "..\\core_cm3\\stm32f10x.h"

 











#line 4675 "..\\core_cm3\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5072 "..\\core_cm3\\stm32f10x.h"

 
#line 5081 "..\\core_cm3\\stm32f10x.h"

 
#line 5090 "..\\core_cm3\\stm32f10x.h"

 
#line 5101 "..\\core_cm3\\stm32f10x.h"

#line 5111 "..\\core_cm3\\stm32f10x.h"

#line 5121 "..\\core_cm3\\stm32f10x.h"

#line 5131 "..\\core_cm3\\stm32f10x.h"

 
#line 5142 "..\\core_cm3\\stm32f10x.h"

#line 5152 "..\\core_cm3\\stm32f10x.h"

#line 5162 "..\\core_cm3\\stm32f10x.h"

#line 5172 "..\\core_cm3\\stm32f10x.h"

 
#line 5183 "..\\core_cm3\\stm32f10x.h"

#line 5193 "..\\core_cm3\\stm32f10x.h"

#line 5203 "..\\core_cm3\\stm32f10x.h"

#line 5213 "..\\core_cm3\\stm32f10x.h"

 
#line 5224 "..\\core_cm3\\stm32f10x.h"

#line 5234 "..\\core_cm3\\stm32f10x.h"

#line 5244 "..\\core_cm3\\stm32f10x.h"

#line 5254 "..\\core_cm3\\stm32f10x.h"

 
#line 5265 "..\\core_cm3\\stm32f10x.h"

#line 5275 "..\\core_cm3\\stm32f10x.h"

#line 5285 "..\\core_cm3\\stm32f10x.h"

#line 5295 "..\\core_cm3\\stm32f10x.h"

 
#line 5306 "..\\core_cm3\\stm32f10x.h"

#line 5316 "..\\core_cm3\\stm32f10x.h"

#line 5326 "..\\core_cm3\\stm32f10x.h"

#line 5336 "..\\core_cm3\\stm32f10x.h"

 
#line 5347 "..\\core_cm3\\stm32f10x.h"

#line 5357 "..\\core_cm3\\stm32f10x.h"

#line 5367 "..\\core_cm3\\stm32f10x.h"

#line 5377 "..\\core_cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5425 "..\\core_cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5495 "..\\core_cm3\\stm32f10x.h"

 
#line 5510 "..\\core_cm3\\stm32f10x.h"

 
#line 5536 "..\\core_cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5757 "..\\core_cm3\\stm32f10x.h"

 
#line 5769 "..\\core_cm3\\stm32f10x.h"

 






 
#line 5786 "..\\core_cm3\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5930 "..\\core_cm3\\stm32f10x.h"



 


#line 5942 "..\\core_cm3\\stm32f10x.h"



 


#line 5954 "..\\core_cm3\\stm32f10x.h"



 


#line 5966 "..\\core_cm3\\stm32f10x.h"



 


#line 5978 "..\\core_cm3\\stm32f10x.h"



 


#line 5990 "..\\core_cm3\\stm32f10x.h"



 


#line 6002 "..\\core_cm3\\stm32f10x.h"



 


#line 6014 "..\\core_cm3\\stm32f10x.h"



 

 


#line 6028 "..\\core_cm3\\stm32f10x.h"



 


#line 6040 "..\\core_cm3\\stm32f10x.h"



 


#line 6052 "..\\core_cm3\\stm32f10x.h"



 


#line 6064 "..\\core_cm3\\stm32f10x.h"



 


#line 6076 "..\\core_cm3\\stm32f10x.h"



 


#line 6088 "..\\core_cm3\\stm32f10x.h"



 


#line 6100 "..\\core_cm3\\stm32f10x.h"



 


#line 6112 "..\\core_cm3\\stm32f10x.h"



 


#line 6124 "..\\core_cm3\\stm32f10x.h"



 


#line 6136 "..\\core_cm3\\stm32f10x.h"



 


#line 6148 "..\\core_cm3\\stm32f10x.h"



 


#line 6160 "..\\core_cm3\\stm32f10x.h"



 


#line 6172 "..\\core_cm3\\stm32f10x.h"



 


#line 6184 "..\\core_cm3\\stm32f10x.h"



 


#line 6196 "..\\core_cm3\\stm32f10x.h"



 


#line 6208 "..\\core_cm3\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6228 "..\\core_cm3\\stm32f10x.h"

 
#line 6239 "..\\core_cm3\\stm32f10x.h"

 
#line 6257 "..\\core_cm3\\stm32f10x.h"











 





 





 
#line 6295 "..\\core_cm3\\stm32f10x.h"

 












 
#line 6316 "..\\core_cm3\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6456 "..\\core_cm3\\stm32f10x.h"

 
#line 6473 "..\\core_cm3\\stm32f10x.h"

 
#line 6490 "..\\core_cm3\\stm32f10x.h"

 
#line 6507 "..\\core_cm3\\stm32f10x.h"

 
#line 6541 "..\\core_cm3\\stm32f10x.h"

 
#line 6575 "..\\core_cm3\\stm32f10x.h"

 
#line 6609 "..\\core_cm3\\stm32f10x.h"

 
#line 6643 "..\\core_cm3\\stm32f10x.h"

 
#line 6677 "..\\core_cm3\\stm32f10x.h"

 
#line 6711 "..\\core_cm3\\stm32f10x.h"

 
#line 6745 "..\\core_cm3\\stm32f10x.h"

 
#line 6779 "..\\core_cm3\\stm32f10x.h"

 
#line 6813 "..\\core_cm3\\stm32f10x.h"

 
#line 6847 "..\\core_cm3\\stm32f10x.h"

 
#line 6881 "..\\core_cm3\\stm32f10x.h"

 
#line 6915 "..\\core_cm3\\stm32f10x.h"

 
#line 6949 "..\\core_cm3\\stm32f10x.h"

 
#line 6983 "..\\core_cm3\\stm32f10x.h"

 
#line 7017 "..\\core_cm3\\stm32f10x.h"

 
#line 7051 "..\\core_cm3\\stm32f10x.h"

 
#line 7085 "..\\core_cm3\\stm32f10x.h"

 
#line 7119 "..\\core_cm3\\stm32f10x.h"

 
#line 7153 "..\\core_cm3\\stm32f10x.h"

 
#line 7187 "..\\core_cm3\\stm32f10x.h"

 
#line 7221 "..\\core_cm3\\stm32f10x.h"

 
#line 7255 "..\\core_cm3\\stm32f10x.h"

 
#line 7289 "..\\core_cm3\\stm32f10x.h"

 
#line 7323 "..\\core_cm3\\stm32f10x.h"

 
#line 7357 "..\\core_cm3\\stm32f10x.h"

 
#line 7391 "..\\core_cm3\\stm32f10x.h"

 
#line 7425 "..\\core_cm3\\stm32f10x.h"

 
#line 7459 "..\\core_cm3\\stm32f10x.h"

 
 
 
 
 

 









#line 7486 "..\\core_cm3\\stm32f10x.h"

 
#line 7494 "..\\core_cm3\\stm32f10x.h"

 
#line 7504 "..\\core_cm3\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7565 "..\\core_cm3\\stm32f10x.h"

 
#line 7574 "..\\core_cm3\\stm32f10x.h"







 



#line 7595 "..\\core_cm3\\stm32f10x.h"



 



 


 
#line 7620 "..\\core_cm3\\stm32f10x.h"

 
#line 7630 "..\\core_cm3\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7656 "..\\core_cm3\\stm32f10x.h"

 


 



 
#line 7680 "..\\core_cm3\\stm32f10x.h"

 
#line 7689 "..\\core_cm3\\stm32f10x.h"







 
#line 7709 "..\\core_cm3\\stm32f10x.h"

 
#line 7720 "..\\core_cm3\\stm32f10x.h"



 
 
 
 
 

 


#line 7749 "..\\core_cm3\\stm32f10x.h"

 









#line 7783 "..\\core_cm3\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7823 "..\\core_cm3\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8287 "..\\core_cm3\\stm32f10x.h"



 

 

  

#line 1 "..\\user\\stm32f10x_conf.h"



















  

 



 
 

#line 1 "..\\lib\\inc\\stm32f10x_bkp.h"




















 

 







 
#line 1 "..\\core_cm3\\stm32f10x.h"







































 



 



 
    
#line 8327 "..\\core_cm3\\stm32f10x.h"



 

  

 

 
#line 33 "..\\lib\\inc\\stm32f10x_bkp.h"



 



 



 



 



 



 







 



 

#line 78 "..\\lib\\inc\\stm32f10x_bkp.h"


 



 

#line 128 "..\\lib\\inc\\stm32f10x_bkp.h"

#line 143 "..\\lib\\inc\\stm32f10x_bkp.h"




 



 



 



 



 

void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);








 



 



 

 
#line 30 "..\\user\\stm32f10x_conf.h"






#line 1 "..\\lib\\inc\\stm32f10x_exti.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_exti.h"



 



 



 



 

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;





 

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;






 

typedef struct
{
  uint32_t EXTI_Line;               
 
   
  EXTIMode_TypeDef EXTI_Mode;       
 

  EXTITrigger_TypeDef EXTI_Trigger; 
 

  FunctionalState EXTI_LineCmd;     
  
}EXTI_InitTypeDef;



 



 



 

#line 124 "..\\lib\\inc\\stm32f10x_exti.h"
                                          
#line 136 "..\\lib\\inc\\stm32f10x_exti.h"

                    


 



 



 



 



 

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);








 



 



 

 
#line 37 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_flash.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_flash.h"



 



 



 



 

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;



 



 



 

#line 77 "..\\lib\\inc\\stm32f10x_flash.h"


 



 







 



 







 



 

 
#line 118 "..\\lib\\inc\\stm32f10x_flash.h"

 
#line 144 "..\\lib\\inc\\stm32f10x_flash.h"

 
#line 211 "..\\lib\\inc\\stm32f10x_flash.h"











 



 







 



 







 



 





#line 270 "..\\lib\\inc\\stm32f10x_flash.h"


 


 
#line 291 "..\\lib\\inc\\stm32f10x_flash.h"






 



 
#line 333 "..\\lib\\inc\\stm32f10x_flash.h"





 
#line 346 "..\\lib\\inc\\stm32f10x_flash.h"



 



 



 



 



 

 
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

 
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);

#line 408 "..\\lib\\inc\\stm32f10x_flash.h"








 



 



 

 
#line 38 "..\\user\\stm32f10x_conf.h"

#line 1 "..\\lib\\inc\\stm32f10x_gpio.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_gpio.h"



 



 



 

#line 53 "..\\lib\\inc\\stm32f10x_gpio.h"
                                     


 

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;





 

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;








 

typedef struct
{
  uint16_t GPIO_Pin;             
 

  GPIOSpeed_TypeDef GPIO_Speed;  
 

  GPIOMode_TypeDef GPIO_Mode;    
 
}GPIO_InitTypeDef;




 

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;





 



 



 

#line 144 "..\\lib\\inc\\stm32f10x_gpio.h"



#line 163 "..\\lib\\inc\\stm32f10x_gpio.h"



 



 

#line 204 "..\\lib\\inc\\stm32f10x_gpio.h"







#line 217 "..\\lib\\inc\\stm32f10x_gpio.h"






#line 245 "..\\lib\\inc\\stm32f10x_gpio.h"
                              


  



 

#line 266 "..\\lib\\inc\\stm32f10x_gpio.h"

#line 274 "..\\lib\\inc\\stm32f10x_gpio.h"



 



 

#line 299 "..\\lib\\inc\\stm32f10x_gpio.h"

#line 316 "..\\lib\\inc\\stm32f10x_gpio.h"



 



  








                                                 


 



 



 



 

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);








 



 



 

 
#line 40 "..\\user\\stm32f10x_conf.h"

#line 1 "..\\lib\\inc\\stm32f10x_iwdg.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_iwdg.h"



 



 



 



 



 



 







 



 

#line 84 "..\\lib\\inc\\stm32f10x_iwdg.h"


 



 







 



 



 



 



 

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);








 



 



 

 
#line 42 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_pwr.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_pwr.h"



 



  



  



  



  



  

#line 70 "..\\lib\\inc\\stm32f10x_pwr.h"


 



 







 



 




 


 



 










 



 



 



 



 

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);








 



 



 

 
#line 43 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_rcc.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_rcc.h"



 



 



 

typedef struct
{
  uint32_t SYSCLK_Frequency;   
  uint32_t HCLK_Frequency;     
  uint32_t PCLK1_Frequency;    
  uint32_t PCLK2_Frequency;    
  uint32_t ADCCLK_Frequency;   
}RCC_ClocksTypeDef;



 



 



 









  



 



#line 94 "..\\lib\\inc\\stm32f10x_rcc.h"



  



 
#line 126 "..\\lib\\inc\\stm32f10x_rcc.h"

#line 141 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 
#line 175 "..\\lib\\inc\\stm32f10x_rcc.h"


 




 
#line 196 "..\\lib\\inc\\stm32f10x_rcc.h"


 

#line 283 "..\\lib\\inc\\stm32f10x_rcc.h"




 

#line 295 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 

#line 317 "..\\lib\\inc\\stm32f10x_rcc.h"


  



 

#line 333 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 

#line 347 "..\\lib\\inc\\stm32f10x_rcc.h"

#line 364 "..\\lib\\inc\\stm32f10x_rcc.h"




 




 








 
#line 396 "..\\lib\\inc\\stm32f10x_rcc.h"


#line 423 "..\\lib\\inc\\stm32f10x_rcc.h"
  



 

#line 435 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 








 



 

#line 462 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 







#line 489 "..\\lib\\inc\\stm32f10x_rcc.h"


 



 

#line 519 "..\\lib\\inc\\stm32f10x_rcc.h"




  



 

#line 555 "..\\lib\\inc\\stm32f10x_rcc.h"
 




 



 







#line 588 "..\\lib\\inc\\stm32f10x_rcc.h"



 



 

#line 608 "..\\lib\\inc\\stm32f10x_rcc.h"

#line 627 "..\\lib\\inc\\stm32f10x_rcc.h"




 



 



 



 



 

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);





#line 668 "..\\lib\\inc\\stm32f10x_rcc.h"

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);


 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);




void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);






void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);





void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);








 



 



  

 
#line 44 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_rtc.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_rtc.h"



 



  



  



  



 



 

#line 64 "..\\lib\\inc\\stm32f10x_rtc.h"


  



 

#line 82 "..\\lib\\inc\\stm32f10x_rtc.h"



 



 



 



 



 

void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetPrescaler(uint32_t PrescalerValue);
void RTC_SetAlarm(uint32_t AlarmValue);
uint32_t  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);








 



 



 

 
#line 45 "..\\user\\stm32f10x_conf.h"

#line 1 "..\\lib\\inc\\stm32f10x_spi.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_spi.h"



 



  



 



 

typedef struct
{
  uint16_t SPI_Direction;           
 

  uint16_t SPI_Mode;                
 

  uint16_t SPI_DataSize;            
 

  uint16_t SPI_CPOL;                
 

  uint16_t SPI_CPHA;                
 

  uint16_t SPI_NSS;                 

 
 
  uint16_t SPI_BaudRatePrescaler;   



 

  uint16_t SPI_FirstBit;            
 

  uint16_t SPI_CRCPolynomial;        
}SPI_InitTypeDef;



 

typedef struct
{

  uint16_t I2S_Mode;         
 

  uint16_t I2S_Standard;     
 

  uint16_t I2S_DataFormat;   
 

  uint16_t I2S_MCLKOutput;   
 

  uint32_t I2S_AudioFreq;    
 

  uint16_t I2S_CPOL;         
 
}I2S_InitTypeDef;



 



 










 
  
#line 136 "..\\lib\\inc\\stm32f10x_spi.h"


 



 







 



 







  



 







 



 







 



 







  



 

#line 220 "..\\lib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 248 "..\\lib\\inc\\stm32f10x_spi.h"


 



 

#line 266 "..\\lib\\inc\\stm32f10x_spi.h"


 



 

#line 282 "..\\lib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 312 "..\\lib\\inc\\stm32f10x_spi.h"






  



 







 



 






 



 







 



 






 



 







 



 

#line 396 "..\\lib\\inc\\stm32f10x_spi.h"


 



 

#line 417 "..\\lib\\inc\\stm32f10x_spi.h"


 



 




 



 



 



 



 

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);








 



 



 

 
#line 47 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_tim.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_tim.h"



 



  



  




 

typedef struct
{
  uint16_t TIM_Prescaler;         
 

  uint16_t TIM_CounterMode;       
 

  uint16_t TIM_Period;            

  

  uint16_t TIM_ClockDivision;     
 

  uint8_t TIM_RepetitionCounter;  






 
} TIM_TimeBaseInitTypeDef;       



 

typedef struct
{
  uint16_t TIM_OCMode;        
 

  uint16_t TIM_OutputState;   
 

  uint16_t TIM_OutputNState;  

 

  uint16_t TIM_Pulse;         
 

  uint16_t TIM_OCPolarity;    
 

  uint16_t TIM_OCNPolarity;   

 

  uint16_t TIM_OCIdleState;   

 

  uint16_t TIM_OCNIdleState;  

 
} TIM_OCInitTypeDef;



 

typedef struct
{

  uint16_t TIM_Channel;      
 

  uint16_t TIM_ICPolarity;   
 

  uint16_t TIM_ICSelection;  
 

  uint16_t TIM_ICPrescaler;  
 

  uint16_t TIM_ICFilter;     
 
} TIM_ICInitTypeDef;




 

typedef struct
{

  uint16_t TIM_OSSRState;        
 

  uint16_t TIM_OSSIState;        
 

  uint16_t TIM_LOCKLevel;        
  

  uint16_t TIM_DeadTime;         

 

  uint16_t TIM_Break;            
 

  uint16_t TIM_BreakPolarity;    
 

  uint16_t TIM_AutomaticOutput;  
 
} TIM_BDTRInitTypeDef;



 

#line 186 "..\\lib\\inc\\stm32f10x_tim.h"

 



 






 
#line 205 "..\\lib\\inc\\stm32f10x_tim.h"
									                                 
 
#line 216 "..\\lib\\inc\\stm32f10x_tim.h"

                                             
#line 225 "..\\lib\\inc\\stm32f10x_tim.h"

 
#line 236 "..\\lib\\inc\\stm32f10x_tim.h"

 
#line 249 "..\\lib\\inc\\stm32f10x_tim.h"

                                         
#line 266 "..\\lib\\inc\\stm32f10x_tim.h"

 
#line 279 "..\\lib\\inc\\stm32f10x_tim.h"
                                                                                                                                                                                                                          


  



 

#line 308 "..\\lib\\inc\\stm32f10x_tim.h"


 



 







  



 

#line 341 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 355 "..\\lib\\inc\\stm32f10x_tim.h"


 



 

#line 373 "..\\lib\\inc\\stm32f10x_tim.h"


  



 







 



 
  






 



 







  



 







  



 







  



 







  



 







  



 







  



 







  



 

#line 497 "..\\lib\\inc\\stm32f10x_tim.h"


  



 







 



 







  



 







  



 







  



 

#line 561 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 577 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 593 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 610 "..\\lib\\inc\\stm32f10x_tim.h"

#line 619 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 665 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 709 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 725 "..\\lib\\inc\\stm32f10x_tim.h"



  



 

#line 742 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 770 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 784 "..\\lib\\inc\\stm32f10x_tim.h"


  



  






 



 







  



 







  



 

#line 833 "..\\lib\\inc\\stm32f10x_tim.h"


  




 

#line 851 "..\\lib\\inc\\stm32f10x_tim.h"



  



 

#line 866 "..\\lib\\inc\\stm32f10x_tim.h"


  



 







  



 





                                     


  



 







  



 

#line 927 "..\\lib\\inc\\stm32f10x_tim.h"


  



 

#line 943 "..\\lib\\inc\\stm32f10x_tim.h"


  



 







  



 

#line 987 "..\\lib\\inc\\stm32f10x_tim.h"
                               
                               



  



 




  



 




  



 

#line 1034 "..\\lib\\inc\\stm32f10x_tim.h"


 



 



 



  



 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);








  



  



 

 
#line 48 "..\\user\\stm32f10x_conf.h"
#line 1 "..\\lib\\inc\\stm32f10x_usart.h"




















 

 







 
#line 33 "..\\lib\\inc\\stm32f10x_usart.h"



 



  



  



  
  
typedef struct
{
  uint32_t USART_BaudRate;            


 

  uint16_t USART_WordLength;          
 

  uint16_t USART_StopBits;            
 

  uint16_t USART_Parity;              




 
 
  uint16_t USART_Mode;                
 

  uint16_t USART_HardwareFlowControl; 

 
} USART_InitTypeDef;



  
  
typedef struct
{

  uint16_t USART_Clock;   
 

  uint16_t USART_CPOL;    
 

  uint16_t USART_CPHA;    
 

  uint16_t USART_LastBit; 

 
} USART_ClockInitTypeDef;



  



  
  
















  
  


                                    




  



  
  
#line 146 "..\\lib\\inc\\stm32f10x_usart.h"


  



  
  
#line 160 "..\\lib\\inc\\stm32f10x_usart.h"


  



  
  





  



  
#line 187 "..\\lib\\inc\\stm32f10x_usart.h"


  



  






  



 
  






  



 







 



 







  



 
  
#line 264 "..\\lib\\inc\\stm32f10x_usart.h"


 



 







  



 







 



 
  







 



 







  



 

#line 336 "..\\lib\\inc\\stm32f10x_usart.h"
                              
#line 344 "..\\lib\\inc\\stm32f10x_usart.h"



  



  



  



  



 

void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);








  



  



  

 
#line 49 "..\\user\\stm32f10x_conf.h"

#line 1 "..\\lib\\inc\\misc.h"




















 

 







 
#line 33 "..\\lib\\inc\\misc.h"



 



 



 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;
 


 



 
























 



 



 



 







 



 

#line 133 "..\\lib\\inc\\misc.h"


 



 

#line 151 "..\\lib\\inc\\misc.h"















 



 







 



 



 



 



 

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 



 

 
#line 51 "..\\user\\stm32f10x_conf.h"

 
 

 
 

 
#line 74 "..\\user\\stm32f10x_conf.h"



 
#line 8298 "..\\core_cm3\\stm32f10x.h"




 

















 









 

  

 

 
#line 28 "..\\dev\\stm32f10x_it.h"

 
 
 
 

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void SPI1_IRQHandler(void);



 
#line 26 "..\\dev\\stm32f10x_it.c"
#line 1 "..\\dev\\dev_uart.h"



#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
 
 
 




 
 



 













  


 








#line 46 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


  
  typedef unsigned int size_t;










    



    typedef unsigned short wchar_t;  
#line 75 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { __int64 quot, rem; } lldiv_t;
    


#line 96 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   



 

   




 
#line 115 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) __int64 atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) __int64 strtoll(const char * __restrict  ,
                               char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned __int64 strtoull(const char * __restrict  ,
                                         char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 415 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 503 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 532 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __pure int abs(int  );
   



 

extern __declspec(__nothrow) __pure div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __pure long int labs(long int  );
   



 




extern __declspec(__nothrow) __pure ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __pure __int64 llabs(__int64  );
   



 




extern __declspec(__nothrow) __pure lldiv_t lldiv(__int64  , __int64  );
   











 
#line 613 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"



 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __pure __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 



 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 867 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


 

#line 5 "..\\dev\\dev_uart.h"
#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 185 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 201 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 224 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 239 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 262 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 494 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"



 

#line 6 "..\\dev\\dev_uart.h"
#line 1 "..\\user\\magdecode.h"



#line 5 "..\\user\\magdecode.h"









#line 23 "..\\user\\magdecode.h"







typedef struct _TRACKTIMEFLOW 
{
	uint16_t Value[1100];
	uint16_t Length;
}TRACK1TIMEFLOW;

typedef struct _TRACK2TIMEFLOW 
{
	uint16_t Value[500];
	uint16_t Length;
}TRACK2TIMEFLOW;

typedef struct _TRACK3TIMEFLOW 
{
	uint16_t Value[1080];
	uint16_t Length;
}TRACK3TIMEFLOW;

typedef struct _TRACKBITFLOW 
{
	uint8_t  Value[800];
	uint16_t Length;
}TRACKBITFLOW;

typedef struct _TRACKDATA 
{
	uint8_t Value[110];
	uint8_t Length;
}TRACKDATA;

extern TRACK1TIMEFLOW Track1TimeFlow;				
extern TRACK2TIMEFLOW Track2TimeFlow;				
extern TRACK3TIMEFLOW Track3TimeFlow;				

extern TRACKBITFLOW TrackBitFlow;					

extern TRACKDATA TempTrackDirtData,TempTrackData;	
extern TRACKDATA Track1Data,Track2Data,Track3Data;	











 
extern uint8_t MagDecodeTrack(uint8_t type);











 
extern void FlushBuffer_Init (void);
















 
extern void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level);










 
extern void MSR_Check_Sync_Pattern (void);










 
extern void MSR_F2F_Decoder (void);










 
extern void MSR_Character_Decoder (void);










 
extern unsigned char GetMSR_CardDataForUART (void);











 
extern void MSR_WaitForReady (void);















 
extern int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length);





#line 7 "..\\dev\\dev_uart.h"








extern volatile unsigned short rec_head0;
extern volatile unsigned short rec_end0;


int dev_com_open(void);
int dev_com_close(void);
int dev_com_write(unsigned char *buf, int len);
int dev_com_read(unsigned char *buf, int len);
void uart_puts(char *s);
void uart_printf(char *fmt, ...);

#line 27 "..\\dev\\stm32f10x_it.c"
#line 28 "..\\dev\\stm32f10x_it.c"


volatile uint16_t TM1ReadValue1 = 0, TM1ReadValue2 = 0;
volatile uint16_t TM2ReadValue1 = 0, TM2ReadValue2 = 0;
volatile uint16_t TM3ReadValue1 = 0, TM3ReadValue2 = 0;
volatile uint8_t TM1CaptureNumber = 0;
volatile uint8_t TM2CaptureNumber = 0;
volatile uint8_t TM3CaptureNumber = 0;
 
 
 
 
 
 

 
 
 





 
void NMI_Handler(void)
{
}





 
void HardFault_Handler(void)
{
   
  while (1)
  {}
}





 
void MemManage_Handler(void)
{
   
  while (1)
  {}
}





 
void BusFault_Handler(void)
{
   
  while (1)
  {}
}





 
void UsageFault_Handler(void)
{
   
  while (1)
  {}
}





 
void DebugMon_Handler(void)
{}





 
void SVC_Handler(void)
{}





 
void PendSV_Handler(void)
{}





 
void SysTick_Handler(void)
{}








 

	void USART1_IRQHandler(void)
{
	unsigned short ch;
	
	
	
	if (((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR1 & 0x20) != 0) && ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 0x20) != 0) ) {
		
		((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~0x20);
		
		if ( ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR3 & 1) != 0) && ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 0x8) != 0)) {
			
			
			ch = (((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR & (u16)0xFF);
			
			((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~0x8);
			rec_end0 = rec_head0;
		} else {
			ch = ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR;
			
			((uint8_t *)Track1TimeFlow . Value)[rec_end0++] = (unsigned char)(ch&0xff);
			if (rec_end0 >= 512) {
				rec_end0 = 0;
			}

		}
	}

	 
	
	if( ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR3 & 1) != 0) && 
		((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 0x2) != 0) )
	{
		 
		
		((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~2);
		
		ch = (((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR & (u16)0xFF);
		 
		
	}

	 
	
	if( ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR1 & 0x100) != 0) && 
		((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 1) != 0) )
	{
		
		while((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & ((uint16_t)0x0020)) == 0)
		{
		}
		 
		
		((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~1);
		
		ch = (((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR & (u16)0xFF);
	}
	 
	
	if( ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR3 & 1) != 0) && 
		((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 0x8) != 0) )
	{
		 
		
		((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~0x8);
		
		ch = (((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR &(u16)0xFF);
	}
	 
	
	if( ((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->CR3 & 1) != 0) && 
		((((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR & 0x4) != 0) )
	{
		 
		
		((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->SR = (u16)(~4);
		
		ch = (((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800))->DR &(u16)0xFF);
	}
}









 
void EXTI4_IRQHandler(void)												 
{
	if (EXTI_GetITStatus(((uint32_t)0x00010)) == SET) {							
		EXTI_ClearITPendingBit(((uint32_t)0x00010));								 
		if (0 == GPIO_ReadInputDataBit(((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0800)), ((uint16_t)0x0010))) {			
			MSR_Check_Sync_Pattern();
			TIM_Cmd(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0400)), ENABLE);										
		} else {
			MSR_WaitForReady();											
			TIM_Cmd(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0400)), DISABLE);	
		}
	}
}









 
void TIM3_IRQHandler(void)												 
{
	if (TIM_GetITStatus(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0400)), ((uint16_t)0x0001)) == SET) {
		TIM_ClearITPendingBit(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0400)), ((uint16_t)0x0001));
		MSR_WaitForReady();												
		TIM_Cmd(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0400)), DISABLE);	
	}
}









 
void EXTI0_IRQHandler(void)																		 
{
	if (EXTI_GetITStatus(((uint32_t)0x00001)) == SET) {
		EXTI_ClearITPendingBit(((uint32_t)0x00001));  													 
		if (TM2CaptureNumber <= 2) {													
			 
			TM2ReadValue1 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;															
			TM2CaptureNumber++;
		} else if (Track2TimeFlow.Length < 500 ) {								
			 
			TM2ReadValue2 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;															

			 

			if (TM2ReadValue2 > TM2ReadValue1) {
				
				SetF2FInputBuffer(1, TM2ReadValue2 - TM2ReadValue1, 0);
			} else {
				
				SetF2FInputBuffer(1, 0xFFFF - TM2ReadValue1 + TM2ReadValue2, 0);
			}




			TM2ReadValue1 = TM2ReadValue2;
    	}
	}
}










 
void EXTI9_5_IRQHandler(void)																	 
{
	if(EXTI_GetITStatus(((uint32_t)0x00040)) == SET)
	{
		EXTI_ClearITPendingBit(((uint32_t)0x00040));   
		if (TM3CaptureNumber <= 2) {
			 
			TM3ReadValue1 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;															
			TM3CaptureNumber++;
		} else if (Track3TimeFlow.Length < 1080 ) {								
			 
			TM3ReadValue2 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;															

			 

			if (TM3ReadValue2 > TM3ReadValue1) {
				
				SetF2FInputBuffer(2, TM3ReadValue2 - TM3ReadValue1, 0);
			} else {
				
				SetF2FInputBuffer(2, 0xFFFF - TM3ReadValue1 + TM3ReadValue2, 0);
			}




			
			TM3ReadValue1 = TM3ReadValue2;
    	}
	}
}









 
void EXTI15_10_IRQHandler(void)																		 
{
	if(EXTI_GetITStatus(((uint32_t)0x00400)) == SET)
	{
		EXTI_ClearITPendingBit(((uint32_t)0x00400));   
		if (TM1CaptureNumber <= 2) {
			 
			TM1ReadValue1 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;																
			TM1CaptureNumber++;
		} else if (Track1TimeFlow.Length < 1100 ) {									
			 
			TM1ReadValue2 = ((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000))->CNT;																

			 

			if (TM1ReadValue2 > TM1ReadValue1) {
				
				SetF2FInputBuffer(0, TM1ReadValue2 - TM1ReadValue1, 0);
			} else {
				
				SetF2FInputBuffer(0, (0xFFFF - TM1ReadValue1) + TM1ReadValue2, 0);
			}




			
			TM1ReadValue1 = TM1ReadValue2;
    	}
	}
}









 
void RTCAlarm_IRQHandler(void)
{

  if(RTC_GetITStatus(((uint16_t)0x0002)) != RESET)
  {
	 
    EXTI_ClearITPendingBit(((uint32_t)0x20000));

     
    if(PWR_GetFlagStatus(((uint32_t)0x00000001)) != RESET)
    {
       
      PWR_ClearFlag(((uint32_t)0x00000001));
    }

     
    RTC_WaitForLastTask();   
     
    RTC_ClearITPendingBit(((uint16_t)0x0002));
     
    RTC_WaitForLastTask();
  }


}


 
