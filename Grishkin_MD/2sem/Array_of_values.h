#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** ��������� ������� �� R � R. */
typedef double (*RRFun)(double);

typedef enum{   // ������
        OK,   /* ���������� ���������� */
        MEMORY,    /* �� ������� �������� ������ */
        PARAM,     /* ������������ �������� ������� ���������� ������ */
}error;

double* arrayOfValues(RRFun* func, int len, double x, error* err);

// ������ ������� ������� ������ � ��������� ��� ���������� ������� � ����� x.
// ��� �������� ���������� ���������� ������ ��������
