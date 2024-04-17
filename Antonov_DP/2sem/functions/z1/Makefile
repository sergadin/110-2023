all: a.out
	./a.out
arrfun_val.o: arrfun_val.c arrfun_val.h
	gcc -c arrfun_val.c
	echo "о, я молодец"
test.o: test.c arrfun_val.c
	gcc -c test.c
a.out: test.o arrfun_val.o
	gcc test.o arrfun_val.o
