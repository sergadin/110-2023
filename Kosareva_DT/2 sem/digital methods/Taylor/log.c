#include "log.h"
#include <math.h>
//#include <stdio.h>

double LOG(double x, double eps) {
	int n = 1;
	double answ = 0;
	double add;
	
	add = x/n;
	
	while ((fabs(add) > eps) && (n < 1000000000)) {
		answ += add;
		//printf("%lf, %lf\n", add, answ);
		add = 0 - add*x*n / (n+1);
		n++;
	}
	
	return answ;
}
