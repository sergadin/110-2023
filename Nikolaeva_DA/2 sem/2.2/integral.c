#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "integral.h"

static double max(double x, double y, double eps);
static double max(double x, double y, double eps){
	double m_1;
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
	int n = 1;
	double integ_1;
	double integ_0;
	double h = (b - a) / n;
	if (a > b)
	{
		*err = NO_INTER;
		return -1;
	}
	do 
	{
		integ_0 = integ_1; //запишем новое значение интеграла в старый, 
		integ_1 = 0;       //а новое обнулим
		for(int i = 0; i < n; i++){
			double x0 = a + i * h;
			double x1 = a + (i + 1) * h;
			integ_1 += ((*f)(x0) + (*f)(x1)) * h / 2;
		}

		n *= 2;
		h = (b - a) / n;
	}
	while(fabs(integ_1 -integ_0) > (max(integ_1, integ_0, 1.0) * eps));
	printf(" Значение интеграла %lf \n", integ_0);
	return integ_0;
}

