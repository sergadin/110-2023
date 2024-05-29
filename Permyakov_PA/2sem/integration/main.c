#include "DetInt.h"
#include <stdio.h>
#include <stdlib.h>

double fsin(double x);
double cube(double x);
double ln(double x);

double fsin(double x)
{
	return sin(x);
}

double cube(double x)
{
	return x * x * x;
}

double ln(double x)
{
	return log(x);
}

typedef struct {	// Структура тестов:
        func f;		// функция
        double a;       // нижний предел интегрирования
        double b;       // верхний
        double eps;     // точность
	double exp;	// ожидаемое значение
        error err_code; // код ошибки
} Test;

int main(void) 
{
	const double pi = 3.14159265359;
        int test_n;
	double ans;
        error err;
        Test tests[] = {
                {
                        (func) fsin,
                        0,
                        pi/2,
			1e-3,
                        1.0,
                        OK
                },
                {
                        (func) cube,
			0.5,
			1.0,
			1e-4,
			0.234375,
			OK
		},
		{
			(func) ln,
			1,
			5,
			1e-3,
			4.04718956217,
			OK
		}
        };

        test_n = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_n; i++) {                                            // Тестирование
                ans = DetInt(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);
                if (err != tests[i].err_code) {
                        printf("%d-й тест не пройден\n", i + 1);
                }
                else if (err == OK) {
                	if (fabs(tests[i].exp - ans) > tests[i].eps) {
                                printf("%d-й тест не пройден\n", i + 1);
				printf("%lf\n", fabs(ans - tests[i].exp));
                	}
			else{
				printf("в %d-ом тесте погрешность в %lf", i+1, fabs(ans - tests[i].exp));
			}
		}
	}
		return 0;
}
