#include <newton_method.h>

static double f''(polynomial p, int n, double x);
static double f'(polynomial p, int n, double x);
static double f(polyonmial p, int n, double x);
static double newton_method(polynomial p, int iter_c, double curr_point, double eps);

static double f''(polynomial p, int n, double x)
{
	double res = 0;
        for (int i = 0; i < (n - 1); i++){
                res += (n - i) * (n - i - 1) * p[i] * pow(x, n - i - 2);
        }
        return res;
}

static double f'(polynomial p, int n, double x)
{
	double res = 0;
	for (int i = 0; i < n; i++){
                res += (n - i) * p[i] * pow(x, n - i - 1);
        }
        return res;
}

static double f(polyonmial p, int n, double x)
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
	iter_n += 1;
	if (fabs(f'(p, n, curr_point)) < 0.000001){
		err = SEGMENT_ERROR;
		iter_n = 0;
		return 0;
	}
	delta = f(p, n, curr_point) / f'(p, n, curr_point);
	if (fabs(delta) < (eps/2)){
		err = OK;
		return 0;
	}
	root -= delta;
	if ((root < a) || (root > b)) {
		err = SEGMENT_ERROR;
		return 0;
	}
	else {
		return newton_method(p, n, a, b, eps, &root, &iter_n, &err);
	}
}

double find_root(polynomial p, int n, double a, double b, double eps,  error* err)
{
	double root;
	int iter_n = 0;
	if (sizeof(p) / sizeof(double) < (n + 1)){
		err = DEGREE_ERROR;
		return 0;
	}
	if (((b - a) > 1) || ((b - a) < 0)){
		err = SEGMENT_ERROR;
		return 0;
	}
	if (f(a) * f(b) < 0){
		if (f(a) * f''(a) > 0){
			root = a;
		}
		else if (f(b) * f''(b) > 0){
			root = b;
		}
                newton_method(p, n, a, b, eps, &root, &iter_n, &err);
	}
	else {
		err = SEGMENT_ERROR;
		return 0;
	}
	if (iter_n > 0){
		printf("сделано %d шагов", iter_n);
		return root;
	}
}
