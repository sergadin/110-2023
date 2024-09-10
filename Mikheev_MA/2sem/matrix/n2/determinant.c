#include "determinant.h"

void swap(int *a, int *b); // свап значений
int sgn(int *arr, int n);  // знак перестановки
int determ(int *arr, int n, int *matr);  // произведение элементов по данной перестановке


int sgn(int *arr, int n){            // функция считает количество инверсий
    int count = 0;                   // если их четно, то возвращает 1, иначе -1
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(arr[i] < arr[j]){
                count++;
            }
        }
    }
    
    if(count % 2 == 0){
        return 1;
    }
    else{
        return -1;
    }
    
}


int determ(int *arr, int n, int *matr){     // произведение элементов по данное перестановке
    double result = 1;
    
    for(int i = 0; i < n; i++){
        
        result = result * matr[i*n + arr[i]];
        //printf("элемент = %d\t", mas[i*n + arr[i]]);
        
    }
    
    return result;
}


void swap(int *a, int *b){
int x = *a;
*a = *b;
*b = x;
}


void determinant(int *arr, int start, int n, int *matr, int *result){
    
    if (start == n - 1){
        
        //for (int i = 0; i < n; i++){    **тут моожно вывести перестановку, по которой считается значение**
        //    printf("%d ", arr[i]);
        //}
        //printf("\n");
        
        *result = *result + determ(arr, n, matr) * sgn(arr, n);
        //printf("result = %d\n", *result);
        }
        
    else{
        for (int i = start; i < n; i++){
            swap(&arr[start], &arr[i]);
            determinant(arr, start + 1, n, matr, result);
            swap(&arr[start], &arr[i]); 
        }
    }
    
}

