#include <math.h>
#include "z7.h"
#include <stdio.h>

//��������������� ��������� ��� ��������
typedef struct 
{
	F_RR f;	// ������� ��� ������������������
	F_RR g;	// ������� ��� ��������
	double x;	// �������������� �������� (��������)
	Error err;	// ����� ������
} BoxTest;

//��������������� ������� ��� ������������: �������������
static double Identical(double x);
//��������������� ������� ��� ������������: ������������ 
static double Polynomial2(double x);
//��������������� ������� ��� ������������: ����������
static double Polynomial3(double x);
//��������������� ������� ��� ������������: �������������
static double Exponential(double x);
//��������������� ������� ��� ������������: ��������
static double Linear(double x);

static double Identical(double x)
{
	return x;
}

static double Polynomial2(double x)
{
	return x * (x - 2e16);
}

static double Polynomial3(double x)
{
	return x*(5 - x)*(x + 5);
}

static double Exponential(double x)
{
	int z = x;
	return 2 ^ z;
}

static double Linear(double x)
{
	return x - 10;
}


int main(void)
{ 
	Error err;
	double eps = 1e-5;
	int n_tests;

	BoxTest tests[] = {
	{cos, sin, 0, BAD},
	{Identical, Identical, 1, BAD},
	{Identical, Identical, 0, GOOD},
	{Polynomial2, cos, 0, BAD},
	{Exponential, Polynomial2, 0, BAD },
	{Linear, Polynomial3, 45, GOOD },
	};
	
	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		sequence_recursive_takes(tests[i].f, tests[i].g, tests[i].x, eps, &err);

		if (err != tests[i].err)
		{
			printf("Tht test %d failed\n", i + 1);
		}
		else
		{
			printf("The test %d has been verified\n", i + 1);
		}
	}

	return 0;
}