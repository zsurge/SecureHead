#include <string.h>
#include <stdint.h>
#include "sha1.h"
//#include "core_cm3.h"


#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

#define F_0_19(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define F_20_39(x, y, z) ((x) ^ (y) ^ (z))
#define F_40_59(x, y, z) (((x) & ((y) | (z))) | ((y) & (z)))
#define F_60_79(x, y, z) ((x) ^ (y) ^ (z))

#define DO_ROUND(F, K) { \
  temp = ROTL(a, 5) + F(b, c, d) + e + *(W++) + K; \
  e = d; \
  d = c; \
  c = ROTL(b, 30); \
  b = a; \
  a = temp; \
}

#define K_0_19 0x5a827999L
#define K_20_39 0x6ed9eba1L
#define K_40_59 0x8f1bbcdcL
#define K_60_79 0xca62c1d6L

#ifndef RUNTIME_ENDIAN

#ifdef WORDS_BIGENDIAN

#define BYTESWAP(x) (x)
#define BYTESWAP64(x) (x)

#else /* WORDS_BIGENDIAN */

#define BYTESWAP(x) ((ROTR((x), 8) & 0xff00ff00L) | \
		     (ROTL((x), 8) & 0x00ff00ffL))
#define BYTESWAP64(x) _byteswap64(x)

#if defined ( __CC_ARM   )
static __inline uint64_t _byteswap64(uint64_t x)
#else
#pragma inline
static uint64_t _byteswap64(uint64_t x)
#endif
{
  uint32_t a = x >> 32;
  uint32_t b = (uint32_t) x;
  return ((uint64_t) BYTESWAP(b) << 32) | (uint64_t) BYTESWAP(a);
}

#endif /* WORDS_BIGENDIAN */

#else /* !RUNTIME_ENDIAN */

#define BYTESWAP(x) _byteswap(sc->littleEndian, x)
#define BYTESWAP64(x) _byteswap64(sc->littleEndian, x)

#define _BYTESWAP(x) ((ROTR((x), 8) & 0xff00ff00L) | \
		      (ROTL((x), 8) & 0x00ff00ffL))
#define _BYTESWAP64(x) __byteswap64(x)

static inline uint64_t __byteswap64(uint64_t x)
{
  uint32_t a = x >> 32;
  uint32_t b = (uint32_t) x;
  return ((uint64_t) _BYTESWAP(b) << 32) | (uint64_t) _BYTESWAP(a);
}

static inline uint32_t _byteswap(int littleEndian, uint32_t x)
{
  if (!littleEndian)
    return x;
  else
    return _BYTESWAP(x);
}

static inline uint64_t _byteswap64(int littleEndian, uint64_t x)
{
  if (!littleEndian)
    return x;
  else
    return _BYTESWAP64(x);
}

static inline void setEndian(int *littleEndianp)
{
  union {
    uint32_t w;
    uint8_t b[4];
  } endian;

  endian.w = 1L;
  *littleEndianp = endian.b[0] != 0;
}

#endif /* !RUNTIME_ENDIAN */

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
#ifdef RUNTIME_ENDIAN
  setEndian (&sc->littleEndian);
#endif /* RUNTIME_ENDIAN */

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
    *(W++) = BYTESWAP(*cbuf);
    cbuf++;
  }

  W16 = &buf[0];
  W14 = &buf[2];
  W8 = &buf[8];
  W3 = &buf[13];

  for (i = 63; i >= 0; i--) {
    *W = *(W3++) ^ *(W8++) ^ *(W14++) ^ *(W16++);
    *W = ROTL(*W, 1);
    W++;
  }

  a = sc->hash[0];
  b = sc->hash[1];
  c = sc->hash[2];
  d = sc->hash[3];
  e = sc->hash[4];

  W = buf;

#ifndef SHA1_UNROLL
#define SHA1_UNROLL 20
#endif /* !SHA1_UNROLL */

