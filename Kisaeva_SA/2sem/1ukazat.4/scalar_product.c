//Вычисление скалярного произведения двух векторов размерности n
#include <stdio.h>
#include <stdlib.h>
#include "scalar_product.h"

/* параметры: prom_znach 		   промежуточное значение при подсчитывании скалярного произведения векторов
*			  res_of_scal_prod     итоговоде значение, которому равно скалярное произведение векторов
*			  n 				   размерность векторного пространства
*			  vector1			   первый вектор, хранит свои координаты как массив
*			  vector2			   второй вектор, хранит свои координаты как массив
*
*  Функция подсчитывает скалярное произведение двух векторов целых чисел размерности n, 
*  используя вспомогательные функции сложения и умножения
*
*/

int scalar_product(int n, int *vector1, int *vector2, summ calc_summ, mult calc_mult) { // функция, считащая скалярное произведение vector1 и vector2 (размерности n)
	int prom_znach, res_of_scal_prod = 0;
	for (int i = 0; i < n; i++) {
		prom_znach = calc_mult(vector1[i], vector2[i]);
		if (i == 0) {
			res_of_scal_prod = prom_znach;
		}
		else {
			res_of_scal_prod = calc_summ(res_of_scal_prod, prom_znach);
		}
	}
	return res_of_scal_prod;
}