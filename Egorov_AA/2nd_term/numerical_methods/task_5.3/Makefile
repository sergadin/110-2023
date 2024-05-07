all: a.out run

interpolation.o: interpolation.c interpolation.h
	gcc -c interpolation.c 

main.o: main.c interpolation.h 
	gcc -c interpolation.c
	
run: a.out
	./a.out
	
a.out: main.o interpolation.o
	gcc main.o interpolation.o -lm
