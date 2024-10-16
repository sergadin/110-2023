all : a.out run

z1_3.o : z1_3.c z1_3.h
	gcc -c z1_3.c 

main.o : main.c z1_3.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z1_3.o
	gcc main.o z1_3.o -lm
