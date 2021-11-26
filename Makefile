CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: led.h led.c
	$(CC) -c led.c -o led.o
	$(AR) rc libMyPeri.a led.o

led_OnOff: ledtest.c
	$(CC) -o led_OnOff ledtest.c -l MyPeri -L.

clean :
	rm -rf *.o *.elf *.a
