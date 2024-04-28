#include <stdio.h>
#include <math.h>

typedef enum {           // Коды ошибок:
	OK,                  //  Все хорошо
	I_LIMIT_EXCEEDED,    //  Превышен лимит итераций
} error;

double calculateSin(double x, double eps, error* err);