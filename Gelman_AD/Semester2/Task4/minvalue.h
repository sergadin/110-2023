#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum 
{           
	OK,
	ITERATION_LIMIT_EXCEEDED,
	WRONG_INTERVAL,
} error;

double min_value(RRFun f, double a, double b, double epsilon, error* error_code);

/* Function for finding the minimum of the given function with the shredding of the even net method
* The function input is a pointer to the function,
* the beginning and the end of the segment on which we need to find the minimum value,
* permissible error and error code.
* 
* In the cycle we look for three points according to the refinement step of the even net and find the vertex of the parabola.
* We compare the function values ​​at the vertex of the parabola and the minimum of three points, 
* and narrow the interval to find the minimum.
* We repeat this process until we achieve the specified accuracy.
* 
* If everything went without errors, the function will return the minimum value (comparable to the epsilon)
*/
