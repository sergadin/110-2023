﻿#include <stdio.h>
#include <math.h>

typedef enum {           // Коды ошибок:
	OK,                  //  Все хорошо
	LIMIT_0,    //  Превышен лимит итераций
	W_ARG       //  Аргумент не принадлежит требуемому отрезку
} Error;

double taylor_sin(double x, double eps, Error* err);

/*
* Функция вычисления синуса в заданной точке, с помощью суммирования ряда Тейлора.
*
* На вход функции подается точка, значение в которой нужно вычислить, допустимая
* погрешность и адрес переменной отвечающей за код ошибки,
* пользуясь разложением синуса в ряд тейлора
*
* Значение точки должно принадлежать промежутку [-2pi, 2pi].
*
* Если все прошло без ошибок функция вернет значение синуса в заданной точке.
*/