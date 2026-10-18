all : a.out run

integral.o : integral.c integral.h
	gcc -c integral.c 

main.o : main.c integral.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o integral.o
	gcc main.o integral.o -lm