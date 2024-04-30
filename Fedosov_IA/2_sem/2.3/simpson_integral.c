#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "simpson_integral.h"

#define LIMIT 30

double simpson_integral(double a, double b, double (*f)(double), double eps, Error *error)
{	

    double N = 4.;		//произвольное начальное значение
    double sum1 = 0., sum2 = 0.; //вторая сумма будет показывать значения интеграла для 2^N отрезков, первая для 2^(N-1)
    double x, h;		//эти числа, i и индексы нужны для работы с отрезками
    double index1, index2;	
    unsigned int i;
    double func;
    *error = OK;
    
    for(int k = 0; k < LIMIT; k ++) { 
        h = (b-a) / N;
        sum1 = sum2 = -(f(a) + f(b));
        index1 = index2 = 4.;
        i = 0;
        for(x = a; x <= b + h / 2.; x += h) {
            sum1 +=  (index1 = 6.-index1) * (func = f(x));
            if (i++%2 == 0) {
                sum2 += (index2 = 6.-index2) * func;
            };
        };
        
        //Тут проверяется, что увеленичение отрезков в 2 раза приведет к изменению значения интеграла меньше, чем на eps, в таком случае вычисления считаются точными
        if (fabs((sum1-2. * sum2) / sum1) <= eps) {
        	return (h * sum1)/3. + h * (2. * sum2 - sum1) / 45.;
        } else { 
        	N*=2.;
        }

    };
    
    if (!(isnan(sum1) || isnan(sum2)) && !(isinf(sum1) || isinf(sum2))) {
    	*error = OK;
    } else {
    	*error = NOT_A_NUMBER;
    	return 0;
    }
    
    *error = OP_LIMIT;
    
    //Возвращается приблизительный ответ
    return (h*sum1)/3.; 
};
