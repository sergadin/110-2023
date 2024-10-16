all : a.out run

z2_3.o : z2_3.c z2_3.h
	gcc -c z2_3.c 

main.o : main.c z2_3.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z2_3.o
	gcc main.o z2_3.o -lm
