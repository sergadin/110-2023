all : a.out run

fillValueArray.o : determine_values.c determine_values.h
	gcc -c -g determine_values.c 

main.o : main.c determine_values.h
	gcc -c -g main.c
run : a.out
	./a.out
        
a.out : main.o determine_values.o
	gcc -g main.o determine_values.o -lm

