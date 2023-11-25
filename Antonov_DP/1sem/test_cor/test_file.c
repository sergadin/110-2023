#include <stdio.h>

typedef enum { OK = 0, E_DATA, E_IO} ERR;

int test_file (FILE *input, ERR *error);

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
