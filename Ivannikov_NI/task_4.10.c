#include <stdio.h>
#include <stdlib.h>

// Функция для вывода подмножества множества {1, ..., N}
void printSubsets(int N, FILE *file);
void printSubsets(int N, FILE *file) 
{
    // Вычисление количества подмножеств
    int count = 1 << N;

    // Перебор всех подмножеств
    for (int i = 0; i < count; i++) 
    {
        // Вывод текущего подмножества в файл
        for (int j = 0; j < N; j++) 
        {
            if (i & (1 << j)) 
            {
                fprintf(file, "%d ", j + 1);
            }
        }
        fprintf(file, "\n");
    }
}

int main(void) 
{
    int N;
    
    // Открытие файлов для чтения и записи
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // Проверка успешного открытия файлов
    if (input == NULL || output == NULL) 
    {
        printf("Ошибка открытия файлов.\n");
        return 1;
    }

    // Считывание значения N из файла
    fscanf(input, "%d", &N);

    // Проверка корректности считывания значения N
    if (N <= 0) 
    {
        printf("Некорректное значение N.\n");
        return 1;
    }

    // Вызов функции для вычисления и вывода подмножеств в файл
    printSubsets(N, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}