#include "MethZeyd.h"



void MethZeyd(double **matr, double **arr, Er *error, int n, int m, double EPS){
    double sum = 0; // сумма произведений коэф. матрицы умноженное на корень
    int count = 0; // счетчик, отвечающий за количество переменных, которые достигают нужной точности
    int max_count = 10000; // максимальное количество итераций
    double x = 0; // переменная для сравнения двух решений на соседних итерациях
    int l = 0;
    
    for(l = 0; l < max_count; l++){  // цикл, который считает количесетво корней, которые достигли нужной точности
        if(count == n){
            break;
        }
        count = 0;
        
        for(int i = 0; i < n; i++){  // цикл, который считает новую итерацию решения системы.
            sum = 0;
            for(int j = 0; j < m - 1; j++){  // цикл который считает сумму произведений коэф.матрицы на решение переменной
            
                if(j == i){
                    continue;
                }
            
                //if(j == m - 1){
                //    sum = sum + matr[i][j];
                //}
            
                sum = sum - (*arr)[j] * matr[i][j];
            
            }
            sum = sum + matr[i][m - 1];
            //printf("sum = %lf\n", sum);
            x = (*arr)[i];
            (*arr)[i] = sum / matr[i][i]; // новое решение
            
            if(fabs(x - (*arr)[i]) < EPS* fmax(1, fabs((*arr)[i]))){  //сравнение старого корня с новым
                count++;
            }
            //for(int i = 0; i < n; i++){
            //    printf("x%d = %lf\n", i + 1, arr[i]);
            //}
        }
    }
    
    *error = OK;
    
    if(l == max_count){
        *error = LIMIT;
    }
    
    for(int i = 0; i < n; i++){
        if(isnan((*arr)[i]) || isinf((*arr)[i])){
            *error = NOT_CORRECT;
        }
    }
    
}
