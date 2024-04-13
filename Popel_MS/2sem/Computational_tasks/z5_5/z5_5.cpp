#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z5_5.h"
#include <time.h>
#define rand_max 23567 
/*	Параметры:
 *		   x - первое значение
 *		   y - второе значение
 *		   eps - погрешность
 *	Функция ищет максимальное значение из трех введенных. 
 */
static double max(double x, double y, double eps);
static double determinate_2(double a11, double a12, double a21, double a22);
static void rand_array(double *arr, int len);
static void to_gnuplot(FILE *f_gn, FILE *gnulpt, double *y, double *y_th, double *x, int len);
static double max(double x, double y, double eps){
	double max_1;
	if (x > y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps>max_1){
		return eps;
	}
	return max_1;
}

static double determinate_2(double a11, double a12, double a21, double a22){
    return (a11*a22 - a12*a21);
}

static void rand_array(double *arr, int len){
	srand(time(NULL));
	
	for (int i = 0; i < len; i++){
		arr[i] = (rand()/rand_max)/10000;
	}
}
static void to_gnuplot(FILE *f_gn, FILE *gnuplt, double *y, double *y_th, double *x, int len){
    for (int i=0; i<len; i++){
        fprintf(f_gn, "%lf    %lf    %lf\n", x[i], y[i], y_th[i]);
    }
    fprintf(gnuplt, "#! /usr/bin/gnuplot -persist\n");
    fprintf(gnuplt, "plot \"output.txt\" u 1:2 w l lc rgb \"blue\", \"output.txt\" u 1:3 w l lc rgb \"green\"");
}

/*	Параметры: f - действительнозначная функция 
 *		   а - левая граница отрезка
 *		   b - правая граница отрезка
 *		   eps - погрешность
 *		   err - код ошибки, по которому будет проводиться проверка
 *	Функция ищет минимальное значение функции на обозначенном отрезке методом золотого сечения. 
 */
Approximation::Approximation(double *xs, double *ys, int len, double eps, Error *err){
    double sum_x = 0., sum_xsq = 0., sum_y = 0., sum_xy = 0;
    double det0, det_a, det_b;
    for (int i=0; i<len; i++){
        sum_x+=xs[i];
        sum_xy += (xs[i]*ys[i]);
        //printf("xs - %lf, ys - %lf, xs*ys - %lf, sum - %lf\n", xs[i], ys[i], xs[i]*ys[i], sum_xy);
        sum_y += ys[i];
        sum_xsq += xs[i]*xs[i];
    }
    //printf("sum_xsq - %lf, sum_x - %lf, sum_xy - %lf, len - %d\n", sum_xsq, sum_x, sum_xy, len);
    det0 = determinate_2(sum_xsq, sum_x, sum_x, len);
    det_a = determinate_2(sum_xy, sum_x, sum_y, len);
    det_b = determinate_2(sum_xsq, sum_xy, sum_x, sum_y);
    printf("det_a - %lf, det_b - %lf, det0 - %lf\n", det_a, det_b, det0);
    a_ = det_a/det0;
    b_ = det_b/det0;
    printf("%lf - %lf\n", a_, b_);

}

double Min_square(RRFun f, double a, double b, int len, double eps, Error *err){
    double max_del = 0., cells = (b-a)/len, del = 0.; 
    double *xs = (double *)malloc(len*sizeof(double));
    double *ys = (double *)malloc(len*sizeof(double));
    double *randx = (double *)malloc(len*sizeof(double));
    double *y_th = (double *)malloc(len*sizeof(double));
    double *y = (double *)malloc(len*sizeof(double));
    FILE *f_gn, *gnuplt;
    int flag = 1;
    for (int j = 0; j<len; j++){
        xs[j] = a + cells*j;
        ys[j] = (*f)(xs[j]);
        
    }
    Approximation g(xs, ys, len, eps, err);
    rand_array(randx, len);
    for (int i = 0; i<len; i++){
        y[i] = (*f)(randx[i]);
        y_th[i] = g(randx[i]);
        /*if (i<10){
        g.get();
        }*/
        if (flag!=0){
        	printf("y = %lf, x = %lf, y_old = %lf\n", y_th[i], randx[i], y[i]);
        	flag-=1;
        }
        del = (y[i]-y_th[i])*(y[i]-y_th[i]);
        max_del = max(0., del, max_del);
    }
    f_gn = fopen("output.txt", "w");
	if (f_gn == NULL){
		printf("Файл не открывается\n");
        *err = FILE_NOT_OPEN;
		return -1;
	}
    gnuplt = fopen("gnuplot.gpi", "w");
	if (gnuplt == NULL){
		printf("Файл не открывается\n");
		fclose(f_gn);
        *err = FILE_NOT_OPEN;
		return -1;
	}
    to_gnuplot(f_gn, gnuplt, y, y_th, randx, len);
    free(xs);
    free(ys);
    free(randx);
    free(y);
    free(y_th);
    fclose(f_gn);
    fclose(gnuplt);
    g.reset();
    return max_del;
}
