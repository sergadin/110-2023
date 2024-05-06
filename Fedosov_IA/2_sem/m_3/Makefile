all : a.out run
get_inverse.o : get_inverse.c get_inverse.h
	gcc -c get_inverse.c 

main.o : main.c get_inverse.h
	gcc -c main.c 
	
run : a.out
	./a.out
      
	
a.out : main.o get_inverse.o
	gcc main.o get_inverse.o -lm