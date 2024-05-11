#include "./utils/utils.h"


double minimum(double a, double b, double (*Function)(double), double epsilon, ERROR *error)
{
    int n = 2;
    double min;
    double x_min;
    double dx = 0;
    double ai = 0;
    double f_ai = 0;

    if(b <= a)
    {
        *error = ERROR_BORDERS;
        return -1;
    }

    if(Function(a) > Function(b))
    {
        min = Function(b);
        x_min = b;
    }
    else
    {
        min = Function(a);
        x_min = a;  
    }

    while(fabs(b-a) > epsilon && n < LIMIT)
    {
        dx = (b-a)/n;
        for(int i = 0; i <= n; i++)
        {
            ai = a+i*dx;
            f_ai = Function(ai);
                if(f_ai < min)
                {
                    min = f_ai;
                    x_min = ai;
                }
        }

        if(fabs(x_min - a) < epsilon)
        {
            a = a;
            b = a + dx;
        }

        if(fabs(x_min - b) < epsilon)
        {
            a = b - dx;
            b = b;
        }

        if(fabs(x_min - a) >= epsilon && fabs(x_min - b) >= epsilon)
        {
             a = x_min - dx;
             b = x_min + dx;  
        }

        n++;
    }

   if(n == LIMIT && fabs(b - a) > epsilon)
    *error = ERROR_LIMIT;

 return min;
}
//Функция исчет минимум непрерывной функции Function на отрезке [a,b], с точностью epsilon.