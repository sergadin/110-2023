all : a.out run

z3_13.o : z3_13.c z3_13.h
	gcc -c z3_13.c 

main313.o : main313.c z3_13.h
	gcc -c main313.c 
	
run : a.out
	./a.out
	
a.out : main313.o z3_13.o
	gcc main313.o z3_13.o -lm