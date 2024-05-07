#include "interpolation.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {          // Структура тестов:
	point* points;
	size_t n;
	point* interp_points;
	size_t m;
	error err_code;
} dataSet;

int main(void) {
	system("chcp 1251");
	const double eps = 1e-4;
	int test_num, func_num = 3;
	error err;

	dataSet tests[] = {
		{ 
			(point[]) { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
			5,
			(point[]) { {0.5, 0.5}, {10, 10}, {5.5, 5.5}, {100, 100} },
			4,
			OK 
		},
		{	
			(point[]) { {0.3, 0.198669}, {0.6, 0.564642}, {0.9, 0.783327}, {1.2, 0.932039}, {1.5, 0.997495}, 
			{1.8, 0.973848}, {2.1, 0.863209}, {2.4, 0.675463}, {2.7, 0.42738}, {3, 0.14112} },
			10,
			(point[]) { {0.5, 0.479426}, {1, 0.84147}, {2, 0.909297} },
			3,
			OK 
		},
		{	
			(point[]) { {0.2, -1.60944}, {0.5, -0.693147}, {0.8, -0.223144}, {1, 0}, {1.2, 0.182322},
			{1.5, 0.405465}, {1.8, 0.587787}, {2, 0.693147}, {2.3, 0.832909}, {2.6, 0.955511} },
			10,
			(point[]) { {0.6, -0.510826}, {0.9, -0.105361}, {1.35, 0.300105} },
			3,
			OK 
		},
		{ 
			(point[]) { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
			5,
			(point[]) { {1, 2}, {2, 3}, {3, 4}, {4, 5} },
			4,
			OK 
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		double* res;
		res = (double*)malloc(sizeof(double) * tests[i].m);
		interpolate(tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, res, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < tests[i].m; j++) {
				if (fabs(res[j] - tests[i].interp_points[j].y) / 2 < eps) {
					printf("%d-й тест не пройден :(\n", i + 1);
					break;
				}
			}
			printf("%d-й тест пройден.\n", i+1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
		free(res);
	}


	return 0;
}
