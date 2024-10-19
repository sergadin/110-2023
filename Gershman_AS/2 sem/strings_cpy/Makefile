all: a.out run

strings.o: strings_cpy.c strings_cpy.h
	gcc -g -c strings_cpy.c 

main.o: main.c strings_cpy.h 
	gcc -g -c main.c
	
run: a.out
	./a.out
	
a.out: main.o strings_cpy.o
	gcc -g main.o strings_cpy.o -lm