#include <stdlib.h>
#include <stdio.h>
#include "value.h"

/*	Parameters:
	f - real functiom (to the enter comes ONLY functions from R to R)
	x - argument
	Function main_function gets the x-es from the Main.c and the test function (example: square) from the Main.c 
*/

void main_function(RRFun f, double* x, int length)
{
	for (int i = 0; i < length; i++)
	{
		x[i] = f(x[i]);
	}
}