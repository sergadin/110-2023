all : pnt_prog
z5.o : z5.c 
	gcc -c z5.c 

main.o : main.c 
	gcc -c main.c 
	
	
pnt_prog : main.o z5.o
	gcc main.o z5.o -lm -o  pnt_prog
