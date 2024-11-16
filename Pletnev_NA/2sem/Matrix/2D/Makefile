all: a.out
	./a.out
    
Matrix_D2.o: Matrix_2D.c Matrix_2D.h
	gcc -c Matrix_2D.c
    
main.o: main.c Matrix_2D.c
	gcc -c main.c
    
a.out: main.o Matrix_2D.o
	gcc main.o Matrix_2D.o
