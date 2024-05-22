#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

// New structure for testing
typedef struct 
{
	const char* file_name; // The file with matrix' elements 
	int n;                // The dimention of the matrix
	Error error;         // Error code
} TestCase;

int main(void) 
{
	FILE* f;
	Error error;
	int result = 0;
	double** matrix = NULL;
	double epsilon = 0.0001;

	TestCase tests[] = 
	{ 
		{"matrix1.txt", 1, OK},
		{"matrix2.txt", 2, OK},
		{"matrix3.txt", 3, OK},
	};

	int number_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < number_tasks; n++) 
	{

		if (tests[n].n == 0) 
		{
			error = ZERO_MATRIX;
			goto terminate;
		}

		// Opening a file, reading matrix element values ​​from it and writing them to the array
		f = fopen(tests[n].file_name, "r");

		if (f == NULL) 
		{
			printf("File did not open\n");
			error = FILE_ERROR;
			goto terminate;
		}
		if (fscanf(f, "%d", &n) != 1)
		{
			printf("File is empty\n");
			error = FILE_ERROR;
			fclose(f);
			goto terminate;
		}

		matrix = (double**)malloc(sizeof(double*) * tests[n].n);

		if (matrix == NULL) 
		{
			printf("Memory error\n");
			fclose(f);
			error = MEMORY_ERROR;
			goto terminate;
		}

		for (int i = 0; i < tests[n].n; i++) 
		{
			matrix[i] = (double*)malloc(sizeof(double) * 2 * tests[n].n);
			if (matrix[i] == NULL) 
			{
				printf("Memory error\n");
				for (int j = 0; j < i; j++) 
				{
					free(matrix[j]);
				}
				free(matrix);
				fclose(f);
				error = MEMORY_ERROR;
				goto terminate;
			}
			for (int j = 0; j < (2 * tests[n].n); j++) 
			{
				if (j < tests[n].n) 
				{
					if (fscanf(f, "%lf", &matrix[i][j]) != 1) 
					{
						printf("Not enough elements in the file\n");
						error = FILE_ERROR;
						fclose(f);
						for (int i = 0; i < tests[n].n; i++) 
						{
							free(matrix[i]);
						}
						free(matrix);
						goto terminate;
					}
				}
			}
		}
		fclose(f);

		gauss_elimination(matrix, tests[n].n, &error, epsilon);

	terminate:
		if (error != tests[n].error) 
		{
			printf("Test №%d is not completed\n", n + 1);
		}
		else if (error == OK) 
		{
			printf("Test №%d is completed. Result:\n\n", n + 1);
			for (int i = 0; i < tests[n].n; i++) 
			{
				for (int j = tests[n].n; j < (2 * tests[n].n); j++) 
				{
					printf("%lf ", matrix[i][j]);
				}
				printf("\n");
				free(matrix[i]);
			}
			free(matrix);
			printf("\n");
		}
		else 
		{
			printf("Test №%d is completed\n", n + 1);
		}
	}
	return 0;
}