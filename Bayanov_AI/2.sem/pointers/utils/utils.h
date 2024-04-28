#include <stdio.h>
#include <math.h>

typedef double (*Fun)(double);
double Composition_of_function(double x, int n, Fun *Functions);