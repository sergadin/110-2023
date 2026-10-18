all: a.out run

stroki.o: stroki.c stroki.h
	gcc -g -c stroki.c 

main.o: main.c stroki.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o stroki.o
	gcc -g main.o stroki.o -lm
