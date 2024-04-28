all: a.out
	./a.out
arrfun_val.o: integration.c integration.h
	gcc -c integration.c
test.o: test.c integration.c
	gcc -c test.c
a.out: test.o integration.o
	gcc test.o integration.o
