all : a.out run

find_diff.o : find_diff.c find_diff.h
	gcc -c find_diff.c 

main.o : main.c find_diff.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o find_diff.o
	gcc main.o find_diff.o -lm