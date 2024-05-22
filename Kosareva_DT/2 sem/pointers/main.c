#include "pointer_7.h"

static double SQRT(double x);
static double HALF(double x);
static double COS(double x);
static double DOUBLE(double x);

static int DIFF(double x, double y);
static int PRODUCT(double x, double y);
static int SUM(double x, double y);

static double SQRT(double x) {
	return sqrt(x);
}

static double HALF(double x) {
	return x/2;
}

static double COS(double x) {
	return cos(x);
}

static double DOUBLE(double x) {
	return x*2.0;
}

static int DIFF(double x, double y) {
	return floor(x - y);
}

static int PRODUCT(double x, double y) {
	return floor(x*y);
}

static int SUM(double x, double y) {
	return floor(x + y);
}

struct test {
	double (*f)(double);
	int (*g)(double, double);
	double x;
};

int main(void) {
	struct test entry[4]={
		{SQRT, DIFF, 1000000},
		{HALF, PRODUCT, 10000},
		{COS, SUM, 1},
		{DOUBLE, DIFF, 1}
	};
	
	for (int i=0; i<4; i++) {
		find_the_null(entry[i].f, entry[i].g, entry[i].x, 10000);
	}
	
	return 0;
}
