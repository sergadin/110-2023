all : a.out run

matr.o : matr.c matr.h
	gcc -c matr.c 

mainmatr.o : mainmatr.c matr.h
	gcc -c mainmatr.c 
	
run : a.out
	./a.out
	
a.out : mainmatr.o matr.o
	gcc mainmatr.o matr.o -lm
