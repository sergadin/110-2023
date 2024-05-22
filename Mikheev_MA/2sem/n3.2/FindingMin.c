#include "FindingMin.h"


double FindingMin(RFun f, double a, double b, double EPS, Er *error){
    double constant;  // константа золотого сечения
    double min_f;  // минимальное значение
    double x1, x2;  // точки из алгоритма золотого сечения
    double f_x1, f_x2; // значение f(x1) и f(x2), чтобы не вызывать функцию дополнительно
    int max_count;   // максимальное количество итераций
    int i;
    max_count = 10000; 
    constant = (3 - sqrt(5)) / 2;
    
    x1 = a + (b - a) * constant;  // определение левой точки
    x2 = b - (b - a) * constant;  // определение правой точки
    f_x1 = f(x1);
    f_x2 = f(x2);
    
    for(i = 0; i < max_count && fabs(f_x1 - f_x2) > fabs(fmax(x2 - x1, 1)) * EPS; i++){
        
        if(f_x1 > f_x2){                  // если значение в левой точке больше
            a = x1;                       // сдвигаем левую границу
            x1 = x2;                      // правая точка становится левой
            f_x1 = f_x2;                  // также меняем значение
            x2 = b - (b - a) * constant;  // считаем новую правую точку
            f_x2 = f(x2);                 // считаем значение в новой правой точке
            min_f = f_x2;                 // если цикл закончится, то значение в этой точке и будет минимальным
        }
        else{
            b = x2;
            x2 = x1;
            f_x2 = f_x1;
            x1 = a + (b - a) * constant;
            f_x1 = f(x1);
            min_f = f_x1;
        }
        
    }
    
    *error = OK;
    
    if(i == max_count){
        *error = LIMIT;
    }
    if(isnan(min_f) || isinf(min_f)){
        *error = NOT_CORRECT;
    }
    
    return min_f;
}
