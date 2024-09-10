all : a.out run

iter.o : iter.c iter.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c iter.c 

main.o : main.c iter.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o iter.o
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic main.o iter.o -lm
