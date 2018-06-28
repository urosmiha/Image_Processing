#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <math.h>
#include "pha_0.h"
#include <string.h>
#include <inttypes.h>

#include <jpeglib.h>

#define VGA
#define ENC
#define WRITE_ALL 0
#define USE_HW 1

#ifdef VGA
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/mman.h>


    #define soc_cv_av
    #include "socal/socal.h"
    #include "socal/hps.h"
    #include "socal/alt_gpio.h"

    #define HW_REGS_BASE ( ALT_STM_OFST )
    #define HW_REGS_SPAN ( 0x04000000 )
    #define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

    //?
    #define FPGA_AXI_BASE   0xC0000000
    #define FPGA_ONCHIP_BASE      (FPGA_AXI_BASE + ONCHIP_SRAM_BASE)

    // modified for 640x480
    //  probably through black magic
    // #define FPGA_ONCHIP_SPAN      0x00040000
    #define FPGA_ONCHIP_SPAN      0x00080000

    #define FPGA_CHAR_BASE (FPGA_AXI_BASE + VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE)
    #define FPGA_CHAR_SPAN VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_SPAN

    /* function prototypes */
    void VGA_text (int, int, char *);
    void VGA_text_clear();
    void VGA_box (int, int, int, int, short);

    // void readImageRows(int start_row, int start_col);

    // pixel buffer
    volatile unsigned int * vga_pixel_ptr = NULL ;
    void *vga_pixel_virtual_base;

    // character buffer
    volatile unsigned int * vga_char_ptr = NULL ;
    void *vga_char_virtual_base;

    // pixel macro
    #define VGA_PIXEL(x,y,color) do{\
        char  *pixel_ptr ;\
        pixel_ptr = (char *)vga_pixel_ptr + ((y)<<10) + (x) ;\
        *(char *)pixel_ptr = (color);\
    } while(0)
#endif /* VGA */

#ifdef ENC
    #include "ecrypt-sync.h"
    #include "my_trivium-sw_only.c"
#endif /* ENC */

#include <time.h>

struct bmp_out_struct {
    unsigned char *bmp_buffer;
    unsigned long bmp_size;
    int row_stride;
    int width;
    int height;
    int pixel_size;
};


#include <time.h>
#include "hwlib.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
//setting for the HPS2FPGA AXI Bridge
#define ALT_AXI_FPGASLVS_OFST (0xC0000000) // axi_master
#define HW_FPGA_AXI_SPAN (0x40000000) // Bridge span 1GB
#define HW_FPGA_AXI_MASK ( HW_FPGA_AXI_SPAN - 1 )

void *sobelInputs1;
void *sobelInputs2;
void *sobelInputs3;
void *sobelControl;
void *sobelResults;
void *test;
void *filter_select;
void *qsys_pointer;
void *sramPointer;

void *masterPointer;

unsigned char processedImage[307200];

uint64_t masker = 0;

bool start = true;

int count = 0;

void initFilter(){
	printf("initialising\n");
	// Open device memory as a file
	// 	This lets us access the FPGA peripherals
	int fd;
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return;
	}

    // printf("initialising 1\n");
	void *virtual_qsys = mmap( NULL, QSYS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, FPGA_AXI_BASE + QSYS_BASE);

	qsys_pointer = (unsigned long *)(virtual_qsys);

    masterPointer = (uint64_t *)qsys_pointer;

    *(uint64_t *)masterPointer = 0;

	return;

}


//int fpgaFilter(unsigned char row[5], unsigned int control_out, unsigned int wr_en_sel, unsigned int wr_addr, unsigned int rd_addr){
int fpgaFilter() {
    return 0;
}

