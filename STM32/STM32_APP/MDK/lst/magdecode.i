#line 1 "..\\user\\magdecode.c"
#line 1 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"


  
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
   













 


#line 185 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 201 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 224 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 239 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 262 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
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
    














































 







#line 494 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"



 

#line 2 "..\\user\\magdecode.c"
#line 1 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
 
 
 





 






 













#line 38 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 129 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 948 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"



 

#line 3 "..\\user\\magdecode.c"
#line 1 "..\\user\\magdecode.h"



#line 1 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"
 
 





 










#line 26 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"







 

     

     
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




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 197 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"

     







     










     











#line 261 "E:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"



 



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

 TRACK1TIMEFLOW Track1TimeFlow;				
 TRACK2TIMEFLOW Track2TimeFlow;				
 TRACK3TIMEFLOW Track3TimeFlow;				

 TRACKBITFLOW TrackBitFlow;					

 TRACKDATA TempTrackDirtData,TempTrackData;	
 TRACKDATA Track1Data,Track2Data,Track3Data;	











 
 uint8_t MagDecodeTrack(uint8_t type);











 
 void FlushBuffer_Init (void);
















 
 void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level);










 
 void MSR_Check_Sync_Pattern (void);










 
 void MSR_F2F_Decoder (void);










 
 void MSR_Character_Decoder (void);










 
 unsigned char GetMSR_CardDataForUART (void);











 
 void MSR_WaitForReady (void);















 
 int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length);





#line 5 "..\\user\\magdecode.c"






volatile char MSR_fCardDataReady = 0;
#line 56 "..\\user\\magdecode.c"








 
static void SetBit(uint8_t *lpByte,uint8_t nBit)
{
    *lpByte |= (0x01<<nBit);
}








 
static void ClearBit(uint8_t *lpByte,uint8_t nBit)
{
    *lpByte &= ~(0x01<<nBit);
}








 
static void CplBit(uint8_t *lpByte,uint8_t nBit)
{
	*lpByte ^= (0x01<<nBit);
}








 
static uint8_t CheckLrcEvenParity(uint8_t *lpIn,uint16_t nLen,uint8_t nBitPos)
{
	uint16_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i <nLen; i++)
	{
		if(((lpIn[i] >> nBitPos) & 0x01) == 0x01)
		{
			BitCnt ++;
		}
	}
	if((BitCnt % 2) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}








 
static uint16_t CheckLrcDirtOnlyOne(uint16_t *lpOutDirtPos,uint8_t *lpIn,uint16_t nLen,uint8_t nBitPos)
{
	uint16_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i <nLen; i++)
	{
		if(((lpIn[i] >> nBitPos) & 0x01) == 0x01)
		{
			*lpOutDirtPos = i;
			BitCnt ++;
		}
	}
	if(BitCnt == 1)								
	{
		return 1;								
	}
	else
	{
		return 0;								
	}	
}








 
static const uint8_t PARITY_TAB[16] = {0, 1, 1, 2, 1, 2, 2, 3,
                                       1, 2, 2, 3, 2, 3, 3, 4};
