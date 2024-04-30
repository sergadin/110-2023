#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z3_2.h"

/*	Параметры:
 *		   x - первое значение
 *		   y - второе значение
 *		   eps - погрешность
 *	Функция ищет максимальное значение из трех введенных. 
 */
static double max(double x, double y, double eps);
static double max(double x, double y, double eps){
	double max_1;
	if (x > y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps>max_1){
		return eps;
	}
	return max_1;
}

/*	Параметры: f - действительнозначная функция 
 *		   а - левая граница отрезка
 *		   b - правая граница отрезка
 *		   eps - погрешность
 *		   err - код ошибки, по которому будет проводиться проверка
 *	Функция ищет минимальное значение функции на обозначенном отрезке методом золотого сечения. 
 */
double Min_GoldenRatio(RRFun f, double a, double b, double eps, Error *err){
    double delta = 0.618; //отношение большего отрезка ко всему промежутку или меньшего отрезка к большему.
    int limit = 100000; //лимит итераций
    double x, y, a_i = a, b_i = b, f_x, f_y; //соответственно: первая и вторая точки, разбивающие отрезок в отношении золотого сечения
	                                     //левая и правая границы рассматриваемого отрезка, значения функции в точках х и у.
    if (a > b){
        *err = NA_WRNG_ORD;
        return 100;
    }
    x =  a_i + (1 - delta) * (b_i - a_i);
    y = a_i + delta * (b_i - a_i);
    f_x = (*f)(x);
    f_y = (*f)(y);
    while (((b_i - a_i) > (max(b_i, a_i, 1.0) * eps)) && (limit > 0)){
        if (f_x > f_y){
            a_i = x;
            x = y;
            y = a_i + delta * (b_i - a_i);
            f_y = (*f)(y);
        }else if (f_x < f_y){
            b_i = y;
            y = x;
            x = a_i + (1 - delta) * (b_i - a_i);
            f_x = (*f)(x);
        }
        limit -= 1;
    }
    if (limit == 0){
        *err = NA_LIMIT;
        return 100000;
    }
    x = (b_i + a_i)/2;
    *err = NA_OK;
    return ((*f)(x));
}
