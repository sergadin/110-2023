#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z2_3.h"

/*	Параметры: х - первое сравниваемое действительное значение
 *             у - второе сравниваемое действительное значение
 *             eps - погрешность - третье сравниваемое значение 
 *      Функция ищет максимальное значение.
 */

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

/*	Параметры: х - действительное значение - точка, в которой необходимо найти х - должна лежать в интервале (0,2), иначе sqrt не сходится.
 *         eps - погрешность.
 *         *err - указатель на код ошибки.
 * Подсчитывает значение функции в точке х по разложению ряда Тейлора. Полученный результат сравнивается с значением sqrt(x).
 */
int Inverse_matr(const char *filename, FILE *fout, int n, double eps, Error *err){
    double **matr = (double **)malloc(sizeof(double *)*n), res;
    FILE *f = NULL;
    double dif, head_el;
    if (n==0){
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
    for (int i = 0; i<n;i++){
        matr[i] = (double *)malloc(sizeof(double)*2*n);
        if (matr[i] == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            return -1;
	    }
        for (int j = 0; j < 2*n; j++){
            if (j<n){
                if (fscanf(f, "%lf", &matr[i][j])!=1){
			        printf("В файле недостаточно значений\n");
            		*err = FILE_WR;
			        return -1;
		        }
            }else if(j==n+i){
                    matr[i][j] = 1;
            }else{
                matr[i][j] = 0;
            }
        }
    }
    fclose(f);
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            if (j!=i){
                dif = matr[j][i]/matr[i][i];
                for (int l = 0; l<2*n;l++){
                    matr[j][l] -= dif*matr[i][l];
                }
            }
        }
    }
    for (int i=0;i<n;i++){
        head_el = matr[i][i];
        for (int j = 0; j<2*n; j++){
            matr[i][j]/=head_el;
        }
    }
    
    for (int i = 0; i<n; i++){
        for (int j = n; j <2*n; j++){
            fprintf(fout, "%lf\n", matr[i][j]);
        }
        free(matr[i]);
    }
    *err = NA_OK;
    free(matr);
    return 1;
 }
