#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "func.h"

/**	Параметры: f - первая действительнозначная функция (на вход подаются ТОЛЬКО функции из R в R!)
 **		   g - вторая действительнозначная функция
 **		   х - аргумент
 **		   eps - погрешность
 **		   err - код ошибки, по которому будет проводиться проверка
 **	Функция получает значения из функции тестирования composing_with_requisition, проверяет правильность выполнения теста. */
	
double composing_with_requisition(RRFun f, RRFun g, double x, double eps, Error *err){
	double y, g_y, y_inter; /** соответственно: значение у, значение g(y), промежуточное значение у*/
	int limit = 10000; /** ограничение по количеству композиций функции f*/
	y = (*f)(x); 
	g_y = (*g)(y);
	
	while ((g_y < 0.) && (limit > 0)){
		y_inter = (*f)(y);
		g_y = (*g)(y_inter);
		y = y_inter;
		limit -= 1;
	}
	if(limit == 0){
		*err = NA_LIMIT;
	}else{
		*err = NA_OK;
	}
	return y;
}
 
