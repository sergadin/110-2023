all: a.out
	./a.out
arrfun_val.o: inverse_matrix.c inverse_matrix.h
	gcc -c inverse_matrix.c
test.o: test.c inverse_matrix.c
	gcc -c test.c
a.out: test.o inverse_matrix.o
	gcc test.o inverse_matrix.o
