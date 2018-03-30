#include <string.h>
#include "des.h"
#include "dukpt.h"
#include "magdecode.h"

//dukpt_type  dukpt_key  __attribute__((at(Track3TimeFlow.Value)));
#define dukpt_key ((dukpt_type *)Track3TimeFlow.Value)
//dukpt_type dukpt_key = ((dukpt_type *)Track3TimeFlow.Value);
uint8_t gkeysize;					
uint8_t gfkeyregsize;
uint8_t gLRC;

//-----------------------------------------------------------------------------
// IDT_LoadInitKey:
// Initialize key serial number register with initial KSN value and 0 initial
// encryption counter value. Populate future key registers using the initial
// key.
// Note: values are passed to IDT_xxx routines in binary, with each byte
// containing 2 hex digit.
//-----------------------------------------------------------------------------
int IDT_LoadInitKey(uint8_t isTDEA,         // indicate whether the key is single or double-length
                    uint8_t *pInitKey,      // init key in binary
                    uint8_t *pInitKSN)      // init key serial number in binary
{
    uint32_t  i;
    uint32_t  currKeyPtr;         // current key pointer
    uint8_t   cryptoReg[SIZE_PIN_BLK] = {0};  // crypto register

    // Set global flag whether we will be doing single DES or triple DES.

    if (isTDEA) {
        gkeysize = SIZE_3DES_KEY;
        gfkeyregsize = SIZE_3DES_KEY + 1;   // key size + 1 byte of LRC
        gLRC = SIZE_3DES_KEY;               // LRC byte follows the key
    }
    else {
        gkeysize = SIZE_DES_KEY;
        gfkeyregsize = SIZE_DES_KEY + 1;    // key size + 1 byte of LRC
        gLRC = SIZE_DES_KEY;                // LRC byte follows the key
    }

    // Init all future key registers to zeros
    for (i = 0; i < NUM_FKEY_REG; i++)  memset(dukpt_key->future_key_reg[i], 0, (SIZE_3DES_KEY + 1));

    // clear encryption counter
    dukpt_key->encrypt_ctr = 0;
    // put address of key Reg #21 in CKP
    currKeyPtr = REG_21;
    // store initial key in future key reg #21
    memcpy(dukpt_key->future_key_reg[currKeyPtr], pInitKey, gkeysize);
    // copy initial key serial number to key serial num reg
    memcpy(dukpt_key->initKSN, pInitKSN, SIZE_KSN_REG);
    // update counter in key serial num reg
    IDT_UpdateKSN(dukpt_key->encrypt_ctr, dukpt_key->initKSN);
    // generate new keys, setting bit #1 in shift reg
    IDT_PropogateKeys(cryptoReg, BIT_1, currKeyPtr);
    // clear current key pointed to
//    memset(dukpt_key->future_key_reg[currKeyPtr], 0, (SIZE_3DES_KEY + 1));
    // set LRC to invalid value
//    dukpt_key->future_key_reg[currKeyPtr][gLRC] = 0xff;
    // increment encryption counter
    dukpt_key->encrypt_ctr++;
    // update counter in key serial num
    IDT_UpdateKSN(dukpt_key->encrypt_ctr, dukpt_key->initKSN);

    return DUKPT_SUCCESS;
}

