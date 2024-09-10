#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct info
{
	int condition;
	double expected;
	double real;
};

double function(double x)
{
	return asin(x);
}


struct info* test(double f(double), int argc, double* args, double* vals, double eps)
{
	struct info* result = malloc(sizeof(struct info)*argc);
	for (int i = 0; i < argc; i++)
	{
		if (fabs((f)(args[i]) - vals[i]) < eps)
		{
			result[i].condition = 1;
			result[i].expected = vals[i];
			result[i].real = f(args[i]);
			
		}
		else
		{
			result[i].condition = 0;
			result[i].expected = vals[i];
			result[i].real = f(args[i]);	
		}
	}
	return result;
}	 
 

