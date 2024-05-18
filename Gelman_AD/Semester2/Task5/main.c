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
		{10, 1e-4,  0.693097, OK},
		{1, 0.0001, 0.405532, OK},
		{2, 0.0001, -0.693147, OK},
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++) 
	{
		value = calculatelog(tests[i].x, tests[i].epsilon, &err);

		if (err != tests[i].error_code) 
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].result - value) / 2 > tests[i].epsilon)) 
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else 
		{
			printf("The %d-th test is completed\n", i + 1);
		}
	}

	return 0;
}