all : a.out run

3.2min.o : 3.2min.c 3.2min.h
	gcc -c 3.2min.c 

main_min.o : main_min.c 3.2min.h
	gcc -c main_min.c 
	
run : a.out
	./a.out
	
a.out : main_min.o 3.2min.o
	gcc main_min.o 3.2min.o -lm