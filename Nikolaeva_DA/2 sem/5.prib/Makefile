all : a.out run

prib.o : prib.c prib.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c prib.c 

main.o : main.c prib.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o prib.o
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic main.o prib.o -lm
