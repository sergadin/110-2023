#include <stdio.h>
#include <stdlib.h>

// Функция для определения позиции самой старшей единицы в битовом представлении числа
int findMostSignificantBitPosition(unsigned int num);
int findMostSignificantBitPosition(unsigned int num) 
{
    int position = -1; // Индекс самой старшей единицы (если таких нет, то значение будет -1)
    
    // Перебор битов числа от младших к старшим(пока число не равно нулю, сдвигаем его на один бит вправо
    // и увеличивает значение переменной position на один)
    while (num > 0) 
    {
        num = num >> 1;
        position++; // Переходим на следующий бит
    }
    
    return position; // Возвращаем позицию самой старшей единицы
}

int main(void) 
{
    int position;
    FILE* outputFile;
    unsigned int number;
    
    // Открытие файла с данными для чтения
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) 
    {
        printf("Ошибка открытия файла ввода.\n");
        return 1;
    }

    // Чтение числа из файла
    if (fscanf(inputFile, "%u", &number) != 1) 
    {
        printf("Ошибка чтения числа из файла.\n");
        fclose(inputFile);
        return 1;
    }

    // Закрытие файла с данными
    fclose(inputFile);

    // Вызов функции для определения позиции самой старшей единицы
    position = findMostSignificantBitPosition(number);

    // Открытие файла для записи результата
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) 
    {
        printf("Ошибка открытия файла вывода.\n");
        return 1;
    }

    // Запись результата в файл
    if (fprintf(outputFile, "%d\n", position) < 0) 
    {
        printf("Ошибка записи результата в файл.\n");
        fclose(outputFile);
        return 1;
    }

    // Закрытие файла для записи результата
    fclose(outputFile);

    return 0;
}