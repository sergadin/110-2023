#include "CalculateTheInt.h"
#define PI 3.14159265358

double func1(double x); // задание функции для тестов
double func2(double x);
double func3(double x);

double func1(double x){
    return 3*x*x;
}

double func2(double x){
    return 4;
}

double func3(double x){
    return sin(x);
}


typedef struct{  // структура теста
    RFun f;      // функция
    double a;    // левая граница отрезка
    double b;    // правая граница отрезка
    double res;  // ожидаемый результат работы
    Er error;    // код ошибки
} Testcase;


int main(void){
    int count = 0; // количество итераций
    Er error = OK;
    int length; // количество тестов
    double result; // результат работы функции
    double EPS = 0.0001; // точность вычислений
    
    Testcase test[] = {
        {func1, 0, 2, 8, OK},
        {func2, -2, 3, 20, OK},
        {func3, PI, 3*PI, 0, OK},
        {func3, PI, 3*PI/2, -1, OK}
    };
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        count = 0;
        
        result = CalculateTheInt(test[i].f, test[i].a, test[i].b, EPS, &count, &error);
        
        if((fabs(result - test[i].res) < EPS) && (error == test[i].error)){
            printf("Тест №%d пройден\nИнтеграл = %lf\nКоличество итераций деления - %d\n\n",i + 1, result, count);            
        }
        else{
            printf("Тест №%d не пройден\n", i + 1);
        }
        
        if(error == NOT_CORRECT){
                printf("Функция задана некорректно\n");
        }
        if(error == LIMIT){
            printf("Превышен лимит итераций - %d\n\n", count);
        }
        
    }
    
    //printf("Интеграл = %lf", result);
    return 0;
}
