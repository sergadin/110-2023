all : a.out run
PosOfWord.o : PosOfWord.c PosOfWord.h
	gcc -c PosOfWord.c 

main.o : main.c PosOfWord.h
	gcc -c main.c 
  
run : a.out
	./a.out
  
a.out : main.o PosOfWord.o
	gcc main.o PosOfWord.o -lm

