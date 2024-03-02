#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z1_3.h"

/*	Параметры: f - действительнозначная функция
 *		   a - действительное число, левая граница 
 *		   b - действительное число, правая граница
 *		   eps - погрешность
 *		   *err - код ошибки, по которому будет проводиться проверка
 *		   *iter - код количества итераций
 *	Функция получает значения структуры для тестирования, проверяет правильность выполнения теста. 
 */
	
double chord_method(RRFun f, double a, double b, double eps, Error *err, int *iter){
	double x_i, f_xi, f_a = (*f)(a), f_b = (*f)(b); /*соответственно: точка пересечения с осью оХ, значение в этой точке, 
									значение в концах отрезка*/
	int limit = 10000000;
    if(a > b){
        *err = NA_WRNG_ORD;
        return -1;
    }
    if(fabs(f_b - f_a) < eps){
        *err = NA_EQUAL_VAL;
        return -1;
    }
    if ((f_a * f_b) > 0){
        *err = NA_NO_ROOT;
        return -1;
        }
    x_i = a - ((f_a * (b-a)) / (f_b - f_a));

    f_xi = (*f)(x_i);
    if (fabs(f_b) < eps){
        *err = NA_OK;
	*iter = 0;
        return b;
    }else if (fabs(f_a) < eps){
        *err = NA_OK;
	*iter = 0;
        return a;
    }else if(fabs(f_xi) < eps){
        *err = NA_OK;
	*iter = 0;
        return x_i;
    }
    while((fabs(f_xi) > eps) && (limit > 0)){
        if ((f_xi * f_b) <= 0){

            a = x_i;
            f_a = f_xi;
        }else if ((f_xi * f_a)<=0){
            b = x_i;
            f_b = f_xi;
        }else{
            *err = NA_NO_ROOT;
            return -1;
        }

        if(fabs(f_b - f_a)<eps){
            *err = NA_EQUAL_VAL;
            return -1;
        }
        x_i = a - ((f_a * (b-a)) / (f_b - f_a));
        f_xi = (*f)(x_i);
        limit -= 1;

    }
    if (limit == 0){
    	*err = NA_NO_ROOT;
    	return -1;
    }
    *iter = 10000000-limit; 
    *err = NA_OK;
    return x_i;

}
