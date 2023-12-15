#include <stdio.h>
#include <stdlib.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int rem_rep_parts (double *arr, int len);      //убирает повторяющиеся части
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа
int rotate (int place, int len, double *arr);	//переносит элемент в конец массива

int rotate (int place, int len, double *arr)
{
<<<<<<< HEAD
	int i;
	double c = arr[place];
	for (i = place; i < len-1; i++)
	{
		arr[i] = arr[i+1];
	}
	arr[len-1] = c;
	return 0;
}

int rem_rep_parts (double *arr, int len)
{
	double e = 0.001;	//маленькое эпсилон для сравнения чисел типа double
	int i, j = 0;	//i нужно для цикла, а j - вспомагательная переменная
	for (i = 1; i < len; i++)
	{
		if (arr[i-j]-arr[i-j-1] < e)
		{ arr[i-j] = 0,rotate (i-j, len, arr), j++; }
=======
	int i, p = 1, lenp = 1;	//i нужно для цикла, а j - вспомагательная переменная
	for (i = 1; i < len; i++)
	{
		if ( arr[i] != arr[i-1] )
		{
		       	arr[p] = arr[i];
			lenp++;
			p++;
		}
>>>>>>> ff381eb (изменение решения 9-ой задачи и добавлено частичное решение 20-ой задачи.)
	}
	return j;
}


int main (void)
{
<<<<<<< HEAD
        int len, i, j;
	double *arr;
=======
        int len, i;
	int *arr;
>>>>>>> ff381eb (изменение решения 9-ой задачи и добавлено частичное решение 20-ой задачи.)
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
        fscanf(input, "%d", &len);
	arr = (double *)malloc(len*sizeof(double));
	for (i = 0; i < len; i++) { test_file_input_double(input, &arr[i], &error); }
	j = rem_rep_parts (arr, len);
	j++;
	for (i = 0; i < len; i++)
	{
		fprintf(output, "%lf ", arr[i]);
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
