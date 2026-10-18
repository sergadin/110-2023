#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z1_3.h"

static int sign(double x);
static double max(double x, double y, double eps);

/* Параметры: х - первое действительное число.
 *	      у - второе действительное число.
 *            eps - погрешность, действительное число.
 * Функция возвращает максимальное значение из трех переданных в нее значений.
 */
static double max(double x, double y, double eps)
{
	double max_1;
	if (x > y)
	{
	max_1 = x;
	}
	else
	{
		max_1 = y;
	}
	if (eps > max_1)
	{
		return eps;
	}
	return max_1;
}

/* Параметры: х - действительное число.
 * Функция возвращает 1, если значение х больше 0 и -1 в противном случае.
 */
static int sign(double x){
	if (x > 0)
	{
		return 1;
	}
	return -1;
}

/*	Параметры: f - действительнозначная функция
 *		   a - действительное число, левая граница 
 *		   b - действительное число, правая граница
 *		   eps - погрешность
 *		   *err - код ошибки, по которому будет проводиться проверка
 *		   *iter - код количества итераций
 *	Функция ищет приближенное значение корня функции f(x) с помощью метода хорд. 
 */
	
double chord_method(RRFun f, double a, double b, double eps, Error *err, int *iter){
	double x_i, x_prev, f_xi, f_a = (*f)(a), f_b = (*f)(b); /*соответственно: точка пересечения с осью оХ, предыдущая точка пересечения с оХ, 
							значение в этой точке, значение в концах отрезка*/
	int limit = 10000000;
	*iter = 0;
	*err = NA_OK;
    	if(a > b)
		{
        	*err = NA_WRNG_ORD;
        	return -1;
    	}
	if (sign(f_a)*sign(f_b)>0)
		{
        	*err = NA_NO_ROOT;
        	return -1;
        }
    x_i = a - ((f_a * (b-a)) / (f_b - f_a));
    x_prev = a;
	f_xi = (*f)(x_i);

    while((fabs(x_i - x_prev) > (max(x_i, x_prev, 1.0) * eps)) && (limit>0))
		{
        	if ((sign(f_xi)*sign(f_b))<0)
			{
			
				a = x_i;
	            f_a = f_xi;
			
	        }
			else if ((sign(f_xi) * sign(f_a))<0)
			{
			
	        	b = x_i;
	        	f_b = f_xi;
			
	        }
			else
			{
			
	            *err = NA_NO_ROOT;
	            return -1;
			
	        }
		
		x_prev = x_i;
	        x_i = a - ((f_a * (b-a)) / (f_b - f_a));
	        f_xi = (*f)(x_i);
	        limit -= 1;

    	}
    	if (limit == 0)
		{
	    	*err = NA_NO_ROOT;
	    	return -1;
    	}
	
    	*iter = 10000000 - limit; 
    	return x_i;
}
