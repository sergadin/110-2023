#include <stdio.h>
#include <stdlib.h>

// Функция для прибавления единицы к числу
void increment(int* arr, int size);
void increment(int* arr, int size) 
{
	for (int i = size - 1; i >= 0; i--)
	{
		if(arr[i] < 9) 
		{ 
			arr[i]++;
			break;
		}
		if (arr[i] == 9) 
		{
			arr[i] = 0;
		}
	}

    int carry = 1; // "Перенос" единицы
    for (int i = size - 1; i >= 0; i--) // Обрабатываем разряды числа, начиная с младшего
    {
        int sum = arr[i] + carry; // Сумма текущей цифры и "переноса"
        arr[i] = sum % 10; // Записываем только остаток от деления на 10
        carry = sum / 10; // Определяем новый "перенос"
    }
}

// Функция для вычитания единицы из числа
void decrement(int* arr, int size);
void decrement(int* arr, int size)
{
	
	for (int i = size - 1; i >= 0; i--)
	{
		if (arr[i] > 0) 
		{
			arr[i]--;
			break;
		}
		if (arr[i] == 0) 
		{
			arr[i] = 9;
		}
	}
	
    int borrow = 1; // "Заем" единицы
    for (int i = size - 1; i >= 0; i--) // Обрабатываем разряды числа, начиная с младшего
    {
        int diff = arr[i] - borrow; // Разность текущей цифры и "займа"
        if (diff < 0) // Если разность отрицательная, значит нужно занять 1 из следующего разряда
        { 
            arr[i] = diff + 10; // Добавляем 10 для получения корректного значения разности
            borrow = 1; // "Заимствование" 1
        } 
        else 
        {
            arr[i] = diff; // В противном случае просто записываем разность
            break; // И выходим из цикла
        }
    }
}

int main(void) 
{
    FILE* inputFile = fopen("input.txt", "r"); // Открываем файл для чтения
    FILE* outputFile;
    int size;
    int *arr = NULL;
    if (inputFile == NULL) 
    {
        printf("Ошибка при открытии файла\n"); // Выводим ошибку, если не удалось открыть файл
        return 1; // Завершаем программу с ошибкой
    }

    fscanf(inputFile, "%d", &size); // Считываем размер массива из файла

    arr = (int*)malloc(size * sizeof(int)); // Выделяем память под массив
    if (arr == NULL) 
    {
        printf("Ошибка при выделении памяти\n"); // Выводим ошибку, если не удалось выделить память
        fclose(inputFile); // Закрываем файл
        return 1; // Завершаем программу с ошибкой
    }
	
	arr[0] = 0;

    for (int i = 1; i < size + 1; i++)
    {
        int digit;
        if (fscanf(inputFile, "%1d", &digit) != 1) // Считываем по одной цифре из файла
        { 
            printf("Ошибка при чтении данных из файла\n"); // Выводим ошибку, если считывание не удалось
            fclose(inputFile); // Закрываем файл
            free(arr); // Освобождаем память
            return 1; // Завершаем программу с ошибкой
        }
        arr[i] = digit; // Записываем считанную цифру в массив
    }

    fclose(inputFile); // Закрываем файл

    increment(arr, size + 1); // Прибавляем единицу к числу

    outputFile = fopen("output.txt", "w"); // Открываем файл для записи
    if (outputFile == NULL) 
    {
        printf("Ошибка при открытии файла\n"); // Выводим ошибку, если не удалось открыть файл
        free(arr); // Освобождаем память
        return 1; // Завершаем программу с ошибкой
    }
	
	if (arr[0] == 0) // если значение arr[0] не изменилось, то не будем его записывать в файл вывода
    {
		for (int i = 1; i < size + 1; i++)
			fprintf(outputFile, "%d", arr[i]);
	}
	else 
    {
		for (int i = 0; i < size + 1; i++)
			fprintf (outputFile, "%d", arr[i]); 
	}

    fclose(outputFile); // Закрываем файл
    free(arr); // Освобождаем память

    return 0; // Завершаем программу без ошибок
}