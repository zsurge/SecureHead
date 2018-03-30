#include <string.h>
#include <stdlib.h>
#include "des.h"
#include "utilities.h"

int getEncodedLength(int EncodeLength)
{
	int modulas = EncodeLength % 3;
	if(modulas == 0)
		return (EncodeLength/3)*4;
	else
		return ((EncodeLength/3)+1)*4;	
}


void to64frombits(uint8_t *out, uint8_t *in, int inlen)
{
    uint8_t fragment;
	for (; inlen >= 3; inlen -= 3)
    {
		*out++ = base64digits[in[0] >> 2];
		*out++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];
		*out++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
		*out++ = base64digits[in[2] & 0x3f];
		in += 3;
    }
    if (inlen > 0)
    {
		*out++ = base64digits[in[0] >> 2];
		fragment = (in[0] << 4) & 0x30;
		if (inlen > 1)
			fragment |= in[1] >> 4;
		*out++ = base64digits[fragment];
		*out++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
		*out++ = '=';
    }
    *out = '\0';
}

int from64tobits(uint8_t *out, uint8_t *in, int maxlen)
{
    int len = 0;
    uint8_t digit1, digit2, digit3, digit4;
	
    if (in[0] == '+' && in[1] == ' ')
		in += 2;
    if (*in == '\r')
		return(0);
	
    do {
		digit1 = in[0];
		if (DECODE64(digit1) == BAD)
			return(-1);
		digit2 = in[1];
		if (DECODE64(digit2) == BAD)
			return(-1);
		digit3 = in[2];
		if (digit3 != '=' && DECODE64(digit3) == BAD)
			return(-1); 
		digit4 = in[3];
		if (digit4 != '=' && DECODE64(digit4) == BAD)
			return(-1);
		in += 4;
		++len;
		if (maxlen && len > maxlen)
			return(-1);
		*out++ = (DECODE64(digit1) << 2) | (DECODE64(digit2) >> 4);
		if (digit3 != '=')
		{
			++len;
			if (maxlen && len > maxlen)
				return(-1);
			*out++ = ((DECODE64(digit2) << 4) & 0xf0) | (DECODE64(digit3) >> 2);
			if (digit4 != '=')
			{
				++len;
				if (maxlen && len > maxlen)
					return(-1);
				*out++ = ((DECODE64(digit3) << 6) & 0xc0) | DECODE64(digit4);
			}
		}
    } while 
		(*in && *in != '\r' && digit4 != '=');
	
    return (len);
}

void GetKeyCkeckValue(uint8_t *pBKey, uint8_t *pBKCV,int iLength,int iEncryption)
{
	uint8_t *pkey;
	uint8_t *block;
	
	pkey = (uint8_t *)malloc((sizeof(uint8_t))*iLength);
	memcpy(pkey,pBKey,iLength);

	block = (uint8_t *)malloc((sizeof(uint8_t))*iLength);
	memset(block,0,iLength);

	if (iEncryption == ET_TDES_MS || iEncryption == ET_TDES_DUKPT || iEncryption == ET_DES_DUKPT)
	{
		if(iLength/8 == 1) 
			tri_des(block,pkey,pkey+8,0);
		else
		{
			tri_des(block,pkey,pkey+8,0);
			tri_des(block+8,pkey,pkey+8,0);
		}
	}
	else if (iEncryption == ET_DES_MS )
	{
		if(iLength/8 == 1) 
			des(block,pkey,0);
		else
		{
			tri_des(block,pkey,pkey+8,0);
			tri_des(block+8,pkey,pkey+8,0);
		}
	}

	memcpy(pBKCV,block,3);

	free(pkey);
	free(block);
}

void GetXORKey(const unsigned char* pBKey1,const unsigned char* pBKey2,unsigned char* pBOutResult,int iLength)
{
	unsigned char*   bTemp;
	unsigned char ch1;
	unsigned char ch2;
	int loop = 0;
	bTemp = pBOutResult;
	for(loop = 0 ; loop < iLength; loop++)
	{
		ch1 = *(pBKey1 + loop);
		ch2 = *(pBKey2 + loop);
		*bTemp = (ch1)^(ch2);
		bTemp++;
	}
}

void GetIK(uint8_t *pBKSN,uint8_t *pBDK, uint8_t *pBIK)
{
	unsigned char tmpKEY[8];
	unsigned char TMP[16];
	unsigned char toXO[] = {0xc0,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0xc0,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00};
	memcpy(tmpKEY,pBKSN,8);
	tmpKEY[7] &= 0xE0;
	tri_des(tmpKEY,pBDK,pBDK+8,0);
	memcpy(pBIK,tmpKEY,8);
	GetXORKey(pBDK,toXO,TMP,16);
	memcpy(tmpKEY,pBKSN,8);
	tmpKEY[7] &= 0xE0;
	tri_des(tmpKEY,TMP,TMP+8,0);
	memcpy(pBIK + 8,tmpKEY,8);
}
