#include "root_3.h"
#include <math.h>

typedef struct {
	R_Rfun f;
	double begin;
	double end;
	double res;
} test;

static double SIN(double x) {
	return sin(x);
}

static double POLYNOM(double x) {
	return (x*x*x - x*x + 2*x - 6);
}

int main(void) {
	test entry[3] = {
		{SIN, 1, 4, 3.1415926535897},
		{SIN, 7, 5, 6.2831853071795},
		{POLYNOM, 1, 2, 1.776045322},
	};
	
	for (int i=0; i<3; i++) {
		root(entry[i].f, entry[i].begin, entry[i].end, 0.0000000001, 1, entry[i].res);
	}
	
	return 0;
}
