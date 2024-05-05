#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z2_3.h"

static double max(double x, double y, double eps);
static double max(double x, double y, double eps){
	double max_1;
	if (x > y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps > max_1){
		return eps;
	}
	return max_1;
}

/*	Параметры: **matr - указатель на матрицу указателей на массивы: в них записана матрица n*2n, где к исходной матрице справа 
 *                                                                                                   приписана единичная порядка n
 *          n - порядок матрицы
 *         *err - указатель на код ошибки.
 * Функция ищет обратную матрицу приведения новой матрицы методом Гаусса к ступенчатому виду 
 * левой половины (исходной матрицы). Полученная в правой части матрица - результат. 
 */
int Inverse_matr(double **matr, int n, Error *err, double eps){
    double dif, head_el;//частное от деления одной строки матрицы на другую, главный элемент строки.
    int ch_zero = 0; //счетчик нулевых элементов в последней строке для проверки матрицы на вырожденность.
    *err = NA_OK;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j != i){
                if (fabs(matr[i][i]) < eps){
                    continue;
                }
                dif = matr[j][i] / matr[i][i];
                for (int l = 0; l < (2 * n); l++){
                    matr[j][l] -= (dif * matr[i][l]);
                }
            }
        }
    }

    for (int j = 0; j < n; j++){
        if(fabs(matr[n-1][j])<eps){
            ch_zero ++;
        }
    }
    if (ch_zero == n){
        for (int i = 0; i < n; i++){
    	    free(matr[i]);
        }
        free(matr);
        *err = NA_SINGLE_MATR;
        return -1;
    }
    for (int i = 0; i < n; i++){
        if (fabs(matr[i][i]) < eps){
                    continue;
                }
        head_el = matr[i][i];
        for (int j = 0; j < (2 * n); j++){
            matr[i][j] /= head_el;
        }
    }
    return 0;
 }
