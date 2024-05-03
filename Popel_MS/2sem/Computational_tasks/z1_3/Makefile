all : a.out run

z1_3.o : z1_3.c z1_3.h
	gcc -c z1_3.c 

main1.o : main1.c z1_3.h
	gcc -c main1.c 
	
run : a.out
	./a.out
	
a.out : main1.o z1_3.o
	gcc main1.o z1_3.o -lm
