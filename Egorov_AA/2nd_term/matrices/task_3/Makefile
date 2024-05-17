all: a.out run

matrix.o: matrix.c matrix.h
	gcc -g -c matrix.c 

main.o: main.c matrix.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o matrix.o
	gcc -g main.o matrix.o -lm
