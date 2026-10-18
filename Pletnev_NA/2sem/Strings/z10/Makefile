all : a.out run

z3_10.o : z3_10.c z3_10.h
	gcc -c z3_10.c 

main.o : main.c z3_10.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o z3_10.o
	gcc main.o z3_10.o -lm