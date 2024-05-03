all: a.out run

fillValueArray.o: findMinValue.c findMinValue.h
	gcc -c findMinValue.c 

main.o: main.c findMinValue.h 
	gcc -c main.c
	
run: a.out
	./a.out
	
a.out: main.o findMinValue.o
	gcc main.o findMinValue.o -lm
