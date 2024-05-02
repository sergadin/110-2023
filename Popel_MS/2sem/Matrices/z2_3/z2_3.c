#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z2_3.h"


/*	Параметры: *filename - имя файла, содержащего элементы матрицы
 *         *fout - файл, в который выгружается итоговая матрица
 *          n - порядок матрицы
 *         *err - указатель на код ошибки.
 * Функция ищет обратную матрицу методом приписывания справа единичной матрицы и приведения новой матрицы методом Гаусса к ступенчатому виду 
 * левой половины (исходной матрицы). Полученная в правой части матрица - результат. 
 */
void Inverse_matr(double **matr, int n, Error *err){
    double dif, head_el;//частное от деления одной строки матрицы на другую, главный элемент строки.
    
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

    for (int i = 0; i < n; i++){
        head_el = matr[i][i];
        for (int j = 0; j < (2 * n); j++){
            matr[i][j] /= head_el;
        }
    }

    *err = NA_OK;
 }
