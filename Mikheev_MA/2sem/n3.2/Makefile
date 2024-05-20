all : a.out run
FindingMin.o : FindingMin.c FindingMin.h
	gcc -c FindingMin.c 

main.o : main.c FindingMin.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o FindingMin.o
	gcc main.o FindingMin.o -lm

