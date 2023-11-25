//3.3 сортировка просеиванием  (медленная сортировка)
//3.6 быстрая сортировка (quicksort)  (быстрая сортировка)

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define UPOR 1
#define NEUPOR -1

void random(int len, int *arr1, int *arr2, int *arr3); //генерирование рандомного массива
void pros_sort(int *arr1, int len); //3.3 сортировка просеиванием
void quick_sort(int *arr2, int first, int last);  //3.6 быстрая сортировка
int test_upor(int *arr, int len); //проверка упорядоченности массива
int comp(const int *a, const int *b); // вспомогательная функция для реализации qsort


//генерирование рандомного массива:
void random(int len, int *arr1, int *arr2, int *arr3) {
	int r;
	for(int i = 0; i < len; i++){
		r = rand()% 1000;		 //rand()% 1000 если хотим рандомное int число в диапазоне от 0 до 999
		arr1[i] = r;
		arr2[i] = r;
		arr3[i] = r;
	}
}

// медленная сортировка просеиванием:
void pros_sort(int *arr1, int len) {
	int c;
	for(int i = 1; i < len; i++) {
		for(int j = i; (j > 0) && (arr1[j] < arr1[j - 1]); j--) {
			c = arr1[j];
			arr1[j] = arr1[j - 1];
			arr1[j - 1] = c;
		}
	}
}

// быстрая сортировка quicksort:
void quick_sort(int *arr2, int first, int last) {
	int i, j;
	int mid, y;
	
	i = first;
	j = last;
	mid = arr2[(first + last) / 2];
	
	while(i <= j) {
		while((arr2[i] < mid) && (i < last)) {
			i++;
		}
		while((arr2[j] > mid) && (j > first)) {
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
int test_upor(int *arr, int len) { // возвращает UPOR, если массив отсортирован, и NEUPOR в противном случае
	int k = UPOR;
	for (int i = 0; i < len - 1; i++) {
		if (arr[i+1] < arr[i]) {
			k = NEUPOR;
		}
	}
	return k;
}

// для qsort:
int comp (const int *a, const int *b) {
    return *a - *b;
}

int main(void) {
	int len;  // длина массива
	int test_1, test_2; // для проверки массива на упорядоченность
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
	
	arr1 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	arr2 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	arr3 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	
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
	
	for (int i = 0; i < 4; i++) { //цикл для просмотра разных длин рандомных массивов
		len = len * pow(2,i);
		
		//заполнение массивов случайными целыми числами:
		random(len, arr1, arr2, arr3);
		
		//выполняем "медленную" сортировку просеиванием:
		start_1 = clock();
		pros_sort(arr1, len);
		fin_1 = clock();
		
		//выполняем "быструю" сортировку:
		start_2 = clock();
		quick_sort(arr2, 0, len - 1); 
		fin_2 = clock();
		
		//выполняем qsort:
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
		if (test_1 == NEUPOR) {
			//медленная сортировка просеиванием неккоректна при длине:
			printf("medl sort pros not korr pri len: %d \n", len);
		}
		else {
			//время медленной сортировки просеиванием:   при длине:
			printf("time medl sort pros: %lf    pri len: %d \n", time_1, len);
//			for (i = 0; i < len; i++){
//				printf("%lf\n", arr1[i]);
//			}
//			printf("\n");
		}
		
		if (test_2 == NEUPOR) {
			//быстрая сортировка(quicksort) неккоректна при длине:
			printf("bustr sort(quicksort) not korr pri len: %d \n", len);
		}
		else { 
			//время быстрой сортировки(quicksort):    при длине:
			printf("time bustr sort(quicksort): %lf    pri len: %d \n", time_2, len);
//			for (i = 0; i < len; i++){
//				printf("%lf\n", arr2[i]);
//			}
//			printf("\n");
		}
		//время функции qsort:
		printf("time function qsort: %lf\n", time_3);
//			for (i = 0; i < len; i++){
//				printf("%lf\n", arr3[i]);
//			}
//			printf("\n");
		printf("\n");
	}
    
    free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}