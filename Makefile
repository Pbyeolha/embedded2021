CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: fndtest
fndtest: libMyPeri.a fndtest.c fnd.h
	$(CC) fndtest.c -l MyPeri -L. -o fndtest

libMyPeri.a: button.o led.o buzzer.o fnd.o
	$(AR) rc libMyPeri.a button.o led.o buzzer.o fnd.o

fnd.o: fnd.c fnd.h
	$(CC) -c fnd.c -o fnd.o

buzzer.o: buzzer.h buzzer.c
	$(CC) -c buzzer.c -o buzzer.o

button.o : button.h button.c
	$(CC) -c button.c -o button.o -lpthread

led.o: led.h led.c
	$(CC) -c led.c -o led.o

clean :
	rm -rf *.o *.elf *.a
