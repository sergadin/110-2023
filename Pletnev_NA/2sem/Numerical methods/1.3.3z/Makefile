all : a.out run

1.3.3z.o : 1.3.3z.c 1.3.3z.h
	gcc -c 1.3.3z.c 

main.o : main.c 1.3.3z.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o 1.3.3z.o
	gcc main.o 1.3.3z.o -lm
