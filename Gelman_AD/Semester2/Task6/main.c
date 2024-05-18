#include <stdio.h>
#include <stdlib.h>
#include "interpolation.h"

// New structure for testing
typedef struct 
{
	point* points;              // An array of particular points
	size_t n;                   // The number of these points
	point* interp_points;       // Exact points of the function (x is used for approximate value, y is used for checking in the tests)
	size_t m;                   // The number of these points
	error error_code;           // Error code
} dataSet;


void make_picture(FILE* out1, FILE* out2, point* p, size_t n, point* i_p, size_t m, double* res, int number);
void make_picture(FILE* out1, FILE* out2, point* p, size_t n, point* i_p, size_t m, double* res, int number) 
{
	for (int i = 0; i < n; i++)
	{
		fprintf(out1, "%lf %lf\n", p[i].x, p[i].y);
	}

	for (int i = 0; i < m; i++)
	{
		fprintf(out2, "%lf %lf\n", i_p[i].x, res[i]);
	}
}

int main(void) 
{
	const double epsilon = 0.1;
	int test_number, function_number = 3;
	error err;

	dataSet tests[] = 
	{
		{ 
			(point[]) { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
			5,
			(point[]) { {0.5, 0.5}, {1.5, 1.5}, {2.8, 2.8}, {3.62, 3.62} },
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
		}
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++) 
	{
		char file_name1[32], file_name2[32];
		sprintf(file_name1, "out%d.txt", 2 * (i + 1) - 1);
		sprintf(file_name2, "out%d.txt", 2 * (i + 1));
		FILE* out1 = fopen(file_name1, "w"), * out2 = fopen(file_name2, "w");
		double* result;
		result = (double*)malloc(sizeof(double) * tests[i].m);

		if (result == NULL) 
		{
			printf("No memory");
			return -1;
		}

		interpolate(tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, result, &err);

		if (err != tests[i].error_code) 
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else if (err == OK) 
		{
			for (int j = 0; j < tests[i].m; j++) 
			{
				if (fabs(result[j] - tests[i].interp_points[j].y) > epsilon) 
				{
					printf("The %d-th test is not completed\n", i + 1);
					goto theend;
				}
			}
			printf("The %d-th test is completed\n", i + 1);
			make_picture(out1, out2, tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, result, i + 1);
		}
		else 
		{
			printf("The %d-th test is completed\n", i + 1);
			make_picture(out1, out2, tests[i].points, tests[i].n, tests[i].interp_points, tests[i].m, result, i + 1);
		}
	theend:
		fclose(out1);
		fclose(out2);
		free(result);
	}
	return 0;
}