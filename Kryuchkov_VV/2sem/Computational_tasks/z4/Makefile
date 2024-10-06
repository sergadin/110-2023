all : a.out run

z4.o : z4.c z4.h
	gcc -c z4.c 

main.o : main.c z4.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z4.o
	gcc main.o z4.o -lm