// iterates of every row,col and channel in bmp_out to filter it and stores result in bmp_processed and then copies
// the results stored in bmp_processed back to bmp_out after the filtering is complete
int myFilter(struct bmp_out_struct *bmp_out) {

    // make a local copy of bmp_out.bmp_buffer
    unsigned char *bmp_buffer = bmp_out->bmp_buffer;
    // assign memory for the processed bmp and have pointer bmp_processed to point to the memory address
    unsigned char *bmp_processed = (unsigned char*) malloc(bmp_out->bmp_size);
    // Black border
    // unsigned char middle = 0;

    bool data_require = true;
    bool one_row = false;

    unsigned char wr_addr = 0;
    unsigned char rd_addr = 0;
    int wr_en_sel = 16;

    int start_row = 0;
    int row = 0;
    int col_count = 0;
    int chan = 0;
    int state = 0;
    int ctrl_out = 0;

    uint64_t response_packet;
    uint64_t control_in_mask = 7;
    uint64_t input_mask = 0xFF00000000000000;
    unsigned char pixel_val;

    uint64_t test_packet = 0;

    int ctrl_in = 0;
    
    unsigned char oneRow[640];
    unsigned char imageRows[5][640];

    while(start_row < 480) {

        if(data_require) {  
            #define val(row, col) bmp_buffer[(row)*bmp_out->row_stride + (col)*bmp_out->pixel_size + chan]
               
                // When system is initialized the SRAMs are empty, so load 5 rows.
                // Load 5 rows of the image
                for(int col = 0; col < 640; col++) {    
                    imageRows[start_row][col] = val(start_row, col);
                    imageRows[start_row+1][col] = val(start_row+1, col);
                    imageRows[start_row+2][col] = val(start_row+2, col);
                    imageRows[start_row+3][col] = val(start_row+3, col); 
                    imageRows[start_row+4][col] = val(start_row+4, col); 
                }

                // Testing
                // imageRows[0][0] = 200;
                // imageRows[0][1] = 50;
                // imageRows[0][2] = 60;
                // imageRows[0][3] = 100;
                // imageRows[0][4] = 200;
                
                // imageRows[1][0] = 70;
                // imageRows[1][1] = 80;
                // imageRows[1][2] = 90;
                // imageRows[1][3] = 50;
                // imageRows[1][4] = 100;
                
                // imageRows[2][0] = 100;
                // imageRows[2][1] = 100;
                // imageRows[2][2] = 90;
                // imageRows[2][3] = 50;
                // imageRows[2][4] = 100;
                
                // imageRows[3][0] = 90;
                // imageRows[3][1] = 90;
                // imageRows[3][2] = 90;
                // imageRows[3][3] = 200;
                // imageRows[3][4] = 200;
                                
                // imageRows[4][0] = 100;
                // imageRows[4][1] = 100;
                // imageRows[4][2] = 90;
                // imageRows[4][3] = 90;
                // imageRows[4][4] = 200;

            #undef val
            data_require = false;

        } else if(one_row) {            
            // After the frist 5 rows of the image have been loaded we need to load only one row at a time
            #define val(row, col) bmp_buffer[(row)*bmp_out->row_stride + (col)*bmp_out->pixel_size + chan]
                // Load 5 rows of the image
                for(int col = 0; col < 640; col++) {    
                    oneRow[col] = val(start_row, col); 
                }
            #undef val
            one_row = false;
        }

        // Display stuff we are sending and receiving
        printf("Wr_addr: %d Rd_addr: %d \n", wr_addr, rd_addr);
        printf("En: %d Ctrl out: %d \n", wr_en_sel, ctrl_out);
        printf("**TEST PACKET: **%" PRIx64 "\n", test_packet);
        printf("-------------------------------- \n");
        printf("Control in: %d \n", ctrl_in);
        printf("Pixel Value: %" PRIx64 "\n", pixel_val);
        printf("RESP PACKET ");
        printf("%" PRIx64 "\n" ,response_packet);
        printf("-------------------------------- \n");

        // In this state we are loading the all five rows so that we can fillout our SRAMs
        if(state == 0) { // Initialize by sending all of the 1st 5 rows

            // Format everything into a temporary packet before assigning it to the master pointer
            test_packet = 0;
            test_packet |= (uint64_t)imageRows[row][col_count] << 56;
            test_packet |= (uint64_t)imageRows[row][col_count+1] << 48;
            test_packet |= (uint64_t)imageRows[row][col_count+2] << 40;
            test_packet |= (uint64_t)imageRows[row][col_count+3] << 32;
            test_packet |= (uint64_t)imageRows[row][col_count+4] << 24;
            test_packet |= (uint64_t)wr_addr << 16;
            test_packet |= (uint64_t)rd_addr << 8;
            test_packet |= (uint64_t)wr_en_sel << 3;
            test_packet |= (uint64_t)ctrl_out;

            *(uint64_t *)masterPointer = test_packet;

            // Go the next row, since we are always loading 5 columns of each of the 5 rows
            // So once we send 40 bits (5 pixels) go to the next row and send 5 pixels from that row
            row++;
            if(row > 4) {
                // Afer the 5th row, go back to first row, but now load 5 columns starting different position.
                row = 0;
                col_count += 5;
                wr_addr++;
                // Don't allow address to go above 255 since address is 8 bits (i.e. max representation 255)
                if(wr_addr > 254) {
                    wr_addr = 0;
                }
            }

            // Update the select signal for writing to the SRAMs
            wr_en_sel = wr_en_sel / 2;
            if(wr_en_sel == 0) {
                wr_en_sel = 16;
            }

            // Indicate that FPGA can start processing windows
            if(col_count > 15) {
                ctrl_out = 3;
            } 

            // Store response from in a temporary package
            response_packet = *(uint64_t *)masterPointer;
            // Control is in the last 3 bits
            control_in_mask = 7;
            ctrl_in = response_packet & control_in_mask;

            // Read pixel value if it is indicated that there is the new pixel to read.
            if(ctrl_in > 0) {
                pixel_val = response_packet & input_mask;
                processedImage[count] = pixel_val;
                count++;
                // Read address is represented by 8 bits only.
                rd_addr++;
                if(rd_addr > 244) {
                    rd_addr = 0;
                }
            }
            // Once we get to the end of the columns, wait on contro signal to indicate that we can send more.
            // Read the pixel values while you wait, if control is indicating this
            if(col_count > 635) {
                while(ctrl_in < 4) {

                    response_packet = *(uint64_t *)masterPointer;               
                    ctrl_in = response_packet & control_in_mask;

                    if(ctrl_in > 0) {
                        // Read pixel values
                        pixel_val = response_packet & input_mask;
                        processedImage[count] = pixel_val;
                        count++;

                        rd_addr++;
                        if(rd_addr > 244) {
                            rd_addr = 0;
                        }
                    }
                }
                // Start again from the 6th row now and from the 0 column
                col_count = 0;
                start_row += 5;
                state = 1;
                one_row = true;
            }
            // In this state we only send one row at a time, starting form the row 6 since we already loaded 5 rows
            // The logic is very similar to above code.
        } else if(state == 1) {

            test_packet = 0;
            test_packet |= (uint64_t)oneRow[col_count] << 56;
            test_packet |= (uint64_t)oneRow[col_count] << 48;
            test_packet |= (uint64_t)oneRow[col_count] << 40;
            test_packet |= (uint64_t)oneRow[col_count] << 32;
            test_packet |= (uint64_t)oneRow[col_count] << 24;
            test_packet |= (uint64_t)wr_addr << 16;
            test_packet |= (uint64_t)rd_addr << 8;
            test_packet |= (uint64_t)wr_en_sel << 3;
            test_packet |= (uint64_t)ctrl_out;

            *(uint64_t *)masterPointer = test_packet;

            col_count += 5;
            wr_addr++;
            if(wr_addr > 254) {
                wr_addr = 0;
            }

            response_packet = *(uint64_t *)masterPointer;
            ctrl_in = response_packet & control_in_mask;

            if(ctrl_in > 0) {
                pixel_val = response_packet & input_mask;
                processedImage[count] = pixel_val;
                count++;

                rd_addr++;

                if(rd_addr > 244) {
                    rd_addr = 0;
                }
            }
            // Once we get to the end of the column wait on control signal to indicat that there FPGA
            // wants more pixels to be sent
            if(col_count > 635) {
                while(ctrl_in < 4) {
                    response_packet = *(uint64_t *)masterPointer;                   
                    ctrl_in = response_packet & control_in_mask;
                    // Read pixels if the are any to be read
                    if(ctrl_in > 0) {

                        pixel_val = response_packet & input_mask;
                        processedImage[count] = pixel_val;
                        count++;

                        rd_addr++;
                        if(rd_addr > 244) {
                            rd_addr = 0;
                        }
                    }                  
                }

                // Update the select signal for writing to the SRAMs
                // We only want to write to one SRAM at a time, so old data does not get overwriten
                wr_en_sel = wr_en_sel / 2;
                if(wr_en_sel == 0) {
                    wr_en_sel = 16;
                }

                col_count = 0;      // Start from 0 column
                start_row += 1;     // Got to the next row
                state = 1;
                one_row = true;     // Indicate that we are now only reading one row at a time not 5.
            }
        }
    }

    printf(" *** One Frame Done *** \n");
    
    // Once you go through all the rows, add the image to the buffer so it can be displayed
    int index = 0;
    // store the filter output
    for(int row = 0; row < bmp_out->height; row++) {
        for(int col = 0; col < bmp_out->width; col++) {
            bmp_processed[(row*bmp_out->row_stride) + col*bmp_out->pixel_size + chan] = processedImage[index];
            index++;
        }
    }
    
    // Replace input with output
    memcpy(bmp_buffer, bmp_processed, bmp_out->bmp_size);

    // printf(" \n Finished \n \n");
    return 1;
}