//-----------------------------------------------------------------------------
// IDT_EncryptPIN:
// Encrypt the PIN block which is created by XOR the PIN number and account
// number by using the DUKPT algorithm. After the encryption is performed,
// a new set of future keys are created and the key used for encryption is
// deleted.
// This function take 2 inputs, a PIN and account number.
// Plain text PINs have the following structure:
// 1---5---9---13--17--21--25--29--33--37--41--45--49--53--57--61---
// | C | N | P | P | P | P | PF| PF| PF| PF| PF| PF| PF| PF| F | F |
// -----------------------------------------------------------------
// Where    C => Control field. 0000.
//          N => PIN Length: [0100..1100] (4 to 12)
//          P => PIN Digit [0000..1001] (1 to 9)
//          PF=> PIN Digit or Fill digit, according to length
//          F => Fill Digit. 1111.
// For example, given a PIN of 1234, the input to pPIN should be:
//     0x04, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF;
// Primary Account Numbers have the following Structure:
// 1---5---9---13--17--21--25--29--33--37--41--45--49--53--57--61---
// | 0 | 0 | 0 | 0 | A1| A2| A3| A4| A5| A6| A7| A8| A9|A10|A11|A12|
// -----------------------------------------------------------------
// Where    0 => Pad Digit. 0000.
//          An=> Primary Account number. The twelve rightmost digits
//               of the primary account number excluding the check digit,
//               which is the last digit.
//
// For example, given an account number of 401234567890, the input to pAcctNum
// should be:
//    0x00, 0x00, 0x40, 0x12, 0x34, 0x56, 0x78, 0x90.
// The current value of KSN is returned in pCurrKSN, while the encrypted PIN
// is returned in pCiphorPin.
//-----------------------------------------------------------------------------
int IDT_EncryptPIN(uint8_t EncryptType,
							  uint32_t encrypt_counter,
                uint8_t *pCurrKSN,            // returns the 10-byte KSN
                uint8_t *pCurrKey,			  		// returns encrypted PIN, 16 hex digits
				uint8_t PinKey)			      // returns encrypted PIN, 16 hex digits
{
    int   position;                   // position of right most set bit
    int   currKeyPtr;                 // current key pointer
    uint32_t   shiftReg = 0;               // shift register: 21-bit reg, whose bits are
                                        // numbered left to right as #1 to #21.

    //uint8_t   currKey[SIZE_3DES_KEY];     // current key used to encrypt
    uint8_t   cryptoReg[SIZE_PIN_BLK] = {0};    // crypto register

    if (dukpt_key->encrypt_ctr > MAX_EC)
        return(DUKPT_ERR_UNINITIALIZED);

    //Copy pinblock into crypto reg
    //memcpy(cryptoReg, pPinBlock, SIZE_CRYP_REG);

    // Get a valid key
    while (1)
    // While LRC of current key is not valid
    {
    
        // Find position of right most set bit in encryption counter
        position = IDT_GetSetBitPos(encrypt_counter);
        // set the corresponding bit in shift reg
        shiftReg = IDT_SetBit(shiftReg, position);
    
        // set current key pointer
        currKeyPtr = position;
        // Get key pointed by the current key pointer
        memcpy (pCurrKey, dukpt_key->future_key_reg[currKeyPtr], gkeysize);
        // Check if LRC key valid
        if (dukpt_key->future_key_reg[currKeyPtr][gLRC] == IDT_CalcLRC(pCurrKey))
            // OK, we've found a valid key
            break;
        else
        {
            // Nope, add shift reg to encryption counter and continue
            dukpt_key->encrypt_ctr += shiftReg;
        }
    }

	dukpt_key->encrypt_ctr = encrypt_counter;

    // Update counter in key serial num
    IDT_UpdateKSN(dukpt_key->encrypt_ctr, dukpt_key->initKSN);

	if(PinKey == 1)
	{
		if (EncryptType) 
		{
			 // Now produce a variant of the key by XORing the
			 // key with 0000 0000 0000 00FF 0000 0000 0000 00FF
			 pCurrKey[SIZE_3DES_KEY - 1] ^= 0xFF;
			 pCurrKey[(SIZE_3DES_KEY / 2) - 1] ^= 0xFF;
		}
		else 
		{
				pCurrKey[SIZE_DES_KEY-1] ^= 0xFF;
		}
	}


	else if(PinKey == 0) // Data Key
	{
	   uint8_t key[SIZE_3DES_KEY]; 
	   uint8_t i;
		if (EncryptType)
		{ // If 1, TDES
			 // Now produce a variant of the key by XORing the key with 0000 0000 00FF 0000 0000 0000 00FF 0000
			 pCurrKey[SIZE_3DES_KEY - 3] ^= 0xFF;
			 pCurrKey[(SIZE_3DES_KEY >> 1) - 3] ^= 0xFF;
			 for(i = 0; i < SIZE_3DES_KEY; i++)
				 key[i] = pCurrKey[i];
			
			 tri_des(pCurrKey,key,key+8,0);
			 tri_des(pCurrKey+8,key,key+8,0);
		}
		else
		{ // If 0, Single DES
			pCurrKey[SIZE_DES_KEY - 3] ^= 0xFF; // Only 8 bits
			for(i = 0; i < SIZE_DES_KEY; i++)
				key[i] = pCurrKey[i];
        
			des(pCurrKey, key,0);   //single encryption
		}
	}

	else if(PinKey == 2) // MAC
	{
		if (EncryptType) 
		{
			 // Now produce a variant of the key by XORing the
			 // key with 0000 0000 0000 00FF 0000 0000 0000 00FF
			 pCurrKey[SIZE_3DES_KEY - 2] ^= 0xFF;
			 pCurrKey[(SIZE_3DES_KEY / 2) - 2] ^= 0xFF;
		}
		else 
		{
				pCurrKey[SIZE_DES_KEY-2] ^= 0xFF;
		}
	}

    // Return the current KSN
    memcpy(pCurrKSN, dukpt_key->initKSN, SIZE_KSN_REG);
    // Return the encrypted ciphor test PIN
    //memcpy(pCiphorPin, cryptoReg, SIZE_CRYP_REG);

    // Generate new future keys and delete current encrypt key
    IDT_GenNewKeys(cryptoReg, shiftReg, currKeyPtr);
//    dukpt_key = init_dukpt_key();
//    save_dukpt_key(dukpt_key);

    return(DUKPT_SUCCESS);
}

