all : a.out run

parabola.o : parabola.c parabola.h
	gcc -c parabola.c 

mainpar.o : mainpar.c parabola.h
	gcc -c mainpar.c 
	
run : a.out
	./a.out
	
a.out : mainpar.o parabola.o
	gcc mainpar.o parabola.o -lm	
	
clean:
	rm -f *.o *.out
