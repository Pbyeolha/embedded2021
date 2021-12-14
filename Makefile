CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: project

project: libMyPeri.a main.c
	$(CC) main.c -l MyPeri -L. -o project -lpthread

libMyPeri.a: button.o led.o buzzer.o fnd.o textlcd.o colorled.o T.o G.o bitmap.o touch.o
	$(AR) rc libMyPeri.a button.o led.o buzzer.o fnd.o textlcd.o colorled.o T.o G.o bitmap.o touch.o

touch.o: touch.c touch.h
	$(CC) -c touch.c -o touch.o

bitmap.o: bitmap.c bitmap.h
	$(CC) -c bitmap.c -o bitmap.o

G.o: G.c G.h
	$(CC) -c G.c -o G.o

T.o: T.c temperature.h
	$(CC) -c T.c -o T.o

colorled.o: colorled.c colorled.h
	$(CC) -c colorled.c -o colorled.o

textlcd.o: textlcd.c textlcd.h
	$(CC) -c textlcd.c -o textlcd.o

fnd.o: fnd.c fnd.h
	$(CC) -c fnd.c -o fnd.o

buzzer.o: buzzer.h buzzer.c
	$(CC) -c buzzer.c -o buzzer.o

button.o : button.h button.c
	$(CC) -c button.c -o button.o

led.o: led.h led.c
	$(CC) -c led.c -o led.o

clean :
	rm -rf *.o *.elf *.a
