#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef double (*RRFun)(double);

typedef enum {
	OK,		//Ошибок нет
	OGRAN,          //Ошибка ограничения на х
	NO_EPS,         //Ошибка ограничения на eps
	NO_LIMIT        //Превышение лимита итераций

} Error;

/*	Параметры: 
 *         eps - погрешность.
 *         *err - указатель на код ошибки.
 * Подсчитывает значение функции в точке х по разложению ряда Тейлора. 
 * Полученный результат сравнивается с значением log(x).
 */


double taylor_log(double x, double eps, Error *err);
