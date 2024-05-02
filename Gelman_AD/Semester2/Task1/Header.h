#include <stdio.h>

/* A set of functions from R to R */
typedef double (*RRFun)(double x);

/*  Calculating f(x0), ..., f(xn-1):
	Parameters:
	f - real functiom (to the enter comes ONLY functions from R to R)
	x - argument
	Function main_function gets the x-es from the Main.c and the test function (example: square) from the Main.c 
*/

void main_function(RRFun f, double* x, int length); 