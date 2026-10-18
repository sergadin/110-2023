all : a.out run
newton_method.o : newton_method.c newton_method.h
	gcc -c newton_method.c 

ch1.1.2z.o : newton_method.c newton_method.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o newton_method.o
	gcc main.o newton_method.o -lm