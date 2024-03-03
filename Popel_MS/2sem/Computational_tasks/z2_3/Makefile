all : a.out run

z2_3.o : z2_3.c z2_3.h
	gcc -c z2_3.c 

main2.o : main2.c z2_3.h
	gcc -c main2.c 
	
run : a.out
	./a.out
	
a.out : main2.o z2_3.o
	gcc main2.o z2_3.o -lm
