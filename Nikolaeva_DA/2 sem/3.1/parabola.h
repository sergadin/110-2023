#include<stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {
	NO_INTER,
	NO_LIMIT,
	OK 		//Ошибок нет
} Error;


/*
 *  *	Параметры: f - действительнозначная функция
 *		   a - левая граница отрезка (должна быть меньше правой)
 *		   b - правая граница отрезка (должна быть больше левой)
 *		   eps - погрешность
 *		   *err - указатель на код ошибки 
  Задаём 2 новые точки x1 и x2. Задаём их так, чтоб они были на одинаковом расстояни от середины. Вычисляем значение функций и находим минимальное значение.
  */
double min_parabolic( RRFun f, double a, double b, double eps, Error *err);
