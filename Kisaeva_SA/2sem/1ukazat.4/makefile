all: a.out run

scalar_product.o: scalar_product.c scalar_product.h
	gcc -c scalar_product.c

a.out: scalar_product.o main4.o
	gcc -o a.out scalar_product.o main4.o

main4.o: main4.c scalar_product.h 
	gcc -g -c main4.c 

run: a.out
	./a.out