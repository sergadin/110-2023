#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {           // ���� ������:
	OK,                  //  ��� ������
	I_LIMIT_EXCEEDED,    //  �������� ����� ��������
	WRONG_INTERVAL,      //  ����������� ����� ��������
} error;

double findRoot(RRFun f, double a, double b, double eps, error* err);