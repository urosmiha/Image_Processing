#define USE_FPGA 0
#define USE_FIFO 0

#include "my_trivium.h"

#define DEBUG 0

// A mess of includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <math.h>

#include <time.h>

#include "trivium.c"

int test_trivium(void) {
    #define LEN 32
    ECRYPT_ctx ctx;
    const u8 key[MAXKEYSIZEB] = "Test key01";
    const u8 iv[MAXIVSIZEB] = "So Random\0";
    //const u8 input[LEN] = "Test input 12345";
    const u8 input[LEN] = "#include \"ecrypt-sync.h\"\r\n#inclu";
    //const u8 input[LEN] = "";
    u8 output[LEN];
    u8 second[LEN];
    int passed = 1;
    int i;

    ECRYPT_init();

    ECRYPT_keysetup(&ctx, key, ECRYPT_MAXKEYSIZE, ECRYPT_MAXIVSIZE);
    ECRYPT_ivsetup(&ctx, iv);
    ECRYPT_encrypt_blocks(&ctx, input, output, (LEN/ECRYPT_BLOCKLENGTH));

    // Use the same key, but need to re setup the iv
    ECRYPT_ivsetup(&ctx, iv);
    ECRYPT_encrypt_blocks(&ctx, output, second, (LEN/ECRYPT_BLOCKLENGTH));

    printf("Testing...\n");
    printf("Key: ");

    for (i=0; i<MAXKEYSIZEB; ++i) {
        printf("%02x", key[i]);
    }

    printf("\n");
    printf("IV: ");

    for (i=0; i<MAXIVSIZEB; ++i) {
        printf("%02x", iv[i]);
    }
    printf("\n");
    printf("\n");

    for (i=0; i<LEN; i+=4) {
        printf("%08x -> %08x -> %08x\n", U8TO32_BIG(input + 4 * i), U8TO32_BIG(output + 4 * i), U8TO32_BIG(second + 4 * i));
        passed &= (second[i] == input[i]);
    }

    if (passed) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    return passed;
}

int trivium_file(char *encrypted, char *decrypted, const u8 key[], const u8 iv[]) {
    //Note that the cipher is reversible, so passing in a decrypted file as the first argument will
    //  result in an encrypted output

    ECRYPT_ctx ctx;

    // Initialise cipher
    ECRYPT_init();
    ECRYPT_keysetup(&ctx, key, ECRYPT_MAXKEYSIZE, ECRYPT_MAXIVSIZE);
    ECRYPT_ivsetup(&ctx, iv);

    #define CHUNK 1024
    char buf[CHUNK];
    char outbuf[CHUNK];
    FILE *infile, *outfile;
    size_t nread;

    // Open file streams
    infile = fopen(encrypted, "rb");
    outfile = fopen(decrypted, "w+");
    if (infile && outfile) {

        while ((nread=fread(buf, 1, sizeof(buf), infile)) > 0) {
            ECRYPT_encrypt_blocks(&ctx, (u8*)buf, (u8*)outbuf, (CHUNK/ECRYPT_BLOCKLENGTH));
            if (nread%4) {
                size_t start = (CHUNK/ECRYPT_BLOCKLENGTH) * ECRYPT_BLOCKLENGTH;
                ECRYPT_encrypt_bytes(&ctx, (u8*)(buf+start), (u8*)(outbuf+start), nread%4);
            }
            fwrite(outbuf, 1, nread, outfile);
        }
        if (ferror(infile) || ferror(outfile)) {
            /* deal with error */
        }
        fclose(infile);
        fclose(outfile);

        return 0;
    }
	return 1;
}

int fd;
int trivium_setup(void) {
    // No FPGA, nothing to do here

    return 0;
}

int trivium_finish(void) {
	// clean up our memory mapping(s?) and exit

    return 0;
}

int trivium_decrypt_file(char* infile, char* outfile) {
    trivium_setup();

    // Keys
    //TODO make these read as input
    const u8 key[MAXKEYSIZEB] = "Test key01";
    const u8 iv[MAXIVSIZEB] = "So Random\0";

    // Execute code
    int ret = trivium_file(infile, outfile, key, iv);

    trivium_finish();

    return ret;
}

int trivium_test_cipher(void) {
    trivium_setup();

    int ret = test_trivium();

    trivium_finish();
    return ret;
}
