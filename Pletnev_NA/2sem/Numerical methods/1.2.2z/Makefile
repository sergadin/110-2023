all : a.out run

1.2.2z.o : 1.2.2z.c 1.2.2z.h
	gcc -c 1.2.2z.c 

main.o : main.c 1.2.2z.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o 1.2.2z.o
	gcc main.o 1.2.2z.o -lm
