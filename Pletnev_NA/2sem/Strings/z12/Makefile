all: a.out run

strings.o: strings.c strings.h
	gcc -g -c strings.c 

main.o: main.c strings.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o strings.o
	gcc -g main.o strings.o -lm
