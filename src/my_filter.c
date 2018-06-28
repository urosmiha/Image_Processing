//#include "my_filter.h"
//// A mess of includes
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>
//#include <sys/mman.h>
//#include <sys/time.h>
//#include <math.h>
//#include "hps_0.h"
//#include "socal/socal.h"
//#include "socal/hps.h"
//#include "socal/alt_gpio.h"
//#include <time.h>
//#define soc_cv_av
//#include "hwlib.h"
//#define HW_REGS_BASE ( ALT_STM_OFST )
//#define HW_REGS_SPAN ( 0x04000000 )
//#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
//
//
//void *sobelInputs1;
//void *sobelInputs2;
//void *sobelInputs3;
//void *sobelControl;
//void *sobelResults;
//
//void initFilter(){
//	printf("initialising\n");
//	// Open device memory as a file
//	// 	This lets us access the FPGA peripherals
//	int fd;
//	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
//		printf( "ERROR: could not open \"/dev/mem\"...\n" );
//		return;
//	}
//
//	// Map hardware registers into memory
//	void *virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );
//
//	if(virtual_base == MAP_FAILED) {
//		printf("ERROR: mmap() failed...\n");
//		close(fd);
//		return;
//	}
//
//	// filter inputs and outputs
//	sobelInputs1 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + ARM_A9_HPS_SOBELINPUTS1_BASE) & (unsigned long)(HW_REGS_MASK));
//	sobelInputs2 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST +ARM_A9_HPS_SOBELINPUTS2_BASE ) & (unsigned long)(HW_REGS_MASK));
//	sobelInputs3 = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + ARM_A9_HPS_SOBELINPUTS3_BASE) & (unsigned long)(HW_REGS_MASK));
//	sobelControl = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + ARM_A9_HPS_SOBELCONTROL_BASE) & (unsigned long)(HW_REGS_MASK));
//	sobelResults = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + ARM_A9_HPS_FILTER_RESULT_BASE) & (unsigned long)(HW_REGS_MASK));
//}
//
//int fpgaFilter(unsigned char values[9]){
//
//	*(uint32_t *)sobelInputs1 |=  values[0]<<24;
//	*(uint32_t *)sobelInputs1 |=  values[1]<<16;
//	*(uint32_t *)sobelInputs1 |=  values[2]<<8;
//
//	printf("\nvalues\n");
//	printf("%d\n",values[0]);
//	printf("%d\n",values[1]);
//	printf("%d\n",values[2]);
//	printf("%d\n",values[3]);
//	printf("%d\n",values[4]);
//	printf("%d\n",values[5]);
//	printf("%d\n",values[6]);
//	printf("%d\n",values[7]);
//	printf("%d\n",values[8]);
//
//
//
//	*(uint32_t *)sobelInputs2 |=  values[3]<<24;
//	*(uint32_t *)sobelInputs2 |=  values[4]<<16;
//	*(uint32_t *)sobelInputs2 |=  values[5]<<8;
//
//	*(uint32_t *)sobelInputs3 |=  values[6]<<24;
//	*(uint32_t *)sobelInputs3 |=  values[7]<<16;
//	*(uint32_t *)sobelInputs3 |=  values[8]<<8;
//
//	*(uint32_t *)sobelControl =  1;
//
//	while(!*(uint32_t *)sobelControl == 2){
//		printf("stuck");
//	}
//
//	printf("%d",*(uint32_t *)sobelResults);
//	return *(uint32_t *)sobelResults;
//}
//
//// iterates of every row,col and channel in bmp_out to filter it and stores result in bmp_processed and then copies
//// the results stored in bmp_processed back to bmp_out after the filtering is complete
//int myFilter(struct bmp_out_struct *bmp_out) {
//    // make a local copy of bmp_out.bmp_buffer
//    unsigned char *bmp_buffer = bmp_out->bmp_buffer;
//    // assign memory for the processed bmp and have pointer bmp_processed to point to the memory address
//    unsigned char *bmp_processed = (unsigned char*) malloc(bmp_out->bmp_size);
//    // Iterate over full image
//    for (int row=0; row<bmp_out->height; ++row) {
//        for (int col=0; col<bmp_out->width; ++col) {
//            // Work on each channel independently
//            for (int chan=0; chan<bmp_out->pixel_size; ++chan) {
//                // Black border
//                unsigned char middle = 0;
//                // check that its not an edge row or column
//                if ((row>0 && row<bmp_out->height-1) && (col>0 && col<bmp_out->width-1)) {
//                	// kind of like a function that inputs row,col and outputs the bmp_buffer[row,col stuff]
//                    #define val(row, col) bmp_buffer[(row)*bmp_out->row_stride + (col)*bmp_out->pixel_size + chan]
//                    // Load all adjacent values to be passed into the sobel filter
//                    unsigned char values[9] = {
//                        val(row-1, col-1), val(row-1, col), val(row-1, col+1),
//                        val(row-0, col-1), val(row-0, col), val(row-0, col+1),
//                        val(row+1, col-1), val(row+1, col), val(row+1, col+1),
//                    };
//                    #undef val
//                    //sobel filter the values
//                    middle = fpgaFilter(values);
//                }
//                // store the filter output
//                bmp_processed[(row*bmp_out->row_stride) + col*bmp_out->pixel_size + chan] = middle;
//            }
//        }
//    }
//
//    // Replace input with output
//    memcpy(bmp_buffer, bmp_processed, bmp_out->bmp_size);
//    return 1;
//}
