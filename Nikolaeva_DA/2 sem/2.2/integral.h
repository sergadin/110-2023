#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);
typedef enum {
	OK = 0,
	NA_LIMIT,
	NO_INTER
} Error;

/* 
 *
 *	Параметры: f - первая действительнозначная функция
 *		   a - левая граница отрезка интегрирования.
 *         b - правая граница отрезка интегрирования.
 *         eps - погрешность.
 *         *err - указатель на код ошибки.
 * Подсчитывается значение интеграла по составной формуле трапеций: путем разбиения отрезка на подотрезки. Далее удваивается число отрезков и находится значение интеграла с точностью eps.
 * Вывод:
 * Если код выполнен без ошибок, выводится код ошибки OK и значение интеграла.
 * Если порядок границ отрезка введены неправильно, выводится код ошибки NO_INTER.
 * Если превышен лимит операций то мы получаем  NO_INTER.
 */

double integral(RRFun f, double a, double b, double eps, Error *err);