int windowFilter(struct bmp_out_struct *bmp_out);
int decodeMjpeg(unsigned char *mjpeg_buffer, unsigned long mjpeg_size);
int decodeJpeg(struct jpeg_decompress_struct *cinfo, struct bmp_out_struct *bmp_out);
int outputBmp(struct bmp_out_struct *bmp_out);
int outputVGA(struct bmp_out_struct *bmp_out);

#define IM_DECODE decodeJpeg
#define IM_PROCESS windowFilter
#define IM_OUTPUT outputVGA

int medianFilter(unsigned char values[9]) {
    // Sort values like a horrible person
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i=1; i<9; ++i) {
            if (values[i-1] > values[i]) {
                unsigned char temp = values[i];
                values[i] = values[i-1];
                values[i-1] = temp;
                sorted = 0;
            }
        }
    }
    return values[4];
}

int convolutionFilter(unsigned char values[9]) {
//    #if 0 // Edge detection
//    const int kernel[9] = { 0,  1,  0,
//                            1, -4,  1,
//                            0,  1,  0 };
//    const int div = 1;
//    #elif 1 // Gaussian
    const int kernel[9] = { 1,  2,  1,
                            2,  4,  2,
                            1,  2,  1 };
    const int div = 16;
////    #else // Identity
//    const int kernel[9] = { 0,  0,  0,
//                            0,  1,  0,
//                            0,  0,  0 };
//    const int div = 1;
//    #endif

    int sum = 0;
    for (int i=0; i<9; ++i) {
        sum += kernel[i]*(int)values[i];
    }
    return (int)(sum / div);
}

