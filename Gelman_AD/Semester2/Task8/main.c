#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

// New structure for testing
typedef struct
{
	const char* file_name; // The file with matrix' elements
	double* result;       // Expected result
	error error_code;         // Error code
} dataSet;

int main(void)
{
	error err;
	int test_number;
	const double epsilon = 0.0001;

	dataSet tests[] =
	{
		{"matrix1.txt", (double[]) { 0.28571428, 0.85714285, 7.42857142, -3.57142857 }, OK},
		{"matrix2.txt", (double[]) { 1000 }, OK},
		{"matrix3.txt", (double[]) { 55.17704468, -0.35057501, -2.53179109, 55.26782329, -1.04136025, -117.35089055, 5.13566938 }, OK}
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++)
	{
		FILE* f;
		double* matrix;
		double* solution;
		int m, n; // The number of strings and the number of rows
		f = fopen(tests[i].file_name, "r");

		// Opening a file, reading matrix element values ​​from it and writing them to the array
		if (f == NULL)
		{
			printf("File did not open\n");
			continue;
		}
		if (fscanf(f, "%d%d", &m, &n) != 2)
		{
			printf("Error reading the file\n");
			fclose(f);
			continue;
		}

		matrix = (double*)malloc(m * n * sizeof(double));
		if (matrix == NULL)
		{
			printf("Random Access Memory is not allocated\n");
			fclose(f);
			continue;
		}

		for (int j = 0; j < m * n; j++)
		{
			if (fscanf(f, "%lf", &matrix[j]) != 1)
			{
				printf("Error reading the file\n");
				fclose(f);
				free(matrix);
				continue;
			}
		}

		solution = gauss_elimination(matrix, m, n, &err);

		if (err != tests[i].error_code)
		{
			printf("Test №%d is not completed\n", i + 1);
		}
		else if (err == OK)
		{
			for (int j = 0; j < m; j++)
			{
				if (fabs(solution[j] - tests[i].result[j]) > epsilon * fmax(fabs(solution[j]), fabs(tests[i].result[j])))
				{
					printf("The %d-th test is not completed\n", i + 1);
					free(matrix);
					free(solution);
				}
			}
			printf("The %d-th test is completed. Solutions:\n", i + 1);
			print_matrix(solution, 1, m);
		}
		else
		{
			printf("The %d-th test is completed\n", i + 1);
		}
		free(matrix);
		free(solution);
		fclose(f);
	}
	return 0;
}