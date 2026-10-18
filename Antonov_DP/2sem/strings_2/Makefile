all: a.out
	./a.out
arrfun_val.o: del_comment.c del_comment.h
	gcc -c del_comment.c
test.o: test.c del_comment.c
	gcc -c test.c
a.out: test.o del_comment.o
	gcc test.o del_comment.o
