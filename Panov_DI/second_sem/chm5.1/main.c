#include "lagrangepolynom.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {          // Структура тестов:
	point* points;                // Массив определенных точек
	int n;                     // Количество этих точек
	point* i_points;              // Точные точки функции(x используется для поиска прибл. значения, y для проверки в тесте)
	int m;                     // Количество этих точек
	error err_code;               // Код ошибки
} dataSet;


void paintgraph(FILE* out1, FILE* out2, point* p, int n, point* i_p, int m, double* res, int number);
void paintgraph(FILE* out1, FILE* out2, point* p, int n, point* i_p, int m, double* res, int number) {
	for (int i = 0; i < n; i++)
		fprintf(out1, "%lf %lf\n", p[i].x, p[i].y);
	for (int i = 0; i < m; i++)
		fprintf(out2, "%lf %lf\n", i_p[i].x, res[i]);
}


int main(void) {
	const double eps = 0.1;
	int test_num, func_num = 3;
	error err;

	dataSet tests[] = {
		{ 
			(point[]) { {0, 0}, {2, 2}, {4, 4}, {6, 6}, {8, 8} },
			5,
			(point[]) { {0.7, 0.7}, {1.4, 1.4}, {2.9, 2.9}, {4.1, 4.1}, {6.34, 6.34} },
			5,
			OK 
		},
		{	
			(point[]) { {2.5, 8.25}, {3, 6}, {3.5, 4.25}, {4, 3}, {4.5, 2.25}, 
			{5, 2}, {5.5, 2.25}, {6, 3}, {6.5, 4.25}, {7, 6} },
			10,
			(point[]) { {2.74, 7.1076}, {4.68, 2.1024}, {6.12, 3.2544} },
			3,
			OK 
		},
		{	
			(point[]) { {0.1, 0.995004}, {0.4, 0.921060}, {0.7, 0.764842}, {1, 0.540302}, {1.2, 0.362357},
			{1.5, 0.070737}, {1.8, -0.227202} },
			7,
			(point[]) { {0.6, 0.825336}, {0.9, 0.62161}, {1.35, 0.219007} },
			3,
			OK 
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		char filename1[32], filename2[32];
		sprintf(filename1, "out%d.txt", 2 * (i + 1) - 1);
		sprintf(filename2, "out%d.txt", 2 * (i + 1));
		FILE* out1 = fopen(filename1, "w"), * out2 = fopen(filename2, "w");
		double* res;
		res = (double*)malloc(sizeof(double) * tests[i].m);
		if (res == NULL) {
			printf("Память не выделилась. ");
			return -1;
		}
		interpolate(tests[i].points, tests[i].n, tests[i].i_points, tests[i].m, res, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден. \n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < tests[i].m; j++) {
				if (fabs(res[j] - tests[i].i_points[j].y) > eps) {
					printf("%d-й тест не пройден. \n", i + 1);
					goto theend;
				}
			}
			printf("%d-й тест пройден.\n", i + 1);
			paintgraph(out1, out2, tests[i].points, tests[i].n, tests[i].i_points, tests[i].m, res, i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
			paintgraph(out1, out2, tests[i].points, tests[i].n, tests[i].i_points, tests[i].m, res, i + 1);
		}
	theend:
		fclose(out1);
		fclose(out2);
		free(res);
	}

	return 0;
}
