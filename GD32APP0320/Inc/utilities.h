#define     uint8_t                   unsigned char
#define     int                  int
#define     uint32_t                  unsigned int

static uint8_t base64digits[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define BAD	0xFF
static uint8_t base64val[] = {
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD, 62, BAD,BAD,BAD, 63,
		52, 53, 54, 55,  56, 57, 58, 59,  60, 61,BAD,BAD, BAD,BAD,BAD,BAD,
		BAD,  0,  1,  2,   3,  4,  5,  6,   7,  8,  9, 10,  11, 12, 13, 14,
		15, 16, 17, 18,  19, 20, 21, 22,  23, 24, 25,BAD, BAD,BAD,BAD,BAD,
		BAD, 26, 27, 28,  29, 30, 31, 32,  33, 34, 35, 36,  37, 38, 39, 40,
		41, 42, 43, 44,  45, 46, 47, 48,  49, 50, 51,BAD, BAD,BAD,BAD,BAD
};
#define isascii(c)   ( (unsigned)(c) < 0x80 )
#define DECODE64(c)  (isascii(c) ? base64val[c] : BAD)


#define ET_DES_MS			0
#define ET_TDES_MS			1
#define ET_DES_DUKPT		2
#define ET_TDES_DUKPT		3
	

int from64tobits(uint8_t *out, uint8_t *in, int maxlen);
void to64frombits(uint8_t *out, uint8_t *in, int inlen);
void GetIK(uint8_t *pBKSN,uint8_t *pBDK,uint8_t *pBIK);
void GetKeyCkeckValue(uint8_t *pBKey, uint8_t *pBKCV,int iLength,int iEncryption);
int getEncodedLength(int EncodeLength);

