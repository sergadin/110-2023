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

int EqualityCheck(const FILE* inp_f, const double eps, const int mxlen);


//функция проверяет, что все элементы в файле равны с собой с учетом погрешности
int EqualityCheck(const FILE* inp_f, const double eps, const int mxlen) {
    
	double x;                              // -элемент последовательности
    double maxx;                           // -наибольшее число в псоледовательности
    double minx;                           // -наименьшее число в псоледовательности
    double checklen = 1 * pow(10, mxlen);  // -пременная для проверки велечины элемента
	char buf[LEN];                         // -вспомогательный стек памяти для считование строки из файла
    
    //вводим бесконечное малое значение, чтобы сравнить с ним
	maxx = -1 * pow(10, 2 * mxlen + 1);
    
    //вводим бесконечное большое значение, чтобы сравнить с ним
	minx = 1 * pow(10, 2 * mxlen + 1);  
    
    //идем по файлу пока мы можем считовать файл
	while (fgets(buf, LEN, inp_f)) { 
        
        //проверяем, что мы можем считать строчки
		if (sscanf(buf, "%lf", &x) != 1) { 
			return Error_Invalid_Data;
		}
		
        //проверяем, что наши элементы не слишком болшие
		if (fabs(x) > checklen)) { 
			return Error_Large_Values;
		}
        
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
	
    //проверяем, что в файл не пуст
	if ((maxx < -1 * pow(10, 2 * mxlen)) || (minx > 1 * pow(10, 2 * mxlen))) {  
		return Error_File_Empty;
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
	int mxlen;   // -максимальный разряд числа
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

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //запускаем работу функции и результат загружаем в вспомогательную переменую
	result = EqualityCheck(inp_f, eps, mxlen); 
    
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

	if (result == Result_Answer_N0) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return Result_Answer_N0;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");
    
    //закрыли файл для чтения
	fclose(inp_f);
    //закрыли файл для записи
	fclose(out_f); 

	return Result_Answer_YES;
}



