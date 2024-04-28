#include "./utils/utils.h"

    
double n_degree(double x, int n)
{
    double y = 1;   
    for(int i = 0; i < n; i++)
             y = y*x;
    return y;
}
//Функция n_degree получает на вход вещественное число x и натуральное число n.
//На выход функция подает значение x в степени n.

double LOG(double x, double epsilon)
{
  double calculated_value = 0;
  int n = 1;
  double n_member = x;
  while(fabs(n_member) >=  epsilon)
   {
    calculated_value += n_member;
    n++;
    if(n % 2 == 0)
    n_member = ((-1)*n_degree(x,n))/n;
    else
    n_member = n_degree(x,n)/n;
   }
    return calculated_value;
}
//Функция LOG получает на вход значение -1 < x <= 1 и заданную точность epsilon. 
//На выход функция подает приближенное значение величины ln(1+x), с точностью epsilon.