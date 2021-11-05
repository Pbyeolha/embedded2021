all : final.elf

final.elf : main.o 1.o 2.o
	gcc main.o 1.o 2.o -o final.elf

main.o : main.c myProject.h
	gcc main.c -o

1.o : 1.c myProject.h
	gcc 1.c -o

2.o : 2.c myProject.h
	gcc 2.c -o

clean :
	rm -rf *.o *.elf
