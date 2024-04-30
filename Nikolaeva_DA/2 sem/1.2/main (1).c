#include <stdio.h>
#include <math.h>
#include "test2.h"
typedef struct testing
{
   double (*Func1)(double);
   double (*Func2)(double);
   double (*Func3)(double);
   double x;
   double y;
} testing;

static double constant(double x);
static double COS(double x);
static double SIN(double x);
static double square(double x);

static double constant(double x){
    return x;
}
static double COS(double x)
{
    return cos(x);
}

static double SIN(double x)
{
    return sin(x);
}

static double square(double x)
{
    return x*x;
}

int main(void)
{
    double (*Func[3])(double) = {NULL};
    double result;
    testing test_number[4] =
    {
        {COS, constant, square,  2, 0.173178},
        {square, SIN, constant, 5, -0.132352},
        {SIN, COS, SIN,  1, 0.618134},
        {COS, COS, COS, 10001, 0.567702}
    };

    for(int i = 0; i < 4; i++)
    {
        Func[0] = test_number[i].Func1;
        Func[1] = test_number[i].Func2;
        Func[2] = test_number[i].Func3;
        result = composing_function(test_number[i].x, 3, Func);
        printf("Test %d\n Value x: %lf, Expected y: %lf \n", i+1, test_number[i].x, test_number[i].y);
        printf("result: %lf\n\n", result);
    }

    return 0;
}


