#include <newton_method.h>

// структура тестов
typedef struct {
        polynomial p;	// указатель на функцию
        int n;		// аргумент1
        double a;       // аргумент2
        double b;       // аргумент3
        double eps;     // аргумент4
	double res;	// указатель на массив ожидаемых значений
        error err_code; // ожидаемый код ошибки
} data;

int main(void)
{
        int test_n = 3;
        error err;
        double ans;

        data tests[] = {
                {
                     	(polynomial) {1, -3, 2},
                        (int) 2,
                        (double) -1.5,
                        (double) -0.7,
                        (double) 0.001,
			(double) -1.0,
                        OK
                },
                {
                        (polynomial) {1, 0, -3},
                        (int) 2,
                        (double) 2,
                        (double) 1.5,
                        (double) 0.0001,
                        (double) 1.7320508,
                        OK
                },
		{
                        (polynomial) {50, -3, 2, 0, 1.73, 2},
                        (int) 5,
                        (double) -1,
                        (double) 0.0,
                        (double) 0.001,
                        (double) -0.542918,
                        OK
                }
        };

        test_num = sizeof(tests) / sizeof(tests[0]);
	for (int i = 0; i < test_n; i++) {
                ans = find_root(tests[i].p, tests[i].n, tests[i].a, tests[i].b, tests[i].eps, &err);
                if (err != tests[i].err_code) {
                        printf("%d-й тест провален\n", i + 1);
                }
                else if (err = OK){
                        if (fabs(ans - tests[i].res) > tests[i].eps) {
                        	printf("%d-й тест провален\n", i + 1);
                                continue;
                        }
                        printf("%d-й тест пройден\n", i + 1);
                }
                else {
                        printf("%d-й тест пройден\n", i + 1);
                }
        }
        return 0;

