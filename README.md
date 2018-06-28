# Image_Processing
Designed on Altera SoC board - FPGA Cyclone V and ARM Processor

Main VHDL files are stored in 'vhdl' directory (project was done Quartus 16.0 IDE) ** files might not be compatible with previous versions of Quartus. QSys will probably show some weird as errors.

Software files are contained in 'src' folder. The main file is named 'memdjpeg_VGA.c', which contains all the necessary logic for executing the program.

## Compiling and Running
When programming the board make sure that both processor and fpga are visible in programmer.
You might have to drag and drop .sof file from the folder.

Software is compiled through EDS Shell just by 'make' command

'memdjpeg_VGA' binary should be generated. Copy this to flash drive, together with SZS.mjpeg and SZS.mjpeg.chiper files.

1. Connect the board and PC with serial cable. In Putty select serial port with baud rate of 115200
2. Log in as root
3. mount /root/dev1 /mnt1 - Mount usb
4. cd /mnt
5. ./memjpeg_VGA SZS.mjpeg SZS.mjpeg.chiper
6. umount /mnt  - Unmount device

## Known fixes to potential issues
Change use of DSP blocks to logic elements if Quatrus complains about it.
