 all : a.out run

 det.o : det.c det.h
 	gcc -c det.c 

 main.o : main.c det.h
 	gcc -c main.c 
	
 run : a.out
 	./a.out
	
 a.out : main.o det.o
	gcc main.o det.o -lm
 