#include <math.h>

/* A set of functions from R to R */
typedef double (*RRFun)(double);

/* Main errors*/
typedef enum
{
	NA_OK, /* Finishing coding without any mistakes */
}Error;


/*  Calculating f(x0), ..., f(xn-1):
	Parameters:
	f - real functiom (to the enter comes ONLY functions from R to R)
	x - argument
	ERROR - an error code for testing
	Function gets the y-es from the test function main_function and checks wether the tests were completed
*/

double main_function(RRFun f, double x, Error* ERROR); 