all : a.out run

kor.o : kor.c kor.h
	gcc -c kor.c 

mainkor.o : mainkor.c kor.h
	gcc -c mainkor.c 
	
run : a.out
	./a.out
	
a.out : mainkor.o kor.o
	gcc mainkor.o kor.o -lm	
