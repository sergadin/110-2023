all : a.out run

fillValueArray.o : fillValueArray.c fillValueArray.h
	gcc -c fillValueArray.c 

main.o : main.c fillValueArray.h 
	gcc -c main.c
run : a.out
	./a.out
	
a.out : main.o fillValueArray.o
	gcc main.o fillValueArray.o -lm
