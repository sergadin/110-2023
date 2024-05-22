all : a.out run

pointer_7.o : pointer_7.c pointer_7.h
	gcc -c pointer_7.c

main.o : main.c pointer_7.h
	gcc -c main.c

run : a.out
	./a.out
	
a.out : main.o pointer_7.o
	gcc main.o pointer_7.o -lm
