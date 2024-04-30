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
int Inverse_matr(const char *filename, FILE *fout, int n, Error *err){
    double **matr = (double **)malloc(sizeof(double *) * n); //массив адресов на строки матрицы
    FILE *f = NULL;
    double dif, head_el;//частное от деления одной строки матрицы на другую, главный элемент строки.
    
    if (n == 0){
        *err = NA_ZERO_MATR;
        return -1;
    }
    if (matr == NULL){
		printf("Оперативная память не выделена\n");
		*err = NA_MEMORY_ERR;
		return -1;
	}
    f = fopen(filename, "r");
	if (f == NULL){
		printf("Файл не открывается\n");
		*err = FILE_WR;
		return -1;
	}
    for (int i = 0; i < n; i++){
        matr[i] = (double *)malloc(sizeof(double) * 2 * n);
        if (matr[i] == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            return -1;
	    }
        for (int j = 0; j < (2 * n); j++){
            if (j < n){
                if (fscanf(f, "%lf", &matr[i][j])!=1){
			        printf("В файле недостаточно значений\n");
            		*err = FILE_WR;
			        return -1;
		        }
            }else if(j == n + i){
                    matr[i][j] = 1;
            }else{
                matr[i][j] = 0;
            }
        }
    }
    fclose(f);

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
    
    for (int i = 0; i < n; i++){
        for (int j = n; j < (2*n); j++){
            fprintf(fout, "%lf\n", matr[i][j]);
        }
        free(matr[i]);
    }

    *err = NA_OK;
    free(matr);
    return 1;
 }
