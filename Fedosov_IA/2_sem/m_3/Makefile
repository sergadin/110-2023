all : a.out run
get_inverse.o : get_inverse.c get_inverse.h
	gcc -c -g get_inverse.c 

main.o : main.c get_inverse.h
	gcc -c -g main.c 
	
run : a.out
	./a.out
      
	
a.out : main.o get_inverse.o
	gcc main.o get_inverse.o -lm