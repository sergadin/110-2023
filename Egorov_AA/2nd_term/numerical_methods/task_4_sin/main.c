#include <stdio.h>
#include "calculateSin.h"

typedef struct {          // Структура тестов:
	double x;             //   - Точка
	double eps;           //   - Точность
	double res;           //   - Ожидаемый результат
	error err_code;       //   - Ожидаемая ошибка
} dataSet;

int main(void) {
	int test_num, i_num;
	error err;
	double value;
	dataSet tests[] = {
		{-3, 1e-4, -0.14112, OK},
		{0.9, 0.0001, 0.7833269, OK},
		{4 + 1000 * M_PI, 0.0001, -0.75680249, INVALID_ARGUMENT},
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		i_num = 0;
		value = calculateSin(tests[i].x, tests[i].eps, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > tests[i].eps)) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
	}

	return 0;
}
