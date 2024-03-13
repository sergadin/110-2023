all : a.out run
bisection.o : bisection.c bisection.h
	gcc -c bisection.c 

main.o : main.c bisection.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o bisection.o
	gcc main.o bisection.o -lm
