#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для сортировки массива чисел методом просеивания
void slowSort(int* arr, int size);
void slowSort(int* arr, int size) 
{
    for(int i = 1; i < size; i++) // Цикл для прохода по всем элементам массива, начиная со второго элемента
    {
		for(int j = i; (j > 0) && (arr[j] < arr[j - 1]); j--) // Вложенный цикл для перестановки текущего 
		// элемента со всеми предыдущими, пока они больше текущего
		{
			int temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
		}
	}
}

// Функция для сортировки массива чисел методом подсчета
void quickSort(int* arr, int size);
void quickSort(int* arr, int size) 
{
    int min = arr[0];
    int max = arr[0];
    
    // Находим максимальное и минимальное значение в массиве
    for (int i = 1; i < size; i++) 
    {
        if (arr[i] < min) 
        {
            min = arr[i];
        }
        if (arr[i] > max) 
        {
            max = arr[i];
        }
    }

    // Создаём массив для подсчёта количества элементов
    int countSize = max - min + 1;
    int* count = (int*)malloc(countSize * sizeof(int));
    
    // Инициализируем массив нулями
    for (int i = 0; i < countSize; i++) 
    {
        count[i] = 0;
    }

    // Подсчитываем количество каждого элемента
    for (int i = 0; i < size; i++) 
    {
        count[arr[i] - min]++;
    }

    // Заполняем исходный массив отсортированными элементами
    int index = 0;
    for (int i = 0; i < countSize; i++) 
    {
        for (int j = 0; j < count[i]; j++) 
        {
            arr[index++] = i + min;
        }
    }

    free(count);
}

// Функция для сортировки массива чисел с использованием библиотечной функции qsort
int compare(const void* a, const void* b);
int compare(const void* a, const void* b) 
{
    return (*(int*)a - *(int*)b);
}

void librarySort(int* arr, int size);
void librarySort(int* arr, int size) 
{
    qsort(arr, size, sizeof(int), compare);
}

// Функция для проверки упорядоченности массива чисел
int isSorted(int* arr, int size);
int isSorted(int* arr, int size) 
{
    for (int i = 0; i < size - 1; i++) 
    {
        if (arr[i] > arr[i + 1]) 
        {
            return 0;
        }
    }
    return 1;
}

// Функция для чтения массива чисел из файла
void readArrayFromFile(char* filename, int** arr, int* size);
void readArrayFromFile(char* filename, int** arr, int* size) 
{
    FILE* file = fopen(filename, "r");
    if (file) {
        fscanf(file, "%d", size);
        *arr = (int*)malloc(*size * sizeof(int));
        for (int i = 0; i < *size; i++) 
        {
            fscanf(file, "%d", &(*arr)[i]);
        }
        fclose(file);
    }
}

// Функция для генерирования случайного массива указанной длины
void generateRandomArray(int** arr, int size);
void generateRandomArray(int** arr, int size) 
{
    *arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) 
    {
        (*arr)[i] = rand() % 1000; // предполагаем, что числа в массиве не превышают 100
    }
}

int main(void) 
{
    srand(time(NULL)); // Устанавливает текущее время

    int* arr;
    int size;

    for (int N = 100; N <= 1000000; N *= 2) 
    {
        generateRandomArray(&arr, N);
        
        // Измеряем время работы медленной сортировки
        clock_t start = clock();
        slowSort(arr, N);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Slow Sort - N: %d - Time taken: %f\n", N, time_taken);

        if (!isSorted(arr, N)) 
        {
            printf("Slow Sort failed!\n");
            return 1;
        }

        // Измеряем время работы быстрой сортировки
        start = clock();
        quickSort(arr, N);
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Quick Sort - N: %d - Time taken: %f\n", N, time_taken);

        if (!isSorted(arr, N)) 
        {
            printf("Quick Sort failed!\n");
            return 1;
        }

        // Измеряем время работы сортировки с использованием библиотечной функции
        start = clock();
        librarySort(arr, N);
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Library Sort - N: %d - Time taken: %f\n", N, time_taken);
        
        if (!isSorted(arr, N))
        {
            printf("Library Sort failed!\n");
            return 1;
        }
    }
    
    return 0;
}
