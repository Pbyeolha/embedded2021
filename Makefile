CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: textlcdtest
textlcdtest: libMyPeri.a textlcdtest.c textlcd.h
	$(CC) textlcdtest.c -l MyPeri -L. -o textlcdtest

libMyPeri.a: button.o led.o buzzer.o fnd.o textlcd.o
	$(AR) rc libMyPeri.a button.o led.o buzzer.o fnd.o textlcd.o

textlcd.o: textlcd.c textlcd.h
	$(CC) -c textlcd.c -o textlcd.o

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
