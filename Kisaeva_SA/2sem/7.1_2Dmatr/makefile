all : a.out run

rang2D.o : rang2D.c rang2D.h
	gcc -c rang2D.c 

main_matr2D.o : main_matr2D.c rang2D.h
	gcc -c main_matr2D.c 
	
run : a.out
	./a.out
	
a.out : main_matr2D.o rang2D.o
	gcc main_matr2D.o rang2D.o -lm