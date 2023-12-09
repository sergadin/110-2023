#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int repl_elem (double *arr, int len);      //убирает повторяющиеся части
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int repl_elem (double *arr, int len)
{
        int i;
	double c = arr[0], t;
        for (i = 1; i < len-1; i++)
        {
		t = arr[i];
		arr [i] = (arr[i+1] + c) / 2;
		c = t;
        }
        return 0;
}


int main (void)
{
        int i;
        double *arr, len;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
	test_file_input_double (input, &len, &error);
	len = (int) len;
        arr = (double *)malloc(len*sizeof(double));
        for (i = 0; i < len; i++) { test_file_input_double (input, &arr[i], &error); }
        repl_elem (arr, len);
	for (i = 0; i < len; i++)
	{
        	fprintf (output, "%lf ", arr[i]);
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