//-----------------------------------------------------------------------------
// IDT_GenNewKeys:
// Generate new future keys.
//-----------------------------------------------------------------------------
void IDT_GenNewKeys(uint8_t *cryptoReg,
                    uint32_t shiftReg,
                    int currKeyPtr)
{
    // if the number of 1 bits in encryption counter is less than 10
    if (IDT_GetNumOfOnes(dukpt_key->encrypt_ctr) < 10)
    {
        // Generating new keys:
        // new keys are generated by performing 3DES encryption using the current
        // key on the KSN whose encryption counter contains the same bit pattern
        // less the right most "1" bit:

        // Generate a set of new keys
        shiftReg >>= 1;
        IDT_PropogateKeys(cryptoReg, shiftReg, currKeyPtr);
        // Erase current key from memory
        memset(dukpt_key->future_key_reg[currKeyPtr], 0, (SIZE_3DES_KEY + 1));
        dukpt_key->future_key_reg[currKeyPtr][gLRC] = 0xff;
        // Increment encryption counter and update it in key serial num register
        dukpt_key->encrypt_ctr++;
        IDT_UpdateKSN(dukpt_key->encrypt_ctr, dukpt_key->initKSN);
    }
    else
    {
        // Erase current key from memory
        memset(dukpt_key->future_key_reg[currKeyPtr], 0, (SIZE_3DES_KEY + 1));
        dukpt_key->future_key_reg[currKeyPtr][gLRC] = 0xff;        // set LRC to invalid value

        // Increment encryption counter and update it in key serial num register
        dukpt_key->encrypt_ctr += shiftReg;
        IDT_UpdateKSN(dukpt_key->encrypt_ctr, dukpt_key->initKSN);
    }
}

//-----------------------------------------------------------------------------
// IDT_SpecialDEAEncrypt
//
// input: 8byte clear text PIN
//
// output: 8Byte Encrypted PIN
//
// Dukpt algorithm defines a "special encrypt routine" which
// treats the key not as a 56-bit key with parity but a
// 64-bit key. To achieve an added level of security the key
// itself is xor'ed into the pinblock before and after the
// dea encryption.
//
//-----------------------------------------------------------------------------
void IDT_SpecialDEAEncrypt(uint8_t *cryptoReg,uint8_t *key)
{
    xor(cryptoReg, key, SIZE_PIN_BLK);
    des(cryptoReg, key, 0);   //single encryption
    xor(cryptoReg, key, SIZE_PIN_BLK);
}

//-----------------------------------------------------------------------------
// IDT_GetSetBitPos
// Return the position of least significant set bit in the 21-bit encryption
// counter.
// Note: the position of a bit is counted from left to right, so bit 0 has a
// position of 20, while bit 20 has a position of 20.
//-----------------------------------------------------------------------------
int IDT_GetSetBitPos(uint32_t reg)    // curent value of register
{
    uint32_t   pos;    // position of set bit
    uint32_t   mask;   // running mask of set bit

    // Run the bit mask from right to left until we hit a set bit
    for (pos = 0, mask = 0x01; pos < NUM_BITS_EC; pos++, mask <<= 1)
    {
        if (reg & mask)
            break;
    }

    return((NUM_BITS_EC - 1) - pos);
}

//-----------------------------------------------------------------------------
// IDT_SetBit
// Sets bit in the 21 bit register reg accoring to pos.
// Note: the position of a bit is counted from left to right, so bit 0 has a
// position of 20, while bit 20 has a position of 20.
//-----------------------------------------------------------------------------
uint32_t IDT_SetBit(uint32_t reg,int pos)
{
    return (reg |= 1L << ((NUM_BITS_EC - 1) - pos));
}

