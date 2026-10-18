all: a.out run

gauss.o: gauss.c gauss.h
	gcc -g -c gauss.c 

main.o: main.c gauss.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o gauss.o
	gcc -g main.o gauss.o -lm
