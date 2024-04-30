all : a.out run
z7.o : z7.c z7.h
	gcc -c z7.c 

ch7.o : ch7.c z7.h
	gcc -c ch7.c 
	
run : a.out
	./a.out
	
a.out : ch7.o z7.o
	gcc ch7.o z7.o -lm

