all : a.out run

findroot.o : findroot.c findroot.h
	gcc -c -g findroot.c 

main.o : main.c findroot.h 
	gcc -c -g main.c

run : a.out
	./a.out
	
a.out : main.o findroot.o
	gcc -g main.o findroot.o -lm