int sobelFilter(unsigned char values[9]) {
    const int sobel_x[9] = { 1,  0, -1,
                             2,  0, -2,
                             1,  0, -1 };
    const int sobel_y[9] = { 1,  2,  1,
                             0,  0,  0,
                            -1, -2, -1 };

    int sumx = 0;
    int sumy = 0;
    for (int i=0; i<9; ++i) {
        sumx += sobel_x[i]*values[i];
        sumy += sobel_y[i]*values[i];
    }
    return (int)sqrt(sumx*sumx + sumy*sumy);
}

#define WINDOW_FUNC sobelFilter
int windowFilter(struct bmp_out_struct *bmp_out) {
    // Take a few local copies to make the code a bit easier to read
    unsigned char *bmp_buffer = bmp_out->bmp_buffer;
    // Filter
    unsigned char *bmp_processed = (unsigned char*) malloc(bmp_out->bmp_size);
    // Iterate over full image
    for (int row=0; row<bmp_out->height; ++row) {
        for (int col=0; col<bmp_out->width; ++col) {
            // Work on each channel independently
            for (int chan=0; chan<bmp_out->pixel_size; ++chan) {
                // Black border
                unsigned char middle = 0;
                if ((row>0 && row<bmp_out->height-1) && (col>0 && col<bmp_out->width-1)) {
                    #define val(row, col) bmp_buffer[(row)*bmp_out->row_stride + (col)*bmp_out->pixel_size + chan]
                    // Load all adjacent values
                    unsigned char values[9] = {
                        val(row-1, col-1), val(row-1, col), val(row-1, col+1),
                        val(row-0, col-1), val(row-0, col), val(row-0, col+1),
                        val(row+1, col-1), val(row+1, col), val(row+1, col+1),
                    };
                    #undef val
                    middle = WINDOW_FUNC(values);
                  //  printf("%d\n",middle);

                }
                // Set output
                bmp_processed[(row*bmp_out->row_stride) + col*bmp_out->pixel_size + chan] = middle;
            }
        }
    }

    // Replace input with output
    memcpy(bmp_buffer, bmp_processed, bmp_out->bmp_size);
    return 1;
}

