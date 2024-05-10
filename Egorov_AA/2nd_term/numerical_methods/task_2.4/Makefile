all: a.out run

calculateIntegral.o: calculateIntegral.c calculateIntegral.h
	gcc -c calculateIntegral.c 

main.o: main.c calculateIntegral.h 
	gcc -c main.c
	
run: a.out
	./a.out
	
a.out: main.o calculateIntegral.o
	gcc main.o calculateIntegral.o -lm
