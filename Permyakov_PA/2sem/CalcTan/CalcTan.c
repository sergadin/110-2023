#include "CalcTan.h"

static double ProcArg(double x);
static double SinTaylor(double x, int n, int fact2n);
static double CosTaylor(double x, int n, int fact2n);

static double ProcArg(double x)
{
	const double pi = 3.14159265359;
	if (x < -pi/2){
		return ProcArg(x + pi);
	}
	else if (x > pi/2){
		return ProcArg(x - pi);
	}
	else {
		return x;
	}
}

static double SinTaylor(double x, int n, int fact2n)
{
	return pow((-1), n) * pow(x, (2 * n + 1)) / (fact2n * (2 * n + 1));
}

static double CosTaylor(double x, int n, int fact2n)
{
	return pow((-1), n) * pow(x, (2 * n)) / (fact2n);
}

double CalcTan(double x, double eps, error* err)
{
	const int limit = 10000;
	const double pi = 3.14159265359;
	int fact2n = 1;
	double sin = 0;
	double cos = 0;
	double tg = 0;
	double pr_tg = 0;
	int n = 0;
	x = ProcArg(x);
	if (fabs(x - pi/2) < 1e-4 || fabs(x + pi/2) < 1e-4){
		*err = ARGUMENT_ERROR;
		return 0;
	}
	while (1){
		sin += SinTaylor(x, n, fact2n);
		cos += CosTaylor(x, n, fact2n);
		tg = sin / cos;
		if (fabs(pr_tg - tg) < (eps/2)){
			*err = OK;
			return tg;
		}
		if (n > limit){
			*err = ITERATION_LIMIT_EXCEEDED;
			return 0;
		}
		pr_tg = tg;
		n++;
                fact2n *= (2 * n - 1) * 2 * n;
	}
}
