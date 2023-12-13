#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int rem_rep_parts (int *arr, int len);      //убирает повторяющиеся части
int test_file_input_int (FILE *input, int *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int rem_rep_parts (int *arr, int len)
{
	int i, j = 0, p = 1, lenp = 1;	//i нужно для цикла, а j - вспомагательная переменная
	for (i = 1; i < len; i++)
	{
		if ( arr[i] != arr[i-1-j] )
		{
		       	arr[p] = arr[i];
			lenp++;
			j = 0;
			p++;
		}
		else 
		{ 
			j++;
		}
	}
	return lenp;
}


int main (void)
{
        int len = 10000000, i;
	int *arr;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
	test_file_input_int(input, &len, &error);
	arr = (int *)malloc(len*sizeof(int));
	for (i = 0; i < len; i++) { test_file_input_int(input, &arr[i], &error); }
	len = rem_rep_parts (arr, len);
	fprintf (output, "длина укороченного массива = %d \n", len);
	for ( i = 0; i < len; i ++)
	{
		fprintf (output, "%d \n", arr[i]);
	}
	free(arr);
        fclose (input);
        fclose (output);
        if ( error == E_DATA)
        {
                printf ( "ошибка при открытии файла \n" );
                        return -1;
        }
        if ( error == E_IO)
        {
                printf ( "ошибка при чтении файла \n" );
                return -1;
        }
        return 0;
}
