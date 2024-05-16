#include "FindingTheRoot.h"
#define PI 3.14159265358


double func1(double x); // задание функции для теста 1
double deriv1(double x); // задание производной функции для теста 1
double func2(double x);
double deriv2(double x);
double func3(double x);
double deriv3(double x);
//double func4(double x);
//double deriv4(double x);


typedef struct{  // Структура теста
    RFun f;      // Функция
    RFun g;      // Производная данной функции
    double a;    // Левая граница отрезка 
    double b;    // Правая граница орезка
    double res;  // Ожидаемый результат
    Er error;    // Адрес ошибки
} Testcase;


double func1(double x){
    return x*x;
}
double deriv1(double x){
    return 2*x;
}


double func2(double x){
    return x*x - 3*x;
}
double deriv2(double x){
    return 2*x - 3;
}


double func3(double x){
    return sin(x);
}
double deriv3(double x){
    return cos(x);
}


//double func4(double x){
//    return atan(x);
//}
//double deriv4(double x){
//    return 1/(1 + x*x);
//}


int main(void){
    int count = 0; // количество итераций
    Er error = OK;
    int length; // количество тестов
    double result;
    double EPS = 0.00001; // заданная точность
    
    Testcase test[] = {
        {func1, deriv1, -2, 5, 0, OK},
        {func2, deriv2, 0.1, 10, 3, OK},
        {func3, deriv3, PI/6, 1.3*PI, PI, OK}
    };
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        count = 0;
        
        result = FindingTheRoot(test[i].f, test[i].g, test[i].a, test[i].b, EPS, &count, &error);
        
        if(fabs(result - test[i].res) < EPS && error == OK){
            printf("Тест №%d пройден\n", i + 1);
        }
        else{
            printf("Тест №%d не пройден \n",i + 1);
        }
        
        if(error == NOT_CORRECT){
                printf("Функция задана некорректно\n");
        }
        if(error == HAVE_NO_ROOT){
                printf("На заданном отрезке нет корня\n");
        }
        if(error != LIMIT){
            printf("Количество итераций - %d\n\n", count);
        }
        else{
            printf("Превышено количество итераций\n\n");
        }
        
    }
    
    return 0;
}
