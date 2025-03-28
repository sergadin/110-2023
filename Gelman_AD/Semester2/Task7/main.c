﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// New structure for testing
struct testing
{
	const char* file_name; // The file with matrix' elements
	int n;                // The dimention of the matrix
	double epsilon;      // The epsilon
	Error error;        // Error code
};

int main(void)
{
	double epsilon = 0.0001;
	int n = 0; // The size of the matrix (from the file)
	double** matrix = NULL; // The pointer to an array containing matrix elements (a variable for storing the result)
	double* vector_b = NULL;
	double* vector_x = NULL;
	FILE* f = NULL;
	Error error;

	struct testing test_number[3] =
	{
		{"matrix1.txt", 2, 0.0001, OK},
		{"matrix2.txt", 3, 0.0001, OK},
		{"matrix3.txt", 2, 0.0001, OK},
	};

	for (int j = 0; j < 3; j++)
	{
		f = fopen(test_number[j].file_name, "r");
		n = test_number[j].n;

		// Opening a file, reading matrix element values ​​from it and writing them to the array
		if (f == NULL)
		{
			printf("File did not open\n");
			error = FILE_ERROR;
			goto terminate;
		}

		vector_b = (double*)malloc((test_number[j].n) * sizeof(double));
		if (vector_b == NULL)
		{
			printf("Memory error\n");
			error = MEMORY_ERROR;
			continue;
		}
		vector_x = (double*)malloc((test_number[j].n) * sizeof(double));
		if (vector_x == NULL)
		{
			free(vector_b);
			printf("Memory error\n");
			error = MEMORY_ERROR;
			continue;
		}

		matrix = (double**)malloc((n) * sizeof(double*));
		if (matrix == NULL)
		{
			printf("Random Access Memory is not allocated\n");
			error = MEMORY_ERROR;
			fclose(f);
			free(vector_b);
			free(vector_x);
			goto terminate;
		}

		for (int i = 0; i < n; ++i)
		{
			matrix[i] = NULL;
			matrix[i] = (double*)malloc((test_number[i].n) * sizeof(double));
			if (matrix[i] == NULL)
			{
				for (int k = 0; k < i; k++)
				{
					free(matrix[k]);
				}
				break;
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				fscanf(f, "%lf", &matrix[i][k]);
			}
			fscanf(f, "%lf", &vector_b[i]);
		}

		fclose(f);
		descent_method(matrix, n, vector_b, vector_x, epsilon, &error);

	terminate:
		if (error != test_number[j].error)
		{
			printf("Test №%d is not completed\n", j + 1);
		}
		else
		{
			for (int k = 0; k < n; k++)
			{
				printf("x%d = %lf ", k + 1, vector_x[k]);
			}
			printf("Test №%d is completed.\n", j + 1);
			// printf("aaaa = %d \n", n);
		}
		free(vector_b);
		free(vector_x);
		for (int i = 0; i < n; i++)
		{
			free(matrix[i]);
		}
		free(matrix);
	}
	return 0;
}