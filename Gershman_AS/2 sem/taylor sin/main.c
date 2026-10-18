#include <stdio.h>
#include "taylor_sin.h"

typedef struct {          // Структура тестов:
	double x;             //   - Точка
	double eps;           //   - Точность
	double res;           //   - Ожидаемый результат
	Error err_code;       //   - Ожидаемая ошибка
} TestCase;

int main(void) {
	int test_num, i_num;
	Error err;
	double value;
	TestCase tests[] = {
		{-2, 0.0001, -0.03489, OK},
		{0.9, 0.0001, 0.7833269, OK},
		{1000, 0.0001, -0.75680249, W_ARG},
	};


	for (int i = 0; i < 3; i++) {                                            // Тестирование
		i_num = 0;
		value = taylor_sin(tests[i].x, tests[i].eps, &err);
		if (err != tests[i].err_code) {
			printf("Тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > tests[i].eps)) {
			printf("Тест %d не пройден\n", i + 1);
		}
		else {
			printf("Тест %d пройден\n", i + 1);
		}
	}

	return 0;
}