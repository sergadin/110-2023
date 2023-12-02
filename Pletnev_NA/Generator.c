#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_array(int** arr, int len, int* error) 
{
	*arr = (int*)malloc(len * sizeof(int));
    
	if ((*arr) == NULL) 
    {
		*error = -1;
		return;
	}
    
	for (int i = 0; i < len; i++)
    {
		(*arr)[i] = rand();
    }
}


int main(void)
{
	FILE* out_f;		// -файл для вывода массива
	char fo[30];		// -вспомогательная перемнная для для ввода имени файла массива
	int* arr = NULL;	// -наш массив для работы
	int len;			// -длина нашего желаемого массива
    
    
    
    
}
