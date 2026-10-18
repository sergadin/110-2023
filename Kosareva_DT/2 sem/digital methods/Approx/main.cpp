#include "appr_3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

typedef struct {
	R_Rfun f;
	std::vector<double> x1;
	std::vector<double> x2;
} test;
	
static double SIN(double x) {
	return sin(x);
}

static double PARABOLA(double x) {
	return (3*x*x - 2*x + 6);
}

int main(void) {
	FILE *F=NULL;
	int i;
	size_t j, n, m;
	test entry[3] = {
		{SIN, {1.4, 1.45, 1.55, 4, 5, 5.6, 6}, {1.5, 4, 5.5, 9}},
		
		{SIN, {1, 2.5, 4, 5.5, 7, 0.1}, {0, 3, 5, 8}},
		
		{PARABOLA, {1, 3, 4, 6, 7, 8}, {3.5, 6.5, 9}}
	};
	double eps = 0.0000001;
	
	char file[32];
	std::vector<double> y1;
	std::vector<double> y2;
	
	for (i=0; i<3; i++) {
		printf("%d : ", i+1);
		n = (entry[i].x1).size();
		m = (entry[i].x2).size();
		y1.resize(n);
		y2.resize(m);
		
		if (n < 3) {
			printf("Недостаточно точек для квадратичной интерполяции\n");
			continue;
		}
		
		std::sort((entry[i].x1).begin(), (entry[i].x1).end());
		for (j=0; (j+1)<n; j++) {
			if (fabs(entry[i].x1[j] - entry[i].x1[j+1]) < 0.000001) {
				printf("Точки не различны\n");
				continue;
			}
		}
		
		sprintf(file, "function%d.txt", i+1);
		F = fopen(file, "w");
		if (F == NULL) {
			printf("Файл функции не открылся\n");
			continue;
		}
		for (double x=-20; x<20; x+=0.01) {
			fprintf(F, "%lf %lf\n", x, (*(entry[i].f))(x));
		}
		fclose(F);
		
		
		sprintf(file, "given%d.txt", i+1);
		F = fopen(file, "w");
		if (F == NULL) {
			printf("Файл данных точек не открылся\n");
			continue;
		}
		
		Y(entry[i].f, entry[i].x1, y1);
		for (j=0; j<n; j++) {
			fprintf(F, "%lf %lf\n", (entry[i].x1)[j], y1[j]);
		}
		fclose(F);
		
		Y(entry[i].f, entry[i].x2, y2);
		
		sprintf(file, "output%d.txt", i+1);
		F = fopen(file, "w");
		if (F == NULL) {
			printf("Файл интерполяции не открылся\n");
			continue;
		}
		printf("Тест успешно пройден\n");
		
		interp(entry[i].x1, y1, entry[i].x2, y2);
		for (j=0; j<m; j++) {
			fprintf(F, "%lf %lf\n", (entry[i].x2)[j], y2[j]);
		}
		fclose(F);
	}
	
	return 0;
}
