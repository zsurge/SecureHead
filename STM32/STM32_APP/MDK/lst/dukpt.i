#line 1 "..\\user\\dukpt.c"
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



 

#line 2 "..\\user\\dukpt.c"
#line 1 "..\\user\\des.h"



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



 



#line 5 "..\\user\\des.h"




void des(uint8_t *datat, uint8_t *keyt, uint8_t encrypt);
void tri_des(uint8_t *dat, uint8_t *key1, uint8_t *key2, uint8_t mode);
void xor(uint8_t *sourceaddr, uint8_t *targetaddr, int length);



#line 3 "..\\user\\dukpt.c"
#line 1 "..\\user\\dukpt.h"







#line 16 "..\\user\\dukpt.h"



#line 29 "..\\user\\dukpt.h"












typedef  struct
{
    unsigned char   keytype;
    unsigned long   encrypt_ctr;
    unsigned char   future_key_reg[21][16 + 1];
    unsigned char   initKSN[10];
} dukpt_type;


extern unsigned char			gkeysize;
extern unsigned char			gfkeyregsize;
extern unsigned char			gLRC;



#line 66 "..\\user\\dukpt.h"

int  IDT_LoadInitKey(unsigned char isTDEA,unsigned char *pInitKey,unsigned char *pInitKSN);      
int IDT_EncryptPIN(unsigned char EncryptType,unsigned int encrypt_counter,unsigned char *pCurrKSN,unsigned char *pCurrKey,unsigned char PinKey);
void IDT_SpecialDEAEncrypt(unsigned char *cryptoReg,unsigned char *key);



unsigned int IDT_ChangeCounter(unsigned int encCntr, unsigned char onebit);
int IDT_GetNumOfOnes(unsigned int encCntr);
unsigned char IDT_CalcLRC (unsigned char *key);
void IDT_GenNewKeys( unsigned char *cryptoReg,unsigned int shiftReg,int currKeyPtr);
void IDT_NonReversibleKeyGen(unsigned char *cryptoReg,unsigned char *key);             
void IDT_PropogateKeys(unsigned char *cryptoReg,unsigned int shiftReg,int currKeyPtr);         
void IDT_InitCryptoReg(unsigned char *cyptoReg,unsigned int shiftReg,unsigned char *ksnReg);
void IDT_UpdateKSN(unsigned int encCntr,unsigned char *pKsnReg);
unsigned int IDT_SetBit(unsigned int reg,int pos);
int IDT_GetSetBitPos(unsigned int reg);

#line 4 "..\\user\\dukpt.c"
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
	unsigned char  Value[800];
	uint16_t Length;
}TRACKBITFLOW;

typedef struct _TRACKDATA 
{
	unsigned char Value[110];
	unsigned char Length;
}TRACKDATA;

extern TRACK1TIMEFLOW Track1TimeFlow;				
extern TRACK2TIMEFLOW Track2TimeFlow;				
extern TRACK3TIMEFLOW Track3TimeFlow;				

extern TRACKBITFLOW TrackBitFlow;					

extern TRACKDATA TempTrackDirtData,TempTrackData;	
extern TRACKDATA Track1Data,Track2Data,Track3Data;	











 
extern unsigned char MagDecodeTrack(unsigned char type);











 
extern void FlushBuffer_Init (void);
















 
extern void SetF2FInputBuffer (unsigned char TrNo, unsigned short int TmrCnt, unsigned char level);










 
extern void MSR_Check_Sync_Pattern (void);










 
extern void MSR_F2F_Decoder (void);










 
extern void MSR_Character_Decoder (void);










 
extern unsigned char GetMSR_CardDataForUART (void);











 
extern void MSR_WaitForReady (void);















 
extern int MSR_GetCharacterDataOn (unsigned char TrNo, unsigned char *pBuf, unsigned char length);





#line 5 "..\\user\\dukpt.c"




unsigned char gkeysize;					
unsigned char gfkeyregsize;
unsigned char gLRC;









