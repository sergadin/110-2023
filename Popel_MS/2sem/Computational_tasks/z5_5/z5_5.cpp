#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z5_5.h"
#include <time.h>

/*	Параметры:
 *		   x - первое значение
 *		   y - второе значение
 *		   eps - погрешность
 *	Функция ищет максимальное значение из трех введенных. 
 */
static double max(double x, double y, double eps);
/*	Параметры:
 *		   *arr - адрес массива
 *		   len - длина массива
 *	Функция составляет случайный массив х-ов. 
 */
static void rand_array(double *arr, int len); 
/*	Параметры:
 *		   *f_gn - адрес файла
 *		   *y - массив значений 
 *		   *y_th - массив значений случайных х-ов аппроксимируемой функции
 *		   *x - массив х-ов
 *		   len - длина массивов
 *	Функция, выполняющая запись координат.
 */
static void to_gnuplot(FILE *f_gn, double *y, double *y_th, double *x, int len); 

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

static void rand_array(double *arr, int len){
	double temp;
	int rand_coef = -1;
	srand(time(NULL));
	for (int i = 0; i < len; i++){
		rand_coef = pow(-1, rand() % 2);
		arr[i] = ((rand() % 10000) * 0.01) * rand_coef;
	}
	for (int j = 0; j < len - 1; j++){
		for(int k = j + 1; k < len; k++){
			if (arr[j] > arr[k]){
				temp = arr[j];
				arr[j] = arr[k];
				arr[k] = temp;
			}
		}
	}
}

static void to_gnuplot(FILE *f_gn, double *y, double *y_th, double *x, int len){
    for (int i = 0; i < len; i++){
        fprintf(f_gn, "%lf    %lf    %lf\n", x[i], y[i], y_th[i]);
    }
}
/*	Параметры:
 *		   *xs - массив х-ов
 *		   *ys - массив значений данной функции
 *		   len - длина массивов
 *	Функция класса, в которой вычисляются коэффициенты прямой линейного приближения функции по заданным значениям и точкам
 */

Approximation::Approximation(double *xs, double *ys, int len){
    double sum_x = 0., sum_xsq = 0., sum_y = 0., sum_xy = 0;
    for (int i = 0; i < len; i++){
        sum_x += xs[i];
        sum_xy += (xs[i] * ys[i]);
        sum_y += ys[i];
        sum_xsq += (xs[i] * xs[i]);
    }
    a_ = (len * sum_xy - sum_x * sum_y) / (len * sum_xsq - sum_x * sum_x);
    b_ = (sum_y - a_*sum_x)/len;

}

/*	Параметры: f - действительнозначная функция 
 *		   а - левая граница отрезка
 *		   b - правая граница отрезка
 *		   len - длина массива / количество х-ов
 *		   eps - погрешность
 *		   err - код ошибки, по которому будет проводиться проверка
 *		   file_name - имя файла
 *	Функция ищет максимальное отклонение функции, полученной линейным приближением, относительно исходной функции. 
 */
double Min_square(RRFun f, double a, double b, int len, double eps, Error *err, const char * file_name){
    double max_del = 0., cells = 0., del = 0.; /*максимальное отклонение, разница между х-ми, текущее отклонение*/
    double *xs = NULL; /*массив х-ов*/
    double *ys = NULL; /*массив значений данной функции*/
    double *randx = NULL; /*массив случайных х-ов*/
    double *y_th = NULL; /*массив значений случайных х-ов аппроксимируемой функции*/
    double *y = NULL; /*массив значений случайных х-ов данной функции*/
    FILE *f_gn; /*файл для построения графиков*/
	
    if((a > b) || (fabs(b - a) < max(a, b, 1.0) * eps)){
    	*err = NA_WRNG_ORD;
    	return -1;
    } 
    cells = (b - a) / len;
    xs = (double *)malloc(len*sizeof(double));
    if (xs == NULL){
		printf("Оперативная память не выделена\n");
		*err = MEMORY_ERR;
		return -1;
	}
    
    ys = (double *)malloc(len*sizeof(double));
    if (ys == NULL){
		printf("Оперативная память не выделена\n");
		free(xs);
		*err = MEMORY_ERR;
		return -1;
	}
	
    randx = (double *)malloc(len*sizeof(double));
    if (randx == NULL){
		printf("Оперативная память не выделена\n");
		free(xs);
		free(ys);
		*err = MEMORY_ERR;
		return -1;
	}
    
    y_th = (double *)malloc(len*sizeof(double));
    if (y_th == NULL){
		printf("Оперативная память не выделена\n");
		*err = MEMORY_ERR;
		free(xs);
		free(ys);
		free(randx);
		return -1;
	}
	
    y = (double *)malloc(len*sizeof(double));
    if (y == NULL){
		printf("Оперативная память не выделена\n");
		free(xs);
		free(ys);
		free(randx);
		free(y_th);
		*err = MEMORY_ERR;
		return -1;
	}
    for (int j = 0; j < len; j++){
        xs[j] = a + cells * j;
        ys[j] = (*f)(xs[j]);
        
    }
    
    Approximation g(xs, ys, len);
    rand_array(randx, len);
    for (int i = 0; i < len; i++){
        y[i] = (*f)(randx[i]);
        y_th[i] = g(randx[i]);
        del = (y[i]-y_th[i])*(y[i]-y_th[i]);
        max_del = max(0., del, max_del);
    }
    
    f_gn = fopen(file_name, "w");
	if (f_gn == NULL){
		printf("Файл не открывается\n");
		*err = FILE_NOT_OPEN;
		free(xs);
		free(ys);
		free(randx);
		free(y);
		free(y_th);
		return -1;
	}
	
    to_gnuplot(f_gn, y, y_th, randx, len);
    
    free(xs);
    free(ys);
    free(randx);
    free(y);
    free(y_th);
    fclose(f_gn);
    g.reset();
    
    return max_del;
}
