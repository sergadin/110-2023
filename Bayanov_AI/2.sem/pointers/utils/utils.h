#include <stdio.h>
#include <math.h>


double Composition_of_function(double x, int n, double (*Functions[n])(double));

static double COS(double x);

static double SIN(double x);

static double MINES_FOUR(double x);

static double SQUARE(double x);

static double COS(double x)
{
    return cos(x);
}

static double SIN(double x)
{
    return sin(x);
}

static double MINES_FOUR(double x)
{
    return x-4;
}

static double SQUARE(double x)
{
    return x*x;
}
