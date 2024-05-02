all: a.out
	./a.out
task_1.o: task_1.c Header.h
	gcc -c task_1.c
Main.o: Main.c task_1.c
	gcc -c Main.c
a.out: Main.o task_1.o
	gcc Main.o task_1.o