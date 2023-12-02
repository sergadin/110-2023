#include <stdio.h>
#include <stdlib.h>
// Функция находит число, встречающееся наибольшее количество раз в массиве.
int findMostFrequentNumber(int* arr, int length);
int findMostFrequentNumber(int* arr, int length) 
{
    int maxCount = 0; // переменная для хранения максимального количества повторений числа
    int mostFrequentNumber = arr[0]; // переменная для хранения числа с наибольшим количеством повторений
    
    for (int i = 0; i < length; i++) 
    {
        int count = 0; // переменная для хранения количества повторений текущего числа
        
        for (int j = 0; j < length; j++) 
        {
            if (arr[j] == arr[i]) 
            {
                count++; // увеличиваем счетчик повторений, если числа равны
            }
        }
        
        if (count > maxCount) 
        {
            maxCount = count; // обновляем максимальное количество повторений
            mostFrequentNumber = arr[i]; // обновляем число с наибольшим количеством повторений
        }
    }
    
    return mostFrequentNumber;
}

int main(void) 
{
    // Открываем файл для чтения
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) 
    {
        // В случае ошибки открытия файла, выводим сообщение об ошибке и завершаем программу
        printf("Error opening file!");
        return 1;
    }
    
    // Определяем переменные для хранения количества чисел в файле
    int count;
    fscanf(file, "%d", &count);
    
    // Создаем динамический массив для хранения чисел из файла
    int* numbers = (int*)malloc(sizeof(int) * count);
    if (numbers == NULL) 
    {
        // В случае ошибки выделения памяти, выводим сообщение об ошибке и завершаем программу
        printf("Error allocating memory!");
        fclose(file); // закрываем файл перед завершением программы
        return 1;
    }
    
    // Считываем числа из файла
    for (int i = 0; i < count; i++) 
    {
        fscanf(file, "%d", &numbers[i]);
    }
    
    fclose(file); // закрываем файл после чтения
    
    // Находим число, которое встречается наибольшее количество раз
    int mostFrequentNumber = findMostFrequentNumber(numbers, count);
    
    // Открываем файл для записи
    file = fopen("output.txt", "w");
    if (file == NULL) 
    {
        // В случае ошибки открытия файла, выводим сообщение об ошибке и завершаем программу
        printf("Error opening file!");
        free(numbers); // освобождаем память, выделенную для массива
        return 1;
    }
    
    // Записываем результат в файл
    fprintf(file, "%d", mostFrequentNumber);
    
    fclose(file); // закрываем файл после записи
    
    free(numbers); // освобождаем память, выделенную для массива
    
    return 0;
}