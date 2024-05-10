#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "integral.h"

static double max(double x, double y, double eps){
	double m_1;
	x = 0;
	y = 0;
	if (x > y){
		m_1 = x;
	}else{
		m_1 = y;
	}
	if (eps > m_1){
		return eps;
	}
	return m_1;
}
double integral(RRFun f, double a, double b, double eps, Error *err){
	int i, n = 1;
	double x0, x1;
	double integ_1 = 0;
	double integ_0 = 0;
	double h, limit = 1000;
	h = (b - a) / n;
	if (a > b)
	{
		*err = NO_INTER;
		return -1;
	} 
	*err = OK;
	do
	{
		integ_0 = integ_1; //запишем новое значение интеграла в старый, 
		integ_1 = 0;       //а новое обнулим
		for(i = 0; i < n; i++){
			x0 = a + i * h;
			x1 = a + (i + 1) * h;
			integ_1 += ((*f)(x0) + (*f)(x1)) * h / 2;
		}

		n *= 2;
		h = (b - a) / n;
	}
	while(fabs(integ_1 - integ_0) > (max(integ_0, integ_1, 1.0) * eps));
	limit -= 1;
	if (limit <= 0){
		*err = NA_LIMIT;
		return integ_0;
	}
	printf(" Значение интеграла %lf \n", integ_0);
	return integ_0;
}