//-----------------------------------------------------------------------------
// IDT_CalcLRC
// Calc the LRC of key.
//-----------------------------------------------------------------------------
uint8_t IDT_CalcLRC(uint8_t *key)
{
    uint32_t     i;
    uint8_t   aLRC;

    aLRC = *key;                                // set LRC to 1st byte of key
    key++;                                      // increment key
    for (i = 0; i < (gkeysize) - 1; i++, key++)
    {
        aLRC ^= *key;                           // XOR key with LRC
    }
    return aLRC;
}

//-----------------------------------------------------------------------------
//  IDT_UpdateKSN:
//  Update the key serial number register (KSN) with the current value of the
//  encryption counter. Note that the left-most 59 bits of the KSN are the
//  59 right-most bits of the initial serial number itself, and the 21
//  rightmost bits of KSN are the curent value of encryption counter.
//-----------------------------------------------------------------------------
void IDT_UpdateKSN(uint32_t encCntr,uint8_t *pKsnReg)
{
    pKsnReg[9] = (uint8_t)(encCntr & 0xFF);
    pKsnReg[8] = (uint8_t)((encCntr >> 8) & 0xFF);
    pKsnReg[7] = (pKsnReg[7] & 0xE0) | (uint8_t)((encCntr >> 16) & 0xFF);
}

//-----------------------------------------------------------------------------
//  IDT_GetNumOfOnes
//  Return the number of ones in the encryption counter.
//-----------------------------------------------------------------------------
int IDT_GetNumOfOnes(uint32_t encCntr)
{
    int i,numOfOnes = 0;
    uint32_t mask;

    // For each bit in encryption counter
    for (i = 0, mask = 0x01; i < 21; i++, mask <<= 1)
    {
        if (encCntr & mask)
            numOfOnes++;
    }

    return(numOfOnes);
}

