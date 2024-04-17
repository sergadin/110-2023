all : a.out run
hermit_interpolation.o : hermit_interpolation.c hermit_interpolation.h
	gcc -c hermit_interpolation.c 

main.o : main.c hermit_interpolation.h
	gcc -c main.c 
	
run : a.out
	./a.out
	gnuplot plot.gnu
      
	
a.out : main.o hermit_interpolation.o
	gcc main.o hermit_interpolation.o -lm
	
