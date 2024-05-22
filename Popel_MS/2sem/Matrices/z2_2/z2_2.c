#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z2_2.h"

/*	Параметры: *matr - адрес на массив (исходное линейное представление матрицы)
 *             *nmatr - адрес на массив (новое линейное представление матрицы - ее минора)
 *             n - размерность исходной матрицы 
 *             m - столбец, по которому строится минор
 *      Функция переписывает в новый массив минор исходной матрицы порядка n-1.
 */
static void new_matr(double * matr, double *nmatr, int n, int m);



 static void new_matr(double * matr, double *nmatr, int n, int m){
    int j = 0;
    for (int i = n; i < n*n; i++){
        if ((i % n) != m){
            nmatr[j] = matr[i];
            j++;
        }
        else {
            continue;
        }
    }
 }


 /*	Параметры: *matr - указатель на массив, содержащий элементы матрицы
 *          n - порядок передаваемой матрицы
 *          eps - погрешность.
 *         *err - указатель на код ошибки.
 * Функция ищет определитель переданной матрицы, рекурсивно сводя ее к поиску определителя матрицы 2х2.
 */
double determinate(double *matr, int n, double eps, Error *err){
    double det = 0; //значение определителя
    double *nmatr = NULL; //новая подматрица (минор) порядка n-1 
    int sgn = 1; //знак минора
    *err = NA_OK;
    if (n == 0){
        *err = NA_ZERO_MATR;
        return -1;
    }

    if (n == 1){
        return matr[0];
    }

    if (n == 2){
        return ((matr[0] * matr[3]) - (matr[1] * matr[2]));
    }
	nmatr = (double *)malloc(((n - 1) * (n - 1)) * sizeof(double));
    for (int i = 0; i < n; i++){
        
        if (nmatr == NULL){
		printf("Оперативная память не выделена\n");
		*err = NA_MEMORY_ERR;
		return -1;
	}

    	new_matr(matr, nmatr, n, i);
        det  += sgn * matr[i] * determinate(nmatr, n-1, eps, err);
        sgn *= -1;
        
    }
	free(nmatr);
    return det;
}
