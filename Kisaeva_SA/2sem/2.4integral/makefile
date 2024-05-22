all : a.out run

2.4integ.o : 2.4integ.c 2.4integ.h
	gcc -c 2.4integ.c 

maininteg.o : maininteg.c 2.4integ.h
	gcc -c maininteg.c 
	
run : a.out
	./a.out
	
a.out : maininteg.o 2.4integ.o
	gcc maininteg.o 2.4integ.o -lm