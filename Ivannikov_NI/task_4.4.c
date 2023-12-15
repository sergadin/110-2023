#include <stdio.h>
#include <stdlib.h>

// Функция для определения позиции самой старшей единицы в битовом представлении числа
int findMostSignificantBitPosition(unsigned int num);
int findMostSignificantBitPosition(unsigned int num) 
{
    int position = -1; // Индекс самой старшей единицы (если таких нет, то значение будет -1)

    // Перебор битов числа от младших к старшим
    while (num > 0) 
    {
        position++; // Переходим на следующий бит

        if (num & 1) 
        {
            // Если текущий бит равен 1, то это самая старшая единица
            return position;
        }

        num >>= 1; // Сдвигаем число на один бит вправо
    }

    return -1; // Если все биты равны 0, то возвращаем -1
}

int main(void) 
{
    // Открытие файла с данными для чтения
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) 
    {
        perror("Ошибка открытия файла ввода");
        return 1;
    }

    // Чтение числа из файла
    unsigned int number;
    if (fscanf(inputFile, "%u", &number) != 1) 
    {
        perror("Ошибка чтения числа из файла");
        fclose(inputFile);
        return 1;
    }

    // Закрытие файла с данными
    fclose(inputFile);

    // Вызов функции для определения позиции самой старшей единицы
    int position = findMostSignificantBitPosition(number);

    // Открытие файла для записи результата
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) 
    {
        perror("Ошибка открытия файла вывода");
        return 1;
    }

    // Запись результата в файл
    if (fprintf(outputFile, "%d\n", position) < 0) 
    {
        perror("Ошибка записи результата в файл");
        fclose(outputFile);
        return 1;
    }

    // Закрытие файла для записи результата
    fclose(outputFile);

    return 0;
}