#include "./utils/utils.h"

    
int sign(double x, double epsilon)
{
            if(fabs(x) < epsilon)
                return 0;

            if(x > 0)
                return 1;
            else
                return -1;
}
//Функция sign получает на вход вещесвенное число x и epsilon.
//На выход функция подает значение 0, если x примерно равен 0, и +-1 в зависимости от знака x.

int root_half(double *x, double a, double b, double (*Function)(double), double epsilon)
{
    int i = 0;
    double c;
    int sign_fa;
    int sign_fb;
    int sign_fc;
    
     while(fabs(b-a) >= epsilon*fabs(a+b)/2 && fabs(b-a) >= epsilon && i < LIMIT)
 {
    c = (a+b)/2;
    sign_fa = sign(Function(a), epsilon);
    sign_fb = sign(Function(b), epsilon);
    sign_fc = sign(Function(c), epsilon);

    if(sign_fa == 0)
            {
                 *x = a;
                return i;
            }
    
    if(sign_fb == 0)
            {
                *x = b;
                return i;
            }
    
    if(sign_fa == sign_fb)
            {
                return -1;
            }

    i ++;
    *x = c;
    
    if(sign_fc == 0)
            {
                return i;
            }
    
    if(sign_fa == sign_fc)
                a = c;
            else
                b = c;
 }

 return LIMIT;
}
//Функция root_half получает на вход указатель *x на вещестевенное число, которое в процеесе успешного выполнения функции root_half
//станет равной корню непрерывной функции Function на отрезке [a,b], с заданной точностью epsilon.
//Функция root_half имеет ограничение на выполнение итераций = 1000000 (LIMIT), а также не может быть реализована при совпадание
//знаков функции в точках a и b, в силу специфики метода реализации.
//На выход функция root_half подает количество итераций, в случаи успешной работы; LIMIT, в случае превышения количества итераций;
//-1 в случае, если метод не реализуем.