#include "FindingMin.h"


double func1(double x);  // функции для теста
double func2(double x);
double func3(double x);


double func1(double x){
    return x*x;
}


double func2(double x){
   return pow(x, 4) - 3*pow(x, 3);
}


double func3(double x){
    return 5*pow(x, 3) + 4*pow(x, 2) - 1;
}

typedef struct{  // Структура теста
    RFun f;      // Функция
    double a;    // Левая граница отрезка
    double b;    // Правая граница отрезка
    double res;  // Ожидаемый результат 
    Er error;    // Код ошибки
}Testcase;


int main(void){
    Er error;
    int length;   // количество тестов
    double result;   // результат работы функции
    double EPS;   // заданная точность
    
    error = OK;
    EPS = 0.00000001;
    
    Testcase test[] = {
        {func1, 2, 1700, 4, OK},
        {func2, -10, 30, func2(2.25), OK},
        {func3, -0.5, 1000, -1, OK}
    };
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        
        result = FindingMin(test[i].f, test[i].a, test[i].b, EPS, &error);
        
        if((fabs(result - test[i].res) / 2 < EPS) && (error == test[i].error)){
            printf("Тест №%d пройден\nМинимальное значение функции = %lf\n\n",i + 1, result);            
        }
        else{
            printf("Тест №%d не пройден\n\n", i + 1);
        }
        
        if(error == NOT_CORRECT){
                printf("Функция задана некорректно\n\n");
        }
        if(error == LIMIT){
            printf("Превышен лимит итераций\n\n");
        }
    }
    
    return 0;
}
