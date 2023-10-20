#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define LEN 4098
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Error_Large_Values -222
#define Error_File_Empty -111


//Функция ищет номер последнего наименьшего числа всей целой последовательности
int LastMinimum(FILE* inp_f, int mxlen) {

	int x;
	int i;
	int minx;
	int mini;
	char buf[LEN];


	//вводим бесконечное большое значение, чтобы сравнить с ним
	minx = 1 * pow(10, 2 * mxlen + 1);
	//результат функции
	mini = 0;
	//номеруем числа в файле
	i = 0;

	while (fgets(buf, LEN, inp_f)) {

		//проверяем, что мы можем считать строчки
		if (sscanf(buf, "%lf", &x) != 1) {
			return Error_Invalid_Data;
		}

		//проверяем, что наши числа не слишком болшие
		if (fabs(x) > 1 * pow(10, mxlen)) {
			return Error_Large_Values;
		}

		if (x <= minx) {
			minx = x;
			mini = i;
		}

		++i;
	}

	//проверяем, что в файл закончился
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//проверяем, что в файл не пуст
	if (minx > 1 * pow(10, 2 * mxlen)) {
		return Error_File_Empty;
	}

	return mini;

}

int main(void) {

	FILE* inp_f;
	FILE* out_f;
	int mxlen;
	int result;
	char fi[30];
	char fo[30];

	printf("Enter the name of the input file:\n");
	scanf("%s", &fi);

	//открыли файл для чтения
	inp_f = fopen(fi, "r");

	//проверяем существование файла. если его нет, выводим ошибку
	if (inp_f == NULL) {
		printf("Error: The file '%s' does not exist\n", fi);
		return Error_File_NOT_Exist;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", &fo);

	//открыли файл для записи
	out_f = fopen(fo, "w");

	printf("Enter the maximum power of 10 to check the numbers\n");
	scanf("%d", &mxlen);

	//запускаем работу функции
	result = LastMinimum(inp_f, mxlen);

	if (result == Error_Invalid_Data) {
		printf("Error: Invalid data entry. Check the input file\n");
		return Error_Invalid_Data;
	}

	if (result == Error_Large_Values) {
		printf("Error: The file input file contains too large values\n");
		return Error_Large_Values;
	}

	if (result == Error_File_Empty) {
		printf("The input file is empty\n");
		return Error_File_Empty;
	}

	//printf("The result is uploaded to the output file\n");
	printf("Result: The number of the last smallest value in the file '%s' is '%d'", fi, result);


	//закрыли файл для чтения
	fclose(inp_f);
	//закрыли файл для записи
	fclose(out_f);

	return 2;
}