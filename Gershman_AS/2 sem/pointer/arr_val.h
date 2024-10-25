#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** ��������� ������� �� R � R. */
typedef double (*RRFun)(double);

typedef enum {   // ������
    OK,   /* ���������� ���������� */
    MEM_ER,    /* �� ������� �������� ������ */
}Error;

double* arr_of_val(RRFun* func, int len, double x, Error* err);

/* ����� ������� �������� �������, � ����� �
*  ���������:
*               func - ������ ���������� �� �������
*               len - ����� ����� �������
*               x - �����, � ������� ��������� ��������
*               err - ��� ������
*/