#include "fillValueArray.h" 

// Заданные функции
double sine(double x);
double cubing(double x);
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

double naturalLog(double x) {
	return log(x);
}

int main(void) {
	const double pi = 3.1415926535, eps = 1e-4;
	int test_num, func_num = 3;
	error err;
	double* value;

	dataSet tests[] = {                                             // Tесты
		{
			(RRFun[]) {sine, cubing, naturalLog},                   // Функции      
			pi / 2,									                // Аргумент
			(double[]) {1.0, 3.87578, 0.451583},	                // Ожидаемые значения
			OK										                // Ожидаемый код ошибки
		},
		{
			(RRFun[]) {sine, cubing, naturalLog},
			-1,
			(double[]) { 1.0, 3.87578, 0.451583},
			INCORRECT_ARGUMENT
		},
		{
			(RRFun[]) {sine, cubing, naturalLog},
			10,
			(double[]) {-0.544021, 1000, 2.30259},
			OK
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {
		value = fillValueArray(tests[i].funcs, func_num, tests[i].x, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < func_num; j++) {
				if (fabs(value[j] - tests[i].res[j]) / 2 > eps) {
					printf("%d-й тест не пройден :(\n", i + 1);
					free(value);
					continue;
				}
			}
			printf("%d-й тест пройден :)\n", i + 1);
		}
		else {
			printf("%d-й тест пройден :)\n", i + 1);
		}

		if (err != MALLOC_ERR)
			free(value);
	}


	return 0;
}
