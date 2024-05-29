all : a.out run
determinant.o : determinant.c determinant.h
	gcc -c determinant.c 

main.o : main.c determinant.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o determinant.o
	gcc main.o determinant.o -lm

