#include <stdio.h>
#include <math.h>

typedef enum {
	OK,
	LIM,    //  �������� ����� ��������
} error;

error error_code;

double taylor_exp(double x, double eps);
