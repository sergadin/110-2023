all : a.out run

integral.o : integral.c integral.h
	gcc -c integral.c 

maininteg.o : maininteg.c integral.h
	gcc -c maininteg.c 
	
run : a.out
	./a.out
	
a.out : maininteg.o integral.o
	gcc maininteg.o integral.o -lm	
	
clean:
	rm -f *.o *.out
