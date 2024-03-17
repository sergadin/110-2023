#include <math.h>
#include "Heading.h"
#include <stdio.h>

typedef struct 
{  /* ����� ����������-��������� ��� ���������� ����� */
	RRFun f; //������� �1
	double x; //�������������� ��������
	double res; //��������� ���������
	Error err; //����� ������
} TestCase;

static double constant(double x); /* ��������������� ������� ��� ������������: ���������*/
static double near_to_zero(double x); /* ��������������� ������� ��� ������������: ���������� ��������� �������� (������������ ������ ����)*/
static double sum_1(double x);  /* ��������������� ������� ��� ������������: ���������� � ��������������� ����� 1*/
static double substract_2(double x); /* ��������������� ������� ��� ������������: �������� �� ��������������� ����� 2*/

static double substract_2(double x) {
	return x - 2;
}

static double constant(double x) {
	return x;
}

static double near_to_zero(double x) {
	return x += 1e-5;
}
static double sum_1(double x) {
	return x + 1;
}

int main(void) 
{
	double res, eps = 1e-7;
	Error err;

	TestCase tests[] = { {sin, cos, 0., 1, NA_OK},
	{sin, substract_2, 0.02, 0., NA_LIMIT},
	{constant, sin, -0.5, 0., NA_LIMIT},
	{sum_1, near_to_zero, -10000 - (1e-6),-(1e-6), NA_OK} };

	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* ���������� ������ */
	for (int n = 0; n < n_tasks; n++) 
	{
		res = composing_with_requisition(tests[n].f, tests[n].g, tests[n].x, eps, &err);
		if (err != tests[n].err) 
		{
			printf("���� �%d �� �������.\n", n + 1);
		}
		else if ((err == NA_OK) && (res - tests[n].res) > eps) 
		{
			printf("���� �%d �� �������.\n", n + 1);
		}
		else if ((err == NA_OK) && (res - tests[n].res) < eps) 
		{
			printf("���� �%d ������� �������. ������ ���������� �������� � = %lf\n", n + 1, res);
		}
		else 
		{
			printf("���� �%d ������� �������.\n", n + 1);
		}
	}
	return 0;
}