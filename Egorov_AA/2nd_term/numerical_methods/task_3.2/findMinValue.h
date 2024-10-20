﻿#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {           // Коды ошибок:
	OK,                   //  Все хорошо
	I_LIMIT_EXCEEDED,     //  Превышен лимит итераций
	WRONG_INTERVAL,       //  Неправильно задан интервал
} error;

double findMinValue(RRFun f, double a, double b, double eps, error* err);

/* Функция поиска минимума функции методом золотого сечения
**
** На вход функции подается указатель на функцию, начало и конец отрезка, на котором
** нужно найти минимальное значение, допустимая погрешность и код ошибки.
** Функция сравнивает значения заданной функции на точках, выбранных методом золотого
** сечения. Выбирает отрезок от точки с минимальным значением, до конца отрезка,
** оставшийся кусок выбрасывает. Причем отношение длины нового отрезка к старому равно
** 0.618. Данное отношение сохраняется, что и дало название этому методу.
** Эту процедуру функция выполняет, пока значение функции в двух точках не будет
** сравнимо с погрешностью.
**
** Если все прошло без ошибок, функция вернет значение(сравнимое с погрешностью)
** заданной функции в точке минимума.
*/
