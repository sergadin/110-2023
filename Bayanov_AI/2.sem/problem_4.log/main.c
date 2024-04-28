
#include "./utils/utils.h"

struct testing 
{
   double x;
   double result;
   double epsilon;
};

int main(void)
{
    double calculated_value;
    double x;
    double result;
    double epsilon;
    struct testing test_number[4] =
    {
        {0, 0, 0.00001},
        {0.5, 0.405465, 0.000001},
        {0.4, 0.336472, 0.000001},
        {0.9, 0.641853, 0.000001}
    };

     for(int i = 0; i < 4; i++)
      {
        x = test_number[i].x;
        result = test_number[i].result;
        epsilon = test_number[i].epsilon;
        calculated_value = LOG(x, epsilon);
              printf("Test %d\nEntered point x: %lf; Expected Result: %lf\n", i+1, test_number[i].x, test_number[i].result);
              printf("Computed ln(1+x): %lf\n", calculated_value);
      }

    return 0;
}