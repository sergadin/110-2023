all : a.out run
find_difference.o : find_difference.c find_difference.h
	gcc -c find_difference.c 

main.o : main.c find_difference.h
	gcc -c main.c 
	
run : a.out
	./a.out
      
	
a.out : main.o find_difference.o
	gcc main.o find_difference.o -lm