
#include "./utils/utils.h"

static double POLYNOMIAL(double x);
static double LOG(double x);
static double COS(double x);

static double POLYNOMIAL(double x)
{
  return x*x*x-5*x*x+3*x+3;
}

static double LOG(double x)
{
  return log(x);
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
    double calculated_minimum;
    double a;
    double b;
    double result;
    double epsilon;
    ERROR error;
    struct testing test_number[4] =
    {
        {POLYNOMIAL,  0, 5, -6, 0.000001, OK},
        {COS, 0, 0.9, 0.621609, 0.000001, OK},
        {LOG, 2, 6,  0.693147, 0.000001, OK},
        {POLYNOMIAL, 3, 2, 0, 0.001, ERROR_BORDERS}
    };

     for(int i = 0; i < 4; i++)
      {
        Function = test_number[i].Functions;
        a = test_number[i].a;
        b = test_number[i].b;
        result = test_number[i].result;
        epsilon = test_number[i].epsilon;
        error = test_number[i].error;
        calculated_minimum = minimum(a, b, Function, epsilon, &error);
               printf("Test %d\nSegment: [%lf, %lf] Expected result: %lf\n", i+1, a, b, result);
                if(error == OK)
               printf("Computed minimum: %lf\n", calculated_minimum);
                if(error == ERROR_BORDERS)
               printf("Borders enterned incorrectly\n");
                if(error == ERROR_LIMIT)
                printf("The required accuracy has not been achieved. Computed minimum: %lf\n", calculated_minimum);
      }

    return 0;
}