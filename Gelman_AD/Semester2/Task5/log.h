#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum 
{
	OK,
	ITERATION_LIMIT_EXCEEDED,
	INVALID_ARGUMENT
} error;

double calculatelog(double x, double epsilon, error* error_code);

/* Function for calculationg the logarithm of a given x with Taylor's series
* 
* The function input is the given x, a permissible error and an error code
* With the Taylor's series log(1 + x) = x - x^2/2! + x^3/3! - ...
* We will calculate the value of logarithm at point x, calculating and summing each term in turn
* Until one of them is comparable to the epsilon.
* 
* If everything went without errors, the function will return the logarithm's value at the given point.
*/
