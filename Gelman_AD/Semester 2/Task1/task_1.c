#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Header.h"

/*	Parameters:
	f - real functiom (to the enter comes ONLY functions from R to R)
	x - argument
	ERROR - an error code for testing
	Function gets the y-es from the test function main_function and checks wether the tests were completed
*/

double main_function(RRFun f, double x, Error* ERROR)
{
	double y;
	y = (*f)(x);
	return y;
}