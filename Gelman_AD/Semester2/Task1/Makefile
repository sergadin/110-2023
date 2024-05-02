all: a.out
	./a.out
value.o: value.c value.h
	gcc -c value.c
Main.o: Main.c value.c
	gcc -c Main.c
a.out: Main.o value.o
	gcc Main.o value.o