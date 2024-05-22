
#include "./utils/utils.h"

static double MINES_FIVE(double x);
static double SQUARE(double x);
static double COS(double x);

static double MINES_FIVE(double x)
{
  return x-5;
}

static double SQUARE(double x)
{
  return x*x;
}

static double COS(double x)
{
  return cos(x);
}

struct testing 
{
   double (*Functions)(double);
   double a;
   double b;
   double result;
   double epsilon;
   ERROR error;
};

int main(void)
{
    double (*Function)(double);
    double calculated_integral;
    double a;
    double b;
    double result;
    double epsilon;
    ERROR error;
    struct testing test_number[4] =
    {
        {MINES_FIVE,  5, 10, 12.500000, 0.000001, OK},
        {COS, 3, 5, -1.100044, 0.000001, OK},
        {SQUARE, 1, 6,  71.666667, 0.000001, OK},
        {MINES_FIVE, 3, 2, 0, 0.001, ERROR_BORDERS}
    };

     for(int i = 0; i < 4; i++)
      {
        Function = test_number[i].Functions;
        a = test_number[i].a;
        b = test_number[i].b;
        result = test_number[i].result;
        epsilon = test_number[i].epsilon;
        error = OK;
        calculated_integral = integral(a, b, Function, epsilon, &error);
               printf("Test %d\nIntegration segment: [%lf, %lf] Expected result: %lf\n", i+1, a, b, result);
                if(error == OK)
               printf("Computed integral: %lf\n", calculated_integral);
                if(error == ERROR_BORDERS)
               printf("Borders enterned incorrectly\n");
                if(error == ERROR_LIMIT)
               printf("The required accuracy has not been achieved. Computed integral: %lf\n", calculated_integral);
      }

    return 0;
}