#include "determine_values.h"

// функции
double arith_mean(double x, double y);
double geom_mean(double x, double y);
double harm_mean(double x, double y);

// структура тестов
typedef struct {
        func f;     // указатель на функцию
        double* X;        // аргумент1
	double* Y;        // аргумент2
	int n;	   	  // аргумент3
        double* res;      // указатель на массив ожидаемых значений
        error err_code;   // ожидаемый код ошибки
} data;

double arith_mean(double x, double y)
{
	return (x + y) * 0.5;
}

double geom_mean(double x, double y)
{
	return sqrt(x*y);
}

double distance(double x, double y)
{
	return fabs(x - y);
}
int main(void)
{
	const double eps = 1e-4;
	int test_n = 3;
	error err;
	double* ans;

	data tests[] = {
		{
			(func) arith_mean, 
			(double[]) {1.0, 2.0, 3.3333},
		       	(double[]) {1.0, 3.0, 2.6666, 4.0},
			3,
			(double[]) {1.0, 2.5, 3.0},
			OK
		},
		{
                        (func) geom_mean,
                        (double[]) {1.0, 2.0, 2.0},
                        (double[]) {1.0, 2.0, 3.0, 4.0},
                        3,
			(double[]) {1.0, 2.0, 2.449489743},
                        OK
                },
		{
                        (func) distance,
                        (double[]) {1.0, 2.0, 0, 10.0},
                        (double[]) {1.0, 2.0, 3.0, 4.0},
                        4,
                        (double[]) {0.0, 0.0, 3.0, 6.0},
                        OK
                },
	};

	test_n = sizeof(tests) / sizeof(tests[0]);

        for (int i = 0; i < test_n; i++) {                                            // Тестирование
                ans = determine_values(tests[i].f, tests[i].X, tests[i].Y, tests[i].n, &err);
                if (err != tests[i].err_code) {
                        printf("%d-й тест не пройден\n", i + 1);
                }
                else if (err == OK) {
                        for (int j = 0; j < tests[i].n; j++) {
                                if (fabs(ans[j] - tests[i].res[j]) > eps) {
                                        printf("%d-й тест не пройден\n", i + 1);
					printf("%d\n", j + 1);
					printf("%lf\n", fabs(ans[j] - tests[i].res[j]));
                                        goto theend;
                                }
                        }
                        printf("%d-й тест пройден\n", i + 1);
                }
		else {
                        printf("%d-й тест пройден\n", i + 1);
                        }
        theend:
                free(ans);
        }

	return 0;
}
