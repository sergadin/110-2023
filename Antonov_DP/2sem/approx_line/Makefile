all: a.out
	./a.out
arrfun_val.o: approx_line.c approx_line.h
	gcc -c approx_line.c
test.o: test.c approx_line.c
	gcc -c test.c
a.out: test.o approx_line.o
	gcc test.o approx_line.o
