#include <stdio.h>
#include <stdlib.h>

// Функция, которая прибавляет единицу к числу
void increment(char* number, int length);
void increment(char* number, int length) 
{
    int carry = 1; // Перенос из старшего разряда, начальное значение - 1
    // Обрабатываем разряды числа, начиная с младшего
    for (int i = length - 1; i >= 0 && carry; i--) 
    {
        int digit = number[i] - '0'; // Преобразуем символ в число
        number[i] = (digit + carry) % 10 + '0'; // Пересчитываем разряд
        carry = (digit + carry) / 10; // Обновляем перенос
    }
    
    // Если все разряды были обработаны, но перенос остался, добавляем его в начало числа
    if (carry) 
    {
        printf("Overflow occurred.\n");
        return;
    }
}

// Функция, которая вычитает единицу из числа
void decrement(char* number, int length);
void decrement(char* number, int length) 
{
    int carry = -1; // Перенос из старшего разряда, начальное значение - (-1)
    // Обрабатываем разряды числа, начиная с младшего
    for (int i = length - 1; i >= 0 && carry; i--) 
    {
        int digit = number[i] - '0'; // Преобразуем символ в число
        number[i] = (digit + carry + 10) % 10 + '0'; // Пересчитываем разряд
        carry = (digit + carry + 10) / 10 - 1; // Обновляем перенос
    }
    
    // Если все разряды были обработаны, но перенос остался, значит число было меньше нуля
    if (carry) 
    {
        printf("Underflow occurred.\n");
        return;
    }
}

int main(void) 
{
    FILE *input_file = fopen("input.txt", "r"); // Открытие файла для чтения
    FILE *output_file = fopen("output.txt", "w"); // Открытие файла для записи

    if (input_file == NULL || output_file == NULL) 
    {
        printf("Failed to open files.\n");
        return 1;
    }
    
    // Чтение длины массива из файла
    int length;
    if (fscanf(input_file, "%d", &length) != 1) 
    {
        printf("Failed to read array length from file.\n");
        return 1;
    }
    
    // Выделение памяти для массива
    char* number = (char*)malloc((length+1)*sizeof(char));
    if (number == NULL) 
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    // Чтение числа из файла
    if (fscanf(input_file, "%s", number) != 1) 
    {
        printf("Failed to read number from file.\n");
        return 1;
    }

    // Прибавление единицы
    increment(number, length);

    // Вывод в файл
    fprintf(output_file, "%s", number);

    // Вычитание единицы
    decrement(number, length);

    // Вывод в файл
    fprintf(output_file, "\n%s", number);
    
    // Освобождение памяти и закрытие файлов
    free(number);
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}