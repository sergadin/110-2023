all : a.out run

4.taylor_cos.o: 4.taylor_cos.c 4.taylor_cos.h
	gcc -c 4.taylor_cos.c

main_cos.o: main_cos.c 4.taylor_cos.h
	gcc -c main_cos.c 
	
run : a.out
	./a.out
	
a.out : main_cos.o 4.taylor_cos.o
	gcc main_cos.o 4.taylor_cos.o -lm	