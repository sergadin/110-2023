#include "interpolationOfFunc.h"


typedef struct{
	point* points;           // массив точек
	int n;                   // количество точек
	point* interp_points;    // точки для проверок
	int m;                   // количество точек
	Er err_code;             // код ошибки
}Testcase;


void write_points(FILE* out1, FILE* out2, point* p, int n, point* i_p, int m, double* res);
void write_points(FILE* out1, FILE* out2, point* p, int n, point* i_p, int m, double* res){
	for (int i = 0; i < n; i++){
		fprintf(out1, "%lf\t%lf\n", p[i].x, p[i].y);
	}
	for (int i = 0; i < m; i++){
		fprintf(out2, "%lf\t%lf\n", i_p[i].x, res[i]);
	}
}


int main(void){
	double EPS = 0.01;
	int length;  //  количество тестов
	Er error;

	Testcase tests[] = {
		{ 
			(point[]) { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
			5,
			(point[]) { {0.5, 0.5}, {1.5, 1.5}, {2.8, 2.8}, {3.62, 3.62} },
			4,
			OK 
		},
		{	
			(point[]) { {0, 0}, {0.3, 0.295520}, {0.6, 0.564642}, {0.9, 0.783327}, {1.2, 0.932039}, {1.5, 0.997495}, 
			{1.8, 0.973848}, {2.1, 0.863209}, {2.4, 0.675463}, {2.7, 0.42738}, {3, 0.14112} },
			11,
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
		}
	};

	length = sizeof(tests) / sizeof(tests[0]);
	

	for (int i = 0; i < length; i++){                                           
		char filename1[32], filename2[32];
		FILE* out1;
		FILE* out2;
		double* res;
		
		sprintf(filename1, "out%d.txt", 2 * (i + 1) - 1);
		sprintf(filename2, "out%d.txt", 2 * (i + 1));
		out1 = fopen(filename1, "w");
		out2 = fopen(filename2, "w");
		
		res = (double*)malloc(sizeof(double) * tests[i].m);
		if (res == NULL) {
			printf("Ошибка памяти\n");
			return -1;
		}
		
		
		interpolate(tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, res, &error);
		
		
		if (error != tests[i].err_code){
			printf("Тест №%d не пройден\n", i + 1);
			fclose(out1);
			fclose(out2);
			free(res);
			return -1;
		}
		
		if (error == OK){
			for (int j = 0; j < tests[i].m; j++) {
				if (fabs(res[j] - tests[i].interp_points[j].y) > EPS) {
					printf("Тест №%d не пройден\n", i + 1);
					fclose(out1);
					fclose(out2);
					free(res);
					return -1;
				}
			}
			printf("Тест №%d успешно пройден\n", i + 1);
			write_points(out1, out2, tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, res);
		}
		
		
		fclose(out1);
		fclose(out2);
		free(res);
	}

	return 0;
}