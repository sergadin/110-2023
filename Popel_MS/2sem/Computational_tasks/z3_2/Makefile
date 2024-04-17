all : a.out run

z3_2.o : z3_2.c z3_2.h
	gcc -c z3_2.c 

main3.o : main3.c z3_2.h
	gcc -c main3.c 
	
run : a.out
	./a.out
	
a.out : main3.o z3_2.o
	gcc main3.o z3_2.o -lm