int IDT_LoadInitKey(unsigned char isTDEA,         
                    unsigned char *pInitKey,      
                    unsigned char *pInitKSN)      
{
    unsigned int  i;
    unsigned int  currKeyPtr;         
    unsigned char   cryptoReg[16] = {0};  

    

    if (isTDEA) {
        gkeysize = 16;
        gfkeyregsize = 16 + 1;   
        gLRC = 16;               
    }
    else {
        gkeysize = 8;
        gfkeyregsize = 8 + 1;    
        gLRC = 8;                
    }

    
    for (i = 0; i < 21; i++)  memset(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[i], 0, (16 + 1));

    
    ((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr = 0;
    
    currKeyPtr = 20;
    
    memcpy(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr], pInitKey, gkeysize);
    
    memcpy(((dukpt_type *)Track3TimeFlow . Value)->initKSN, pInitKSN, 10);
    
    IDT_UpdateKSN(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);
    
    IDT_PropogateKeys(cryptoReg, (1L << 20), currKeyPtr);
    

    

    
    ((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr++;
    
    IDT_UpdateKSN(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);

    return 1;
}


































int IDT_EncryptPIN(unsigned char EncryptType,
							  unsigned int encrypt_counter,
                unsigned char *pCurrKSN,            
                unsigned char *pCurrKey,			  		
				unsigned char PinKey)			      
{
    int   position;                   
    int   currKeyPtr;                 
    unsigned int   shiftReg = 0;               
                                        

    
    unsigned char   cryptoReg[16] = {0};    

    if (((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr > 0x200000)
        return(-7);

    
    

    
    while (1)
    
    {
    
        
        position = IDT_GetSetBitPos(encrypt_counter);
        
        shiftReg = IDT_SetBit(shiftReg, position);
    
        
        currKeyPtr = position;
        
        memcpy (pCurrKey, ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr], gkeysize);
        
        if (((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr][gLRC] == IDT_CalcLRC(pCurrKey))
            
            break;
        else
        {
            
            ((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr += shiftReg;
        }
    }

	((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr = encrypt_counter;

    
    IDT_UpdateKSN(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);

	if(PinKey == 1)
	{
		if (EncryptType) 
		{
			 
			 
			 pCurrKey[16 - 1] ^= 0xFF;
			 pCurrKey[(16 / 2) - 1] ^= 0xFF;
		}
		else 
		{
				pCurrKey[8-1] ^= 0xFF;
		}
	}


	else if(PinKey == 0) 
	{
	   unsigned char key[16]; 
	   unsigned char i;
		if (EncryptType)
		{ 
			 
			 pCurrKey[16 - 3] ^= 0xFF;
			 pCurrKey[(16 >> 1) - 3] ^= 0xFF;
			 for(i = 0; i < 16; i++)
				 key[i] = pCurrKey[i];
			
			 tri_des(pCurrKey,key,key+8,0);
			 tri_des(pCurrKey+8,key,key+8,0);
		}
		else
		{ 
			pCurrKey[8 - 3] ^= 0xFF; 
			for(i = 0; i < 8; i++)
				key[i] = pCurrKey[i];
        
			des(pCurrKey, key,0);   
		}
	}

	else if(PinKey == 2) 
	{
		if (EncryptType) 
		{
			 
			 
			 pCurrKey[16 - 2] ^= 0xFF;
			 pCurrKey[(16 / 2) - 2] ^= 0xFF;
		}
		else 
		{
				pCurrKey[8-2] ^= 0xFF;
		}
	}

    
    memcpy(pCurrKSN, ((dukpt_type *)Track3TimeFlow . Value)->initKSN, 10);
    
    

    
    IDT_GenNewKeys(cryptoReg, shiftReg, currKeyPtr);



    return(1);
}





void IDT_GenNewKeys(unsigned char *cryptoReg,
                    unsigned int shiftReg,
                    int currKeyPtr)
{
    
    if (IDT_GetNumOfOnes(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr) < 10)
    {
        
        
        
        

        
        shiftReg >>= 1;
        IDT_PropogateKeys(cryptoReg, shiftReg, currKeyPtr);
        
        memset(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr], 0, (16 + 1));
        ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr][gLRC] = 0xff;
        
        ((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr++;
        IDT_UpdateKSN(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);
    }
    else
    {
        
        memset(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr], 0, (16 + 1));
        ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr][gLRC] = 0xff;        

        
        ((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr += shiftReg;
        IDT_UpdateKSN(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);
    }
}















void IDT_SpecialDEAEncrypt(unsigned char *cryptoReg,unsigned char *key)
{
    xor(cryptoReg, key, 16);
    des(cryptoReg, key, 0);   
    xor(cryptoReg, key, 16);
}








int IDT_GetSetBitPos(unsigned int reg)    
{
    unsigned int   pos;    
    unsigned int   mask;   

    
    for (pos = 0, mask = 0x01; pos < 21; pos++, mask <<= 1)
    {
        if (reg & mask)
            break;
    }

    return((21 - 1) - pos);
}







unsigned int IDT_SetBit(unsigned int reg,int pos)
{
    return (reg |= 1L << ((21 - 1) - pos));
}





unsigned char IDT_CalcLRC(unsigned char *key)
{
    unsigned int     i;
    unsigned char   aLRC;

    aLRC = *key;                                
    key++;                                      
    for (i = 0; i < (gkeysize) - 1; i++, key++)
    {
        aLRC ^= *key;                           
    }
    return aLRC;
}








void IDT_UpdateKSN(unsigned int encCntr,unsigned char *pKsnReg)
{
    pKsnReg[9] = (unsigned char)(encCntr & 0xFF);
    pKsnReg[8] = (unsigned char)((encCntr >> 8) & 0xFF);
    pKsnReg[7] = (pKsnReg[7] & 0xE0) | (unsigned char)((encCntr >> 16) & 0xFF);
}





int IDT_GetNumOfOnes(unsigned int encCntr)
{
    int i,numOfOnes = 0;
    unsigned int mask;

    
    for (i = 0, mask = 0x01; i < 21; i++, mask <<= 1)
    {
        if (encCntr & mask)
            numOfOnes++;
    }

    return(numOfOnes);
}





unsigned int IDT_ChangeCounter(unsigned int encCntr, unsigned char onebit)
{
    unsigned char    i, numOfOnes = 0;
    unsigned int   mask, tmp_mask;

    
    for (i = 0, mask = 0x100000, tmp_mask = 0x100000; (numOfOnes < onebit)&&(i < 21); i++)
    {
		if(i!=0)
		{
            mask >>= 1;
	    	tmp_mask += mask;
		}
        if (encCntr & mask)
            numOfOnes++;	
    }

	encCntr &= tmp_mask;

    return(encCntr);
}





void IDT_InitCryptoReg(unsigned char *cyptoReg,unsigned int shiftReg,unsigned char *ksnReg)
{
    unsigned int     i;
    unsigned char   buf1[8] = {0};
    unsigned char   buf2[8] = {0};

    
    for (i = 0; i < 3; i++) {
        buf1[(8 - 1) - i] =
            (unsigned char)((shiftReg >> (8 * i)) & 0xFF);;
    }

    
    memcpy(buf2, (ksnReg + 2), 8);

    
    for (i = 0; i < 8; i++) {
        cyptoReg[i] = buf1[i] | buf2[i];
    }
}





void IDT_PropogateKeys(unsigned char *cryptoReg,          
                       unsigned int shiftReg,           
                       int currKeyPtr)         
{
    int  posSR, posEC;
    unsigned char   *cr1, *cr2;
    unsigned char   *fkeyRegL, *fkeyRegR;
    unsigned char   swap1, swap2;

    cr1 = cryptoReg;
    cr2 = cryptoReg + 8;

    while (shiftReg)                     
    {
        
        IDT_InitCryptoReg(cryptoReg, shiftReg, ((dukpt_type *)Track3TimeFlow . Value)->initKSN);

#line 446 "..\\user\\dukpt.c"

        
        posSR = IDT_GetSetBitPos(shiftReg);
        swap1 = posSR % 2;
        fkeyRegL = ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[posSR];
        fkeyRegR = fkeyRegL + 8;

 
		if (1)
		{
		
            
            
            IDT_NonReversibleKeyGen(cryptoReg, ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr]);


            
            posEC = IDT_GetSetBitPos(((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr);
            swap2 = posEC % 2;
            if (((dukpt_type *)Track3TimeFlow . Value)->encrypt_ctr)
                swap2 ^= 1;
            else
                swap2 = 0;

            if (swap2)
                swap1 ^= 1;

            if (swap1) {
                
                memcpy(fkeyRegR, cr1, 8);
                memcpy(fkeyRegL, cr2, 8);
            }
            else {
                
                memcpy(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[posSR], cryptoReg, gkeysize);
            }





        }
        else {
            
            
            
            IDT_SpecialDEAEncrypt(cryptoReg, ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[currKeyPtr]);
            
            memcpy(((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[posSR], cryptoReg, gkeysize);
        }

        
        ((dukpt_type *)Track3TimeFlow . Value)->future_key_reg[posSR][gLRC] = IDT_CalcLRC(cryptoReg);

        
        shiftReg >>= 1;
    }
}
















void IDT_NonReversibleKeyGen(unsigned char *cryptoReg,       
                             unsigned char *key)             
{
    unsigned char *cr1, *cr2;
    unsigned char *keyL, *keyR;
    unsigned char cArray[] = {
        0xc0, 0xc0, 0xc0, 0xc0,
        0x00, 0x00, 0x00, 0x00,
        0xc0, 0xc0, 0xc0, 0xc0,
        0x00, 0x00, 0x00, 0x00
    };

    cr1 = cryptoReg;
    cr2 = cryptoReg + 8;
    keyL = key;
    keyR = key + 8;

    
    memcpy(cr2, cr1, 8);       
    xor(cr2, keyR, 8);
    


    des(cr2, keyL,0);   

    
    xor(cr2, keyR, 8);
    
    xor(key, cArray, 16);
    
    xor(cr1, keyR, 8);
    


    des(cr1, keyL,0);   
    
    xor(cr1, keyR, 8);
}

