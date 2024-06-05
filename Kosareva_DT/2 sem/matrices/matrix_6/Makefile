all : a.out run

main.o : main.c matrix_6.h
	gcc -c main.c

matrix_6.o : matrix_6.c matrix_6.h
	gcc -c matrix_6.c

a.out : main.o matrix_6.o
	gcc main.o matrix_6.o -lm

run : a.out
	./a.out
