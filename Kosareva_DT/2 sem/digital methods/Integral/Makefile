all : a.out run

main.o : main.c int_1.h
	gcc -c main.c

int_1.o : int_1.c int_1.h
	gcc -c int_1.c
	
run : a.out
	./a.out

a.out : main.o int_1.o
	gcc main.o int_1.o -lm
