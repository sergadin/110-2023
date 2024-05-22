all : a.out run

log.o : log.c log.h
	gcc -c log.c 

mainlog.o : mainlog.c log.h
	gcc -c mainlog.c 
	
run : a.out
	./a.out
	
a.out : mainlog.o log.o
	gcc mainlog.o log.o -lm	
	
clean:
	rm -f *.o *.out
