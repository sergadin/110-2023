#include "CalcTan.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {        // Структура тестов:
        double x;       // точка
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
        Test tests[] = {
                {
                        0.0,
			1e-3,
			0.0,
                        OK
                },
		{
			pi/3,
			1e-4,
			1.73205080757,
			OK
		},
		{
			pi/6,
			1e-3,
			0.57735026919,
			OK
		}
	};
	test_n = sizeof(tests) / sizeof(tests[0]);

        for (int i = 0; i < test_n; i++) {                                            // Тестирование
                ans = CalcTan(tests[i].x, tests[i].eps, &err);
                if (err != tests[i].err_code) {
                        printf("%d-й тест не пройден\n", i + 1);
                }
                else if (err == OK) {
                        if (fabs(tests[i].exp - ans) > tests[i].eps) {
                                printf("%d-й тест не пройден\n", i + 1);
                                printf("%lf\n", fabs(ans - tests[i].exp));
                        }
                        else{
                                printf("в %d-ом тесте погрешность равна %lf\n", i+1, fabs(ans - tests[i].exp));
                        }
                }
        }
                return 0;
}
