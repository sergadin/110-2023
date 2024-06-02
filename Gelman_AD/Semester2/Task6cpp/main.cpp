#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "interpolation.h"

// New structure for testing
typedef struct
{
	std::vector<double> x;       // The arguments of the function
	std::vector<double> y;      // The values of the function
	std::vector<double> x1;    // The given mesh for approximate function
	error error_code;         // Error code
} dataSet;


void make_picture(FILE* out1, FILE* out2, std::vector<double> x, std::vector<double> y, std::vector<double> x1, std::vector<double> res, int number);
void make_picture(FILE* out1, FILE* out2, std::vector<double> x, std::vector<double> y, std::vector<double> x1, std::vector<double> res, int number)
{
	for (int i = 0; i < 5; i++)
	{
		fprintf(out1, "%lf %lf\n", x[i], y[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		fprintf(out2, "%lf %lf\n", x1[i], res[i]);
	}
}

int main(void)
{
	const double epsilon = 0.1;
	int test_number;
	error err;

	dataSet tests[] =
	{
		{
			{1, 2, 3, 4, 5},
			{1, 4, 9, 16, 25},
			{1.5, 2.5, 3.5, 4.5},
			OK
		},
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++)
	{
		char file_name1[32], file_name2[32];
		sprintf(file_name1, "out%d.txt", 2 * (i + 1) - 1);
		sprintf(file_name2, "out%d.txt", 2 * (i + 1));
		FILE* out1 = fopen(file_name1, "w"), * out2 = fopen(file_name2, "w");

		std::vector<double> result = interpolate(tests[i].x, tests[i].y, tests[i].x1, &err);

		if (err != tests[i].error_code)
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else
		{
			printf("The %d-th test is completed\n", i + 1);
			make_picture(out1, out2, tests[i].x, tests[i].y, tests[i].x1, result, i + 1);
		}
	theend:
		fclose(out1);
		fclose(out2);
	}
	return 0;
}