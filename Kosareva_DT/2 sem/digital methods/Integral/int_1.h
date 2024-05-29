typedef double (*R_Rfun)(double);

typedef struct {
	R_Rfun f;
	double a;
	double b;
	double res;
} test;

void integral(test entry, double eps, int limit);
double rect(R_Rfun f, double a, double b, int n);
