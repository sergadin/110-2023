all : a.out run

z3_13.o : z3_13.c z3_13.h
	gcc -c z3_13.c 

main1.o : main1.c z3_13.h
	gcc -c main1.c 
	
run : a.out
	./a.out
	
a.out : main1.o z3_13.o
	gcc main1.o z3_13.o -lm