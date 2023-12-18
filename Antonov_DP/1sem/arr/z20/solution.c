#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file_input_int (FILE *input, int *num, ERR *error);	//считывает целое число
int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int merge_arr (double *arr1, double *arr2, int len1, int len2);      //создаёт из двух неубывающих массивов один неубывающий
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного число
int file_read_arr (FILE *input, double *arr, int len, ERR *error);	//считывает массивы из файла

int merge_arr (double *arr1, double *arr2, int len1, int len2)
{
        int i = 0, j = 0, p = 0;	//i - индекс arr1, j - индекс arr2, p - вспомагательный индекс
	double save = 0;	//save - сохраняет элемент для перемещения в другой массив
	for ( i = 0; (i < len1) && (j < len2); i++)
	{
		if ((arr1[i] > arr2[j]) && ((arr2[p] > arr2[j]) || (p == j)) )
		{
			save = arr1[i];
			arr1[i] = arr2[j];
			arr2[j] = save;
			j++;
		}
		else 
		{
			if (arr1[i] > arr2[p])
			{
				save = arr1[i];
				arr1[i] = arr2[p];
				arr2[p] = save;
				p++;
			}
		}
		if ((p >= j) || (p == len2)) { p = 0; }
	}
	p = j;
	for (i = 0; i < len2; i++)
	{
		if ((arr2[i] > arr2[j]) && ((p == len2) || (arr2[j] <= arr2[p])))
		{
			save = arr2[i];
                        arr2[i] = arr2[j];
                        arr2[j] = save;
                        j++;
		}
		else if (arr2[j] > arr2[p])
		{
			save = arr2[i];
			arr2[i] = arr2[p];
			arr2[p] = save;
			p++;
		}
		if (j == len2) { j = i+1; }
	}
	return 0;
}


int main (void)
{
        int len1, len2, i;
        double *arr1, *arr2;	// arr1 и arr2 соответственно два данных массива
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
	test_file_input_int(input, &len1, &error);
	arr1 = (double *)malloc(len1 * sizeof(double));
	for ( i = 0; i < len1; i ++)
        {
                test_file_input_double(input, &arr1[i], &error);
        }
	test_file_input_int(input, &len2, &error);
	arr2 = (double *)malloc(len2 * sizeof(double));
        for ( i = 0; i < len2; i ++)
        {
                test_file_input_double(input, &arr2[i], &error);
        }
	merge_arr(arr1, arr2, len1, len2);
        for ( i = 0; i < len1; i ++)
        {
                fprintf (output, "%lf \n", arr1[i]);
        }
        for ( i = 0; i < len2; i ++)
        {
                fprintf (output, "%lf \n", arr2[i]);
        }
        free(arr1);
	free(arr2);
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
