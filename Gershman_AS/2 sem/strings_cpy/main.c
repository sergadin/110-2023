#include <stdlib.h>
#include <stdio.h>
#include "strings_cpy.h"

typedef struct {          // Структура тестов:
	const char* input;               // Имя файла
	const char* output;
	Error err_code;                  // Код ошибки
} dataSet;


int main(void) {
	int test_num;
	Error err;

	dataSet tests[] = {
		{ "input1.txt", "output1.txt", OK },
		{ "input2.txt", "output2.txt", OK },
		{ "input3.txt", "output3.txt", OK }
	};


	for (int i = 0; i < 3; i++) {                                           
		FILE* input, * output;

		if ((input = fopen(tests[i].input, "r")) == NULL) {
			printf("Тест %d не пройден. Не удалось открыть input файл\n", i + 1);
			continue;
		}
		if ((output = fopen(tests[i].output, "w")) == NULL) {
			printf("Тест %d не пройден. Не удалось открыть output файл\n", i + 1);
			fclose(input);
			continue;
		}

		copyWords(input, output, &err);

		if (err != tests[i].err_code) {
			printf("Тест %d не пройден\n", i + 1);
		}
		else if (err == OK) {
			printf("Тест %d пройден. Результат в output%d.txt\n", i + 1, i + 1);
		}
		else {
			printf("Тест %d пройден.\n", i + 1);
		}
		fclose(input);
		fclose(output);
	}

	return 0;
}