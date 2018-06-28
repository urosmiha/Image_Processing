#
TARGET = memdjpeg_VGA

#
DIRECTORY = F:

#
PLATFORM = ARM

#
ifeq ($(PLATFORM),ARM)
	CROSS_COMPILE = arm-linux-gnueabihf-
	CFLAGS = -g -Wall  -I ${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include \
		-I ${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
	LDFLAGS =  -g -Wall
	CC = $(CROSS_COMPILE)gcc -std=c99
	ARCH= arm
else
	CC = gcc
endif

LDFLAGS += -ljpeg -lm

#profile
CFLAGS += -pg
LDFLAGS += -pg

$(TARGET): $(TARGET).o

build: $(TARGET)

#$(TARGET): main.o
#	$(CC) $(LDFLAGS)   $^ -o $@

#%.o : %.c
#	$(CC) $(CFLAGS) -c $< -o $@

OUTPUTS = memdjpeg memdjpeg_VGA
.PHONY: clean
clean:
	rm -f $(OUTPUTS) *.a *.o *~

.PHONEY: load
load: $(TARGET)
	cp -f $< $(DIRECTORY)/$(TARGET)

.PHONY: output_clean
output_clean:
	rm output*.ppm
