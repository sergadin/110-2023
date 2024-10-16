all: a.out run

lagrangepolynom.o: lagrangepolynom.c lagrangepolynom.h
	gcc -c lagrangepolynom.c 

main.o: main.c lagrangepolynom.h 
	gcc -c main.c
	
run: a.out
	./a.out
	
	
a.out: main.o lagrangepolynom.o
	gcc main.o lagrangepolynom.o -lm
