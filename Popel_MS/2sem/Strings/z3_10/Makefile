all : a.out run

z3_10.o : z3_10.c z3_10.h
	gcc -c z3_10.c 

main310.o : main310.c z3_10.h
	gcc -c main310.c 
	
run : a.out
	./a.out
	
a.out : main310.o z3_10.o
	gcc main310.o z3_10.o -lm