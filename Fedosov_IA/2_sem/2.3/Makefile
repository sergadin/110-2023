all : a.out run
simpson_integral.o : simpson_integral.c simpson_integral.h
	gcc -c simpson_integral.c 

main.o : main.c simpson_integral.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o simpson_integral.o
	gcc main.o simpson_integral.o -lm
