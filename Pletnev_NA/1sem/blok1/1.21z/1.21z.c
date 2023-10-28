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

int Counter(const FILE* inp_f, const int mxlen);

//Функция ищет наибольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка
int Counter(const FILE* inp_f, const int mxlen) {

	int x;                                 // -текущий элемент последовательности 
	int px;                                // -предыдущий элемент последовательности
	int gl_k;                              // -ниабольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка
	int lc_k;                              // -текущее количество элементов в постоянном участке целой последовательности
	int gl_sm;                             // -наибольшая сумма элементов в постоянном участке целой последовательности
	int lc_sm;                             // -текущая сумма элементов в постоянном участке целой последовательности
	double checklen = 1 * pow(10, mxlen);  // -пременная для проверки велечины элемента
	char buf[LEN];                         // -вспогательный стек памяти для считование строки из файла


	//вводим бесконечное маленькое значение нулевого элемента
	px = -1316134912;
    gl_k = -2;
    lc_k = -1;
    lc_sm = px;
    gl_sm = 0;

    //идем по файлу пока мы можем считовать файл
	while (fgets(buf, LEN, inp_f)) {

		//проверяем, что мы можем считать строчки
		if (sscanf(buf, "%d", &x) != 1) {
			return Error_Invalid_Data;
		}

		//проверяем, что наши числа не слишком болшие
		if (abs(x) > checklen) {
			return Error_Large_Values;
		}
		
		//проверяем, что предыдущий элемент равен нынешнему
		if (x == px){
            lc_k += 1;
            lc_sm += x;
            
            //проверяем, что локальная сумма большее глобальной
            if (lc_sm > gl_sm) {
                gl_k = lc_k;
                gl_sm = lc_sm;
            }  
            
            //проверяем, что при равной сумме локальный счетчик больше глобальной
            if ((lc_sm ==  gl_sm) && (lc_k > gl_k)) {
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

	//проверяем, что в файл не пуст
	if (px == -1316134912) {
		return Error_File_Empty;
	}
    
    
    //возращаем результат функции (наибольшое количество элементов в постоянном участке целой последовательности с наибольшей суммой элементов этого участка)
    return gl_k;
}

int main(void){
    
	FILE* inp_f; // -файл наших значений для обработки
	FILE* out_f; // -файл для вывода ответа
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

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //запускаем работу функции и результат загружаем в вспомогательную переменую
	result = Counter(inp_f, mxlen); 
    
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

	fprintf(out_f, "Result: The largest number of elements in a constant section of the whole sequence with the largest sum of elements of this section = %d", result);
    
    //закрыли файл для чтения
	fclose(inp_f);
    //закрыли файл для записи
	fclose(out_f); 

	return Result_Answer_YES;
}
