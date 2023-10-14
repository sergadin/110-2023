#include <stdio.h>

int test_file (FILE *input);

int test_file (FILE *input)
{
	if (input == NULL){
	       printf ("Не удалось открыть: inut.txt");
	       return -1;
	}
	{
		return 0;
	}
}	
