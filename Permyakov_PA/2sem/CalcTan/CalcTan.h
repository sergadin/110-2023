#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {                          // Коды ошибок:
        OK,                             // - все хорошо
        ITERATION_LIMIT_EXCEEDED,       // - слишком долго считает
	ARGUMENT_ERROR			// - аргумент вне области определения
} error;

double CalcTan(double x, double eps,  error* err);

// Посчиать тангенс с данной точностью в данной точке.
