#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "rang2D.h"

int rang(int N, int M, double **matr, double eps, error *err) {
	int rang = 0; // значение ранга
	double leader = 1; // лидер строки
	double sled_leader = 1; // следующий найденный лидер, который соответствует столбцу с первым найденным лидером
	int j = 0; // переменная для перехода по строкам матрицы
	double d = 0; // используется для перестановки элементов
	*err = OK;
	for(int i = 0; i < M; i++) {
		j = rang;
		while (j < N) {
			if(fabs(matr[j][i]) < eps) {
				j++;
				continue;
			}
			leader = matr[j][i];
			// меняем строки местами, поднимаем первую строку с лидером
			for(int r = 0; r < M; r++) {
				d = matr[rang][r];
				matr[rang][r] = matr[j][r];
				matr[j][r] = d;
			}
			for(int k = j + 1; k < N; k++) { 
				sled_leader = matr[k][i]; // ищем след строку с главным элементом в этом столбце
				// вычитаем из строки со след лидером строку с первым наденным лидером, соответствующим данному столбцу
				if (fabs (sled_leader) > eps) { 
					for (int s = 0; s < M; s++) {
						matr[k][s] -= matr[rang][s] * (sled_leader / leader);
					}
				}
			}
			rang++;
			break;
		}
	}
	return rang;
}