//-----------------------------------------------------------------------------
//  IDT_ChangeCounter
//  Return the number of ones in the encryption counter.
//-----------------------------------------------------------------------------
unsigned int IDT_ChangeCounter(uint32_t encCntr, uint8_t onebit)
{
    uint8_t    i, numOfOnes = 0;
    uint32_t   mask, tmp_mask;

    // For each bit in encryption counter
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
//-----------------------------------------------------------------------------
//  IDT_InitCryptoReg
//  Initialize the crypto reg by or'ing
//  the rightmost 64 bits of the ksn with the shift counter.
//-----------------------------------------------------------------------------
void IDT_InitCryptoReg(uint8_t *cyptoReg,uint32_t shiftReg,uint8_t *ksnReg)
{
    uint32_t     i;
    uint8_t   buf1[SIZE_CRYP_REG] = {0};
    uint8_t   buf2[SIZE_CRYP_REG] = {0};

    // Put the value of shift reg into the right most 3 bytes of temp buf 1
    for (i = 0; i < 3; i++) {
        buf1[(SIZE_CRYP_REG - 1) - i] =
            (uint8_t)((shiftReg >> (8 * i)) & 0xFF);;
    }

    // Put the right 8 bytes of key serial num into temp buf 2
    memcpy(buf2, (ksnReg + 2), SIZE_CRYP_REG);

    // OR them togather
    for (i = 0; i < SIZE_CRYP_REG; i++) {
        cyptoReg[i] = buf1[i] | buf2[i];
    }
}

//-----------------------------------------------------------------------------
//  IDT_PropogateKeys
//  Generate descendent keys of a particular key.
//-----------------------------------------------------------------------------
void IDT_PropogateKeys(uint8_t *cryptoReg,          // crypto register
                       uint32_t shiftReg,           // shift register
                       int currKeyPtr)         // current key pointer
{
    int  posSR, posEC;
    uint8_t   *cr1, *cr2;
    uint8_t   *fkeyRegL, *fkeyRegR;
    uint8_t   swap1, swap2;

    cr1 = cryptoReg;
    cr2 = cryptoReg + SIZE_CRYP_REG;

    while (shiftReg)                     // do while shift reg no zero
    {
        // Init cyrpto reg by ORing lower 64 bits of KSN with shift reg
        IDT_InitCryptoReg(cryptoReg, shiftReg, dukpt_key->initKSN);

#if(0)
        if (debug) {
            if (outFile)
                fprintf(fp, "EC = %02X%02X%02X ",
                        cryptoReg[5] & 0x1F, cryptoReg[6], cryptoReg[7]);
            else
                printf("EC = %02X%02X%02X ",
                       cryptoReg[5] & 0x1F, cryptoReg[6], cryptoReg[7]);
        }
#endif // DBG

        // find position of least significant set bit in shift reg
        posSR = IDT_GetSetBitPos(shiftReg);
        swap1 = posSR % 2;
        fkeyRegL = dukpt_key->future_key_reg[posSR];
        fkeyRegR = fkeyRegL + SIZE_CRYP_REG;

 //       if (dukpt_key->keytype) {
		if (1)
		{
		
            // if we use double length key, geneate a new double length key using
            // this folloiwng call:
            IDT_NonReversibleKeyGen(cryptoReg, dukpt_key->future_key_reg[currKeyPtr]);

#ifdef SWAP
            // find position of least significant set bit in encryption counter
            posEC = IDT_GetSetBitPos(dukpt_key->encrypt_ctr);
            swap2 = posEC % 2;
            if (dukpt_key->encrypt_ctr)
                swap2 ^= 1;
            else
                swap2 = 0;

            if (swap2)
                swap1 ^= 1;

            if (swap1) {
                // HACK: swap upper and lower 8 bytes
                memcpy(fkeyRegR, cr1, SIZE_CRYP_REG);
                memcpy(fkeyRegL, cr2, SIZE_CRYP_REG);
            }
            else {
                // copy new key into future key reg pointed by this position
                memcpy(dukpt_key->future_key_reg[posSR], cryptoReg, gkeysize);
            }
#else
            // copy new key into the future key reg pointed by this position
            memcpy(dukpt_key->future_key_reg[posSR], cryptoReg, gkeysize);
#endif

        }
        else {
            // if we use single length key, generate a new single length key
            // using the follwing call which use all 64-bit when generating
            // key
            IDT_SpecialDEAEncrypt(cryptoReg, dukpt_key->future_key_reg[currKeyPtr]);
            // copy new key into the future key reg pointed by this position
            memcpy(dukpt_key->future_key_reg[posSR], cryptoReg, gkeysize);
        }

        // calc LRC and store with new key
        dukpt_key->future_key_reg[posSR][gLRC] = IDT_CalcLRC(cryptoReg);

        // shift sr right 1 bit
        shiftReg >>= 1;
    }
}

//-----------------------------------------------------------------------------
// IDT_NonReversibleKeyGen:
// Generate a new double-length key .
// Input:
// --cyrpto reg contains 16-byte data to be encrypted.
// --key reg contains the double length key used for encryption.
// Output:
// --crypto reg contains newly generate double length key.
// CR-1: crypto reg 1 (8 bytes)
// CR-2: crypto reg 2 (8 bytes)
// KR-L: left half of key reg
// KR-R: right half of key reg
// DEAen(data, key): apply DEA encryption on "data" using "key"
// DEAde(data, key): apply DEA decryption on "data" using "key"
//-----------------------------------------------------------------------------
void IDT_NonReversibleKeyGen(uint8_t *cryptoReg,       // crypto register
                             uint8_t *key)             // key register
{
    uint8_t *cr1, *cr2;
    uint8_t *keyL, *keyR;
    uint8_t cArray[] = {
        0xc0, 0xc0, 0xc0, 0xc0,
        0x00, 0x00, 0x00, 0x00,
        0xc0, 0xc0, 0xc0, 0xc0,
        0x00, 0x00, 0x00, 0x00
    };

    cr1 = cryptoReg;
    cr2 = cryptoReg + SIZE_CRYP_REG;
    keyL = key;
    keyR = key + SIZE_CRYP_REG;

    // CR-2 = CR-1 xor KR-R
    memcpy(cr2, cr1, SIZE_CRYP_REG);       // copy content of CR-1 to CR-2
    xor(cr2, keyR, SIZE_CRYP_REG);
    // CR-2 = DEAen(CR-2, KR-L)

//    encrypt(SIZE_CRYP_REG, cr2, keyL);
    des(cr2, keyL,0);   //single encryption

    // CR-2 = CR-2 xor KR-R
    xor(cr2, keyR, SIZE_CRYP_REG);
    // KR = KR xor c0c0 c0c0 0000 0000 c0c0 c0c0 0000 0000
    xor(key, cArray, SIZE_3DES_KEY);
    // CR-1 = CR-1 xor KR-R
    xor(cr1, keyR, SIZE_CRYP_REG);
    // CR-1 = DEAen(CR-1, KR-L)

//    encrypt(SIZE_CRYP_REG, cr1, keyL);
    des(cr1, keyL,0);   //single encryption
    // CR-1 = CR-1 xor KR-R
    xor(cr1, keyR, SIZE_CRYP_REG);
}

