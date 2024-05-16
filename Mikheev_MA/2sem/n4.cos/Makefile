all : a.out run
TaylorOfcos.o : TaylorOfcos.c TaylorOfcos.h
    gcc -c TaylorOfcos.c 

main.o : main.c TaylorOfcos.h
    gcc -c main.c 
  
run : a.out
    ./a.out
  
a.out : main.o TaylorOfcos.o
    gcc main.o TaylorOfcos -lm

