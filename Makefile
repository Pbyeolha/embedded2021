CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: buttontest
buttontest: libMyPeri.a buttontest.c button.h
	$(CC) buttontest.c -l MyPeri -L. -o buttontest

libMyPeri.a: button.o led.o
	$(AR) rc libMyPeri.a button.o led.o

button.o: button.h button.c
	$(CC) -c button.c -o button.o

led.o: led.h led.c
	$(CC) -c led.c -o led.o

clean :
	rm -rf *.o *.elf *.a
