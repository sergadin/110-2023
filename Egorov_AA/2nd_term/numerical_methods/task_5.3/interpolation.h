#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef struct {
	double x, y;
} point;

typedef enum {           // Коды ошибок:
	OK,                   //  Все хорошо
	I_LIMIT_EXCEEDED,     //  Превышен лимит итераций
	WRONG_INTERVAL,       //  Неправильно задан интервал
} error;

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err);

/* 
**
** 
** 
** 
** 
** 
** 
** 
** 
**
** 
** 
*/
