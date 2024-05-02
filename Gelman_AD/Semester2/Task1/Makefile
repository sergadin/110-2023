all: a.out
	./a.out
value.o: value.c value.h
	gcc -c value.c
main.o: main.c value.c
	gcc -c main.c
a.out: main.o value.o
	gcc main.o value.o