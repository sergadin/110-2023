#include <math.h>
#include "Heading.h"
#include <stdio.h>

// New structure for testing
typedef struct 
{ 
	RRFun f; // Function
	double x; // The element from the Domain of the Function
	double result; // The expected result
	Error ERROR; // The address of the error
} TestCase;

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
	int n = 5;
	double x[] = { 1, 2, 3, 4, 5 };
	double result;
	Error ERROR;

	// Calculation & printing results of the function square(x) 
	for (int i = 0; i < n; i++) 
	{
		printf("square(%lf) = %lf\n", x[i], square(x[i]));
	}

	printf("\n");

	// Calculation & printing results of the function cube(x) 
	for (int i = 0; i < n; i++) 
	{
		printf("cube(%lf) = %lf\n", x[i], cube(x[i]));
	}

	// Calculation & printing results of the function sum(x) 
	for (int i = 0; i < n; i++)
	{
		printf("sum(%lf) = %lf\n", x[i], sum(x[i]));
	}

	return 0;
}