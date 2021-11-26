CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: final.elf

final.elf: libMyPeri.a ledtest.o
	$(CC) ledtest.o -l MyPeri -L. -o final.elf

libMyPeri.a: led.o 
	$(AR) rc libMyPeri.a led.o

led.o: led.c led.h

ledtest.o: ledtest.c led.h

clean :
	rm -rf *.o *.elf *.a
