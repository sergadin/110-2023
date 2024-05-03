all : a.out run

z2_3.o : z2_3.c z2_3.h
	gcc -c z2_3.c 

main23.o : main23.c z2_3.h
	gcc -c main23.c 
	
run : a.out
	./a.out
	
a.out : main23.o z2_3.o
	gcc main23.o z2_3.o -lm