all : a.out run
1.1.2z.o : 1.1.2z.c 1.1.2z.h
	gcc -c 1.1.2z.c 

ch1.1.2z.o : 1.1.2z.c 1.1.2z.h
	gcc -c ch1.1.2z.c 
	
run : a.out
	./a.out
	
a.out : ch1.1.2z.o 1.1.2z.o
	gcc ch1.1.2z.o 1.1.2z.o -lm

