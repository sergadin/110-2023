all: a.out
	./a.out
arrfun_val.o: teylor_cos.c teylor_cos.h
	gcc -c teylor_cos.c
test.o: test.c teylor_cos.c
	gcc -c test.c
a.out: test.o teylor_cos.o
	gcc test.o teylor_cos.o
