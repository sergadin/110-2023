#include <stdio.h>

// Структура для представления отрезка
typedef struct
{
    int start; // Начало отрезка
    int end; // Конец отрезка
} Segment;

// Функция, которая сортирует массив по возрастания
void BubbleSort(Segment arr[], int n);
void BubbleSort(Segment arr[], int n)
{
    int i, j;
    Segment temp;
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(arr[j].start > arr[j+1].start)
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Функция для вычисления отрезков с наибольшей длиной
void findLongestSegments(Segment arr[], int n);
void findLongestSegments(Segment arr[], int n)
{
    // Изначально максимальная длина равна длине первого отрезка
    int maxStart = arr[0].start;
    int maxEnd = arr[0].end;
    for(int i = 1; i < n; i++) // Проходим по оставшимся отрезкам
    {
        if(arr[i].start <= maxEnd)
        {
            if(arr[i].end > maxEnd)
            {
                maxEnd = arr[i].end;
            }
        }
        else
        {
            maxStart = arr[i].start;
            maxEnd = arr[i].end;
        }
    }
    printf("[%d, %d]\n", maxStart, maxEnd); // Выводим начальную и конечную точку максимального отрезка
}

int main(void)
{
    // Открываем файлы для чтения и записи
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL || outputFile == NULL) // Если открыть файлы не удалось, то выводим ошибку
    {
        printf("Failed to open the files.\n");
        return 1;
    }
    
    int n;
    fscanf(inputFile, "%d", &n); // Считываем количество отрезков

    if (n <= 0) // Если количество отрезков меньше нуля, то выводим ошибку считывания
    {
        printf("Reading error");
        return 1;
    }
    
    Segment segments[n]; // Массив для хранения отрезков
    
    // Считываем значения segments[i].start и segments[i].end из файла
    for(int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d %d", &segments[i].start, &segments[i].end);
    }
    
    // Вызываем функции
    BubbleSort(segments, n);
    findLongestSegments(segments, n);
    
    // Закрываем файлы
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}
