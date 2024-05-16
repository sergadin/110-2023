all : a.out run
Gaussian_method.o : Gaussian_method.c Gaussian_method.h
	gcc -c Gaussian_method.c 

main.o : main.c Gaussian_method.h
	gcc -c main.c 
	
run : a.out
	./a.out
      
	
a.out : main.o Gaussian_method.o
	gcc main.o Gaussian_method.o -lm
	