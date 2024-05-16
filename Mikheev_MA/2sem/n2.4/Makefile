all : a.out run
CalculateTheInt.o : CalculateTheInt.c CalculateTheInt.h
	gcc -c CalculateTheInt.c 

main.o : main.c CalculateTheInt.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o CalculateTheInt.o
	gcc main.o CalculateTheInt.o -lm

