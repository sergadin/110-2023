#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "root.h"

/* 
Parameters:
x — pointer to the resulting root
a, b - borders of the segment
function — function pointer
epsilon — specified accuracy
*/

// Function for checking for the roots
int sign(double x)
{
	if (x > 0)
	{
		return 1;
	}
	else if (x < 0)
	{
		return -1;
	}
	return 0;
}

int root_chords(double* x, double a, double b, double (*function)(double), double epsilon)
{
	double fa, fb, fc, c[2];
	int i = 0, sgnfa, sgnfb, sgnfc, iterations_number; 

	c[0] = a; // Beginning of the segment
	c[1] = b; // Ending of the segment
	fa = function(a); 
	fb = function(b);

	// Checking the conditions for interations (the number of repeated actions)
	if (fabs(fa) < epsilon) 
	{ 
		*x = a; 
		return 1; 
	}

	if (fabs(fb) < epsilon) 
	{ 
		*x = b; 
		return 1; 
	}

	sgnfa = sign(fa); 
	sgnfb = sign(fb);

	if (sgnfa * sgnfb != -1)
	{
		return 0;
	}

	// Finding the root
	for (iterations_number = 1; fabs(c[1] - c[0]) > epsilon; iterations_number++)
	{
		// Sequential saving of intermediate point
		i = !i;
		c[i] = (a * fb - b * fa) / (fb - fa);

		fc = function(c[i]); 
		sgnfc = sign(fc);

		// If the function value is small
		if (fabs(fc) < epsilon) 
		{ 
			*x = c[i]; 
			return iterations_number + 1;
		}

		// Choosing the subsegment [a,c] or [c,b]
		if (sgnfc * sgnfa == 1) 
		{ 
			a = c[i]; 
			fa = fc; 
		}
		else // (sgnfb * sgnfc == 1)
		{ 
			b = c[i]; 
			fb = fc; 
		}
	}

	*x = c[i]; // the last value of C is returned
	return iterations_number; // the number of iterations is returned
}
