#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minvalue.h"

typedef struct // New structure for testing
{
	RRFun f;                //   Function pointer
	double a;              //    Beginning of the segment
	double b;             //     Ending of the segment
	double result;       //      Expected result
	error error_code;   //       Expected error
} dataSet;

static double square(double x); /* Testing function: returns x to the power of 2*/
static double cube(double x);  /* Testing function: returns x to the power of 3*/
static double sum(double x);  /* Testing function: returns x plus 1*/

static double square(double x)
{
	return x * x;
}

static double cube(double x)
{
	return x * x * x;
}

static double sum(double x)
{
	return x + 1;
}

int main(void) 
{
	int test_number;
	error error_code;
	double value;
	const double epsilon = 1e-3;
	dataSet tests[] = 
	{                                   
		{square, 1, 5, 1, OK},		
		{cube, -1, 5, -1, OK},
		{sum, -10, 10, -11, OK}
	};

	test_number = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_number; i++) 
	{
		value = min_value(tests[i].f, tests[i].a, tests[i].b, epsilon, &error_code);
		if (error_code != tests[i].error_code) 
		{
			printf("The %d-th test is not completed\n", i + 1);
		}
		else if ((error_code == OK) && (fabs(tests[i].result - value) / 2 > epsilon)) 
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