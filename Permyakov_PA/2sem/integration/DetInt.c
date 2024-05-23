#include <gauss_method.h>

static double 2dotGaussQuad(func f, double a, double b);

static double 2dotGaussQuad(func f, double a, double b)	// двуточечная квадратура Гаусса
{
	return 0.5 * (b - a) * (f(0.5 * (a + b - ((b - a) / sqrt(3))))
		       	+ f(0.5 * (a + b + ((b - a) / sqrt(3)))));
}

double DetInt(func f, double a, double b, double eps, error* err)
{
	int iter_c = 0;
	int lim = 10000;
	int n = 1;
	double cur_int;
	double prev_int;
	double delta = b - a;
	if (b < a){
		err = SEGMENT_ERROR;
		return 0;
	}

	cur_int = 2dotGaussQuad(f, a, b);
	while (1){
		iter_c++;
		prev_int = cur_int;
		delta /= 2;
		n *= 2;
		cur_int = 0;
		for (int i = 0; i < n; i++){
			cur_int += 2dotGaussQuad(func f, a + i * delta, a + (i + 1) * delta);
		}
		if (iter_c > lim){
			err = ITERATION_LIMIT_EXCEEDED;
			return 0;
		}
		if (fabs(cur_int - prev_int) < (eps * fmax(fabs(cur_int), fabs(prev_int)))){
			err = OK;
			break;
		}
	}
	printf("Интеграл посчитан за %d шагов", iter_c);
	return cur_int;
}
