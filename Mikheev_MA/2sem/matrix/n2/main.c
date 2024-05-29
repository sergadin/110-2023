#include "determinant.h"


typedef struct{  //структура теста
    const char* inp;
    int res;
}Testcase;


int main(void){
    FILE* input;
    int n; // размер матрицы
    int length; // количество тестов
    int *matr = NULL; // массив для матрицы
    int *arr = NULL; // массив для перестановок
    int result = 0;
    
    
    Testcase test[] = {
        {"input1.txt", 1},
        {"input2.txt", 0}, 
        {"input3.txt", 54},
        {"input4.txt", 54}
        
    };
    
    length = sizeof(test) / sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        result = 0;
        if((input = fopen(test[i].inp, "r")) == NULL){
            printf("Ошибка открытия файла в тесте №%d", i + 1);
            return -1;
        }
        if(fscanf(input, "%d", &n) != 1){
            printf("Ошибка чтения файла в тесте №%d", i + 1);
            fclose(input);
            return -1;
        }

        matr = (int*)malloc(n*n * sizeof(int));
        if(matr == NULL){
            printf("Ошибка выделения памяти в тесте №%d", i + 1);
            fclose(input);
            return -1;
        }
        
        
        arr = (int*)malloc(n * sizeof(int));
        if(arr == NULL){
            printf("Ошибка выделения памяти в тесте №%d", i + 1);
            fclose(input);
            free(matr);
            return -1;
        }
        
        for(int j = 0; j < n*n; j++){
            if((fscanf(input, "%d", &matr[j])) != 1){
                printf("Ошибка чтения файла в тесте №%d", i + 1);
                fclose(input);
                free(matr);
                return -1;
            }
        }
        
        for(int j = 0; j < n; j++){ // заполнение массива перестановок
            arr[j] = j;
        }
        
        
        determinant(arr, 0, n, matr, &result); // вычисление определителя
        
        
        if(result == test[i].res){
            printf("Тест №%d успешно пройден\nЗначение = %d\n", i + 1, result);
        }
        else{
            printf("Тест №%d не пройден\nЗначение не совпало", i + 1);
        }
        
        printf("\n");
        fclose(input);
        free(arr);
        free(matr);
    }
    
    
    return 0;
}