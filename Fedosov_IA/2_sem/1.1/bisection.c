#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "bisection.h"

#define LIMIT 1000


//Функция определяет являются ли 2 числа одного знака
int are_same_signs (double left_border_val, double right_border_val) {
	if ((left_border_val > 0 && right_border_val > 0) || (left_border_val < 0 && right_border_val < 0)) 
		return 1;
	return 0;
}	

		
//Функция определяет является ли значение нулем с точностью eps
int is_zero(double value, double eps) {
	if (value < eps && value > -eps)
		return 1;
	return 0;
}



double bisection(Rfun f, double eps, double a, double b, Error *error) {
	double left_border_val = (*f)(a);	//Значение функции на левой границе
	double right_border_val = (*f)(b);	//Значение функции на правой границе
	double midpoint;			//Середина отрезка [a,b]
	double midpoint_value;			//Значение в середине отрезка [a,b]

	for(int i = 0; i < LIMIT; i++) {
		
		//Сразу проверяем являются ли границы отрезка корнями		
		if (is_zero(left_border_val, eps))
			return a;
		if (is_zero(right_border_val, eps))
			return b;	
		

		//Проверка на совпадение знаков границ
		if (are_same_signs(left_border_val, right_border_val)) {
			*error = SAME_SIGNS;
			return -1;
		}

		//Средняя точка отрезка и значение функции в ней
		midpoint = a + (b - a) / 2;
                midpoint_value = (*f)(midpoint);

		//Выбираем сделать среднюю точку левой или правой границей нового отрезка
		if (midpoint_value * right_border_val < 0){
			a = midpoint;
			left_border_val = midpoint_value;
		} else {
			b = midpoint;
			right_border_val = midpoint_value;
		}
	}

	*error = OP_LIMIT; //Превышен предел операций
			   
	return -1;
}





