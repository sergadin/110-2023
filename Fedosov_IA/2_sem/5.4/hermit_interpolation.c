#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hermit_interpolation.h"

//функция, проверяющая не выходят ли новые точки за границы старых
int check_borders (double* domain, int n, double* new_domain, int N) {
	if (new_domain[0] < domain[0] || new_domain[N - 1] > domain[n - 1]) {
		return 0;
	}
	return 1;
}


//функция, которая из массива точек находит отрезок, в котором содержится точка x
int find_segment(double x, double* domain, int n) {
	for (int i = 0; i < n; i ++) {
		if (x > domain[i] && x < domain[i + 1]) {
			return i;
		}
	}
	return -1;
}


//функция, находящая коэффиценты кубического многочлена и возвращающая значения многочлена на точке
double hermit_spline (double x, int index, double* domain, double* f_values, double* df_values) {
	double check;
	double x1 = domain[index];
	double x2 = domain[index + 1];
	double f1 = f_values[index];
	double f2 = f_values[index + 1];
	double df1 = df_values[index];
	double df2 = df_values[index + 1];

	double x0 = x - x1;
	double h = x2 - x1;
	double c2 = (3 * f2 - 3 * f1 - h * df2 - 2 * h * df1) / (h * h);
	double c3 = (2 * f1 - 2 * f2 + h * df2 + h * df1) / (h * h * h);

	return f1 + df1 * x0 + c2 * x0 * x0 + c3 * x0 * x0 * x0;
}


//вспомогательная функция, которая для заданной точки вычисляет приближенное значение
double get_value(double x, double* domain, double* f_values, double* df_values, int n) {
	double value;

	//сначала ищется нужный отрезок
	int segment_index = find_segment(x, domain, n);

	//далее на этом отрезке находится значение функции в точке
	value = hermit_spline(x, segment_index, domain, f_values, df_values);

	return value;
} 


//Основная функция
double* hermite_interpolation (double* domain, int n, double* f_values, double* df_values, double* new_domain, int N, Error *error) {
	double* new_f_values;

	if (n == 0) {
		*error = EMPTY;
		return 0;
	}

	if (N == 0) {
		*error = NO_ANSWER;
		return 0;
	}

	if (!(check_borders(domain, n, new_domain, N))){
		*error = BORDERS;
		return 0;
	}
	
	new_f_values = (double *)malloc(N * sizeof(double));

	for (int i = 0; i < N; i ++) {
		new_f_values[i] = get_value(new_domain[i], domain, f_values, df_values, n);
	}

	*error = OK;
	return new_f_values;
}




