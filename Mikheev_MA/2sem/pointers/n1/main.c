#include "mas_of_arg.h"
#define EPS 0.0001
#define PI 3.14159265358



double func(double x);                // Функция для задания функции

typedef struct{        // Структура для проведения теста
    RRFun f;           // Функция R -> R заданная по условию
    double mas_arg;    // Аргумент из последовательности (последовательность задана массивом)
    double res;        // Ожидаемое значение данной функции в точке
    Er error;          // Адрес ошибки
} Testcase;

double func(double x){    // Тут можно задавать функцию
    return sin(x);
}

int main(void){
    Er error;
    error = OK;
    int length = 4;
    
    double mas_arg[] = {0, PI/2, PI/6, PI/4};  // Последовательность аргументов
    
    Testcase tests[] = {
        {func, mas_arg[0], 0, OK},
        {func, mas_arg[1], 1, OK},
        {func, mas_arg[2], 0.5, OK},
        {func, mas_arg[3], 0.707106781, OK}
    };
    
    mas_of_arg(tests[0].f, mas_arg, &error, length);
    
    for(int i = 0; i < length; i++){
        if(fabs(tests[i].res - mas_arg[i]) > EPS){
            error = NOT_OK;
        }
        if(tests[i].error == error){
            printf("Тест пройден №%d\n",i + 1);
        }
        else{
            printf("Тест не пройден №%d\n",i + 1);
        }
        error = OK;
    }
    
//    for(int i = 0; i < length; i++){
//        mas_of_arg(tests[i].f, tests[i].mas_arg, mas_arg, &error, i);
//        if(fabs(tests[i].res - mas_arg[i]) > EPS){
//            error = NOT_OK;
//        }
//        if(tests[i].error == error){
//            printf("Тест пройден №%d\n",i + 1);
//        }
//        else{
//            printf("Тест не пройден №%d\n",i + 1);
//        }
//        error = OK;
        //printf("  %lf\n", mas_arg[i]);
//    }
    
    return 0;
}
