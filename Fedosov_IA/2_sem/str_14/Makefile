all : a.out run
formate.o : formate.c formate.h
	gcc -c formate.c 

main.o : main.c formate.h
	gcc -c main.c 
	
run : a.out
	./a.out
      
	
a.out : main.o formate.o
	gcc main.o formate.o -lm