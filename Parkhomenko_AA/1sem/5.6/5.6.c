#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SORT_Search(double *array, int length);
void swap(double *a, double *b);
int coverage(double *array, int length, double a, double b);
void unite(double *array, int length);
double max(double x1, double x2);

void SORT_Search(double *array, int length) //сортирует отрезки в массиве по началу координат
{
	int i, j, p;

	for (i = 0; i < ( length-2); i=i+2) {
		p = i ;// сохраним значение i
		for (j = i + 2;( j >=0 && (array[i] - array[j]) > 0); j = j - 2){ // меняем элементы до тех пор пока не найдем место для элемента a[j] в уже отсортированной части массива
			swap(array + i, array + j);
			swap(array + (i + 1 ), array + (j + 1));
			i = (i - 2) % length;
			if (i < 0) {
				break;
			}
		}
		i = p;
	}
}

void swap(double *a, double *b) // обмен между двумя элементами массива
{
	double c = *a;

	*a = *b;
	*b = c;
}

int coverage(double *array, int length, double a, double b) //проверяет, покрывает ли введенный отрезок отрезки в массиве. Если такой отрезок есть, функция возвращает 1, в противном случае - 0.
{
	int i, res = 0;

	for (i = 0; i < length; i = i + 2)
	{
		if (array[i] <= a && a <= array[i + 1] && array[i] <= b && b <= array[i + 1]) // Если а и в между двумя концами непересекающихся отрезков то нам подходит 
			res = 1;
	}

	return res;

}

void unite(double *array, int length) //сравнивает конец одного отрезка с началом следующего и, если конец больше начала, объединяет их
{
	int i = 1,j,c = 0;
	
	while (i < length)
	{
		while(array[i] - array[i + 1] > -0.00001) // Если конец отрезка больше начала следующего отрезка, то соединяем
			{	
				if (fabs(array[i + 2]) < 0.00001 && fabs(array[i + 1]) < 0.00001) // Если начало и конц 0, то выходим из цикла
				{
					break;
				}	
				c += 1; 
				array[i] = max(array[i], array[i + 2]); // конец отрезка делаем наобильшим из концов отрезка i и i + 1
				for (j = i + 1; j < length - 2; j++) // поднимаем отрезки наверх 
				{
		  			array[j] = array[(j + 2) % length]; 
				}
			        array[(length - c) % length] = 0; // зануляем, если отрезки вложены, чтобы выходить из цикла
                                array[(length - c -1) % length] = 0; 
				if (c >= length)
				{
					break;
				}
			}
		i = i + 2;
		if (c >= length)
		{
			break;
		}

		if (fabs(array[i + 2]) < 0.00001 && fabs(array[i + 1]) < 0.00001)
                                {
                                        break;
                                }


	}

}	

double max(double x1, double x2) //возвращает максимальное значение из двух переданных значений
{
	double c; 

	c = x1;
	if ( c < x2){
		c = x2;
	}

	return c;
}


int main ( void)
{
	FILE *input; // входной файл
	double *array; // массив
	int count, i; // количество отрезков и индекс для задания массива
	double a, b; // начало и конец входного отрезка
	int result;

	printf("Введите начало и конец отрезка\n");
	scanf("%lf %lf", &a, &b);
	if (a > b)
	{
		printf("Неверные входные данные\n");
		return -1;
	}
	else if (a == b)
	{
		printf("Точка не является отрезком\n");
		return -1; 
	}

	input = fopen("input.txt", "r");
	if (input == NULL) {
		printf("Не удалось открыть входной файл\n");
		return -1;
	}

	if ((fscanf(input, "%d", &count) != 1) || (count <= 0)) {
		printf("Не удалось прочитать первый элемент\n");
		return -1;
	}

	count = count * 2; // длина массива

	array = (double*)malloc(count * sizeof(double));
	for (i = 0; i < count; i++) {
		if (fscanf(input, "%lf", &array[i]) != 1) {
			printf("Первый элемент не равен длине предполагаемого массива\n");
			return -1;
		}
	}

	if (fscanf(input, "%lf", &array[i + 1]) == 1) {
		printf("Первый элемент не равен длине предполагаемого массива\n");
		return -1;
	}

	SORT_Search(array, count); //сортировка по началу координат
	unite(array, count); // объединение отрезков 
	result = coverage(array, count, a, b); // проверка на покрытие отрезка входными данными
	if (result < 1)
		printf("Не покрывает\n");
	else
		printf("Покрывает\n");

	free(array);
	fclose(input);
	return 0;
}