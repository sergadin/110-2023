#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

double pow_n(double x, int n)
{
	double y = 1;
	int i;   
	for(i = 0; i < n; i++)
		y = y * x;
	return y;
}

double taylor_log(double x, double eps, Error *err) {
	double value = 0;
	int n = 1;
	double term = x;
	int limit = 10000;
	*err = OK;
        if (x <= 0){
		*err = OGRAN;
		return -1;
	}
	if (eps <= 0) {
		*err = NO_EPS;
		printf("eps должно быть больше 0\n");
		return -1;
	}
	while(fabs(term) >=  eps)
	{
		value += term;
		n++;
		if(n % 2 == 0)
			term = ((-1) * pow_n(x,n)) / n;
		else
			term = pow_n(x,n) / n;
	}
	if (limit == 0){
		*err = NO_LIMIT;
		return -1;
	}
	return value;
}
    

