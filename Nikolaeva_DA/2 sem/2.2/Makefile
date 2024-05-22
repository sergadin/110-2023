all : a.out run

integral.o : integral.c integral.h
	gcc -c -g integral.c 

maininteg.o : maininteg.c integral.h
	gcc -c -g maininteg.c 
	
run : a.out
	./a.out
	
a.out : maininteg.o integral.o
	gcc -g maininteg.o integral.o -lm	
	
clean:
	rm -f *.o *.out
