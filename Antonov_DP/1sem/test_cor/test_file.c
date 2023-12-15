#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO} ERR;

int test_file (FILE *input, ERR *error);
int test_file_input_double (FILE *input, double *num, ERR *error);
<<<<<<< HEAD
=======
int test_file_input_int (FILE *input, int *num, ERR *error);
int file_read_arr (FILE *input, double *arr, int len, ERR *error);
>>>>>>> ff381eb (изменение решения 9-ой задачи и добавлено частичное решение 20-ой задачи.)

int test_file_input_double (FILE *input, double *num, ERR *error)
{
        if (fscanf (input, "%lf", & *num) != 1){
                if (feof(input) != 0) { return 1; }
                else { *error = E_IO; return -1; }
        }
        return 0;
}

int test_file (FILE *input, ERR *error)
{
	if (input == NULL){
	       printf ("Не удалось открыть: input.txt");
	       *error = E_DATA;
	}
	{
		return 0;
	}
<<<<<<< HEAD
}	
=======
}

int test_file_input_int (FILE *input, int *num, ERR *error)
{
        if (fscanf (input, "%d", & *num) != 1){
                if ( feof(input) != 0) { return 1; }
                else { *error = E_IO; return -1; }
        }
        return 0;
}

int file_read_arr (FILE *input, double *arr, int len, ERR *error)
{
	int i, incr = 1, decr = -1;
	arr = (double *)malloc(len * sizeof(double));
	for (i = 0; i < len; i++)
	{
		test_file_input_double(input, &arr[i], error);
	}
	for (i = 1; i < len; i++)
	{
		if (arr[i-1] < arr[i]) { decr = 0; }
		if (arr[i-1] > arr[i]) { incr = 0; }
	}
	return incr + decr;
}
>>>>>>> ff381eb (изменение решения 9-ой задачи и добавлено частичное решение 20-ой задачи.)
