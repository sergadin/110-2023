#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Множество функций из R в R. */
typedef double (*RRFun)(double);

typedef enum {   // ошибки
    OK,   /* Корректное выполнение */
    MEM_ER,    /* Не удалось выдулить память */
}Error;

double* arr_of_val(RRFun* func, int len, double x, Error* err);

/* Вывод массива значиний функций, в точке х
*  Параметры:
*               func - массив указателей на функции
*               len - длина этого массива
*               x - точка, в которой считается значение
*               err - код ошибки
*/