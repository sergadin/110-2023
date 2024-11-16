all: a.out run

Matrix_1D.o: Matrix_1D.c Matrix_1D.h
	gcc -c Matrix_1D.c

main.o: main.c Matrix_1D.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o Matrix_1D.o
	gcc -g main.o Matrix_1D.o -lm