all : a.out run

taylor_log.o : taylor_log.c taylor_log.h
	gcc -c taylor_log.c 

main.o : main.c taylor_log.h
	gcc -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o taylor_log.o
	gcc main.o taylor_log.o -lm
