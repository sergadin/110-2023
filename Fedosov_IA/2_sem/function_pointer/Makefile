all : a.out run
is_zero.o : is_zero.c is_zero.h
	gcc -c is_zero.c 

main.o : main.c is_zero.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o is_zero.o
	gcc main.o is_zero.o -lm
