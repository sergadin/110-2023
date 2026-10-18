all : a.out run

real.o : real.c real.h
	gcc -c real.c 

main.o : main.c real.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o real.o
	gcc main.o real.o -lm
