all : a.out run



compare_files.o : compare_files.c compare_files.h

	gcc -c -g compare_files.c



main.o : main.c compare_files.h

	gcc -c -g main.c

run : a.out

	./a.out



a.out : main.o compare_files.o

	gcc -g main.o compare_files.o -lm
