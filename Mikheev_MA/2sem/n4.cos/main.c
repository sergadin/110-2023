#include "TaylorOfcos.h"
#define PI 3.14159265358



typedef struct{
    double x;
    double res;
    Er error;
}Testcase;




int main(void){
    Er error = OK;
    int length; 
    double result;
    double EPS = 0.0000001;
    
    Testcase test[] = {
        {0, 1, OK},
        {PI/3, 0.5, OK},
        {PI/6, sqrt(3)/2, OK},
        {-2*PI/3, -0.5, OK}
    };
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        
        result = TaylorOfcos(test[i].x, &error, EPS);
        
        if((fabs(result - test[i].res) < EPS) && (error == test[i].error)){
            printf("Тест №%d пройден\nЗначение cos(%lf) = %lf\n\n",i + 1, test[i].x, result);            
        }
        else{
            printf("Тест №%d не пройден\n", i + 1);
        }
        
        if(error == NOT_CORRECT){
                printf("Аргумент задан некорректно\n");
        }
        if(error == LIMIT){
            printf("Превышен лимит итераций\n");
        }
        
    }
    
    
    return 0;
}
