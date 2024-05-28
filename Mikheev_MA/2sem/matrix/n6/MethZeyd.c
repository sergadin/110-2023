#include "MethZeyd.h"

double max()


void MethZeyd(double **matr, double *solution, Er *error, int m, int n){
    double sum = 0; // сумма произведений коэф. матрицы на решение переменной
    double x = 0;  // переменная для сравнения двух решений на соседних итерациях
    int max_count = 1000;  // максимальное количество итераций
    int count = 0;  // счетчик, отвечающий за количество переменных, которые достигают нужной точности
    //*error = NOT_OK;
    
    for(int i = 0; i < m && *error != NOT_OK;; i++){   // цикл, который считает количесетво корней, которые достигли нужной точности
        *solution[i] = 0;
    }
    
    
    for(int j = 0; j < max_count && count != m; j++){  // цикл, который считает количесетво корней, которые достигли нужной точности
        count = 0;
        
        for(int i = 0; i < m; i++){  // цикл, который считает новую итераци решений системы.
            sum = 0;
            
            for(int l = 0; l < n; l++){ // цикл который считает сумму произведений коэф.матрицы на решение переменной
                
                if(l == i){ // мы не берем коэфф i-ой переменной
                    continue;
                }
                if(l == n - 1){ // столбец свободных переменных прибавляется со знаком +
                    sum = sum + matr[i][l];
                }
                else{
                sum = sum - matr[i][l] * (*solution[l]);  
                }
            
                //x = *solution[i];
                //*solution[i] = 1/matr[i][i] * sum;
                
                //if(fabs(x - *solution[i]) < EPS){
                //    count++;
                //}
                
            }
    
            x = *solution[i];
            *solution[i] = 1/matr[i][i] * sum;  // новое решение
    
            if(fabs(x - *solution[i]) < EPS){   // сравнение решений соседних итераций с нужной точностью
                *error = NOT_OK;
            }
    
        }
    }
    
    
    
}

