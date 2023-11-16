#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer 222

int LastMinimum(FILE* inp_f);

//Функция ищет номер последнего наименьшего элемента всей целой последовательности
int LastMinimum(FILE* inp_f) {

	int x;            // -элемент последовательности
	int i;            // -вспомогательная перемная для номерации элементов в последовательности
	int minx;         // -наименьшее число в псоледовательности
	int mini;         // -результат функции - номер последнего наименьшего элемента последовательности  


	if (fscanf(inp_f, "%d", &x) != 1) {
		return Error_Invalid_Data;
	}

	minx = x;
	mini = 0;
	i = 1;

	//идем по файлу пока мы можем считовать файл
	while (fscanf(inp_f, "%d", &x) == 1) {

		//ищем последней наименьшей элемент в файле
		if (x <= minx) {
			minx = x;
			mini = i;
		}

		++i;
	}

	//проверяем, что в файл закончился (все строки считали правильно)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//возращаем ответ на задачу (номер последнего наименьшего элемента последовательности)
	return mini;

}

int main(void) {

	FILE* inp_f; // -файл наших значений для обработки
	FILE* out_f; // -файл для вывода ответа
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

	//запускаем работу функции и результат загружаем в вспомогательную переменую
	result = LastMinimum(inp_f);

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
	fprintf(out_f, "Result: The number of the last smallest element in the sequence = %d", result);

	//закрыли файл для записи
	fclose(out_f);

	return Result_Answer;
}
