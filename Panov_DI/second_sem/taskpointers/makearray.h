#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {               // Коды ошибок
	OK,
	MALLOC_ERR,
	INCORRECT_ARGUMENT
} error;

double* makearray(RRFun* functions, int func_num, double x, error* err);

/*
** Функция заполняет массив полученных значений в точке x
** Функции подается массив указателей на функции (functions), количество функций (func_num), точка x, код ошибки (err).
** Функция создает массив и находит значения в точке икс, далее заполняет ими массив.
** Если все прошло без ошибок, функция вернет указатель на созданный массив
*/

