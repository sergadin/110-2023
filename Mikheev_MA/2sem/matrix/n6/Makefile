all : a.out run
MethZeyd.o : MethZeyd.c MethZeyd.h
	gcc -c MethZeyd.c 

main.o : main.c MethZeyd.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o MethZeyd.o
	gcc main.o MethZeyd.o -lm

