#include <stdio.h>

// Функция для вычисления объединения отрезков наибольшей длины
void findLongestUnion(FILE *inputFile, FILE *outputFile);
void findLongestUnion(FILE *inputFile, FILE *outputFile) 
{
    int numSegments;
    fscanf(inputFile, "%d", &numSegments); // Считываем количество отрезков из файла ввода
    
    int start[numSegments]; // Массив для хранения начал отрезков
    int end[numSegments]; // Массив для хранения концов отрезков
    
    // Считываем начало и конец каждого отрезка из файла ввода
    for (int i = 0; i < numSegments; i++) 
    {
        fscanf(inputFile, "%d %d", &start[i], &end[i]);
    }
    
    // Ищем отрезки, объединение которых дает наибольшую длину
    int maxStart = start[0]; // Предполагаем, что первый отрезок дает наибольшую длину
    int maxEnd = end[0];
    
    for (int i = 1; i < numSegments; i++) 
    {
        if (start[i] > maxEnd) // Если начало текущего отрезка больше конца предыдущего, то объединение больше
        {
            maxStart = start[i];
            maxEnd = end[i];
        } 
        else if (end[i] > maxEnd) // Если конец текущего отрезка больше конца предыдущего, то обновляем конец
        {
            maxEnd = end[i];
        }
    }
    
    // Выводим результат в файл вывода
    fprintf(outputFile, "%d %d\n", maxStart, maxEnd);
    fprintf(outputFile, "%d\n", maxEnd - maxStart);
}

int main(void)
{
    FILE *inputFile, *outputFile;
    
    // Открываем файлы ввода и вывода
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    
    // Проверяем успешность открытия файлов
    if (inputFile == NULL || outputFile == NULL) 
    {
        printf("Ошибка при открытии файлов!\n");
        return 1;
    }
    
    // Вызываем функцию для вычисления результата
    findLongestUnion(inputFile, outputFile);
    
    // Закрываем файлы
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}