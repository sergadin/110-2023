#include "findMinValue.h"

double findMinValue(RRFun f, double a, double b, double eps, error* err) {
	const double phi = 0.38196;      // ���������, � ������� ������� �����������
	int limit = 10000;               // ����������� �� ���������� ��������

	if (a > b) {
		*err = WRONG_INTERVAL;       // �������� ������ ��������� ������� ��������� 
		return -1;
	}

	while ((fabs((*f)(b) - (*f)(a)) > eps * fabs((*f)(a) + (*f)(b)) / 2) ||    // ������������� �����
		(fabs((*f)(b) - (*f)(a)) > eps)) {
		double x1, x2;                                                       

		x1 = a + phi * (b - a);
		x2 = b - phi * (b - a);

		if ((*f)(x1) < (*f)(x2)) {
			b = x2;
		}
		else {
			a = x1;
		}
		limit--;
	}

	if (limit <= 0) {               // �������� ������ �� ���������� ���������� ��������
		*err = I_LIMIT_EXCEEDED;
		return -1;
	}

	printf("Minimum: %lf\n", fabs((*f)((b + a) / 2)));
	*err = OK;
	return (*f)((b + a) / 2);
}
