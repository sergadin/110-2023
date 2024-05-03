#include "./utils/utils.h"

static double Simpson(double a, double b, double (*Function)(double))
{
 double result;
 result = (Function(a)+3*Function((2*a+b)/3)+3*Function((a+2*b)/3)+Function(b))*(b-a)/8;
 return result;
}
//Вспомогательная функция примерного вычисления интеграла по формуле Симпсона.

double integral(double a, double b, double (*Function)(double), double epsilon, ERROR *error)
{
    int n = 256;
    int iterations = 1;
    double dx = (b-a)/n;
    double sum_old = 0;
    double sum_now = 0;

    if(b <= a)
    {
        *error = ERROR_BORDERS;
        return -1;
    }

    for(int i = 0; i < n; i++)
    {
         sum_old += Simpson(a+i*dx , a+(i+1)*dx , Function);
    }

    n = n*2;
    dx = (b-a)/n;

    for(int i = 0; i < n; i++)
    {
        sum_now += Simpson(a+i*dx , a+(i+1)*dx , Function);
    }    

    while(fabs(sum_old - sum_now) > epsilon && iterations < LIMIT)
    {
        sum_old = sum_now;
        sum_now = 0;
        n = n*2;
        dx = (b-a)/n;

        for(int i = 0; i < n; i++)
        {
            sum_now += Simpson(a+i*dx , a+(i+1)*dx , Function);
        }

         iterations++;
    }


   if(iterations == LIMIT && fabs(sum_old - sum_now) > epsilon)
      *error = ERROR_LIMIT;

 return sum_now;
}
//Функция вычисляет определенный интеграл непрерывной функции Function на отрезке [a,b], с точностью epsilon.