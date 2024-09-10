all : a.out run
FormatingPar.o : FormatingPar.c FormatingPar.h
	gcc -c FormatingPar.c 

main.o : main.c FormatingPar.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o FormatingPar.o
	gcc main.o FormatingPar.o -lm

