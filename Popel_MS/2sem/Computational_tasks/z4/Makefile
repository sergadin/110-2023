all : a.out run

z4.o : z4.c z4.h
	gcc -c z4.c 

main4.o : main4.c z4.h
	gcc -c main4.c 
	
run : a.out
	./a.out
	
a.out : main4.o z4.o
	gcc main4.o z4.o -lm
