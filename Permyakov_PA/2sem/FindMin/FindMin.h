#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*func)(double);

typedef enum {               // Коды ошибок:
        OK,                  // - все хорошо
        INCORRECT_ARGUMENT,   // - дан аргумент, не соответствующий области определений функции
	ITERATION_LIMIT_EXCEEDED,		// - слишком много итераций
} error;

double FindMin(func f, double a, double b, double eps,  int* iter,  error* err);

/* для заданного отреза [a, b],
** на которой функция ограничена снизу и определена,
** функции f: IR x IR -> IR вычислить минимум f c точностью eps на нем.
**
** На вход подается отрезок [a, b], функция проверяет меньше а, чем b.
** Методом деления сетки находится минимум, если в какой то момент
** в точке не будет существовать функция - ошибка.
*/

