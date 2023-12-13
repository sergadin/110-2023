#include <stdio.h>

typedef enum { OK = 0, E_DATA, E_IO} ERR;

int test_file (FILE *input, ERR *error);
int test_file_input_double (FILE *input, double *num, ERR *error);
int test_file_input_double (FILE *input, double *num, ERR *error);

int test_file_input_double (FILE *input, double *num, ERR *error)
{
        if (fscanf (input, "%lf", & *num) != 1){
                if ( feof(input) != 0) { return 1; }
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
}

int test_file_input_int (FILE *input, int *num, ERR *error)
{
        if (fscanf (input, "%d", & *num) != 1){
                if ( feof(input) != 0) { return 1; }
                else { *error = E_IO; return -1; }
        }
        return 0;
}

