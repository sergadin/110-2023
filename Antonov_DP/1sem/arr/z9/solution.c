#include <stdio.h>
#include <stdlib.h>
#include <math.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int rem_rep_parts (double *arr, int len);      //убирает повторяющиеся части
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int rem_rep_parts (double *arr, int len)
{
	double e = 0.001, save;	//маленькое эпсилон для сравнения чисел типа double
	int i, j = 0;	//i нужно для цикла, а j - вспомагательная переменная
	save
	for (i = 1; i < len; i++)
	{
		if ( fabs(arr[i] - arr[i-1]) > e)
		{
			arr[j] = arr[i];
			j++;
		}
	}
	return j;
}


int main (void)
{
        int len, i;
	double *arr;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
        fscanf(input, "%d", &len);
	arr = (double *)malloc(len*sizeof(double));
	for (i = 0; i < len; i++) { test_file_input_double(input, &arr[i], &error); }
	len = rem_rep_parts (arr, len);
	fprintf(output, "%d \n", len + 1);
	fprintf(output, "%lf \n", save);
	for (i = 0; i < len; i++)
	{
		fprintf(output, "%lf \n", arr[i]);
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
