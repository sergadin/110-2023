#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// New structure for testing
typedef struct 
{
	const char* file_name; // The file with matrix' elements 
	double result;        // Expected result
	Error err;           // Error code
} TestCase;

static double max(double x, double y, double epsilon);
static double max(double x, double y, double epsilon) 
{
	double max_1;
	if (x > y) 
	{
		max_1 = x;
	}
	else 
	{
		max_1 = y;
	}
	if (epsilon > max_1) 
	{
		return epsilon;
	}
	return max_1;
}


int main(void) 
{
	double result = 0;
	double epsilon = 1e-5;
	int order = 0; // The size of the matrix (from the file)
	double* matrix = NULL; // The pointer to an array containing matrix elements (a variable for storing the result)
	FILE* f = NULL;
	Error err;

	TestCase tests[] = 
	{ 
		{"matr1.txt", 4, OK},
		{"matr2.txt", 6.5, OK},
		{"matr3.txt", -20, OK},
	};

	int number_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < number_tasks; n++) 
	{
		f = fopen(tests[n].file_name, "r");

		//Opening a file, reading matrix element values ​​from it and writing them to the array
		if (f == NULL) 
		{
			printf("File did not open\n");
			err = FILE_WR;
			goto terminate;
		}

		if (fscanf(f, "%d", &order) != 1) 
		{
			printf("File is empty\n");
			err = FILE_WR;
			fclose(f);
			goto terminate;

		}

		matrix = (double*)malloc((order * order) * sizeof(double));
		if (matrix == NULL) 
		{
			printf("Random Access Memory is not allocated\n");
			err = MEMORY_ERROR;
			fclose(f);
			goto terminate;
		}

		for (int i = 0; i < (order * order); ++i) 
		{
			if (fscanf(f, "%lf", &matrix[i]) != 1) 
			{
				printf("Not enough elements in the file\n");
				err = FILE_WRONG;
				free(matrix);
				fclose(f);
				goto terminate;
			}
		}

		fclose(f);
		result = determinate(matrix, order, epsilon, &err);
		free(matrix);

		terminate:
		if (err != tests[n].err) 
		{
			printf("Test №%d is not completed\n", n + 1);
		}
		else if ((err == OK) && ((fabs(result - tests[n].result)) > (max(result, tests[n].result, 1.0) * epsilon))) 
		{
			printf("Test №%d is not completed. %lf\n", n + 1, result);
		}
		else if ((err == OK) && ((fabs(result - tests[n].result)) < (max(result, tests[n].result, 1.0) * epsilon))) 
		{
			printf("Test №%d is completed. The solution from the matrix: %lf\n", n + 1, result);
		}
		else 
		{
			printf("Test №%d is completed.\n", n + 1);
		}
	}
	return 0;
}