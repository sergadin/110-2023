all : a.out run

findmin.o : findmin.c findmin.h
	gcc -c -g findmin.c 

main.o : main.c findmin.h 
	gcc -c -g main.c

run : a.out
	./a.out
	
a.out : main.o findmin.o
	gcc -g main.o findmin.o -lm
