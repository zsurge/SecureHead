#ifndef _DUKPT_H_
#define _DUKPT_H_

#define     uint8_t                   unsigned char
//#define     int                  int
#define     uint32_t                  unsigned int

#define     DUKPT_ERR_UNDEFINED      0       /* Undefined error such as malloc failure, etc */
#define     DUKPT_ERR_BADPIN        -1      /* PIN number is invalid */
#define     DUKPT_ERR_BADACCT       -2      /* Account number is invalid */
#define     DUKPT_ERR_CHECKSUMACCT  -5      /* Account number fails check sum */
#define     DUKPT_ERR_BADKEY        -4      /* Invalid Dukpt Key */
#define     DUKPT_ERR_BADKSN        -6      /* Invalid Ksn Data */
#define     DUKPT_ERR_UNINITIALIZED -7      /* Initial Key not loaded */
#define     DUKPT_SUCCESS            1       /* No Error */

#define SWAP

#define SIZE_KSN_REG        10      // size of key serial number register
#define SIZE_KSN_MIN	    10		// min size
#define SIZE_KSN_MAX	    20		// max size
#define SIZE_ENC_CNTR       3       // size of encryption counter
#define SIZE_CRYP_REG       8       // size of crypto register (1 or 2)
#define SIZE_PIN_BLK        16      // pin block size
#define SIZE_3DES_KEY       16      // 3DES key size
#define SIZE_DES_KEY        8       // DES key size
#define NUM_FKEY_REG        21		// # of future key registers
#define NUM_BITS_EC         21      // # of valid bits in encryption counter

#define MAX_EC              0x200000

#define BIT_1               (1L << 20)
#define BIT_21              (1L <<  0)

#define REG_1               0
#define REG_21              20

//#define TRUE				1
//#define FALSE				0

typedef  struct
{
    unsigned char   keytype;
    unsigned long   encrypt_ctr;
    unsigned char   future_key_reg[NUM_FKEY_REG][SIZE_3DES_KEY + 1];
    unsigned char   initKSN[SIZE_KSN_REG];
} dukpt_type;

//extern dukpt_type	dukpt_key;
extern uint8_t			gkeysize;
extern uint8_t			gfkeyregsize;
extern uint8_t			gLRC;

#define SWAP

#define SIZE_KSN_REG        10      // size of key serial number register
#define SIZE_KSN_MIN	    10		// min size
#define SIZE_KSN_MAX	    20		// max size
#define SIZE_ENC_CNTR       3       // size of encryption counter
#define SIZE_CRYP_REG       8       // size of crypto register (1 or 2)
#define SIZE_PIN_BLK        16      // pin block size
#define SIZE_3DES_KEY       16      // 3DES key size
#define SIZE_DES_KEY        8       // DES key size
#define NUM_FKEY_REG        21		// # of future key registers
#define NUM_BITS_EC         21      // # of valid bits in encryption counter

int  IDT_LoadInitKey(uint8_t isTDEA,uint8_t *pInitKey,uint8_t *pInitKSN);      // init key serial number in binary
int IDT_EncryptPIN(uint8_t EncryptType,uint32_t encrypt_counter,uint8_t *pCurrKSN,uint8_t *pCurrKey,uint8_t PinKey);// returns encrypted PIN, 16 hex digits
void IDT_SpecialDEAEncrypt(uint8_t *cryptoReg,uint8_t *key);



unsigned int IDT_ChangeCounter(uint32_t encCntr, uint8_t onebit);
int IDT_GetNumOfOnes(uint32_t encCntr);
uint8_t IDT_CalcLRC (uint8_t *key);
void IDT_GenNewKeys( uint8_t *cryptoReg,uint32_t shiftReg,int currKeyPtr);
void IDT_NonReversibleKeyGen(uint8_t *cryptoReg,uint8_t *key);             // key register
void IDT_PropogateKeys(uint8_t *cryptoReg,uint32_t shiftReg,int currKeyPtr);         // current key pointer
void IDT_InitCryptoReg(uint8_t *cyptoReg,uint32_t shiftReg,uint8_t *ksnReg);
void IDT_UpdateKSN(uint32_t encCntr,uint8_t *pKsnReg);
uint32_t IDT_SetBit(uint32_t reg,int pos);
int IDT_GetSetBitPos(uint32_t reg);

#endif  /* _DUKPT_H_ */
