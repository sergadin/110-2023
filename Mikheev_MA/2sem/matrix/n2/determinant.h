#include <stdio.h>
#include <stdlib.h>


/* Функция вычисляет определитель матрицы размером N на N (коэф. матрицы целочисленные)
**
** Функция вычисляет определитель по определению (через перестановки). На входе подается
** массив перестановок, начальную позицию (тк функция работает рекурсивно), размер матрицы, 
** матрицу(в виде одномерного массива), адрес итогового результата (тк функция работает рекурсивно
** все промежуточные значение приходится записывать в переменную, которая объявлена в мейне)
**
** Функция считает все перестановки, на каждой из них она считает промежуточные значения,
** те произведение элементов по данной перестановке и суммирует с предыдущими.
*/
void determinant(int *arr, int start, int n, int *matr, int *result); 