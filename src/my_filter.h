#ifndef MY_FILTER_H
#define MY_FILTER_H
#include "Computer_System.h"
struct bmp_out_struct {
    unsigned char *bmp_buffer;
    unsigned long bmp_size;
    int row_stride;
    int width;
    int height;
    int pixel_size;
};
//
//void initFilter();
//int fpgaBMP(struct bmp_out_struct *bmp_out);
//int myFilter(struct bmp_out_struct *bmp_out);
//void fpgaFilter(unsigned char values[9]);

#endif /* MY_TRIVIUM_H */
