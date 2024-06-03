all: a.out
	./a.out
arrfun_val.o: str_property.c str_property.h
	gcc -c str_property.c
test.o: test.c str_property.c
	gcc -c test.c
a.out: test.o str_property.o
	gcc test.o str_property.o
