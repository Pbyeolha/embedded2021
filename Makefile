CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: ledtest.elf

ledtest.elf: libMyPeri.a
	$(CC) -l Myperi -L. -o ledtest.elf

libMyperi.a: led.o
	$(AR) rc libMyperi.a led.o

led.o: led.c led.h
	$(CC) -c led.c
clean :
	rm -rf *.o *.elf *.a
