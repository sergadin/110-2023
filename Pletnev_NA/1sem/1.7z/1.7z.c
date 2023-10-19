#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define LEN 4098

//функция проверяет, что все числа в файле равны с собой с учетом погрешности
int EqualityCheck(FILE* inp_f, double eps, int mxlen)
{
	double x, maxx, minx;
	char buf[LEN];

	maxx = -1 * pow(10, 2 * mxlen + 1);  //вводим бесконечное малое значение, чтобы сравнить с ним
	minx = 1 * pow(10, 2 * mxlen + 1);  //вводим бесконечное большое значение, чтобы сравнить с ним

	while (fgets(buf, LEN, inp_f)) { //идем по файлу пока мы можем считовать файл

		if (sscanf(buf, "%lf", &x) != 1) { //проверяем, что мы можем считать строчки
			return -2;
		}

		if (fabs(x) > 1 * pow(10, mxlen)) {  //проверяем, что наши числа не слишком болшие
			return -1;
		}

		if (x > maxx) { //ищем наибольшое значение в файле
			maxx = x;
		}

		if (x < minx) { //ищем наименьшее значение в файле
			minx = x;
		}

	}

	if (!feof(inp_f)) {
		return -2;
	}

	if ((maxx < -1 * pow(10, 2 * mxlen)) || (minx > 1 * pow(10, 2 * mxlen))) {  //проверяем, что в файл не пуст
		return 0;
	}

	if ((maxx - minx) > eps) { //проверяем, что все наши зажатые числа лежат в предлах погрешности
		return 1;
	}

	return 2;
}


int main(void) {

	FILE* inp_f;
	FILE* out_f;
	double eps;
	int mxlen;
	int result;
	char fi[30];
	char fo[30];

	printf("Enter the name of the input file:\n");
	scanf("%s", &fi);

	inp_f = fopen(fi, "r");  //открыли файл для чтения

	if (inp_f == NULL) {                             //проверяем существование файла. если его нет, выводим ошибку
		printf("Error: The file '%s' does not exist\n", fi);
		return -3;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", &fo);

	out_f = fopen(fo, "w"); //открыли файл для записи

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	printf("Enter the maximum power of 10 to check the numbers\n");
	scanf("%d", &mxlen);


	result = EqualityCheck(inp_f, eps, mxlen); //запускаем работу функции

	if (result == -2) {
		printf("Error: Invalid data entry. Check the input file\n");
		return -2;
	}

	if (result == -1) {
		printf("Error: The file input file contains too large values\n");
		return -1;
	}

	if (result == 0) {
		printf("The input file is empty\n");
		return 0;
	}

	printf("The result is uploaded to the output file\n");

	if (result == 1) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return 1;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");

	fclose(inp_f); //закрыли файл для чтения
	fclose(out_f); //закрыли файл для записи

	return 2;
}



