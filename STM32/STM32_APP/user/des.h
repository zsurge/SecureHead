#ifndef _des_h
#define _des_h

#include <stdint.h>

//#define BYTE unsigned char

//void des(unsigned char *dat, unsigned char *key1, unsigned char mode);
void des(uint8_t *datat, uint8_t *keyt, uint8_t encrypt);
void tri_des(uint8_t *dat, uint8_t *key1, uint8_t *key2, uint8_t mode);
void xor(uint8_t *sourceaddr, uint8_t *targetaddr, int length);

#endif

