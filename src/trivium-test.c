#include "ecrypt-sync.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "my_trivium.h"

int main(int argc, char *argv[]) {
	if (argc != 4 && argc != 3 && argc != 1) {
		fprintf(stderr, "USAGE: %s input output [keyfile]\n", argv[0]);
		return 1;
	}
	
	if (argc == 1) {
		return trivium_test_cipher();
	} else {		
		u8 key[MAXKEYSIZEB] = "";
		u8 iv[MAXIVSIZEB] = "";
		
		if (argc == 4) {
			FILE *keyfile = fopen(argv[3], "rb");
			fread(key, 1, sizeof(key), keyfile);
			fread(iv, 1, sizeof(iv), keyfile);
			fclose(keyfile);
		}
		
		print_key(key);
		print_iv(iv);
		
		return trivium_decrypt_file(argv[1], argv[2], (const u8*)key, (const u8*)iv);
	}
}
