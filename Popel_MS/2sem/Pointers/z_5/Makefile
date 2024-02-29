all : a.out run
z5.o : z5.c z5.h
	gcc -c z5.c 

main.o : main.c z5.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z5.o
	gcc main.o z5.o -lm

