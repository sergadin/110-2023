#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polygon.h"

// New structure for testing
typedef struct 
{
	RRFun f;          // The main function
	double a;         // Beginning of the segment
	double b;         // Ending of the segment
	double result;    // Expected result
	Error error_code; // Expected error
} TestCase;

static double max(double x, double y, double epsilon);
static double max(double x, double y, double epsilon)
{
	double max_1;
	if (x > y)
	{
		max_1 = x;
	}
	else
	{
		max_1 = y;
	}
	if (epsilon > max_1)
	{
		return epsilon;
	}
	return max_1;
}

static double square(double x); /* Testing function: returns x to the power of 2*/
static double cube(double x); /* Testing function: returns x to the power of 3*/
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
	double result, epsilon = 1e-5;
	Error error_code;

	TestCase tests[] = 
	{ 
		{square, 1, 3, 8.666667, OK},
		{cube, 5, 162, 172186708.489589, OK},
		{sum, -4, -0.5, -4.375000, OK},
	};

	int number_tasks = sizeof(tests) / sizeof(tests[0]); // The number of the tests
	for (int n = 0; n < number_tasks; n++) 
	{
		result = Integrate(tests[n].f, tests[n].a, tests[n].b, epsilon, &error_code);

		if (error_code != tests[n].error_code)
		{
			printf("Test ¹%d is not completed.\n", n + 1); // WRONG_ORDER
		}
		else if ((error_code == OK) && ((fabs(result - tests[n].result)) >= (max(result, tests[n].result, 1.0) * epsilon)))
		{
			printf("Test ¹%d is not completed. The integral value: %lf\n", n + 1, result); // The integrade is greater then itself * epsilon
		}
		else if ((error_code == OK) && ((fabs(result - tests[n].result)) < (max(result, tests[n].result, 1.0) * epsilon))) 
		{
			printf("Test ¹%d is completed. The integral value: %lf\n", n + 1, result); // The integrade is less then itself * epsilon
		}
		else if (error_code == ITERATION_LIMIT_EXCEEDED)
		{
			printf("Test ¹%d is completed. The approximate integral value: %lf\n", n + 1, result); // The integrade is approximate
		}
		else 
		{
			printf("Test ¹%d is completed.\n", n + 1); // Everything is OK
		}
	}
	return 0;
}