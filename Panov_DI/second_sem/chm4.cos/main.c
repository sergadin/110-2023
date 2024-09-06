#include <stdio.h>
#include "countcos.h"

typedef struct {          // Структура тестов:
	double x;             //   - Точка
	double eps;           //   - Точность
	double res;           //   - Ожидаемый результат
	error err_code;       //   - Ожидаемая ошибка
} dataSet;

int main(void) {
	const double PI = 3.1415926535;
	int test_num, i_num;
	error err;
	double value;
	dataSet tests[] = {
		{3, 0.00001, -0.98999, OK},
		{0, 0.00001, 1, OK},
		{PI / 2, 0.00001, 0, OK},
		{0.8, 0.00001, 0.696707, OK},
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		i_num = 0;
		value = countcos(tests[i].x, tests[i].eps, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден. \n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > tests[i].eps)) {
			printf("%d-й тест не пройден. \n", i + 1);
		}
		else {
			printf("%d-й тест пройден. \n", i + 1);
		}
	}

	return 0;
}
