#include "appr_3.h"

double square(dot A, dot B, dot C, double x) {
	double a, b, c; //коэффициенты
	
	a = (B.y-A.y)/(B.x-A.x)/(B.x-C.x) + (C.y-A.y)/(C.x-A.x)/(C.x-B.x);
	b = (C.y-A.y) / (C.x-A.x) - a*(C.x+A.x);
	c = A.y - a*A.x*A.x - b*A.x;
	
	return a*x*x + b*x + c;
}


void Y(R_Rfun f, const std::vector<double> &x, std::vector<double> &y) {
	std::size_t i;
	for (i=0; i<x.size(); i++) {
		y[i] = (*f)(x[i]);
	}
	return;
}

void interp(const std::vector<double> &x1, const std::vector<double> &y1, const std::vector<double> &x2, std::vector<double> &y2) {
	std::size_t i, j;
	std::size_t n, m;
	dot A, B, C;
	
	n = x1.size();
	m = x2.size();
	for (i=0; i<m; i++) {
		j = 0;
		while ((x1[j] < x2[i]) && (j < n)) {
			j++;
		}
		if ((j == n) || (j == n-1)) {
			A.x = x1[n-3];
			A.y = y1[n-3];
			B.x = x1[n-2];
			B.y = y1[n-2];
			C.x = x1[n-1];
			C.y = y1[n-1];
		}
		else if ((j == 0) || (j == 1)) {
			A.x = x1[0];
			A.y = y1[0];
			B.x = x1[1];
			B.y = y1[1];
			C.x = x1[2];
			C.y = y1[2];
		}
		else {
			A.x = x1[j-2];
			A.y = y1[j-2];
			B.x = x1[j-1];
			B.y = y1[j-1];
			C.x = x1[j];
			C.y = y1[j];
		}
		
		y2[i] = square(A, B, C, x2[i]);
	}
	return;
}
