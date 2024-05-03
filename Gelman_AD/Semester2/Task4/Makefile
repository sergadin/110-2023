all: a.out run

minvalue.o : minvalue.c minvalue.h
gcc - c minfalue.c

main.o : main.c minvalue.h
gcc - c main.c

run : a.out
. / a.out

a.out : main.o minvalue.o
gcc main.o minvalue.o - lm