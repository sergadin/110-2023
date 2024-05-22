all : a.out run
mas_of_arg.o : mas_of_arg.c mas_of_arg.h
	gcc -c mas_of_arg.c 

main.o : main.c mas_of_arg.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o mas_of_arg.o
	gcc main.o mas_of_arg.o -lm

