all: a.out run

matrix.o: matrix.c matrix.h
	gcc -c matrix.c 

main.o: main.c matrix.h 
	gcc -c main.c
	
run: a.out
	./a.out
	
a.out: main.o matrix.o
	gcc main.o matrix.o -lm
