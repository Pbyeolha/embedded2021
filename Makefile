CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: ledtest
ledtest: libMyPeri.a ledtest.c led.h
	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a: led.o 
	$(AR) rc libMyPeri.a led.o

led.o: led.c led.h
	$(CC) -o led.o -c led.c

clean :
	rm -rf *.o *.elf *.a
