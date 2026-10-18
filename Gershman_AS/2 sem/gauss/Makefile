all: a.out run

matrix.o: matrix.c gauss_method.h
	gcc -g -c gauss_method.c 

main.o: main.c gauss_method.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o matrix.o
	gcc -g main.o gauss_method.o -lm