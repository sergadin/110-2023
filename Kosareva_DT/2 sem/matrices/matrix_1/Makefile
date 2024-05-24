all : a.out run

main.o : main.c matrix_1.h
	gcc -c main.c

operations.o : operations.c matrix_1.h
	gcc -c operations.c

matrix_1.o : matrix_1.c matrix_1.h
	gcc -c matrix_1.c

a.out : main.o matrix_1.o operations.o
	gcc main.o matrix_1.o operations.o -lm

run : a.out
	./a.out
