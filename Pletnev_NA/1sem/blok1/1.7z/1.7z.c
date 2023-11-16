#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer_N0 111
#define Result_Answer_YES 222

int EqualityCheck(FILE* inp_f, double eps);


//функция проверяет, что все элементы в файле равны с собой с учетом погрешности
int EqualityCheck(FILE* inp_f, double eps) {

	double x;                              // -элемент последовательности
	double maxx;                           // -наибольшее число в псоледовательности
	double minx;                           // -наименьшее число в псоледовательности


	if (fscanf(inp_f, "%lf", &x) != 1) {
		return Error_Invalid_Data;
	}

	maxx = x;
	minx = x;

	//идем по файлу пока мы можем считовать файл
	while (fscanf(inp_f, "%lf", &x) == 1) {

		//ищем наибольший элемент в файле
		if (x > maxx) {
			maxx = x;
		}

		//ищем наименьший элемент в файле
		if (x < minx) {
			minx = x;
		}

	}

	//проверяем, что в файл закончился (все строки считали правильно)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//проверяем, что все наши зажатые элементы лежат в предлах погрешности
	if ((maxx - minx) > eps) {

		//возращаем отрицательный ответ
		return Result_Answer_N0;
	}

	//возращаем положительный ответ
	return Result_Answer_YES;
}


int main(void) {

	FILE* inp_f; // -файл наших значений для обработки
	FILE* out_f; // -файл для вывода ответа
	double eps;  // -погрешность, с которой мы проверяем элементы 
	int result;  // -вспомогательная перемнная для загрузки результата нашей функции
	char fi[30]; // -вспомогательная перемнная для ввода имени файла наших значений
	char fo[30]; // -вспомогательная перемнная для для ввода имени файла ответа

	printf("Enter the name of the input file:\n");
	scanf("%s", fi);

	//открыли файл для чтения
	inp_f = fopen(fi, "r");

	//проверяем существование файла. если его нет, выводим ошибку
	if (inp_f == NULL) {
		printf("Error: The file '%s' does not exist\n", fi);
		return Error_File_NOT_Exist;
	}

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	//запускаем работу функции и результат загружаем в вспомогательную переменую
	result = EqualityCheck(inp_f, eps);

	//закрыли файл для чтения
	fclose(inp_f);

	if (result == Error_Invalid_Data) {
		printf("Error: Invalid data entry. Check the file '%s'\n", fi);
		return Error_Invalid_Data;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	//открыли файл для записи
	out_f = fopen(fo, "w");

	printf("The result is uploaded to the file '%s'\n", fo);

	if (result == Result_Answer_N0) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return Result_Answer_N0;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");

	//закрыли файл для записи
	fclose(out_f);

	return Result_Answer_YES;
}



