CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: textlcdtest
colorledtest: libMyPeri.a colorledtest.c colorled.h
	$(CC) colorledtest.c -l MyPeri -L. -o colorledtest

libMyPeri.a: button.o led.o buzzer.o fnd.o textlcd.o colorled.o
	$(AR) rc libMyPeri.a button.o led.o buzzer.o fnd.o textlcd.o colorled.o

colorled.o: colorled.c colorled.h
	$(CC) -c colorled.c -o colorled.o

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
