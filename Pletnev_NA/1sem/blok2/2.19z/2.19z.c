#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Error_File_NOT_Exist -666
#define Error_Invalid_Data -555
#define Error_Unallocated_Memory -444
#define Error_Array_Empty -333
#define Result_Answer_N0 111
#define Result_Answer_YES 222

int NumberSearch(int* arr, int len, int y);


//функции ищет и возрощает индекс введенгого числа в массиве
int NumberSearch(int* arr, int len, int y)
{
    
    int il = 0;        // -левая граница массива
    int ir = len-1;    // -правая граница массива
    int i = ir;        // -индекс на текущем моменте проверки
    int c = 0;         // -счетчик
    
    if (arr == NULL)
	{
		printf("Error:The array is empty\n");
		return Error_Array_Empty;
	}
    
    
    while ((arr[i] != y) && (c != len))
    {
        
        i = ((ir+il)/2);
        
        if (y <= arr[i]) 
        {
            ir = i;
        }
        
        else
        {
            il = i;
        }
        
        c++;
    }
    
    //printf("%d - c\n", c);
    
    if (c == len)
    {
        return Result_Answer_N0;
    }
    
    return i;
}




int main(void)
{
	FILE* inp_f;		// -файл наших значений для обработки
	FILE* out_f;		// -файл для вывода ответа
	char fi[30];		// -вспомогательная перемнная для ввода имени файла наших значений
	char fo[30];		// -вспомогательная перемнная для для ввода имени файла ответ
	int code = 0;		// -резултат фнукции
	int* arr = NULL;	// -наш массив для работы
	int len;			// -длина нашего массива
	int y;				// -число на которое нужно сдвинуть элементы массива

	printf("Enter the name of the input file:\n");
	scanf("%s", fi);

	//открыли файл для чтения
	inp_f = fopen(fi, "r");

	//проверяем существование файла. если его нет, выводим ошибку
	if (inp_f == NULL)
    {
		printf("Error: The file '%s' does not exist\n", fi);
		code = Error_File_NOT_Exist;
        fclose(inp_f);
        return code;
	}

	if (fscanf(inp_f, "%d", &len) != 1)
    {
		code = Error_Invalid_Data;
        fclose(inp_f);
        return code;
	}

	arr = (int*)malloc((len + 1) * sizeof(int));

	if (arr == NULL)
    {
		printf("Error: RAM is not allocated\n");
		code = Error_Unallocated_Memory;
        fclose(inp_f);
        return code;
	}

	for (int i = 0; i < len; i++) 
    {

		if (fscanf(inp_f, "%d", &arr[i]) != 1) 
        {
			printf("Error: Invalid data entry. Check the file '%s'\n", fi);
			code = Error_Invalid_Data;
            fclose(inp_f);
            return code;
		}

	}

	//закрыли файл для чтения
	fclose(inp_f);
	
	printf("Enter the number whose position you want to find:\n");
	scanf("%d", &y);

	code = NumberSearch(arr, len, y);
    
    if (code == Error_Array_Empty) 
    {
		return code;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	//открыли файл для записи
	out_f = fopen(fo, "w");

	printf("The result is uploaded to the file '%s'\n", fo);

	if (code == Result_Answer_N0)
    {
        fprintf(out_f, "There is no number (%d) to in this array ", y);
    }
    
    else
    {
        fprintf(out_f, "TThe index of this number (%d) is equal to %d ", y, code);
    }

	//закрыли файл для записи
	fclose(out_f);
	free(arr);

	return code;
}
