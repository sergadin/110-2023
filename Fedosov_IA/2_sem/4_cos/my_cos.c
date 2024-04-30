#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_cos.h"


double my_cos(double x, double eps) {

	//первое слагаемое в ряде тейлора для косинуса равно 1, поэтому изначально задаются значения для вычисления второго слагаемого: 2-я степень, отрицательный коэффицент	
	double cos = 1;		//искомое значение косинуса
	double next_term = 1;	//следующее слагаемое в разложении косинуса
	int power = 2;		//степень слагаемого
	int sign = -1;		//знак слагаемого
	 
	do {	
		//явно вычисляются слагаемые ряда тейлора
		next_term = sign * fabs(next_term) * x * x / (power * (power - 1));
		cos += next_term;
		sign *= -1;  
		power += 2;	
	} while (fabs(next_term) > eps);
	
	return cos;
}	

		
	
