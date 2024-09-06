all : a.out run

countcos.o : countcos.c countcos.h
	gcc -c -g countcos.c 

main.o : main.c countcos.h 
	gcc -c -g main.c

run : a.out
	./a.out
	
a.out : main.o countcos.o
	gcc -g main.o countcos.o -lm
