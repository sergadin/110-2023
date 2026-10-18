all : a.out run

z5_5.o : z5_5.cpp z5_5.h
	g++ -c z5_5.cpp 

main.o : main.cpp z5_5.h
	g++ -c main.cpp 
	
run : a.out
	./a.out
	chmod +x gnuplot.gpi
	./gnuplot.gpi
	
a.out : main.o z5_5.o
	g++ main.o z5_5.o -lm
	
