#include "CalculateTheInt.h"

double funcGauss(RFun f, double a, double b);
double funcGauss(RFun f, double a, double b){ 
    double res;
    
    res = (b - a)/2 * (f( ((a + b)/2) - (b - a)/2/sqrt(3) )  +  f( (a + b)/2 + (b - a)/2/sqrt(3) ));
    
    return res;
}

double CalculateTheInt(RFun f, double a, double b, double EPS, int *count, Er *error){
    double x = a, y = b;
    double integral = 0;
    int max_count = 12;
    int cur_count = 0;
    double sum1 = 0;
    double sum2 = 0;
    
    for(int n = 2; (cur_count < max_count); n = n*2){  // деление отрезка, пока не достигнется нужная точность
        cur_count++;
        sum2 = sum1;
        sum1 = 0;
        x = a;
        
        for(int i = 1; i < n + 1; i++){        // Вычисление площадей на подотрезках 
            y = a + i*(b - a)/n;
            
            sum1 = sum1 + funcGauss(f, x ,y);
            
            x = y;
        }
        
        if(fabs(sum1 - sum2) < fabs(fmax(sum1, sum2))*EPS){ // Условие на остановку разбиений
            integral = sum1;
            break;
        }
        
        integral = sum1;
    }
    *error = OK;
    *count = cur_count;
    
    if(cur_count == max_count){
        *error == LIMIT;
    }
    
    if(isnan(integral) || isinf(integral)){
        *error = NOT_CORRECT;
    }
    
    //printf("Ошибка - %d\n", *error);
    //printf("Интеграл = %lf\n", integral);
    
    return integral;
}
