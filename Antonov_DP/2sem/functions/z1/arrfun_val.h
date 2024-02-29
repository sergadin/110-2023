#include <stdio.h>

typedef double (*RRFun)(double x);

void arrfun_val (RRFun f, double *arr, int len);
