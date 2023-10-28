#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#define LEN 4098
#define LEN_ARRAY_A 4098
#define LEN_ARRAY_B 4098
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Error_Large_Values -222
#define Error_File_Empty -111
#define Result_Answer_N0 111
#define Result_Answer_YES 222



int TransferFromFileToArray(const FILE * inp_f, const int len);



int ArrayShift(const int arr);


int TransferFromFileToArray(const FILE * inp_f, const int len){
    
    int i = 0;                                          // -индекс элемента последовательности
    double x;                                           // -элемент последовательности
    double arr[len] = {-1 * pow(10, 2 * mxlen + 1)};    // -массив, куда записываем данные
    double checklen = 1 * pow(10, mxlen);               // -пременная для проверки велечины 
    char buf[LEN];                                      // -вспомогательный стек памяти для считование строки из файла
    
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
		
        i++
        
        arr[i] = x
    }
      
    //проверяем, что в файл закончился (все строки считали правильно)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}
	
    //проверяем, что в файл не пуст
	if (arr == {-1 * pow(10, 2 * mxlen + 1)}) {  
		return Error_File_Empty;
	}  
        
    return arr
}


//функция 
int ArrayShift(int arr){
    
}





int main(void) {
    
    {
        FILE* inp_f; // -файл наших значений для обработки
        FILE* out_f; // -файл для вывода ответа
        int mxlen;   // -максимальный разряд числа
        int result;  // -вспомогательная перемнная для загрузки результата нашей функции
        char fi[30]; // -вспомогательная перемнная для ввода имени файла наших значений
        char fo[30]; // -вспомогательная перемнная для для ввода имени файла ответа
        
    }
    
    
    {
        printf("Enter the name of the input file:\n");
        scanf("%s", fi);
        
        //открыли файл для чтения
        inp_f = fopen(fi, "r");  
        
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
    }
    
    

    {
        //запускаем работу функции и результат загружаем в вспомогательную переменую
        result1 = TransferFromFileToArray(inp_f, mxlen); 
        
        if (result1 == Error_Invalid_Data) {
            printf("Error: Invalid data entry. Check the file '%s'\n", fi);
            return Error_Invalid_Data;
        }

        if (result1 == Error_Large_Values) {
            printf("Error: The file file '%s' contains too large values\n", fi);
            return Error_Large_Values;
        }

        if (result1 == Error_File_Empty) {
            printf("The file '%s' is empty\n", fi);
            return Error_File_Empty;
        }
    }
	
	
    //закрыли файл для чтения
	fclose(inp_f);
    //закрыли файл для записи
	fclose(out_f); 
    
    
    

	printf("The result is uploaded to the file '%s'\n", fo);
    
    
}
