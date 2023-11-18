#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#include <stdlib.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer 222


int Counter(FILE* inp_f);

//Функция ищет наибольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка
int Counter(FILE* inp_f) {

	int x;                                 // -текущий элемент последовательности 
	int px;                                // -предыдущий элемент последовательности
	int gl_k;                              // -ниабольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка
	int lc_k;                              // -текущее количество элементов в постоянном участке целой последовательности
	int gl_sm;                             // -наибольшая сумма элементов в постоянном участке целой последовательности
	int lc_sm;                             // -текущая сумма элементов в постоянном участке целой последовательности
	
	if (fscanf(inp_f, "%d", &x) != 1) {
		return Error_Invalid_Data;
	}
    
    px = x;
    
	lc_k = 1;
	lc_sm = px;

	//считаем превый постоянный участок
	while ((fscanf(inp_f, "%d", &x) == 1) && (x == px)) {

		lc_k += 1;
		lc_sm += x;
		px = x;
	}

    gl_k = lc_k;
	gl_sm = lc_sm;

	px = x;

	lc_k = 1;
	lc_sm = x;
    
    //идем по файлу пока мы можем считовать файл
	while (fscanf(inp_f, "%d", &x) == 1) {

		//проверяем, что предыдущий элемент равен нынешнему
		if (x == px) {
			lc_k += 1;
			lc_sm += x;

			//проверяем, что локальная сумма больше глобальной
			if (lc_sm > gl_sm) {
				gl_sm = lc_sm;
				gl_k = lc_k;
			}

			//проверяем, что при равной сумме локальный счетчик больше глобальной
			if ((lc_sm == gl_sm) && (lc_k > gl_k)) {
				gl_k = lc_k;
			}

		}

		else {
			lc_k = 1;
			lc_sm = x;

		}

		px = x;
	}

	//проверяем, что в файл закончился (все строки считали правильно)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//возращаем результат функции (наибольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка)
	return gl_k;
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
	result = Counter(inp_f);

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
	fprintf(out_f, "Result: The largest number of elements in a constant section of the whole sequence with the largest sum of elements of this section = %d", result);

	//закрыли файл для записи
	fclose(out_f);

	return Result_Answer;
}
