all : a.out run


arr_val.o : arr_of_val.c arr_val.h

	gcc -c -g arr_val.c



main.o : main.c arr_val.h

	gcc -c -g main.c

run : a.out

	./a.out



a.out : main.o arr_val.o

	gcc -g main.o arr_val.o -lm