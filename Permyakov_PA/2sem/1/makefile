all: a.out

a.out: main.o values_at_point.o
	gcc main.o values_at_point.o -o
$@
.o:
	gcc -c $< -o $@
