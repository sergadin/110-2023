all : a.out run

1.3root.o : 1.3root.c 1.3root.h
	gcc -c 1.3root.c 

mainroot.o : mainroot.c 1.3root.h
	gcc -c mainroot.c 
	
run : a.out
	./a.out
	
a.out : mainroot.o 1.3root.o
	gcc mainroot.o 1.3root.o -lm