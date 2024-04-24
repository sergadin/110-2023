
#include "./utils/utils.h"

struct testing 
{
   double (*Functions0)(double);
   double (*Functions1)(double);
   double (*Functions2)(double);
   double x;
   double result;
};//Структура тестов, которые проверяют нашу функцию композиции на 3 заданных функций из R в R

int main(void)
{
    double (*Functions[3])(double);
    double Calculated_value;
    struct testing test_number[4] =
    {
        {COS, MINES_FOUR, SQUARE,  2, 1},
        {SQUARE, SIN, MINES_FOUR, 5, 0.708073},
        {SIN, COS, SIN,  1, 0.618134},
        {COS, COS, COS, 10001, 0.567702}
    };

     for(int i = 0; i < 4; i++)
      {
        Functions[0] = test_number[i].Functions0;
        Functions[1] = test_number[i].Functions1;
        Functions[2] = test_number[i].Functions2;
        Calculated_value = Composition_of_function(test_number[i].x, 3, Functions);
                printf("Test %d\n Entered value x: %lf, Expected result: %lf \n", i+1, test_number[i].x, test_number[i].result);
                printf("Calculated value: %lf\n", Calculated_value);
      }

    return 0;
}