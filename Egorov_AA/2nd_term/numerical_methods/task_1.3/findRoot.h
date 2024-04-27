#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {           // Коды ошибок:
	OK,                  //  Все хорошо
	I_LIMIT_EXCEEDED,    //  Превышен лимит итераций
	WRONG_INTERVAL,      //  Неправильно задан интервал
} error;

double findRoot(RRFun f, double a, double b, double eps, error* err);