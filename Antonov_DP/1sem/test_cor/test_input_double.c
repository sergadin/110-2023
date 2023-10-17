#include <stdio.h>

typedef enum { OK = 0, E_DATA, E_IO} ERR;

int test_file_input_double (FILE *input, double *num, ERR *error);

int test_file_input_double (FILE *input, double *num, ERR *error)
{
	if (fscanf (input, "%lf", & *num) != 1){
		*error = E_IO;
		return -1;
	}
	return 0;
}
