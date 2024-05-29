all : a.out run

main.o : main.c root_3.h
	gcc -c main.c

root_3.o : root_3.c root_3.h
	gcc -c root_3.c
	
run : a.out
	./a.out

a.out : main.o root_3.o
	gcc main.o root_3.o -lm
