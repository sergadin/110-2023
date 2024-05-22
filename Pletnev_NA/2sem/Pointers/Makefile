all : a.out run
z7.o : z7.c z7.h
	gcc -c z7.c 

chz7.o : chz7.c z7.h
	gcc -c chz7.c 
	
run : a.out
	./a.out
	
a.out : ch7.o z7.o
	gcc chz7.o z7.o -lm

