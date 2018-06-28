#include "my_trivium.h"
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
#include "hps_0.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include <time.h>
#define soc_cv_av
#include "hwlib.h"
#include "hps_0.h"
// Optionally reverse the byte order for displaying the key and iv
// Since the processor will reverse the order displaying it this way makes it
//	easier to copy and paste into vhdl with bit order 80 DOWNTO 1
#define REVERSE 1
#define USE_FPGA 1

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#if USE_FPGA


	void *trivium_setup_1;
	void *trivium_setup_2;
	void *trivium_setup_3;
	void *keystream_1;
	void *keystream_2;
	void *keystream_3;
	void *setup_received;
	void *setup_sent;
    void *state;
    void *test;
    void *out1;
    void *out2;
    void *out3;

	// You will need to fill these out in order to communicate with your FPGA implementation
	void ECRYPT_init(void) {


		printf("initialising\n");
		// Open device memory as a file
		// 	This lets us access the FPGA peripherals
		int fd;
		if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
			printf( "ERROR: could not open \"/dev/mem\"...\n" );
			return;
		}

		// Map hardware registers into memory
		void *virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

		if(virtual_base == MAP_FAILED) {
			printf("ERROR: mmap() failed...\n");
			close(fd);
			return;
		}

		//Pointers to the IV and KEY Inputs to be read in VHDL
		trivium_setup_1 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + TRIVIUM_SETUP_1_BASE) & (unsigned long)(HW_REGS_MASK));
		trivium_setup_2 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + TRIVIUM_SETUP_2_BASE) & (unsigned long)(HW_REGS_MASK));
		trivium_setup_3 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + TRIVIUM_SETUP_3_BASE) & (unsigned long)(HW_REGS_MASK));

		//Pointers to the IV and KEY Inputs to be read in VHDL
		keystream_1 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + KEYSTREAM_1_BASE) & (unsigned long)(HW_REGS_MASK));
		keystream_2 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + KEYSTREAM_2_BASE) & (unsigned long)(HW_REGS_MASK));
		keystream_3 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + KEYSTREAM_3_BASE) & (unsigned long)(HW_REGS_MASK));

		//Pointer to acknowledgment from VHDL that the IV and KEY has been received
		setup_received = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SETUP_RECEIVED_BASE) & (unsigned long)(HW_REGS_MASK));
		setup_sent = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SETUP_SENT_BASE) & (unsigned long)(HW_REGS_MASK));
		state = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + STATE_BASE) & (unsigned long)(HW_REGS_MASK));

		//Pointer to acknowledgment from VHDL that the IV and KEY has been received
		out1 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + OUT1_BASE) & (unsigned long)(HW_REGS_MASK));
		out2 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + OUT2_BASE) & (unsigned long)(HW_REGS_MASK));
		out3 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + OUT3_BASE) & (unsigned long)(HW_REGS_MASK));
		test = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + TEST_BASE) & (unsigned long)(HW_REGS_MASK));

	}

	void ECRYPT_keysetup(

	  ECRYPT_ctx* ctx,
	  const u8* key,
	  u32 keysize,
	  u32 ivsize) {

	      printf("key setup\n");
		*(uint32_t *)trivium_setup_3 = 825260389;
		*(uint32_t *)trivium_setup_2 = 1797289075;
		*(uint32_t *)trivium_setup_1 = 1700003840;
		*(uint32_t *)setup_sent = 1;

		//delay until VHDL has received and setup the key
		while(*(uint32_t *)setup_received != 1){};
	}

	void ECRYPT_ivsetup(
	  ECRYPT_ctx* ctx,
	  const u8* iv) {
	    printf("iv setup\n");
	    printf("%u\n",*(uint32_t *)trivium_setup_3 );
	    printf("%u\n",*(uint32_t *)trivium_setup_2 );
	    printf("%u\n",*(uint32_t *)trivium_setup_1 );

		*(uint32_t *)trivium_setup_3 =  7171940;
		*(uint32_t *)trivium_setup_2 = 1851871776;
		*(uint32_t *)trivium_setup_1 = 1867710464;
		*(uint32_t *)setup_sent = 2;
		//delay until VHDL has received and setup the key
		while(*(uint32_t *)setup_received != 2){};
//		u8 ivReceived[10];
//		ivReceived[0] = (*(uint32_t *)out3) & 0xFF;
//		ivReceived[1] = (*(uint32_t *)out3>>8) & 0xFF;
//		ivReceived[2] = (*(uint32_t *)out2) & 0xFF;
//		ivReceived[3] = (*(uint32_t *)out2>>8) & 0xFF;
//		ivReceived[4] = (*(uint32_t *)out2>>16) & 0xFF;
//		ivReceived[5] = (*(uint32_t *)out2>>24) & 0xFF;
//		ivReceived[6] = (*(uint32_t *)out1) & 0xFF;
//		ivReceived[7] = (*(uint32_t *)out1>>8) & 0xFF;
//		ivReceived[8] = (*(uint32_t *)out1>>16) & 0xFF;
//		ivReceived[9] = (*(uint32_t *)out1>>24) & 0xFF;

		*(uint32_t *)setup_sent = 0;
		*(uint32_t *)state = 2;
	}

	void ECRYPT_process_bytes(
	  int action,
	  ECRYPT_ctx* ctx,
	  const u8* input,
	  u8* output,
	  u32 msglen) {
		printf("processing\n");
		int i=0;
		int j=0;
		printf("\nmost significant 32 bits of cipher block\n");
		printf("\n%u", (*(uint32_t *)keystream_1));

//		while(i<12){
//			wait until a 96 bit chunk of the keystream is ready
//
//			if(*(uint32_t *)setup_sent == 3 ){
//				output[i]= (*(uint32_t *)keystream_1) & 0xFF;
//				output[i+1]= (*(uint32_t *)keystream_1>>8) & 0xFF;
//				output[i+2]= (*(uint32_t *)keystream_1>>16) & 0xFF;
//				output[i+3]= (*(uint32_t *)keystream_1>>24) & 0xFF;
//
//				output[i+4]= (*(uint32_t *)keystream_2) & 0xFF;
//				output[i+5]= (*(uint32_t *)keystream_2>>8) & 0xFF;
//				output[i+6]= (*(uint32_t *)keystream_2>>16) & 0xFF;
//				output[i+7]= (*(uint32_t *)keystream_2>>24) & 0xFF;
//
//				if(j<3){
//					output[i+8]= (*(uint32_t *)keystream_3) & 0xFF;
//					output[i+9]= (*(uint32_t *)keystream_3>>8) & 0xFF;
//					output[i+10]= (*(uint32_t *)keystream_3>>16) & 0xFF;
//					output[i+11]= (*(uint32_t *)keystream_3>>24) & 0xFF;
//					j++;
//				}
//				i+=12;
//				printf("\nleast significant 32 bits\n");
//				printf("\n%u", (*(uint32_t *)keystream_1));
//				signal to generate more chunks of the keystream
//				*(uint32_t *)setup_sent = 3;
//			}
//			else{
//				*(uint32_t *)setup_sent = 0;
//			}
//		}
	}
