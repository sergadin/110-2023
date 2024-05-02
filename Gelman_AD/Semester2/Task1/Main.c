#include <stdlib.h>
#include <stdio.h>
#include "Header.h"

// New structure for testing
typedef struct testcase
{ 
	RRFun f; // Function
	double* x; // The element from the Domain of the Function
	int length; // The number of the elements in the Domain
} testcase;

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
	int length = 5;
	double x[] = { 1, 2, 3, 4, 5 };

	struct testcase tests_square[] =
	{
		{square, x, 5},
		{square, x, 5},
	};

	struct testcase tests_cube[] =
	{
		{cube, x, 5},
		{cube, x, 5},
	};

	struct testcase tests_sum[] =
	{
		{sum, x, 5},
		{sum, x, 5},
	};

	// Calculation & printing results of the function square(x) 

	for (int i = 0; i < 2; i++) 
	{
		main_function(tests_square[i].f, tests_square[i].x, tests_square[i].length);
		for (int j = 0; j < tests_square[i].length; j++)
		{
			printf("%lf \n", tests_square[i].x[j]);
		}
	}

	// Calculation & printing results of the function cube(x) 
	for (int i = 0; i < 2; i++)
	{
		main_function(tests_cube[i].f, tests_cube[i].x, tests_cube[i].length);
		for (int j = 0; j < tests_cube[i].length; j++)
		{
			printf("%lf \n", tests_cube[i].x[j]);
		}
	}

	// Calculation & printing results of the function sum(x) 
	for (int i = 0; i < 2; i++)
	{
		main_function(tests_sum[i].f, tests_sum[i].x, tests_sum[i].length);
		for (int j = 0; j < tests_sum[i].length; j++)
		{
			printf("%lf \n", tests_sum[i].x[j]);
		}
	}

	return 0;
}