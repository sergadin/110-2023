all : a.out run

z1_3.o : 1.3root.c 1.3root.h
	gcc -c 1.3root.c 

main1.o : mainroot.c 1.3root.h
	gcc -c mainroot.c 
	
run : a.out
	./a.out
	
a.out : mainroot.o 1.3root.o
	gcc mainroot.o 1.3root.o -lm