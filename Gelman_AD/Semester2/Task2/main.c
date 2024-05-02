#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "root.h"

typedef struct // New structure for testing
{         
	RRFun function;         //   Function pointer
	double a;              //    Beginning of the segment
	double b;             //     Ending of the segment
	double result;       //      Expected result
	int number_fcalls;  //        Number of function calls
	error error_code;  //       Expected error
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
}int main()
{
	double x; 
	int number_fcalls = 0;
	double result; 

	result = root_chords(&x, -10, 45, square, 1.e-15);
	if (result)
	{
		printf("x=%lg\n number of interations =%d\n", x, result - 1);
		printf("number of function calls =%d\n", number_fcalls);
	}
	else
	{
		printf("method is not applicable\n");
	}
	return 0;
}