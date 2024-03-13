#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z_2_3.h"

/*	Параметры: f - действительнозначная функция 
 *		       а - левая граница отрезка интегрирования. Должна быть меньше правой границы.
 *             b - правая граница отрезка интегрирования. Должна быть больше левой границы.
 *             n - количество подотрезков в разбиении.
 *             *err - указатель на код ошибки.
 *      Функция подсчитывает приближенное значение интеграла функции f(x) с помощью метода Симпсона с заданным разбиением.
 */
static double Integrate(RRFun f, double a, double b, double n, Error *err);
static double Integrate(RRFun f, double a, double b, double n, Error *err){
	double dx, summa, simps_sum; /* Соответственно: подотрезок разбиения, интегральная сумма.*/
	int k = 4;
	dx = (b - a) / n;
	summa = (*f)(a) + (*f)(b);
	for (int i = 1; i<n; i++){
	    summa += k*((*f)(a + i*dx));
	    k = 6 - k;
	}
	summa = (summa * dx) / 3;
	return summa;
}
/*	Параметры: f - действительнозначная функция 
 *		       а - левая граница отрезка интегрирования. Должна быть меньше правой границы.
 *             b - правая граница отрезка интегрирования. Должна быть больше левой границы.
 *             eps - погрешность.
 *             *err - указатель на код ошибки.
 *      Функция определяет лучшее приближение значения интергала. Используется алгоритм удвоения сетки.
 */
double Simpson_method(RRFun f, double a, double b, double eps, Error *err){
    double s1, s2; /*Соответственно: первая интегральная сумма, вторая интегральная сумма.*/
    int n = 1024;
    if (a >= b){
        *err = NA_WRNG_ORD;
        return -1;
    }
    s1 = Integrate(f, a, b, n, err);
    n = 2048;
    while (fabs(s1-s2)>eps){
        s2 = Integrate(f, a, b, n, err);
        s1 = s2;
        n = 2*n;
    }
    *err = NA_OK;
    return s2; 
}
