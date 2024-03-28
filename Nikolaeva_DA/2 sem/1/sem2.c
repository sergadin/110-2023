#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"hh.1"


typedef double(*f)(double);//пусть функция типа double


double composing_function(f *funcs, double eps, double x, Error *error){
	double y = x;
	int limit = 1000; //кол-во композиций функции f
	for(i = 0; i < limit; i++){
		y = funcs[i](y);
	}
	if(limit == 0){
		*error = infinity;
	}
	else{
		*error = OK;

	return y;
}


