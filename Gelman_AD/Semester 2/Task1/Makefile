all : a.out run
task_1.o : task_1.c Header.h
	gcc -c task_1.c 

Main.o : Main.c Header.h
	gcc -c Main.c 
	
run : a.out
	./a.out
	
a.out : Main.o task_1.o
	gcc Main.o task_1o -lm