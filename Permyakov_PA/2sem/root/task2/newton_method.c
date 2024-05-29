#include "newton_method.h"

static double ddf(polynomial p, int n, double x);
static double df(polynomial p, int n, double x);
static double f(polynomial p, int n, double x);
static int newton_method(polynomial p, int n, double a, double b, double eps, double *root, int *iter_n, error* err);

static double ddf(polynomial p, int n, double x)
{
	double res = 0;
        for (int i = 0; i < (n - 1); i++){
                res += (n - i) * (n - i - 1) * p[i] * pow(x, n - i - 2);
        }
        return res;
}

static double df(polynomial p, int n, double x)
{
	double res = 0;
	for (int i = 0; i < n; i++){
                res += (n - i) * p[i] * pow(x, n - i - 1);
        }
        return res;
}

static double f(polynomial p, int n, double x)
{
	double res = 0;
	for (int i = 0; i < (n + 1); i++){
		res += p[i] * pow(x, n - i);
	}
	return res;
}

static int newton_method(polynomial p, int n, double a, double b, double eps, double *root, int *iter_n, error* err)
{
	double delta;
	int limit = 10000;
	*iter_n += 1;
	if (fabs(df(p, n, *root)) < 0.000001){
		*err = SEGMENT_ERROR;
		return 0;
	}
	delta = f(p, n, *root) / df(p, n, *root);
	if (fabs(delta) < (eps/2)){
		*err = OK;
		return 0;
	}
	*root -= delta;
	if ((*root < a) || (*root > b)) {
		*err = SEGMENT_ERROR;
		return 0;
	}
	if (*iter_n > limit){
		*err = ITERATION_LIMIT_EXCEEDED;
		return 0;
	}
	else {
		return newton_method(p, n, a, b, eps, root, iter_n, err);
	}
}

double find_root(polynomial p, int n, double a, double b, double eps,  error* err)
{
	double root;
	int iter_n = 0;
	//if (sizeof(p) / sizeof(double) < (n + 1)){
	//	*err = DEGREE_ERROR;
	//	return 0;
	//}
	if (((b - a) > 1) || ((b - a) < 0)){
		*err = SEGMENT_ERROR;
		return 0;
	}
	if (f(p, n, a) * f(p, n, b) < 0){
		if (f(p, n, a) * ddf(p, n, a) > 0){
			root = a;
		}
		else if (f(p, n, b) * ddf(p, n, b) > 0){
			root = b;
		}
		else {
			*err = SEGMENT_ERROR;
                	return 0;
		}
                newton_method(p, n, a, b, eps, &root, &iter_n, err);
	}
	else {
		*err = SEGMENT_ERROR;
		return 0;
	}
	if (iter_n > 0){
		printf("сделано %d шагов\n", iter_n);
		return root;
	}
}
