#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int pyramid_sort (double *arr, int len);      //сортирует пузырьковым методом
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int pyramid_sort (double *arr, int len)
{
        int i, j, p = 1;
        double save;
	while (p < len)
	{
		for (i = 0; i < ((int) len / 2) - 1; i++)
		{
			j = (2 * i) + 1;
			if ((arr[i] < arr[j]) && (arr[j + 1] < arr[j]))
			{
				save = arr[i];
				arr[i] = arr[j];
				arr[j] = save;
				}
			else if ((arr[i] < arr[j + 1]))
			{
				save = arr[i];
				arr[i] = arr[j + 1];
				arr[j + 1] = save;
			}
		}
		p = p * 2;
	}
	return 0;
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
        pyramid_sort (arr, len);
        fprintf(output, "%d \n", len);
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
