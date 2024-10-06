all: a.out run

log.o: log.c log.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c log.c

main.o: main.c log.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c main.c

run: a.out
	./a.out

a.out: main.o log.o
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic main.o log.o -o a.out -lm

