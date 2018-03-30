#line 1 "..\\user\\sha1.c"
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



 

#line 2 "..\\user\\sha1.c"
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



 



#line 3 "..\\user\\sha1.c"
#line 1 "..\\user\\sha1.h"



#line 5 "..\\user\\sha1.h"



 


struct _SHA1Context {
  uint64_t totalLength;
  uint32_t hash[5];
  uint32_t bufferLength;
  union {
    uint32_t words[16];
    uint8_t bytes[64];
  } buffer;



};

typedef struct _SHA1Context SHA1Context;





void SHA1Init (SHA1Context *sc);
void SHA1Update (SHA1Context *sc, const void *data, uint32_t len);
void SHA1Final (SHA1Context *sc, uint8_t hash[20]);





#line 4 "..\\user\\sha1.c"











#line 23 "..\\user\\sha1.c"








#line 37 "..\\user\\sha1.c"






static __inline uint64_t _byteswap64(uint64_t x)




{
  uint32_t a = x >> 32;
  uint32_t b = (uint32_t) x;
  return ((uint64_t) ((((((b)) >> (8)) | (((b)) << (32 - (8)))) & 0xff00ff00L) | (((((b)) << (8)) | (((b)) >> (32 - (8)))) & 0x00ff00ffL)) << 32) | (uint64_t) ((((((a)) >> (8)) | (((a)) << (32 - (8)))) & 0xff00ff00L) | (((((a)) << (8)) | (((a)) >> (32 - (8)))) & 0x00ff00ffL));
}



#line 100 "..\\user\\sha1.c"

static const uint8_t padding[64] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void
SHA1Init (SHA1Context *sc)
{




  sc->totalLength = 0LL;
  sc->hash[0] = 0x67452301L;
  sc->hash[1] = 0xefcdab89L;
  sc->hash[2] = 0x98badcfeL;
  sc->hash[3] = 0x10325476L;
  sc->hash[4] = 0xc3d2e1f0L;
  sc->bufferLength = 0L;
}

static void
burnStack (int size)
{
  char buf[128];

  memset (buf, 0, sizeof (buf));
  size -= sizeof (buf);
  if (size > 0)
    burnStack (size);
}

static void
SHA1Guts (SHA1Context *sc, const uint32_t *cbuf)
{
  uint32_t buf[80];
  uint32_t *W, *W3, *W8, *W14, *W16;
  uint32_t a, b, c, d, e, temp;
  int i;

  W = buf;

  for (i = 15; i >= 0; i--) {
    *(W++) = ((((((*cbuf)) >> (8)) | (((*cbuf)) << (32 - (8)))) & 0xff00ff00L) | (((((*cbuf)) << (8)) | (((*cbuf)) >> (32 - (8)))) & 0x00ff00ffL));
    cbuf++;
  }

  W16 = &buf[0];
  W14 = &buf[2];
  W8 = &buf[8];
  W3 = &buf[13];

  for (i = 63; i >= 0; i--) {
    *W = *(W3++) ^ *(W8++) ^ *(W14++) ^ *(W16++);
    *W = (((*W) << (1)) | ((*W) >> (32 - (1))));
    W++;
  }

  a = sc->hash[0];
  b = sc->hash[1];
  c = sc->hash[2];
  d = sc->hash[3];
  e = sc->hash[4];

  W = buf;





#line 322 "..\\user\\sha1.c"
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((d) ^ ((b) & ((c) ^ (d)))) + e + *(W++) + 0x5a827999L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };

  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0x6ed9eba1L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };

  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + (((b) & ((c) | (d))) | ((c) & (d))) + e + *(W++) + 0x8f1bbcdcL; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };

  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };
  { temp = (((a) << (5)) | ((a) >> (32 - (5)))) + ((b) ^ (c) ^ (d)) + e + *(W++) + 0xca62c1d6L; e = d; d = c; c = (((b) << (30)) | ((b) >> (32 - (30)))); b = a; a = temp; };




  sc->hash[0] += a;
  sc->hash[1] += b;
  sc->hash[2] += c;
  sc->hash[3] += d;
  sc->hash[4] += e;
}

void
SHA1Update (SHA1Context *sc, const void *vdata, uint32_t len)
{
  const uint8_t *data = vdata;
  uint32_t bufferBytesLeft;
  uint32_t bytesToCopy;
  int needBurn = 0;

#line 465 "..\\user\\sha1.c"
  while (len) {
    bufferBytesLeft = 64L - sc->bufferLength;

    bytesToCopy = bufferBytesLeft;
    if (bytesToCopy > len)
      bytesToCopy = len;

    memcpy (&sc->buffer.bytes[sc->bufferLength], data, bytesToCopy);

    sc->totalLength += bytesToCopy * 8L;

    sc->bufferLength += bytesToCopy;
    data += bytesToCopy;
    len -= bytesToCopy;

    if (sc->bufferLength == 64L) {
      SHA1Guts (sc, sc->buffer.words);
      needBurn = 1;
      sc->bufferLength = 0L;
    }
  }


  if (needBurn)
    burnStack (sizeof (uint32_t[86]) + sizeof (uint32_t *[5]) + sizeof (int));
}

void
SHA1Final (SHA1Context *sc, uint8_t hash[20])
{
  uint32_t bytesToPad;
  uint64_t lengthPad;
  int i;

  bytesToPad = 120L - sc->bufferLength;
  if (bytesToPad > 64L)
    bytesToPad -= 64L;

  lengthPad = _byteswap64(sc->totalLength);

  SHA1Update (sc, padding, bytesToPad);
  SHA1Update (sc, &lengthPad, 8L);

  if (hash) {
    for (i = 0; i < 5; i++) {



      hash[0] = (uint8_t) (sc->hash[i] >> 24);
      hash[1] = (uint8_t) (sc->hash[i] >> 16);
      hash[2] = (uint8_t) (sc->hash[i] >> 8);
      hash[3] = (uint8_t) sc->hash[i];

      hash += 4;
    }
  }
}

