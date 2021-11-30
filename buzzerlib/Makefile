CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: buzzertest
buzzertest: libMyPeri.a buzzertest.c buzzer.h
   $(CC) buzzertest.c -l MyPeri -L. -o buzzertest

libMyPeri.a: button.o led.o buzzer.o
   $(AR) rc libMyPeri.a button.o led.o buzzer.o

buzzer.o: buzzer.h buzzer.c
   $(CC) -c buzzer.c -o buzzer.o

button.o : button.h button.c
   $(CC) -c button.c -o button.o

led.o: led.h led.c
   $(CC) -c led.c -o led.o

clean :
   rm -rf *.o *.elf *.a