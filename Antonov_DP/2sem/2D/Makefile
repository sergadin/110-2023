all: a.out
	./a.out
arrfun_val.o: solv_lin_equations.c solv_lin_equations.h
	gcc -c solv_lin_equations.c
test.o: test.c solv_lin_equations.c
	gcc -c test.c
a.out: test.o solv_lin_equations.o
	gcc test.o solv_lin_equations.o
