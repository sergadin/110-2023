all : a.out run

main.o : main.cpp appr_3.h
	g++ -c main.cpp

appr_3.o : appr_3.cpp appr_3.h
	g++ -c appr_3.cpp
	
run : a.out
	./a.out
	
	gnuplot plot1.gnu
	gnuplot plot2.gnu
	gnuplot plot3.gnu

a.out : main.o appr_3.o
	g++ main.o appr_3.o -lm
