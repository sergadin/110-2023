#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*R_Rfun)(double);
typedef int (*RR_Zfun)(double, double);

void find_the_null(R_Rfun f, RR_Zfun g, double x, int limit);
