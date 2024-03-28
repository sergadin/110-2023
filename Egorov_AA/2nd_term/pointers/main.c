#include "fillValueArray.h" 

// Заданные функции
double sine(double x);
double cubing(double x);
double reverseNum(double x);
double naturalLog(double x);

// Структура тестов
typedef struct {
	RRFun* funcs;     // Указатель на массив указателей на функции :)
	double x;         // Аргумент
	double* res;      // Указатель на массив ожидаемых значений
	error err_code;   // Ожидаемый код ошибки
} dataSet;

double sine(double x) {
	return sin(x);
}

double cubing(double x) {
	return x * x * x;
}

double reverseNum(double x) {
	return 1 / x;
}

double naturalLog(double x) {
	return log(x);
}

int main(void) {
	const double pi = 3.1415926535, eps = 1e-4;
	int test_num, func_num = 4;
	error err;
	double* value;

	dataSet tests[] = {                                                       // тесты
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},         // Функции
			pi / 2,                                                   // Аргумент
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},             // Ожидаемые значения
			MALLOC_ERR                                                // Ожидаемый код ошибки
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			pi / 2,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			OK
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			0,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			INCORRECT_ARGUMENT
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			-1,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			INCORRECT_ARGUMENT
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	fillValueArray(tests[0].funcs, -1, tests[0].x, &err);                    // Отдельно выделен первый тест.
	if (err == MALLOC_ERR)                                                   // На вход подается неправильное количество функций
		printf("1-й тест пройден :)\n");                                 // для умышленной ошибки выделения памяти.

	for (int i = 1; i < test_num; i++) {
		value = fillValueArray(tests[i].funcs, func_num, tests[i].x, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
			continue;
		}
		else if (err == INCORRECT_ARGUMENT) {                                    // Много elseif-оф, т.к. сравнивать значения массивов нельзя,
			printf("%d-й тест пройден :)\n", i + 1);                         // если будет одна из этих ошибок
			continue;
		}
		else if (err == MALLOC_ERR) {
			printf("%d-й тест пройден :)\n", i + 1);
			continue;
			}
		else {
			for (int j = 0; j < func_num; j++) {
				if (fabs(value[j] - tests[i].res[j]) > eps) {
					printf("%d-й тест не пройден :(\n", i + 1);
					break;
				}
			}
			printf("%d-й тест пройден :)\n", i + 1);
			free(value);
		}
	}
	
	
	return 0;
}
