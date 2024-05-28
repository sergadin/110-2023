#include "MethZeyd.h"


typedef struct{  //структура теста
    const char* inp;
    double* res;
    Er error;
}Testcase;



int main(void){
    int m; // количество строк
    int n; // количество столбцов
    int length; // количество тестов
    Er error = OK;
    double **matr = NULL;
    double *solution = NULL;
    FILE* input;
    FILE* output;
    
    Testcase test[] = {
        {input1.txt, (double[]) {1, 1, 1}, OK}
    }
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int k = 0; k < length; i++){
        if(input = fopen(test[i].inp, "r") == NULL){
            printf("Ошибка открытия файла в тесте №%d", k + 1);
            return -1;
        }
        if(fscanf(input, "%d %d", &m, &n) != 2){
            printf("Ошибка чтения файла в тесте №%d", k + 1);
            fclose(input);
            return -1;
        }
        
        matr = (double*)malloc(m*n*sizeof(double));
        if(matr == NULL){
            printf("Ошибка выделения памяти в тесте №%d", k + 1);
            fclose(input);
            return -1;
        }
        
        solution = (double*)malloc(m*sizeof(double));
        if(solution == NULL){
            printf("Ошибка выделения памяти в тесте №%d", k + 1);
            free(matr);
            fclose(input);
            return -1;
        }
        
        
        for(int j = 0; j < n; j++){                                  // заполнение матрицы
            for(int i = 0; i < m; i++){
                if(fscanf(input("%lf", &matr[i][j])) != 1){
                    printf("Ошибка чтения файла в тесте №%d", k + 1);
                    fclose(input);
                    free(matr);
                    free(solution);
                    return -1;
                }
            }
        }
        
        
        MethZeyd(matr, &solution, error);
        
        
    }
    
    
    
    
    
    
    
    return 0;
}