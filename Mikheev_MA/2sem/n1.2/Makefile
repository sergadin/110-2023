all : a.out run
FindingTheRoot.o : FindingTheRoot.c FindingTheRoot.h
    gcc -c FindingTheRoot.c 

main.o : main.c FindingTheRoot.h
    gcc -c main.c 
  
run : a.out
    ./a.out
  
a.out : main.o FindingTheRoot.o
    gcc main.o FindingTheRoot -lm
