all : a.out run

rectanglemeth.o : rectanglemeth.c rectanglemeth.h
	gcc -c -g rectanglemeth.c 

main.o : main.c rectanglemeth.h 
	gcc -c -g main.c

run : a.out
	./a.out
	
a.out : main.o rectanglemeth.o
	gcc -g main.o rectanglemeth.o -lm
