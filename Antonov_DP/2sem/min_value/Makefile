all: a.out
	./a.out
arrfun_val.o: min_value.c min_value.h
	gcc -c min_value.c
test.o: test.c min_value.c
	gcc -c test.c
a.out: test.o min_value.o
	gcc test.o min_value.o
