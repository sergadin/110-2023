#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// New structure for testing
typedef struct 
{
	const char* file_name; //�������� �����, � ������� ��������� �������� �������
	double result; //��������� ���������
	Error err; //����� ������
} TestCase;

static double max(double x, double y, double eps);
static double max(double x, double y, double eps) 
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
	if (eps > max_1) 
	{
		return eps;
	}
	return max_1;
}


int main(void) 
{
	double res = 0, eps = 1e-5;
	int ord = 0; //������� ������� - ����������� �� �����
	double* matr = NULL; //��������� �� ������, ���������� �������� �������, ���������� ��� ������ ����������
	FILE* f = NULL;
	Error err;

	TestCase tests[] = 
	{ 
		{"matr1.txt", 4, NA_OK},
		{"matr2.txt", 6.5, NA_OK},
		{"matr3.txt", -20, NA_OK},
	};

	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* ���������� ������ */

	for (int n = 0; n < n_tasks; n++) 
	{
		f = fopen(tests[n].file_name, "r");

		if (f == NULL) 
		{								/*�������� �����, ���������� �� ���� �������� ��������� ������� � ������ �� � ������.*/
			printf("���� �� �����������\n");
			err = FILE_WR;
			goto terminate;
		}

		if (fscanf(f, "%d", &ord) != 1) 
		{
			printf("���� ����\n");
			err = FILE_WR;
			fclose(f);
			goto terminate;

		}

		matr = (double*)malloc((ord * ord) * sizeof(double));
		if (matr == NULL) 
		{
			printf("����������� ������ �� ��������\n");
			err = NA_MEMORY_ERR;
			fclose(f);
			goto terminate;
		}

		for (int i = 0; i < (ord * ord); ++i) 
		{
			if (fscanf(f, "%lf", &matr[i]) != 1) 
			{
				printf("� ����� ������������ ��������\n");
				err = FILE_WR;
				free(matr);
				fclose(f);
				goto terminate;
			}
		}

		fclose(f);
		res = determinate(matr, ord, eps, &err);
		free(matr);

		terminate:
		if (err != tests[n].err) 
		{
			printf("���� �%d �� �������.\n", n + 1);
		}
		else if ((err == NA_OK) && ((fabs(res - tests[n].res)) > (max(res, tests[n].res, 1.0) * eps))) 
		{
			printf("���� �%d �� �������. %lf\n", n + 1, res);
		}
		else if ((err == NA_OK) && ((fabs(res - tests[n].res)) < (max(res, tests[n].res, 1.0) * eps))) 
		{
			printf("���� �%d ������� �������. �������� ������������ �������: %lf\n", n + 1, res);
		}
		else 
		{
			printf("���� �%d ������� �������.\n", n + 1);
		}
	}
	return 0;
}