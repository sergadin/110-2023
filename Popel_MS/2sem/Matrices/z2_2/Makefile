all : a.out run

z2_2.o : z2_2.c z2_2.h
	gcc -c z2_2.c 

main2.o : main2.c z2_2.h
	gcc -c main2.c 
	
run : a.out
	./a.out
	
a.out : main2.o z2_2.o
	gcc main2.o z2_2.o -lm