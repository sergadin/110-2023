#include <stdio.h>
#include <stdlib.h>

// Структура для представления отрезка 
typedef struct 
{
    int start; // Начало отрезка
    int end; // Конец отрезка
} Segment;

// Функция для вычисления максимальной длины объединения отрезков
void findLongestSegments(Segment* segments, int numSegments);
void findLongestSegments(Segment* segments, int numSegments) 
{
    // Изначально максимальная длина равна длине первого отрезка
    int maxStart = segments[0].start; // Начальная точка наибольшего объединения
    int maxEnd = segments[0].end; // Конечная точка наибольшего объединения 

    // Проходим по оставшимся отрезкам
    for (int i = 1; i < numSegments; i++) 
    {
        if (segments[i].start > maxEnd) // Если начальная точка отрезка больше конца предыдущего отрезка, то
        {
            printf("(%d, %d) ", maxStart, maxEnd);
            maxStart = segments[i].start;
            maxEnd = segments[i].end;
        }
        else if (segments[i].end > maxEnd) // Иначе если конечная точка больше конца предыдущего отрезка, то
        {
            maxEnd = segments[i].end;
        }
    }
    printf("(%d, %d)\n", maxStart, maxEnd);
}

int main(void) 
{
    // Открываем файлы ввода и вывода
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    // Проверяем успешность открытия файлов
    if (inputFile == NULL || outputFile == NULL) 
    {
        printf("Error opening input or output file.\n");
        return 1;
    }

    // Считывание значения numSegments из файла
    int numSegments;
    fscanf(inputFile, "%d", &numSegments);
    
    if (numSegments <= 0)
    {
        printf("Reading error.\n");
        return 1;
    }

    // Выделяем память
    Segment* segments = (Segment*)malloc(numSegments * sizeof(Segment));
    if (segments == NULL)
    {
        printf("Error allocating memory.\n");
        return 1;
    }

    // Считываем значения segments[i].start и segments[i].end из файла
    for (int i = 0; i < numSegments; i++) 
    {
        fscanf(inputFile, "%d %d", &segments[i].start, &segments[i].end);
    }

    // Вызов функции для нахождения максимальной длины объединения отрезков
    findLongestSegments(segments, numSegments);

    // Освобождаем память 
    free(segments);
    
    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
