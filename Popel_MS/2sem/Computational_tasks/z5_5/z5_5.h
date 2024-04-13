#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Множество функций из R в R*/
typedef double (*RRFun)(double);

/* Основные ошибки*/
typedef enum {
	NA_OK, /* нет ошибок */
    NA_WRNG_ORD, /* неправильный порядок ввода значений границ отрезка*/
    NA_LIMIT,
    NA_ZERO_DET,
    FILE_NOT_OPEN, /* превышен лимит обращения к функции */
}Error;


/* Подсчет значений композиции функции.
 *	
 *	Параметры: f - действительнозначная функция 
 *		   a - левая граница отрезка (должна быть меньше правой)
 *		   b - правая граница отрезка (должна быть больше левой)
 *		   eps - погрешность
 *		   *err - указатель на код ошибки
 *  Функция находит минимальное значение на отрезке методом золотого сечения. Если на вход подается функция-константа, 
 *  считается, что минимального значения нет. Если функция монотонна, минимальное значение принимается на одной из границ отрезка.
 *  Вывод:
 *  Если функция выполнена без ошибок, выводится код ошибки NA_OK и найденное значение функции.
 *  Если границы отрезка введены не в правильном порядке (левая граница болше правой) - выводится код ошибки NA_WRNG_ORD.
 *  Если превышен лимит обращений к функции (100000), выводится код ошибки NA_LIMIT.
 */

double Min_square(RRFun f, double a, double b, int len, double eps, Error *err);

class Approximation{
    private:
        double a_, b_;
    public:
        Approximation(double *xs, double *ys, int len, double eps, Error *err);
        void reset(){a_ = b_ = 0.;}
        Approximation(){a_=0., b_ = 0.;}
        double operator()(double x) const{
            return a_ * x + b_;
        }
        void get(){
        	printf("Значения a_ - %lf и b_ - %lf\n", a_, b_);
        }
        ~Approximation(){}

};
