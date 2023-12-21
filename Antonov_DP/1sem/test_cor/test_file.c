#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, E_DATA, E_IO} ERR;

int test_file (FILE *input, ERR *error);
int test_file_input_double (FILE *input, double *num, ERR *error);
int test_file_input_int (FILE *input, int *num, ERR *error);
int sorted_arr (double *arr, int len);

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
	return 0;
}

int test_file_input_int (FILE *input, int *num, ERR *error)
{
        if (fscanf (input, "%d", & *num) != 1){
                if ( feof(input) != 0) { return 1; }
                else { *error = E_IO; return -1; }
        }
        return 0;
}

int sorted_arr (double *arr, int len)
{
	int i, incr = 1, decr = -1;
	double e;
	for (i = 1; i < len; i++)
	{
		if ((arr[i] - arr[i - 1]) > 0) { decr = 0; }
		if (arr[i-1] - arr[i] > 0) { incr = 0; }
	}
	return incr + decr;
}
