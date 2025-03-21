#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*������� �� R � R*/
typedef double (*FR_R)(double);

/* ������ ���� */
typedef enum
{
	WRONG_AB,	//������������ �������
	LIMIT_0,	//������� ���������, �� �� ������� �����, ��� � ������� �������
	GOOD,		//������� ���������; ������� �����, ��� � ������� �������
} Error;

/*
* ���������:
*	� f - ������� R -> R ��� ������ ��������;
*	� a - ������ ������� ��� ������ ��������;
*	� b - ����� ������� ��� ������ ��������;
*	� eps - �����������;
*	� *err - ��������� �� ������;
* -----------------------------------------------------------------------------------------
*	�� ���� ������� ��������� ����������� ������������ ������� �� �������. ����� ���� ��������� ������� �� ���������� � ������ ��������� ������� �������� � �������� ������ �� ���
*/

double min_step(FR_R f, double a, double b, double eps, Error* err);
