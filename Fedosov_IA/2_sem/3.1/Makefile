all : a.out run
find_min.o : find_min.c find_min.h
	gcc -c find_min.c 

main.o : main.c find_min.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o find_min.o
	gcc main.o find_min.o -lm