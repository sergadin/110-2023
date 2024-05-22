
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
   double x;
   double a;
   double b;
   double epsilon;
};//Структура тестов, которые проверяют нашу функцию поиска корня на заданных непрерывных функций из R в R

int main(void)
{
    double (*Function)(double);
    int iterations;
    double x;
    double a;
    double b;
    double epsilon;
    struct testing test_number[4] =
    {
        {MINES_FIVE,  5, 1, 43, 0.0001},
        {COS, 1.570796, 0, 2, 0.000001},
        {SQUARE, 0, -2,  2, 0.0001},
        {MINES_FIVE, 5, 0, 23, 0.000001}
    };

     for(int i = 0; i < 4; i++)
      {
        Function = test_number[i].Functions;
        a = test_number[i].a;
        b = test_number[i].b;
        epsilon = test_number[i].epsilon;
        iterations = root_half(&x, a, b, Function, epsilon);
                printf("Test %d\nEntered root x: %lf\n", i+1, test_number[i].x);
              if(iterations == LIMIT)
                printf("Computed root: %lf Iteration limit exceeded\n", x);
              if(iterations == -1)
                printf("Computed root: The method is not implementable\n");
              if(iterations != -1 && iterations != LIMIT)
                printf("Computed root: %lf Number of iterations: %d\n", x, iterations);
      }

    return 0;
}