#else /* Software trivium */
	#include "trivium.c"
#endif /* USE_FPGA */

void print_key(const u8 key[]) {
	printf("Key: ");
	#if !REVERSE
		for (int i=0; i<MAXKEYSIZEB; ++i) {
			printf("%02x", key[i]);
		}
	#else
		for (int i=MAXKEYSIZEB; i; --i) {
			printf("%02x", key[i-1]);
		}
	#endif
	printf("\n");
}

void print_iv(const u8 iv[]) {
	printf("IV: ");
	#if !REVERSE
		for (int i=0; i<MAXIVSIZEB; ++i) {
			printf("%02x", iv[i]);
		}
	#else
		for (int i=MAXIVSIZEB; i; --i) {
			printf("%02x", iv[i-1]);
		}
	#endif
	printf("\n");
}

int test_trivium(void) {
    #define LEN 32
    ECRYPT_ctx ctx;
    const u8 key[MAXKEYSIZEB] = "Test key01";
    const u8 iv[MAXIVSIZEB] = "So Random\0";
    //const u8 input[LEN] = "Test input 12345";
    //const u8 input[LEN] = "#include \"ecrypt-sync.h\"\r\n#inclu";
    const u8 input[LEN] = "";
    u8 output[LEN];
    u8 second[LEN];
    int passed = 1;
    int i;

    printf("start test");

    // Initialise
	ECRYPT_init();
	ECRYPT_keysetup(&ctx, key, ECRYPT_MAXKEYSIZE, ECRYPT_MAXIVSIZE);

    // Encrypt
	ECRYPT_ivsetup(&ctx, iv);

	printf("input value before\n" );
	for (i=0; i<LEN; ++i) {
		printf("%02x", input[i]);
	}

	ECRYPT_process_bytes(0, &ctx, input, output, (LEN/ECRYPT_BLOCKLENGTH));


	//ECRYPT_encrypt_blocks(&ctx, input, output, (LEN/ECRYPT_BLOCKLENGTH));

    // Decrypt
	//ECRYPT_ivsetup(&ctx, iv);
	//ECRYPT_encrypt_blocks(&ctx, output, second, (LEN/ECRYPT_BLOCKLENGTH));

    // Output results of encryption/decryption and test
	printf("Testing...\n");
	print_key(key);
	print_iv(iv);
	printf("\n");

	for (i=0; i<LEN; ++i) {
		passed &= (second[i] == input[i]);
		printf("%02x", input[i]);
	}
	printf("\n\t\t\tv v v v v v v v\n");
	for (i=0; i<LEN; ++i) {
		printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(output[i]));

	//	printf("%02x", output[i]);
	}
	printf("\n\t\t\tv v v v v v v v\n");
	for (i=0; i<LEN; ++i) {
		printf("%02x", second[i]);
	}
	printf("\n");

    // Display test result
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
    // Hint: This would be a good place to setup your memory mappings
	#ifdef ARM
	if((fd = open( "/dev/mem", ( O_RDWR | O_SYNC ))) == -1) {
		printf("ERROR: could not open \"/dev/mem\"...\n");
		return(1);
	}
	#endif

    return 0;
}

int trivium_finish(void) {
	// And now clean up all the memory mappings
    close(fd);
    return 0;
}

int trivium_decrypt_file(char* infile, char* outfile, const u8 key[], const u8 iv[]) {
    trivium_setup();

    // Execute code
    int ret = trivium_file(infile, outfile, key, iv);

    trivium_finish();
    return ret;
}

int trivium_test_cipher(void) {
    trivium_setup();
	
	// Test for input reversible cipher
    int ret = test_trivium();

    trivium_finish();
    return ret;
}
