all : a.out run

pos_word.o : pos_word.c pos_word.h
	gcc -c pos_word.c 

main_str4.o : main_str4.c pos_word.h
	gcc -c main_str4.c 
	
run : a.out
	./a.out
	
a.out : main_str4.o pos_word.o
	gcc main_str4.o pos_word.o -lm