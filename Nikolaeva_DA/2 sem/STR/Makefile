all : a.out run

str.o : str.c str.h
	gcc -c str.c 

main.o : main.c str.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o str.o
	gcc main.o str.o -lm
