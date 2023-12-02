//2. Пузырьковая сортировка.
//6. Быстрая сортировка (quicksort)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SORT 1
#define NESORT -1

void random_arr(int len, int *arr1, int *arr2, int *arr3); //генерирование рандомного массива
void pyz_sort(int *arr1, int len); //сортировка просеиванием
void quick_sort(int *arr2, int first, int last);  //быстрая сортировка
int test_ypor(int *arr, int len); //проверка упорядоченности массива
int comp(const int *a, const int *b); // вспомогательная функция для реализации qsort


//генерирование рандомного массива:
void random_arr(int len, int *arr1, int *arr2, int *arr3) {
	int r;
	for(int i = 0; i < len; i++){
		r = rand()% 1000;		 //rand()% 1000 если хотим рандомное int число в диапазоне от 0 до 999
		arr1[i] = r;
		arr2[i] = r;
		arr3[i] = r;
	}
}

// медленная сортировка просеиванием:
void pyz_sort(int *arr1, int len) {
	int c;
    int i = 0;
    int j = 0;
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                c = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j +1] = c;
            }
		}
	}
}

// быстрая сортировка quicksort:
void quick_sort(int *arr2, int first, int last) {
	int i, j;
	int index, y;
	
	i = first;
	j = last;
	index = arr2[(first + last) / 2];
	
	while(i <= j) {
        while((arr2[i] < index) && (i < last)) {
			i++;
		}
		while((arr2[j] > index) && (j > first)) {
			j--;
		}
		
		if(i <= j) {
			y = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = y;
			i++;
			j--;
		}
	}
	if(first < j) {
		quick_sort(arr2, first, j);
	}
	if(i < last) {
		quick_sort(arr2, i, last);
	}
}

// проверка упорядоченности:
int test_upor(int *arr, int len) { // возвращает SORT, если массив отсортирован, и NESORT в противном случае
	int k = SORT;
	for (int i = 0; i < len - 1; i++) {
		if (arr[i+1] < arr[i]) {
			k = NESORT;
		}
	}
	return k;
}

// для qsort:
int comp (const int *a, const int *b) {
    return *a - *b;
}




int main(void) {
	int len;  
	int test_1, test_2; 
	clock_t start_1, start_2, start_3, fin_1, fin_2, fin_3; // для подсчета времени работы сортировок
	double time_1, time_2, time_3; // для подсчета времени работы сортировок
	int *arr1 = NULL; // для медленной сортировки
	int *arr2 = NULL; // для быстрой сортировки
	int *arr3 = NULL; // сортировка с помощью функции qsort
	
	printf("vvedite dlinu massiva: len = \n"); //введите длину массива len
	if ((scanf ("%d", &len) != 1) || (len < 1)) {
		printf ("not korr len\n"); // некорректная длина
		return -1;
	}
	
	arr1 = (int *) malloc((len * pow(2, 4)) * sizeof(int));
	arr2 = (int *) malloc((len * pow(2, 4)) * sizeof(int));
	arr3 = (int *) malloc((len * pow(2, 4)) * sizeof(int));
	
	if (arr1 == NULL) {
		printf ("Memory error arr1\n");
		return -1;
	}
	if (arr2 == NULL) {
		printf ("Memory error arr2\n");
		return -1;
	}
	if (arr3 == NULL) {
		printf ("Memory error arr3\n");
		return -1;
	}
	
	for (int i = 0; i < 5; i++) { //цикл для просмотра разных длин рандомных массивов
		//заполнение массивов случайными целыми числами:
		random_arr(len, arr1, arr2, arr3);
		
		start_1 = clock();
		pyz_sort(arr1, len);
		fin_1 = clock();
		
        
		start_2 = clock();
		quick_sort(arr2, 0, len - 1); 
		fin_2 = clock();
		

		start_3 = clock();
		qsort(arr3, len, sizeof(int), (int(*) (const void *, const void *)) comp);
		fin_3 = clock();
		
		//записываем полученное время в типе double:
		time_1 = (double)(fin_1 - start_1)/CLOCKS_PER_SEC;
		time_2 = (double)(fin_2 - start_2)/CLOCKS_PER_SEC;
		time_3 = (double)(fin_3 - start_3)/CLOCKS_PER_SEC;
		
		//проверка массивов на упорядоченность:
		test_1 = test_upor(arr1, len);
		test_2 = test_upor(arr2, len);
		
		//вывод:
if (test_1 == NESORT) {
		printf("медленная сортировка неккоректна при длине: %d \n", len);
	} else {
		printf("//время медленной сортировки: %lf    при длине: %d \n", time_1, len);
	}
	
	if (test_2 == NESORT) {
		printf("быстрая сортировка(quicksort) неккоректна при длине: %d \n", len);
	} else { 
		printf("время быстрой сортировки(quicksort): %lf    при длине: %d \n", time_2, len);
	}
	printf("время функции qsort: %lf\n", time_3);
	printf("\n");

	len = len * 2;
}

free(arr1);
free(arr2);
free(arr3);

return 0;
}