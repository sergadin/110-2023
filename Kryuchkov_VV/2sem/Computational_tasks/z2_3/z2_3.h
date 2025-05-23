#include <math.h>

/* Множество функций из R в R*/
typedef double (*RRFun)(double);

/* Основные ошибки*/
typedef enum 
{
	NA_OK, /*Нет ошибок*/
    NA_WRNG_ORD, /*Неправильный порядок введенных границ*/
    NA_LIMIT, /*Превышение лимита итераций*/
}Error;


/* Подсчет значений композиции функции.
 *	
 *	Параметры: f - первая действительнозначная функция 
 *		   a - левая граница отрезка интегрирования.
 *         b - правая граница отрезка интегрирования.
 *         eps - погрешность.
 *         *err - указатель на код ошибки.
 * Подсчитывается значение подынтегральной суммы с помощью метода Симспона: производится разбиение отрезка на четное число подотрезков.
 * Для границ двух соседних подотрезков находятся значения, на которых строится парабола. Подсчитывается площадь под параболой на этих двух
 * подотрезках.
 * Вывод: 
 * Если код выполнен без ошибок, выводится код ошибки NA_OK и значение подынтегральной суммы.
 * Если порядок границ отрезка введены неправильно, выводится код ошибки NA_WRNG_ORD.
 */

double Simpson_method(RRFun f, double a, double b, double eps, Error *err);
