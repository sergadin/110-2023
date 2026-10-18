all : a.out run

makearray.o : makearray.c makearray.h
	gcc -c -g makearray.c 

main.o : main.c makearray.h 
	gcc -c -g main.c

run : a.out
	./a.out
	
a.out : main.o makearray.o
	gcc -g main.o makearray.o -lm