static uint8_t CheckOddParity(uint8_t nByte)
{
    return (PARITY_TAB[nByte&0x0f]+PARITY_TAB[(nByte>>4)&0x0f])&0x01;
}








 
static uint8_t CheckDirtOnlyOne(uint8_t nByte)
{
	uint8_t i,BitCnt;
	
	BitCnt = 0; 
	for(i = 0; i < 8; i++)
	{
		if((nByte & 0x01) == 0x01)
		{
			BitCnt ++;
		}
		nByte >>= 1;
	}
	if(BitCnt == 1)								
	{
		return 1;						
	}
	else
	{
		return 0;
	}	
}








 
static uint16_t GetDelta(uint16_t FirstData,uint16_t SecondData)
{
	if(FirstData > SecondData)
	{
		return FirstData - SecondData;
	}
	else
	{
		return SecondData - FirstData; 
	}
}








 
static uint16_t PllSmooth(uint16_t *lpIn,uint16_t nLen)
{
	uint32_t i,average = 0;

	if(nLen >= 8)
	{
		for(i = 1; i <= 8; i++)
		{
			average += lpIn[nLen-i];
		}
		average /= 8;
	}
	else
	{
		for(i = 0; i < nLen; i++)
		{
			average += lpIn[i];
		}
		average /= nLen;
	}
	return (uint16_t)average;
}









 
static void ResortMagData( uint8_t  type)
{

	uint16_t lpInTimeFlowLength,*lpInTimeFlowValue;
	uint16_t i,nLoopCount = 0,uData;
	type = type >> 4;
	if (1 == type)
	{
		lpInTimeFlowLength = Track1TimeFlow.Length;
		lpInTimeFlowValue = Track1TimeFlow.Value;
	}
	else if (2 == type)
	{
		lpInTimeFlowLength = Track2TimeFlow.Length;
		lpInTimeFlowValue = Track2TimeFlow.Value;
	}
	else if (3== type)
	{
		lpInTimeFlowLength = Track3TimeFlow.Length;
		lpInTimeFlowValue = Track3TimeFlow.Value;
	}
	else
	{
		return ;
	}
	nLoopCount = lpInTimeFlowLength / 2;
	
	for ( i = 0; i < nLoopCount; i ++ )
	{
		uData = lpInTimeFlowValue[i];
		lpInTimeFlowValue[i] = lpInTimeFlowValue[lpInTimeFlowLength-i-1];
		lpInTimeFlowValue[lpInTimeFlowLength-i-1] = uData;
	}
#line 340 "..\\user\\magdecode.c"
}





















 
uint8_t DecodeTimeToBit(uint8_t type)
{
	uint8_t  bSync = 0,bFlag,bCompensate = 0;
	uint8_t  ProbePulse = 0,ProbeDirt = 0;
	uint16_t SyncCnt = 0,CurTimeFlowCnt = 0,CurPercent = 0;
	uint32_t i,j;
	uint16_t CurPllCycle = 0,CurPllCycleTemp[8] = {0},curnclen = 0;
	int ProbeTotalTime = 0;
	uint16_t lpInTimeFlowLength;

    uint16_t *lpInTimeFlowValue;



    uint16_t ltmpu16, ltmpu16_next;

	type = type >> 4;
	if (1 == type)
	{
		lpInTimeFlowLength = Track1TimeFlow.Length;
		lpInTimeFlowValue = Track1TimeFlow.Value;
	}
	else if (2 == type)
	{
		lpInTimeFlowLength = Track2TimeFlow.Length;
		lpInTimeFlowValue = Track2TimeFlow.Value;
	}
	else if (3== type)
	{
		lpInTimeFlowLength = Track3TimeFlow.Length;
		lpInTimeFlowValue = Track3TimeFlow.Value;
	}
	else
	{
		return 3;
	}
	memset((uint8_t*)&TrackBitFlow,0,sizeof(TRACKBITFLOW));
    
	for(CurTimeFlowCnt = 0; CurTimeFlowCnt < lpInTimeFlowLength; CurTimeFlowCnt++)
	{
		if(!bSync)																								
		{

            if((lpInTimeFlowValue[CurTimeFlowCnt] == 0) || (lpInTimeFlowValue[CurTimeFlowCnt] > 30000))		




            {
				continue;
			}

			i = GetDelta(CurPllCycle,lpInTimeFlowValue[CurTimeFlowCnt]);
			i = (i*100) /lpInTimeFlowValue[CurTimeFlowCnt];
			CurPllCycle = lpInTimeFlowValue[CurTimeFlowCnt];





			if(i > 30)																							
			{
				SyncCnt = 0;
			}
			else
			{
				SyncCnt ++;
				if(SyncCnt >= 8)															
				{
					bSync = 1;
					ProbeDirt = 0;
					ProbePulse = 0;
					ProbeTotalTime = 0;
					TrackBitFlow.Length = 0;
					curnclen = 0;
					for(i = 0; i < (uint32_t)CurTimeFlowCnt+1; i ++)
					{
						

						CurPllCycleTemp[i%8] = lpInTimeFlowValue[i];



					}
					curnclen = CurTimeFlowCnt+1;
				}
			}
		}
		else
		{

			ltmpu16  = lpInTimeFlowValue[CurTimeFlowCnt];



            ProbeTotalTime += ltmpu16;
			CurPllCycle = PllSmooth(CurPllCycleTemp,8);
			CurPercent = (ProbeTotalTime * 100) / CurPllCycle;
			i = (ltmpu16*100) / CurPllCycle; 
			if(i >= 20 && i < 33)															
			{
				ProbeDirt = 1;
			}
			if(CurPercent >= 33 && CurPercent < 70)											
			{
				if(i < 20)
				{
					ProbeDirt = 1;															
				}
				ProbePulse ++;																
			}
			else if(CurPercent >= 70 && CurPercent < 130)									
			{             
				bFlag = 0;

				ltmpu16_next = lpInTimeFlowValue[CurTimeFlowCnt + 1];



				if((!(CurPercent >= 90 && CurPercent < 110)) && ((CurTimeFlowCnt+1) < lpInTimeFlowLength))
				{
					if(((ltmpu16_next !=0 ) && (((ltmpu16_next * 100) / CurPllCycle) < 33)) 
						&& ((((ProbeTotalTime+ltmpu16_next) * 100) / CurPllCycle) < 110))	
					{
						bFlag = 1;
						bCompensate ++;
					}
				}
				if(bFlag == 0)
				{
					if(bCompensate == 0)													
					{
						if(ProbePulse == 1 && ((ltmpu16*100) / CurPllCycle) < 20)
						{
							ProbePulse = 0;													
						}
					}
					if(CurPllCycle > ProbeTotalTime)
					{
						i = CurPllCycle - ProbeTotalTime;
						if((i * 100 / CurPllCycle) < 35)
						{
							CurPllCycleTemp[curnclen%8] = ProbeTotalTime;curnclen++;
							ProbeTotalTime = 0;
						}
						else
						{
							j = (7 * i) / 8;
							CurPllCycleTemp[curnclen%8] = ProbeTotalTime + j;curnclen++;
							ProbeTotalTime = CurPllCycle - (ProbeTotalTime + j);
						}
					}
					else
					{
						i = ProbeTotalTime - CurPllCycle;
						if((i * 100 / CurPllCycle) < 35)
						{
							CurPllCycleTemp[curnclen%8] = ProbeTotalTime;curnclen++;
							ProbeTotalTime = 0;
						}
						else
						{
							j = (1 * i) / 8;
							CurPllCycleTemp[curnclen%8] = ProbeTotalTime - j;curnclen++;
							ProbeTotalTime = j;
						}
					}
					if(ProbeDirt == 1)
					{
						if (TrackBitFlow.Length < 800)
							TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
						else
							break;
					}
					else 
					{
						if(ProbePulse > 0)			
						{
							if (TrackBitFlow.Length < 800)
								TrackBitFlow.Value[TrackBitFlow.Length++] = 1;
							else
								break;
						}
						else
						{
							if (TrackBitFlow.Length < 800)
								TrackBitFlow.Value[TrackBitFlow.Length++] = 0;
							else
								break;
						}
					}
					bCompensate = 0;
					ProbePulse = 0;
					ProbeDirt = 0;
				}
			}
			else if(CurPercent >= 130)																			
			{
				j = 0; 
				while(ProbeTotalTime >= CurPllCycle) 
				{
					j ++;
					if (j>10)
						break;
					CurPllCycleTemp[curnclen%8] = CurPllCycle;curnclen++;
					ProbeTotalTime -= CurPllCycle;
					CurPllCycle = PllSmooth(CurPllCycleTemp,8);
					if (TrackBitFlow.Length < 800)
						TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
					else
						break;
				}
				ProbeDirt = 0;
				ProbePulse = 0;
				bCompensate = 0;
				i = (ProbeTotalTime*100)/CurPllCycle;	
				if(i < 40)											
				{
					CurPllCycleTemp[(curnclen-1)%8] += ProbeTotalTime;
					ProbeTotalTime = 0;
				}
				else if(i >= 70)
				{
					CurPllCycleTemp[curnclen%8] = ProbeTotalTime;curnclen++;
					if (TrackBitFlow.Length < 800)
						TrackBitFlow.Value[TrackBitFlow.Length++] = 2;
					else
						break;
					ProbeTotalTime = 0;	
				}
				else
				{
					ProbeDirt = 1;
					ProbePulse = 1;
				}
			}
		}
	}
	
	if(!bSync)
	{
		memset((uint8_t*)&TrackBitFlow, 0, sizeof(TRACKBITFLOW));
		return 0;
	}
	else
	{
		return 1;
	}
}










 
uint8_t DecodeTrackData(uint8_t type)
{
	TRACKDATA *lpOutTrackData;
	uint16_t i,j,k,m,FirstBitCnt,SndBitCnt,FirstOkByteCnt,SndOkByteCnt;
	uint8_t BitCnt = 0,SyncStep,bFlag,bData;
	uint8_t bSyncHead,bCorrectDirt,bCheckOk,DecodeTimes,bFinalSucc,bFinalCorrect;
	uint8_t bEachCorrected;			
		
	if (0x15 == type|| 0x16 == type || 0x17 == type || 0x18 == type)
	{
		lpOutTrackData = &Track1Data;
	}
	else if (0x25 == type)
	{
		lpOutTrackData = &Track2Data;
	}
	else if (0x35 == type || 0x36 == type || 0x37 == type)
	{
		lpOutTrackData = &Track3Data;
	}
	else
		return 2;

	memset((uint8_t*)lpOutTrackData,0,sizeof(TRACKDATA));
	if (!TrackBitFlow.Length)
		return 2;
	
	FirstBitCnt = 0;
	SndBitCnt = 0;
	FirstOkByteCnt = 0;
	SndOkByteCnt = 0;
	bFinalSucc = 0;

	for(DecodeTimes = 0; DecodeTimes < 2; DecodeTimes ++)				
	{
		bSyncHead = 0;
		SyncStep = 0;
		bFinalCorrect = 0;
		bEachCorrected = 0;
		
		for(k = 0; k < TrackBitFlow.Length; k ++)
		{
			if(DecodeTimes == 0)									    
			{
				i = k;
			}
			else														
			{
				i = TrackBitFlow.Length - (k + 1);
			}
			bData = TrackBitFlow.Value[i];
			if(bData == 2)												
			{
				bData = 0;
			}
			if(!bSyncHead)												
			{
				if (7 == (type & 0x0F))
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 0)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 1)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 0)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 0)
							{
								SyncStep = 6;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 6:
							if(bData == 1)							
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0x45;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(5 == (type & 0x0F))
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 1)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 0)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 1)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)											
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0x0B;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(6 == (type & 0x0F))											
				{
					switch (SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							} else {
								SyncStep = 0;
							}
							break;
						case 1:
							if(bData == 0)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							memset((uint8_t*)&TempTrackDirtData, 0, sizeof(TempTrackDirtData));
							memset((uint8_t*)&TempTrackData, 0, sizeof(TempTrackData));
							if(bData == 1 && 0x16 == type)							
							{
								TempTrackData.Value[0] = 0x05;
								SyncStep = 3;
							}
							else if(bData == 0 && 0x36 == type)						
							{
								TempTrackData.Value[0] = 0x01;
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 0)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 0)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 0)											
							{
								bSyncHead = 1;
								BitCnt = 0;
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
				else if(8 == (type & 0x0F))											
				{
					switch(SyncStep)
					{
						case 0:
							if(bData == 1)
							{
								SyncStep = 1;
							}
							break;
						case 1:
							if(bData == 1)
							{
								SyncStep = 2;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 2:
							if(bData == 1)
							{
								SyncStep = 3;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 3:
							if(bData == 1)
							{
								SyncStep = 4;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 4:
							if(bData == 1)
							{
								SyncStep = 5;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 5:
							if(bData == 1)
							{
								SyncStep = 6;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 6:
							if(bData == 1)
							{
								SyncStep = 7;
							}
							else
							{
								SyncStep = 0;
							}
							break;
						case 7:
							if(bData == 1)							
							{
								bSyncHead = 1;
								BitCnt = 0;
								memset((uint8_t*)&TempTrackDirtData,0,sizeof(TempTrackDirtData));
								memset((uint8_t*)&TempTrackData,0,sizeof(TempTrackData));
								TempTrackData.Value[0] = 0xff; 
								TempTrackData.Length = 1;
								TempTrackDirtData.Length = 1;
							}
							SyncStep = 0;
							break;
					}
				}
			}
			else
			{
				if(TrackBitFlow.Value[i] == 0)
				{
					ClearBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);		
				}
				else if(TrackBitFlow.Value[i] == 1)
				{
					SetBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);
				}
				else 
				{
					ClearBit(&TempTrackData.Value[TempTrackData.Length],BitCnt);
					SetBit(&TempTrackDirtData.Value[TempTrackDirtData.Length],BitCnt);
				}
				BitCnt ++;
				if (7 == (type & 0x0F))
				{
					BitCnt %= 7;
				}
				else if(5 == (type & 0x0F))
				{
					BitCnt %= 5;
				}
				else if(6 == (type & 0x0F))
				{
					BitCnt %= 6;
				}
				else if(8 == (type & 0x0F))
				{
					BitCnt %= 8;
				}
				
				if(BitCnt == 0)																
				{
					if (TempTrackData.Length < 110-1  )
					{
						TempTrackData.Length ++;
						TempTrackDirtData.Length ++;
					}
					else
					{
						break;
					}
				}
			}
		}

		type &= 0x0F;																		
		if(bSyncHead)																		
		{
			if(DecodeTimes == 0)
			{
				if (7 == type)
				{
					FirstBitCnt = TempTrackData.Length * 7;
				}
				else if(5 == type)
				{
					FirstBitCnt = TempTrackData.Length * 5;
				}
				else if(6 == type)
				{
					FirstBitCnt = TempTrackData.Length * 6;
				}
				else if(8 == type)
				{
					FirstBitCnt = TempTrackData.Length * 5;
				}
			}
			else
			{
				if (7 == type)
				{
					SndBitCnt = TempTrackData.Length * 7;
				}
				else if (5 == type)
				{
					SndBitCnt = TempTrackData.Length * 5;
				}
				else if (6 == type)
				{
					SndBitCnt = TempTrackData.Length * 6;
				}
				else if (8 == type)
				{
					SndBitCnt = TempTrackData.Length * 8;
				}
			}
			bFlag = 0;
			for(j = 0; (bFlag == 0) && (j < 2); j++)										
			{
				for(i = 1; i < TempTrackData.Length; i ++)
				{
					
					if (7 == type)
					{
						bData = 0x7F;
					}
					else if (6 == type)
					{
						bData = 0x3F;
					}
					else if (5 == type)
					{
						bData = 0x1F;
					}
					else if (8 == type)
					{
						bData = 0xFF;
					}
					if(
					((8 != type)&&((TempTrackData.Value[i] & bData) == 0x1F)) ||
					((8 == type)&&((TempTrackData.Value[i] & bData) == 0xFF))
					)																			
					{
						TempTrackData.Length = i + 2;											
						TempTrackDirtData.Length = i + 2;
						bFlag = 1;
						break;
					}
				}
				if(bFlag == 0 && j == 0 && 6 != type)											
				{
					for(i = 0; i < TempTrackData.Length; i ++)									
					{
						if(!CheckOddParity(TempTrackData.Value[i]))								
						{
							if(CheckDirtOnlyOne(TempTrackDirtData.Value[i]))
							{
								TempTrackData.Value[i] ^= TempTrackDirtData.Value[i]; 
								if (7 == type)
								{
									bData = 0x7F;
								}
								else if(5 == type)
								{
									bData = 0x1F;
								}
								else if(8 == type)
								{
									bData = 0xFF;
								}
								
								if(
								((8 != type)&&((TempTrackData.Value[i] & bData) == 0x1F)) ||
								((8 == type)&&((TempTrackData.Value[i] & 0xFF) == 0xFF))
								)						
								{
									bEachCorrected++;
									TempTrackDirtData.Value[i] = 0x00;							
									bFinalCorrect = 1;	
									break;
								}
								else
								{
									TempTrackData.Value[i] ^= TempTrackDirtData.Value[i];		
								}
							}
						}
					}
				}
			}
			if(bFlag == 1 && 6 != type)															
			{
				do
				{
					bCheckOk = 1;
					bCorrectDirt = 0;
					for(i = 0; i < TempTrackData.Length; i ++)									
					{
						if(!CheckOddParity(TempTrackData.Value[i]))								
						{
							if(DecodeTimes == 0)
							{
								if(FirstOkByteCnt < 8)							
								{
									FirstOkByteCnt = 0;
								}
							}
							else
							{
								if(SndOkByteCnt < 8)
								{
									SndOkByteCnt = 0;
								}
							}
							bCheckOk = 0;
							if(CheckDirtOnlyOne(TempTrackDirtData.Value[i]))
							{
								bEachCorrected++;
								TempTrackData.Value[i] ^= TempTrackDirtData.Value[i];
								TempTrackDirtData.Value[i] = 0x00;
								bCorrectDirt = 1;
								bFinalCorrect = 1;
							}
						}
						else																	
						{
							if(DecodeTimes == 0)
							{
								FirstOkByteCnt++;
							}
							else
							{
								SndOkByteCnt++;
							}
						}
					}
					if (7 == type)
					{
						bData = 6;
					}
					else if (5 == type)
					{
						bData = 4;
					}
					else if( 8 == type)
					{
						bData = 7;
					}
					for(i = 0; i < bData; i ++)
					{
						if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)i))					
						{
							bCheckOk = 0;
							if(CheckLrcDirtOnlyOne(&j,TempTrackDirtData.Value,TempTrackDirtData.Length,(uint8_t)i))	
							{
								bEachCorrected++;
								CplBit(&TempTrackData.Value[j],(uint8_t)i);
								ClearBit(&TempTrackDirtData.Value[j],(uint8_t)i);
								bCorrectDirt = 1;
								bFinalCorrect = 1;
							}
						}
					}
				}while(bCorrectDirt);
				if(!bCheckOk)																					
				{
					do																						
					{
						bCheckOk = 1;
						bCorrectDirt = 0;
						k = 0;
						m = 0;
						for(i = 0; i < TempTrackData.Length; i ++)									
						{
							if(!CheckOddParity(TempTrackData.Value[i]))								
							{
								bCheckOk = 0;
								k++;
								m = i;
								if (7 == type)
								{
									bData = 6;
								}
								else if (5 == type)
								{
									bData = 4;
								}
								else if (8 == type)
								{
									bData = 7;
								}
								
								for(j = 0; j < bData; j ++)
								{
									if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))					
									{
										bEachCorrected++;
										CplBit(&TempTrackData.Value[i],(uint8_t)j);
										bCorrectDirt = 1;
										bFinalCorrect = 1;
										break;
									}
								}
							}
						}
						if(k == 1 && bCorrectDirt == 0)										
						{
							if (7 == type)
							{
								bData = 6;
							}
							else if (5 == type)
							{
								bData = 4;
							}
							else if (8 == type)
							{
								bData = 7;
							}
							bEachCorrected++;
							CplBit(&TempTrackData.Value[m],bData);
							bCorrectDirt = 1;
							bFinalCorrect = 1;
						}
						if (7 == type)
						{
							bData = 6;
						}
						else if (5 == type)
						{
							bData = 4;
						}
						else if (8 == type)
						{
							bData = 7;
						}
						
						for(j = 0; j < bData; j ++)
						{
							if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))					
							{
								bCheckOk = 0;
								break;
							}
						}
					}while(bCorrectDirt);
				}
				
				if(bCheckOk && (bEachCorrected <= ((type == 5) ? 3 * 1: 1)))					
				{
					if(TempTrackData.Length >= 3)
					{
						bFlag = 0;
						for(i = 1; i < (TempTrackData.Length-2); i ++)										
						{
							if (5 == type)
								TempTrackData.Value[i] &= 0x0F;
							else
								break;
							if(bFinalCorrect == 1)															
							{
								if(!((TempTrackData.Value[i] <= 0x09) || TempTrackData.Value[i] == 0x0E  || TempTrackData.Value[i] == 0x0D  || TempTrackData.Value[i] == 0x0C))
								{
									bFlag = 1;
								}
							}
						}
						if(bFlag == 0)
						{
							if(DecodeTimes == 0)															   
							{
								for(i = 0; i < TempTrackData.Length; i++)										
								{
									if (7 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x3F) + 0x20;
									}
									else if (5 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x0F) + 0x30;
									}
									else if (8 == type)
									{
										lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x7F);
									}
								}
								lpOutTrackData->Length = TempTrackData.Length+1; 	
							}
							else
							{
								if(TempTrackData.Length > lpOutTrackData->Length)
								{
									for(i = 0; i < TempTrackData.Length; i++)										
									{
										if (7 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x3F) + 0x20;
										}
										else if( 5 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x0F) + 0x30;
										}
										else if( 8 == type)
										{
											lpOutTrackData->Value[i+1] = (TempTrackData.Value[i] & 0x7F);
										}
									}
									lpOutTrackData->Length = TempTrackData.Length+1;
								}									
							}
							bFinalSucc = 1;
						}
					}
				}
			} else if (bFlag == 1 && 6 == type) {
				bData = 6;
				bCheckOk = 0;
				for(j = 0; j < bData; j ++)
				{
					if(!CheckLrcEvenParity(TempTrackData.Value,TempTrackData.Length,(uint8_t)j))		
					{
						bCheckOk = 1;
						break;
					}
				}
				
				if (0 == bCheckOk) {																	
					if(DecodeTimes == 0)															   
					{
						for(i = 0; i < TempTrackData.Length; i++)										
						{
							lpOutTrackData->Value[i+1] = TempTrackData.Value[i] + 0x20;
						}
						lpOutTrackData->Length = TempTrackData.Length+1;
					}
					else
					{
						if(TempTrackData.Length > lpOutTrackData->Length)
						{
							for(i = 0; i < TempTrackData.Length; i++)										
							{
								lpOutTrackData->Value[i+1] = TempTrackData.Value[i] + 0x20;
							}
							lpOutTrackData->Length = TempTrackData.Length+1;
						}									
					}
					bFinalSucc = 1;
				}
			}
		}
	}
	if(bFinalSucc == 1)
	{
		if(lpOutTrackData->Length < 4 )
		{
			return 2;										
		}
		else
		{
			return 0;										
		}
	}
	else
	{
		if(((FirstOkByteCnt >= 8 && FirstBitCnt >= 100) || (SndOkByteCnt >= 8 && SndBitCnt >= 100)))
		{
			return 1;									
		}
		else
		{
			return 2;									
		}
	}
}








 
void InitMagDecode(void)
{
	memset((uint8_t*)&Track1TimeFlow, 0, sizeof(Track1TimeFlow));
	memset((uint8_t*)&Track2TimeFlow, 0, sizeof(Track2TimeFlow));
	memset((uint8_t*)&Track3TimeFlow, 0, sizeof(Track3TimeFlow));
	
	memset((uint8_t*)&TrackBitFlow, 0, sizeof(TrackBitFlow));

	memset((uint8_t*)&Track1Data, 0, sizeof(Track1Data));
	memset((uint8_t*)&Track2Data, 0, sizeof(Track2Data));
	memset((uint8_t*)&Track3Data, 0, sizeof(Track3Data));
}








 
uint8_t MagDecodeTrack(uint8_t type)
{
	uint8_t DecodeTimes, bFlag, bBrushError = 0;
	for(DecodeTimes = 0; DecodeTimes < 2; DecodeTimes++)
	{
		if(DecodeTimes == 1)
		{
			ResortMagData(type);						
		}
		if(DecodeTimeToBit(type))
		{
			bFlag = DecodeTrackData(type);
			if(bFlag == 0)
			{
				return 0;
			}
			else if(bFlag == 1)
			{
				bBrushError = 1;
			}
		}
	}
	if(bBrushError == 1)
	{
		return 1;
	}
	return 2;
}













 
 void FlushBuffer_Init (void)
{
	InitMagDecode();
	MSR_Check_Sync_Pattern();
}

















 
 void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level)
{
	
		switch (TrNo) {
			case 0:Track1TimeFlow.Value[Track1TimeFlow.Length++] = TmrCnt; break;
			case 1:Track2TimeFlow.Value[Track2TimeFlow.Length++] = TmrCnt; break;
			case 2:Track3TimeFlow.Value[Track3TimeFlow.Length++] = TmrCnt; break;
		}
	
}











 
 void MSR_Check_Sync_Pattern (void)
{
	MSR_fCardDataReady = 0;
	return;
}











 
 void MSR_F2F_Decoder (void)
{
	return;
}











 
 void MSR_Character_Decoder (void)
{
	if (Track1TimeFlow.Length > 20) {			
		MagDecodeTrack(1);						
	}
	
	if (Track2TimeFlow.Length > 20) {			
		MagDecodeTrack(2);						
	}
	
	if (Track3TimeFlow.Length > 20) {			
		MagDecodeTrack(3);						
	}
	return;
}











 
 unsigned char GetMSR_CardDataForUART (void)
{
	int i;
	if (Track1Data.Length > 2) {
		printf("TK1:");
		for (i = 2; i < Track1Data.Length - 2; i++) {
			printf("%c", Track1Data.Value[i]);
		}
		printf("\r\n");
	}
	
	if (Track2Data.Length > 2) {
		printf("TK2:");
		for (i = 2; i < Track2Data.Length - 2; i++) {
			printf("%c", Track2Data.Value[i]);
		}
		printf("\r\n");
	}
	
	if (Track3Data.Length > 2) {
		printf("TK3:");
		for (i = 2; i < Track3Data.Length - 2; i++) {
			printf("%c", Track3Data.Value[i]);
		}
		printf("\r\n");
	}
	
	return 0;
}












 
 void MSR_WaitForReady (void)
{
	MSR_fCardDataReady = 1;
}
















 
 int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length)
{
	int ret = 0;
	if (pBuf == 0) {
		return -3;
	}
	memset(pBuf, 0, length);
	switch (TrNo) {
		case 0:
			if (Track1TimeFlow.Length > 20) {					
				ret = MagDecodeTrack(0x17);						
				if (0 != ret) {									

					if (0 != ret) {
						ret = MagDecodeTrack(0x18);				
					}



					if (0 != ret) {
						ret = MagDecodeTrack(0x16);				
					}

				}
				if (0 == ret) {									
					Track1Data.Value[0] = 0x2B;					
					Track1Data.Length -= 2;						
					memcpy(pBuf, &Track1Data.Value[1], (Track1Data.Length - length < 0) ? Track1Data.Length : length);
					Track1Data.Length += 2;						
				}
			} else {
				ret = 2;
			}
			break;
		case 1:
			if (Track2TimeFlow.Length > 20) {					
				ret = MagDecodeTrack(0x25);						
				if (0 == ret) {									
					Track2Data.Value[0] = 0x2C;					
					Track2Data.Length -= 2;						
					memcpy(pBuf, &Track2Data.Value[1], (Track2Data.Length - length < 0) ? Track2Data.Length : length);
					Track2Data.Length += 2;						
				}
			} else {
				ret = 2;
			}
			break;
		case 2:
			if (Track3TimeFlow.Length > 20) {					
				ret = MagDecodeTrack(0x35);						
				if (0 != ret) {									

					if (0 != ret) {
						ret = MagDecodeTrack(0x37);				
					}


					if (0 != ret) {
						ret = MagDecodeTrack(0x36);				
					}

				}
				if (0 == ret) {									
					Track3Data.Value[0] = 0x2D;					
					Track3Data.Length -= 2;						
					memcpy(pBuf, &Track3Data.Value[1], (Track3Data.Length - length < 0) ? Track3Data.Length : length);
					Track3Data.Length += 2;						
				}
			} else {
				ret = 2;
			}
			break;
		default:
			ret = 3;
			break;
	}
	return (0 - ret);
}




