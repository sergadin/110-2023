all : a.out run

z2_2.o : z2_2.c z2_2.h
	gcc -c z2_2.c 

main.o : main.c z2_2.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z2_2.o
	gcc main.o z2_2.o -lm