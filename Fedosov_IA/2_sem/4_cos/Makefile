all : a.out run
my_cos.o : my_cos.c my_cos.h
	gcc -c my_cos.c 

main.o : main.c my_cos.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o my_cos.o
	gcc main.o my_cos.o -lm
