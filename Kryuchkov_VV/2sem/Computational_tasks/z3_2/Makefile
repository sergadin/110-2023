all : a.out run

z3_2.o : z3_2.c z3_2.h
	gcc -c z3_2.c 

main.o : main.c z3_2.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z3_2.o
	gcc main.o z3_2.o -lm
