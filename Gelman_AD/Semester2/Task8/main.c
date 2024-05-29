#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

// New structure for testing
struct testing
{
	const char* file_name; // The file with matrix' elements
	double* result;       // Expected result
	Error error;         // Error code
};

int main(void)
{
	FILE* f = NULL;
	Error error;
	double* matrix = NULL;
	double* solution = NULL;
	double epsilon = 0.0001;

	struct testing test_number[3] =
	{
		{"matrix1.txt", (double[]) { 0.25 }, OK},
		{"matrix2.txt", (double[]) { 2, -1 }, OK},
		{"matrix3.txt", (double[]) { 0, 0.5, 0 }, OK}
	};

	for (int i = 0; i < 3; i++)
	{
		f = fopen(test_number[i].file_name, "r");
		int m, n; // The number of strings and the number of rows

		// Opening a file, reading matrix element values ​​from it and writing them to the array
		if (f == NULL)
		{
			printf("File did not open\n");
			error = FILE_ERROR;
			goto terminate;
		}
		if (fscanf(f, "%d%d", &m, &n) != 2)
		{
			printf("Error reading the file\n");
			error = FILE_ERROR;
			goto terminate;
		}

		matrix = (double*)malloc(m * n * sizeof(double));
		// matrix = (double**)malloc(sizeof(double*) * tests[n].n); from task 7
		if (matrix == NULL)
		{
			printf("Random Access Memory is not allocated\n");
			fclose(f);
			error = MEMORY_ERROR;
			goto terminate;
		}

		for (int j = 0; j < m * n; j++)
		{
			if (fscanf(f, "%lf", &matrix[j]) != 1)
			{
				printf("Error reading the file\n");
				goto terminate;
			}
		}
		fclose(f);

		solution = gauss_elimination(matrix, m, n, &error);

	terminate:
		if (error != test_number[i].error)
		{
			printf("Test №%d is not completed\n", i + 1);
		}
		else
		{
			printf("Test №%d is completed. Result:\n\n", i + 1);
			for (int j = 0; j < m; j++)
			{
				if (fabs(solution[j] - test_number[i].result[j]) > epsilon * fmax(fabs(solution[j]), fabs(test_number[i].result[j])))
				{
					printf("The %d-th test is not completed\n", i + 1);
					free(matrix);
					free(solution);
				}
				printf("The %d-th test is completed\n", i + 1);
				print_matrix(solution, 1, m);
			}
		}
		free(matrix);
		free(solution);
	}
	return 0;
}