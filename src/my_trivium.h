#ifndef MY_TRIVIUM_H
#define MY_TRIVIUM_H

#define MAXKEYSIZEB ((ECRYPT_MAXKEYSIZE + 7) / 8)
#define MAXIVSIZEB ((ECRYPT_MAXIVSIZE + 7) / 8)
#include "ecrypt-sync.h"

// int trivium_decrypt_file(char* infile, char* outfile, const u8 key[], const u8 iv[]);
int trivium_test_cipher(void);

void print_key(const u8 key[]);
void print_iv(const u8 iv[]);

#endif /* MY_TRIVIUM_H */
