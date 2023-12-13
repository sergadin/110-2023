#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Функция сдвигает элементы массива на K позиций
// Функция для инвертирования части массива
//int shift_array_el_na_K(int* Array, int len) {
void invert(int* Array, int len) {
    
    int start = 0;
    int end = len - 1;
    while (start < end) {
        int temp = Array[start];
        Array[start] = Array[end];
        Array[end] = temp;
        start++;
        end--;
    }
}

//с использованием инвертирования
void shift_array_el_na_K(int* Array, int len, int k) {
    k %= len;
    invert(Array, len - k);
    invert(Array + len - k, k);
    invert(Array, len);
}

// Функция для вывода массива на экран
void printArray(int* Array, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", Array[i]);
    }
    printf("\n");
}

int main(void) {
    FILE *file_in = fopen("2.11.1.txt", "r");
    FILE *file_out = fopen("2.11.2.txt", "w");
    int len = 0, k = 0, main_return_code = 0;
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
    
    if (fscanf(file_in, "%d%d", &len, &k) != 2) {
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
    
       shift_array_el_na_K(Array, len, k);
    
    for (int i = 0; i < len; i++) {
        printf("%d ", Array[i]);
    }
    printf("\n");

    /* printf("Введите размер массива: ");
    scanf("%d", &n);

    int arr[n];
    printf("Введите элементы массива: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Введите количество позиций для сдвига: ");
    scanf("%d", &k);

    printf("Исходный массив: ");
    printArray(arr, n);

    // Применяем первое решение
    move_1(arr, n, k);
    printf("Массив после сдвига: ");
    printArray(arr, n);

    // Перезаписываем исходный массив
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    return 0;
}
*/
    
terminate_1:
    free(Array);
    
terminate:
    fclose(file_in);
    fclose(file_out);
    
    return main_return_code;
}
