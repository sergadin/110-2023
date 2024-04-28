all : a.out run

fillValueArray.o : fillValueArray.c fillValueArray.h
	gcc -c -g fillValueArray.c 

main.o : main.c fillValueArray.h 
	gcc -c -g main.c
run : a.out
	./a.out
	
a.out : main.o fillValueArray.o
	gcc -g main.o fillValueArray.o -lm
