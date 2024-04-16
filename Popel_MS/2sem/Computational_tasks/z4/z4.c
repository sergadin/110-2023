#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z4.h"

/*	Параметры: х - первое сравниваемое действительное значение
 *             у - второе сравниваемое действительное значение
 *             eps - погрешность - третье сравниваемое значение 
 *      Функция ищет максимальное значение.
 */

static double max(double x, double y, double eps);
static double max(double x, double y, double eps){
	double max_1;
	if (x > y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps > max_1){
		return eps;
	}
	return max_1;
}

/*	Параметры: х - действительное значение - точка, в которой необходимо найти х - должна лежать в интервале (0,2), иначе sqrt не сходится.
 *         eps - погрешность.
 *         *err - указатель на код ошибки.
 * Подсчитывает значение функции в точке х по разложению ряда Тейлора. Полученный результат сравнивается с значением sqrt(x).
 */
double Taylor_sqrt(double x, double eps, Error *err){
    int limit = 100000, n = 1; //лимит итераций; номер итерации. 
    double sqrt_sum = 1, temp = 1; //текущая сумма разложения в ряд Тейлора; значение текущего слагаемого.
    if ((fabs(x) < eps) || (x < 0)){
        *err = NA_FORB_VAL;
        return -1;
    }
    while((fabs(temp) > eps) && (limit > 0)){
    	temp *= (((-1) * (2 * n) * (2 * n - 1)) * (x - 1)) / ((n * n * 4));
        sqrt_sum += temp / (1 - 2 * n);
        limit -= 1;
        n += 1;
    }
    if (limit == 0){
    	*err = NA_LIMIT;
    	return -1;
    }
    *err = NA_OK;
    return sqrt_sum;
}
