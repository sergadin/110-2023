#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strings.h"

// New structure for testing
typedef struct 
{
	const char* file_name; // The file with matrix' elements 
	Error err;            // Error code
} TestCase;

int main(void) 
{
	FILE* fout, * f;
	Error err;
	int result = 0; // Number of strings, result
	size_t length = 1024;
	char* buf = NULL; // An array of strings, current line
	err = OK;

	TestCase tests[] = 
	{ {"string1.txt", OK},
	  {"string2.txt", OK},
	  {"string3.txt", OK},
	};

	int n_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < n_tasks; n++) 
	{

		f = fopen(tests[n].file_name, "r");
		if (f == NULL) 
		{
			printf("File did not open\n");
			err = FILE_ERROR;
			goto terminate;
		}

		buf = (char*)malloc(1024 * sizeof(char));
		if (buf == NULL) 
		{
			printf("Memory error\n");
			err = MEMORY_ERROR;
			fclose(f);
			goto terminate;
		}

		if (getline(&buf, &length, f) == -1) 
		{
			err = FILE_ERROR;
			fclose(f);
			free(buf);
			goto terminate;
		}

		free(buf);
		rewind(f);

		fout = fopen("string_correct.txt", "w");

		if (fout == NULL) 
		{
			printf("File did not open\n");
			err = FILE_ERROR;
			fclose(f);
			goto terminate;
		}

		result = split_string(f, fout, &err);
		fclose(f);
		fclose(fout);

		terminate:
		if (err != tests[n].err) 
		{
			printf("The ¹%d test is not completed.\n", n + 1);
		}
		else if (err == OK)
		{
			printf("The ¹%d test is completed. Modified string is written to the file string_correct.txt\n", n + 1);
		}
		else 
		{
			printf("The ¹%d test is completed.\n", n + 1);
		}
	}
	return 0;
}