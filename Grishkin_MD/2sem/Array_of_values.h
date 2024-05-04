#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Множество функций из R в R. */
typedef double (*RRFun)(double);

typedef enum{   // ошибки
        OK,   /* Корректное выполнение */
        MEMORY,    /* Не удалось выдулить память */
        PARAM,     /* Некорректное значение входных параметров вызова */
}error;

double* arrayOfValues(RRFun* func, int len, double x, error* err);

// данная функция создает массив и заполняет его значениями функций в точке x.
// при успешном выполнении возвращает массив значений
