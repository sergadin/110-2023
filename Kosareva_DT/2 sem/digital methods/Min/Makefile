all : a.out run

main.o : main.c min_3.h
	gcc -c main.c

min_3.o : min_3.c min_3.h
	gcc -c min_3.c
	
run : a.out
	./a.out

a.out : main.o min_3.o
	gcc main.o min_3.o -lm
