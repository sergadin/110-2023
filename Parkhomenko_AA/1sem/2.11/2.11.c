#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Функция сдвигает элементы массива на K позиций
void shift_array_el_na_K(int *Array, int len, int K);

void shift_array_el_na_K(int *Array, int len, int K) {
    // Если K больше длины массива или равно нулю, то сдвиг не требуется
    if (K >= len || K == 0)
        return;
    
    // Вычисляем индекс первого элемента после сдвига
    int shiftIndex = (len - K) % len;
    int temp;
    
    // Сдвигаем элементы массива
    for (int i = 0; i < len; i++) {
        temp = Array[i];
        
        // Вычисляем индекс элемента после сдвига
        int newIndex = (i + shiftIndex) % len;
        Array[i] = Array[newIndex];
        Array[newIndex] = temp;
    }
}

int main(void) {
    FILE *file_in = fopen("2.11.1.txt", "r");
    FILE *file_out = fopen("2.11.2.txt", "w");
    int len = 0, K = 0, main_return_code = 0;
    int *Array = NULL;
    
    if (file_in == NULL) {
        printf("error opening the file_in\n");
        return -1;
    }
    
    if (file_out == NULL) {
        printf("error opening the file_out\n");
        fclose(file_in);
        return -1;
    }
    
    if (fscanf(file_in, "%d%d", &len, &K) != 2) {
        printf("пустой файл\n");
        fclose(file_in);
        fclose(file_out);
        return -1;
    }
    
    Array = (int *)malloc(len * sizeof(int));
    if (Array == NULL) {
        printf("Оперативная память не выделена\n");
        main_return_code = -1;
        goto terminate;
    }
    
    for (int i = 0; i < len; ++i) {
        if (fscanf(file_in, "%d", &Array[i]) != 1) {
            printf("В файле недостаточно значений\n");
            main_return_code = -1;
            goto terminate_1;
        }
    }
    
    shift_array_el_na_K(Array, len, K);
    
    for (int i = 0; i < len; i++) {
        printf("Массив:\n");
printf("%d ", Array[i]);
}
    
terminate_1:
    free(Array);
    
terminate:
    fclose(file_in);
    fclose(file_out);
    
    return main_return_code;
}