// argc tells us the number of arguments passed to main
//argv contains a 1D array of strings where every string is one
// of the arguments that was passed to main
// argc is always at least 1 as argv[0] is the executeable name to run it
// argc is the cipher stream for decrypting and argv stores the actual mjpeg images
int main (int argc, char *argv[]) {
	int rc, i;
    int fd;

    // reserve 1024 characters for syslog_prefix
	char *syslog_prefix = (char*) malloc(1024);
	sprintf(syslog_prefix, "%s", argv[0]);
	openlog(syslog_prefix, LOG_PERROR | LOG_PID, LOG_USER);

    #ifdef ENC
		// we need 3 arguments for this
        if (argc != 3) {
            fprintf(stderr, "USAGE: %s encrypted_file unencrypted_file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        // encfile is SZS cipher
        char *encfile = argv[1];
        // infile is the mjpeg
        char *infile = argv[2];
    #else
        // we need 3 arguments not 2
        if (argc != 2) {
            fprintf(stderr, "USAGE: %s input_file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        char *infile = argv[1];
    #endif

    #ifdef VGA
        // === get FPGA addresses ==================
        // Open /dev/mem
        if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) 	{
            printf( "ERROR: could not open \"/dev/mem\"...\n" );
            return( 1 );
        }

        // === get VGA char addr =====================
        // get virtual addr that maps to physical
        vga_char_virtual_base = mmap( NULL, FPGA_CHAR_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, FPGA_CHAR_BASE );
        if( vga_char_virtual_base == MAP_FAILED ) {
            printf( "ERROR: mmap2() failed...\n" );
            close( fd );
            return(1);
        }

        // Get the address that maps to the FPGA LED control
        vga_char_ptr =(unsigned int *)(vga_char_virtual_base);

        // === get VGA pixel addr ====================
        // get virtual addr that maps to physical
        vga_pixel_virtual_base = mmap( NULL, FPGA_ONCHIP_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, FPGA_ONCHIP_BASE);
        if( vga_pixel_virtual_base == MAP_FAILED ) {
            printf( "ERROR: mmap3() failed...\n" );
            close( fd );
            return(1);
        }

        // Get the address that maps to the FPGA pixel buffer
        vga_pixel_ptr =(unsigned int *)(vga_pixel_virtual_base);

        // ===========================================
        // clear the screen
        VGA_box (0, 0, 639, 479, 0x00);
        // clear the text
        VGA_text_clear();
    #endif

//   SSS    EEEEEEE  TTTTTTT  U     U  PPPP
// SS   SS  E           T     U     U  P   PP
// S        E           T     U     U  P    PP
// SS       E           T     U     U  P   PP
//   SSS    EEEE        T     U     U  PPPP
//      SS  E           T     U     U  P
//       S  E           T     U     U  P
// SS   SS  E           T      U   U   P
//   SSS    EEEEEEE     T       UUU    P

	// Variables for the source jpg
	struct stat file_info;
	unsigned long mjpg_size;
	unsigned char *mjpg_buffer;

    #ifdef ENC
        // Unencrypt file passing the cipher stream and mjpeg file
        trivium_decrypt_file(encfile, infile);
    #endif

	// Load the jpeg data from a file into a memory buffer for
	// the purpose of this demonstration.
	// Normally, if it's a file, you'd use jpeg_stdio_src, but just
	// imagine that this was instead being downloaded from the Internet
	// or otherwise not coming from disk

    // stat is used to determine info about a file based on its file path
    // the info about the file will be stored in the 'file_info' structure
    // returns an int value to say if the stat was successful
	rc = stat(infile, &file_info);
	if (rc) {
		syslog(LOG_ERR, "FAILED to stat source jpg");
		exit(EXIT_FAILURE);
	}

	// stores the size of the file that got stat
	mjpg_size = file_info.st_size;
	// create an address buffer thats large enough to store the file
	mjpg_buffer = (unsigned char*) malloc(mjpg_size + 100);


	fd = open(infile, O_RDONLY);
	i = 0;

	// read the infile into the buffer
	while (i < mjpg_size) {
		rc = read(fd, mjpg_buffer + i, mjpg_size - i);
		syslog(LOG_INFO, "Input: Read %d/%lu bytes", rc, mjpg_size-i);
		i += rc;
	}
	close(fd);

    // Decode MJPEG
    rc = decodeMjpeg(mjpg_buffer, mjpg_size);

	// And free the input buffer
	free(mjpg_buffer);

    return rc;
}

int decodeMjpeg(unsigned char *mjpeg_buffer, unsigned long mjpeg_size) {
	initFilter();

    //   SSS    TTTTTTT     A     RRRR     TTTTTTT
    // SS   SS     T       A A    R   RR      T
    // S           T      A   A   R    RR     T
    // SS          T     A     A  R   RR      T
    //   SSS       T     AAAAAAA  RRRR        T
    //      SS     T     A     A  R RR        T
    //       S     T     A     A  R   R       T
    // SS   SS     T     A     A  R    R      T
    //   SSS       T     A     A  R     R     T

    // printf("Here Now \n");

	syslog(LOG_INFO, "Proc: Create Decompress struct");
	// Allocate a new decompress struct, with the default error handler.
	// The default error handler will exit() on pretty much any issue,
	// so it's likely you'll want to replace it or supplement it with
	// your own.
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);


	syslog(LOG_INFO, "Proc: Set memory buffer as source");
	// Configure this decompressor to read its data from a memory
	// buffer starting at unsigned char *jpg_buffer, which is jpg_size
	// long, and which must contain a complete jpg already.
	//
	// If you need something fancier than this, you must write your
	// own data source manager, which shouldn't be too hard if you know
	// what it is you need it to do. See jpeg-8d/jdatasrc.c for the
	// implementation of the standard jpeg_mem_src and jpeg_stdio_src
	// managers as examples to work from.
	jpeg_mem_src(&cinfo, mjpeg_buffer, mjpeg_size);


    /* Injecting MJPEG support (from raw video format)
     *
     * The jpeg_mem_src will continue to read from the same buffer just fine
     *  on its own. All we need to do is keep going and catching it before it
     *  can fail (i.e. we need to detect the final frame).
     *
     * * * * * * * * Begin * * * * * * * */

    clock_t begin = clock();
    unsigned int jpg_count = 0;
    while (*(cinfo.src->next_input_byte)) {
        // Prepare
        struct bmp_out_struct bmp_out;

        // Decode
        // this function takes a jpeg out of the mjpeg and stores it in
        // bmp_out
        // printf("Fine here 2\n");
        IM_DECODE(&cinfo, &bmp_out);


        // this is where all the filtering happens. We can replace this with a sw/hw implementation
         //Process
        if(USE_HW == 0){
			#ifdef IM_PROCESS
				IM_PROCESS(&bmp_out);
			#endif
        }
        else{
            // printf("Starting filt \n");
        	myFilter(&bmp_out);
            // printf("FUNCT DONE \n");

        }

        // Output
        #ifdef IM_OUTPUT
            IM_OUTPUT(&bmp_out);
        #endif

        // Clean up
        free((void*)bmp_out.bmp_buffer);
        jpg_count++;

        // printf("Fine here \n");
    }
    // printf("Go here \n");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    syslog(LOG_INFO, "Successfully loaded %u JPEGs in %fs", jpg_count, time_spent);

	// Once you're really really done, destroy the object to free everything
	jpeg_destroy_decompress(&cinfo);

// DDDD       OOO    N     N  EEEEEEE
// D  DDD    O   O   NN    N  E
// D    DD  O     O  N N   N  E
// D     D  O     O  N N   N  E
// D     D  O     O  N  N  N  EEEE
// D     D  O     O  N   N N  E
// D    DD  O     O  N   N N  E
// D  DDD    O   O   N    NN  E
// DDDD       OOO    N     N  EEEEEEE

	syslog(LOG_INFO, "End of decompression");
	return EXIT_SUCCESS;
}


/** Function to decode individual frame
 * Take pointer to encoded JPEG (in memory), return a pointer to the decoded BMP
 *  Don't forget to free memory
 **/
int decodeJpeg(struct jpeg_decompress_struct *cinfo, struct bmp_out_struct *bmp_out) {
    //syslog(LOG_INFO, "Proc: Read the JPEG header");
    // Have the decompressor scan the jpeg header. This won't populate
    // the cinfo struct output fields, but will indicate if the
    // jpeg is valid.

    // printf("I am decoding now \n");

    int rc = jpeg_read_header(cinfo, TRUE);

    if (rc != 1) {
        syslog(LOG_ERR, "File does not seem to be a normal JPEG");
        exit(EXIT_FAILURE);
    }

    //syslog(LOG_INFO, "Proc: Initiate JPEG decompression");
    // By calling jpeg_start_decompress, you populate cinfo
    // and can then allocate your output bitmap buffers for
    // each scanline.
    jpeg_start_decompress(cinfo);

    bmp_out->width = cinfo->output_width;
    bmp_out->height = cinfo->output_height;
    bmp_out->pixel_size = cinfo->output_components;

    //syslog(LOG_INFO, "Proc: Image is %d by %d with %d components",
    //        width, height, pixel_size);

    bmp_out->bmp_size = bmp_out->width * bmp_out->height * bmp_out->pixel_size;
    bmp_out->bmp_buffer = (unsigned char*) malloc(bmp_out->bmp_size);

    // The row_stride is the total number of bytes it takes to store an
    // entire scanline (row).
    bmp_out->row_stride = bmp_out->width * bmp_out->pixel_size;

    //syslog(LOG_INFO, "Proc: Start reading scanlines");
    //
    // Now that you have the decompressor entirely configured, it's time
    // to read out all of the scanlines of the jpeg.
    //
    // By default, scanlines will come out in RGBRGBRGB...  order,
    // but this can be changed by setting cinfo->out_color_space
    //
    // jpeg_read_scanlines takes an array of buffers, one for each scanline.
    // Even if you give it a complete set of buffers for the whole image,
    // it will only ever decompress a few lines at a time. For best
    // performance, you should pass it an array with cinfo->rec_outbuf_height
    // scanline buffers. rec_outbuf_height is typically 1, 2, or 4, and
    // at the default high quality decompression setting is always 1.
    while (cinfo->output_scanline < cinfo->output_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = bmp_out->bmp_buffer + \
                           (cinfo->output_scanline) * bmp_out->row_stride;

        jpeg_read_scanlines(cinfo, buffer_array, 1);

    }
    //syslog(LOG_INFO, "Proc: Done reading scanlines");

    // Once done reading *all* scanlines, release all internal buffers,
    // etc by calling jpeg_finish_decompress. This lets you go back and
    // reuse the same cinfo object with the same settings, if you
    // want to decompress several jpegs in a row.
    //
    // If you didn't read all the scanlines, but want to stop early,
    // you instead need to call jpeg_abort_decompress(cinfo)
    jpeg_finish_decompress(cinfo);

    // At this point, optionally go back and either load a new jpg into
    // the jpg_buffer, or define a new jpeg_mem_src, and then start
    // another decompress operation.
    // printf("I have finished decoding now \n");
    return 1;
}

int outputBmp(struct bmp_out_struct *bmp_out) {
    static unsigned int jpg_count = 0;
    int ret = 0;
    // Only output every 240 frames
    if (WRITE_ALL || !(jpg_count % 240)) {
        // Write the decompressed bitmap out to a ppm file, just to make sure
        // it worked.
        char outfile[20];
        sprintf(outfile, "output%d.ppm", jpg_count);
        int fd = open(outfile, O_CREAT | O_WRONLY, 0666);
        char buf[1024];

        int rc = sprintf(buf, "P6 %d %d 255\n", bmp_out->width, bmp_out->height);
        write(fd, buf, rc); // Write the PPM image header before data
        write(fd, bmp_out->bmp_buffer, bmp_out->bmp_size); // Write out all RGB pixel data

        close(fd);

        syslog(LOG_INFO, "Output frame %u successful", jpg_count);
        ret = 1;
    }
    ++jpg_count;
    return ret;
}

int outputVGA(struct bmp_out_struct *bmp_out) {
    #ifdef VGA
        for (int i=1; i<bmp_out->width; ++i) {
            if (i >= 640) break;
            for (int j=1; j<bmp_out->height; ++j) {
            	//printf("here");
                if (j >= 480) break;
                char pixel_colour;
                #define val(row, col, chan) bmp_out->bmp_buffer[(row)*bmp_out->row_stride + (col)*bmp_out->pixel_size + chan]
                pixel_colour = (val(j, i, 0) & 0xe0) >> 0 | (val(j, i, 1) & 0xe0) >> 3 | (val(j, i, 2) & 0xc0) >> 6;
                VGA_PIXEL(i, j, pixel_colour);
            }
        }
        return 1;
    #else
        return 0;
    #endif
}

#ifdef VGA
    /****************************************************************************************
     * Subroutine to send a string of text to the VGA monitor
    ****************************************************************************************/
    void VGA_text(int x, int y, char * text_ptr)
    {
        volatile char * character_buffer = (char *) vga_char_ptr ;	// VGA character buffer
        int offset;
        /* assume that the text string fits on one line */
        offset = (y << 7) + x;
        while ( *(text_ptr) )
        {
            // write to the character buffer
            *(character_buffer + offset) = *(text_ptr);
            ++text_ptr;
            ++offset;
        }
    }

    /****************************************************************************************
     * Subroutine to clear text to the VGA monitor
    ****************************************************************************************/
    void VGA_text_clear()
    {
        volatile char * character_buffer = (char *) vga_char_ptr ;	// VGA character buffer
        int offset, x, y;
        for (x=0; x<70; x++){
            for (y=0; y<40; y++){
        /* assume that the text string fits on one line */
                offset = (y << 7) + x;
                // write to the character buffer
                *(character_buffer + offset) = ' ';
            }
        }
    }

    /****************************************************************************************
     * Draw a filled rectangle on the VGA monitor
    ****************************************************************************************/
    #define SWAP(X,Y) do{int temp=X; X=Y; Y=temp;}while(0)

    void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
    {
        char  *pixel_ptr ;
        int row, col;

        /* check and fix box coordinates to be valid */
        if (x1>639) x1 = 639;
        if (y1>479) y1 = 479;
        if (x2>639) x2 = 639;
        if (y2>479) y2 = 479;
        if (x1<0) x1 = 0;
        if (y1<0) y1 = 0;
        if (x2<0) x2 = 0;
        if (y2<0) y2 = 0;
        if (y1>y2) SWAP(y1,y2);
        for (row = y1; row <= y2; row++)
            for (col = x1; col <= x2; ++col)
            {
                //640x480
                pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
                // set pixel color
                *(char *)pixel_ptr = pixel_color;
            }
    }
#endif
