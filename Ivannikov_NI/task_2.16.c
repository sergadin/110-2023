#include <stdio.h>
#include <stdlib.h>
// Функция для проверки является ли массив счастливым
int isLucky(int arr[], int size);
int isLucky(int arr[], int size)
{
	int sum1 = 0, sum2 = 0;
	int k = -1;

	//Вычисляем сумму всех элементов массива
	for (i = 0; i < size; i++)
	{
		sum1 += arr[i];
	}
	// Проверяем каждую позицию k
	for (i = 0; i < size; i++)
	{
		sum2 += arr[i];
		sum1 -= arr[i];

		if (sum1 == sum2)
		{
			k = i;
			break;
		}
	}
	return (k != -1);
}
int main(void)
{
	FILE *inputFile, *outputFile;
	int* arr = NULL;
	int size, num, i;
	//Открываем файлы для чтения и записи
	inputFile = fopen("input.txt","r");
	outputFile = fopen("output.txt","w");
	if (inputFile == NULL || outputFile == NULL)
	{
		fprintf(stderr,"Ошибка при открытии файлов.\n");
		return 1;
	}
	// Считываем размер и элементы массива из файла 
	fscanf(inputFile,"%d",&size);
	for (i = 0; i < size; i++)
	{
		fscanf(inputFile, "%d", &num);
		arr[i]=num;
	}
	//Проверяем является ли массив счастливым
	arr=(int*) malloc(size*sizeof(int));
	int isLuckyArray = isLucky(arr, size);
	//Выводим результат в файл
	fprintf(outputFile, "%s", isLuckyArray ? "Счастливый массив" : "Несчастливый массив");
	//Закрываем файлы
	fclose(inputFile);
	fclose(outputFile);
	free(arr);

	return 0;
}