#if SHA1_UNROLL == 1
  for (i = 19; i >= 0; i--)
    DO_ROUND(F_0_19, K_0_19);

  for (i = 19; i >= 0; i--)
    DO_ROUND(F_20_39, K_20_39);

  for (i = 19; i >= 0; i--)
    DO_ROUND(F_40_59, K_40_59);

  for (i = 19; i >= 0; i--)
    DO_ROUND(F_60_79, K_60_79);
#elif SHA1_UNROLL == 2
  for (i = 9; i >= 0; i--) {
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
  }

  for (i = 9; i >= 0; i--) {
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
  }

  for (i = 9; i >= 0; i--) {
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
  }

  for (i = 9; i >= 0; i--) {
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
  }
#elif SHA1_UNROLL == 4
  for (i = 4; i >= 0; i--) {
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
  }

  for (i = 4; i >= 0; i--) {
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
  }

  for (i = 4; i >= 0; i--) {
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
  }

  for (i = 4; i >= 0; i--) {
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
  }
#elif SHA1_UNROLL == 5
  for (i = 3; i >= 0; i--) {
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
  }

  for (i = 3; i >= 0; i--) {
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
  }

  for (i = 3; i >= 0; i--) {
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
  }

  for (i = 3; i >= 0; i--) {
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
  }
#elif SHA1_UNROLL == 10
  for (i = 1; i >= 0; i--) {
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
    DO_ROUND(F_0_19, K_0_19);
  }

  for (i = 1; i >= 0; i--) {
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
    DO_ROUND(F_20_39, K_20_39);
  }

  for (i = 1; i >= 0; i--) {
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
    DO_ROUND(F_40_59, K_40_59);
  }

  for (i = 1; i >= 0; i--) {
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
    DO_ROUND(F_60_79, K_60_79);
  }
#elif SHA1_UNROLL == 20
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);
  DO_ROUND(F_0_19, K_0_19);

  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);
  DO_ROUND(F_20_39, K_20_39);

  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);
  DO_ROUND(F_40_59, K_40_59);

  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
  DO_ROUND(F_60_79, K_60_79);
#else /* SHA1_UNROLL */
#error SHA1_UNROLL must be 1, 2, 4, 5, 10 or 20!
#endif

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

#ifdef SHA1_FAST_COPY
  if (sc->bufferLength) {
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

  while (len > 63) {
    sc->totalLength += 512L;

    SHA1Guts (sc, data);
    needBurn = 1;

    data += 64L;
    len -= 64L;
  }

  if (len) {
    memcpy (&sc->buffer.bytes[sc->bufferLength], data, len);

    sc->totalLength += len * 8L;

    sc->bufferLength += len;
  }
#else /* SHA1_FAST_COPY */
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
#endif /* SHA1_FAST_COPY */

  if (needBurn)
    burnStack (sizeof (uint32_t[86]) + sizeof (uint32_t *[5]) + sizeof (int));
}

void
SHA1Final (SHA1Context *sc, uint8_t hash[SHA1_HASH_SIZE])
{
  uint32_t bytesToPad;
  uint64_t lengthPad;
  int i;

  bytesToPad = 120L - sc->bufferLength;
  if (bytesToPad > 64L)
    bytesToPad -= 64L;

  lengthPad = BYTESWAP64(sc->totalLength);

  SHA1Update (sc, padding, bytesToPad);
  SHA1Update (sc, &lengthPad, 8L);

  if (hash) {
    for (i = 0; i < SHA1_HASH_WORDS; i++) {
#ifdef SHA1_FAST_COPY
      *((uint32_t *) hash) = BYTESWAP(sc->hash[i]);
#else /* SHA1_FAST_COPY */
      hash[0] = (uint8_t) (sc->hash[i] >> 24);
      hash[1] = (uint8_t) (sc->hash[i] >> 16);
      hash[2] = (uint8_t) (sc->hash[i] >> 8);
      hash[3] = (uint8_t) sc->hash[i];
#endif /* SHA1_FAST_COPY */
      hash += 4;
    }
  }
}

