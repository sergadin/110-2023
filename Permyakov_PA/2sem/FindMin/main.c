#include "FindMin.h"
#include <stdio.h>
#include <stdlib.h>

double fsin(double x);
double k(double x);
double f(double x);

double fsin(double x)
{
        return sin(x);
}

double k(double x)
{
        return x + pow(x, -1);
}

double f(double x)
{
        return x*x - pow(x, -1);
}

typedef struct {        // Структура тестов:
        func f;         // функция
        double a;       // начало отреза
        double b;       // конец
        double eps;     // точность
        double exp;     // ожидаемое значение
        error err_code; // код ошибки
} Test;

int main(void)
{
	const double pi = 3.14159265359;
        int test_n;
        double ans;
        error err;
	int iter_c = 0;
        Test tests[] = {
                {
                        (func) fsin,
                        pi,
                        2*pi,
                        1e-3,
                        3*pi/2,
                        OK
                },
                {
                        (func) k,
                        0.0,
                        3.0,
                        1e-4,
                        1.0,
                        OK
                },
                {
                        (func) f,
                        -2.0,
                        0.0,
                        1e-3,
                        -0.79370052598,
                        OK
                }
        };

        test_n = sizeof(tests) / sizeof(tests[0]);
	for (int i = 0; i < test_n; i++) {
		iter_c = 0;		// Тестирование
                ans = FindMin(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &iter_c, &err);
                if (err != tests[i].err_code) {
                        printf("%d-й тест не пройден\n", i + 1);
			printf("%d\n", err);
                }
                else if (err == OK) {
                        if (fabs(tests[i].exp - ans) > tests[i].eps) {
                                printf("%d-й тест не пройден\n", i + 1);
                                printf("%lf\n", fabs(ans - tests[i].exp));
                        }
                }
        }
                return 0;
}
