#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z2_3.h"


/*	Параметры: **matr - указатель на матрицу указателей на массивы: в них записана матрица n*2n, где к исходной матрице справа 
 *                                                                                                   приписана единичная порядка n
 *          n - порядок матрицы
 *         *err - указатель на код ошибки.
 * Функция ищет обратную матрицу приведения новой матрицы методом Гаусса к ступенчатому виду 
 * левой половины (исходной матрицы). Полученная в правой части матрица - результат. 
 */
void Inverse_matr(double **matr, int n, Error *err){
    double dif, head_el;//частное от деления одной строки матрицы на другую, главный элемент строки.
    int ch_zero = 0; //счетчик нулевых элементов в последней строке для проверки матрицы на вырожденность.
    *err = NA_OK;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j != i){
                dif = matr[j][i] / matr[i][i];
                for (int l = 0; l < (2 * n); l++){
                    matr[j][l] -= (dif * matr[i][l]);
                }
            }
        }
    }

    for (int j = 0; j < n; j++){
        if(matr[n-1][j] == 0){
            ch_zero ++;
        }
    }
    if (ch_zero == n){
        *err = NA_SINGLE_MATR;
    }
    for (int i = 0; i < n; i++){
        head_el = matr[i][i];
        for (int j = 0; j < (2 * n); j++){
            matr[i][j] /= head_el;
        }
    }
 }
