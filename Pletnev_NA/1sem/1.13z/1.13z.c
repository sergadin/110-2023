#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#define LEN 4098
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Error_Large_Values -222
#define Error_File_Empty -111
#define Result_Answer_N0 111
#define Result_Answer_YES 222

int LastMinimum(FILE* inp_f, int mxlen);

//Функция ищет номер последнего наименьшего элемента всей целой последовательности
int LastMinimum(FILE* inp_f, int mxlen) {

	int x;                                 // -элемент последовательности
	int i;                                 // -вспомогательная перемная для номерации элементов в последовательности
	double minx;                           // -наименьшее число в псоледовательности
	double checklen = 1 * pow(10, mxlen);  // -пременная для проверки велечины элемента
	int mini;                              // -результат функции - номер последнего наименьшего элемента последовательности  
	char buf[LEN];                         // -вспомогательный стек памяти для считование строки из файла


	//вводим бесконечное большое значение, чтобы сравнить с ним элементы
	minx = 1 * pow(10, 2 * mxlen + 1);
	mini = 0;
	i = 1;
    
    //идем по файлу пока мы можем считовать файл
	while (fgets(buf, LEN, inp_f)) {

		//проверяем, что мы можем считать строчки
		if (sscanf(buf, "%d", &x) != 1) {
			return Error_Invalid_Data;
		}

		//проверяем, что наши элементы не слишком болшие
		if (abs(x) > checklen) {
			return Error_Large_Values;
		}
        
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

	//проверяем, что в файл не пуст
	if (minx > 1 * pow(10, 2 * mxlen)) {
		return Error_File_Empty;
	}
    
    //возращаем ответ на задачу (номер последнего наименьшего элемента последовательности)
	return mini;

}

int main(void){
    
	FILE* inp_f; // -файл наших значений для обработки
	FILE* out_f; // -файл для вывода ответа
	int mxlen;   // -максимальный разряд элемента
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

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);
    
    //открыли файл для записи
	out_f = fopen(fo, "w"); 

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //запускаем работу функции и результат загружаем в вспомогательную переменую
	result = LastMinimum(inp_f, mxlen); 
    
	if (result == Error_Invalid_Data) {
		printf("Error: Invalid data entry. Check the file '%s'\n", fi);
		return Error_Invalid_Data;
	}

	if (result == Error_Large_Values) {
		printf("Error: The file file '%s' contains too large values\n", fi);
		return Error_Large_Values;
	}

	if (result == Error_File_Empty) {
		printf("The file '%s' is empty\n", fi);
		return Error_File_Empty;
	}

	printf("The result is uploaded to the file '%s'\n", fo);

	fprintf(out_f, "Result: The number of the last smallest element in the sequence = %d", result);
    
    //закрыли файл для чтения
	fclose(inp_f);
    //закрыли файл для записи
	fclose(out_f); 

	return Result_Answer_YES;
}
