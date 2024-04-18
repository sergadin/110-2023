all: a.out
        ./a.out
arrfun_val.o: find_root.c find_root.h
        gcc -c find_root.c
test.o: test.c arrfun_val.c
        gcc -c test.c
a.out: test.o find_root.o
        gcc test.o find_root.o
