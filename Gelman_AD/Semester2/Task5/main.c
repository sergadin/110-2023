#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

// New structure for testing
typedef struct 
{
	double x;         // A point
	double epsilon;   // Epsilon
	double result;    // Expected result
	error error_code; // Expected error
} dataSet;

int main(void) 
{
	int test_number;
	error err;
	double value;
	dataSet tests[] = 
	{
		{0.5, 0.000001, 0.405465, OK},
		{0.4, 0.000001, 0.336472, OK},
		{0.9, 0.000001, 0.641853, OK}
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++) 
	{
		value = calculatelog(tests[i].x, tests[i].epsilon, &err);

		if (err != tests[i].error_code) 
		{
			printf("The %d-th test is not completed aaa, error code %lf \n", i + 1, tests[i].error_code);
		}
		else if ((err == OK) && (fabs(tests[i].result - value) / 2 > tests[i].epsilon)) 
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else 
		{
			printf("The %d-th test is completed\n", i + 1);
		}

		printf("Taylor result: %lf\n", value);
	}

	return 0;
}