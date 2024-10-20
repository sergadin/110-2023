﻿#include <stdio.h>
#include <stdlib.h>
#include "stroki.h"

typedef struct {          // Структура тестов:
	const char* input;               // Имя файла
	const char* output;
	error_t err_code;                // Код ошибки
} dataSet;


int main(void) {
	int test_num;
	error_t err;

	dataSet tests[] = {
		{ "input1.txt", "output1.txt", SUCCESS },
		{ "input2.txt", "output2.txt", SUCCESS },
		{ "input3.txt", "output3.txt", SUCCESS }
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input, * output;

		if ((input = fopen(tests[i].input, "r")) == NULL) {
			printf("%d-й тест не пройден. Не удалось открыть инпут файл\n", i + 1);
			continue;
		}
		if ((output = fopen(tests[i].output, "w")) == NULL) {
			printf("%d-й тест не пройден. Не удалось открыть аутпут файл\n", i + 1);
			fclose(input);
			continue;
		}

		process_string(input, output, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден. \n", i + 1);
		}
		else if (err == SUCCESS) {
			printf("%d-й тест пройден. Результат в output%d.txt\n", i + 1, i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
		fclose(input);
		fclose(output);
	}

	return 0;
}
