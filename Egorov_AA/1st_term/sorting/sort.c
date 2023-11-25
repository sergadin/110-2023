#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// меняет значения двух переменных местами
void swap(int* a, int* b);

// сортировка обменами в порядке возрастания 
void swap_sort(int* arr, int len);

// слияние двух массивов, сортируя элементы в порядке возрастания
void merge(int* arr, int* temp, int left, int mid, int right);

// сортировка слиянием
void merge_sort(int* arr, int* temp, int left, int right);

// сравнение двух элементов на равенство(вспомог. функ. для qsort)
int compare(const void* i, const void* j);

// проверка массива на упорядоченность
int check_sorted_array(int* arr, int len);

// генерация массива заданной длины
void generate_array(int** arr, int len, int* error);

// тест на время сортировки массива длины N, 2N, 4N, 8N
void sorting_time_test(int* arr, int* arr_copy, int len, int base_len, int* error);


void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}


void swap_sort(int* arr, int len) {
	int max_i, max_num;
	for (int k = len - 1; k > 0; k--) {
		max_num = arr[0];
		max_i = 0;
		for (int i = 1; i <= k; i++) {
			if (max_num < arr[i]) {
				max_num = arr[i];
				max_i = i;
			}
		}
		if (max_i != k)
			swap(arr + k, arr + max_i);
	}
}


void merge(int* arr, int* temp, int left, int mid, int right) {
	int i = 0, j = 0, k = left;
	int l_size = mid + 1 - left, r_size = right - mid;

	for (int q = 0; q < l_size; q++)
		temp[q] = arr[left + q];
	for (int q = 0; q < r_size; q++)
		temp[l_size + q] = arr[mid + q + 1];

	while ((i < l_size) && (j < r_size)) {
		if (temp[i] < temp[l_size + j]) {
			arr[k++] = temp[i++];
		}
		else {
			arr[k++] = temp[l_size + j++];
		}
	}

	while (i < l_size)
		arr[k++] = temp[i++];
	
	while (j < r_size)
		arr[k++] = temp[l_size + j++];

}


void merge_sort(int* arr, int* temp, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(arr, temp, left, mid);
		merge_sort(arr, temp, mid + 1, right);

		merge(arr, temp, left, mid, right);
	}
}


int compare(const void* i, const void* j)
{
	return (*(int*)i - *(int*)j);
}


int check_sorted_array(int* arr, int len) {
	for (int i = 0; i < (len-1); i++) {
		if (arr[i] > arr[i + 1])
			return 0;
	}
	return 1;
}


void generate_array(int** arr, int len, int* error) {
	*arr = (int*)malloc(len * sizeof(int));
	if ((*arr) == NULL)
		*error = -1;
    
	srand(time(NULL));
	for (int i = 0; i < len; i++)
		(*arr)[i] = rand();
}


void sorting_time_test(int* arr, int* arr_copy, int len, int base_len, int* error) {
	double swap_time, merge_time, qsort_time;
	clock_t swap_start, swap_end, merge_start,
			merge_end, qsort_start, qsort_end;
    int temp[len];

	generate_array(&arr, len, error);
	arr_copy = (int*)malloc(len * sizeof(int));
	if (arr_copy == NULL)
		*error = -1;
	for (int i = 0; i < len; i++)
		arr_copy[i] = arr[i];

	printf("\nN: %d\n", len);

	swap_start = clock();
	swap_sort(arr, len);
	swap_end = clock();
	swap_time = ((double)(swap_end - swap_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len))
		printf("%.3lf seconds\n", swap_time);

	for (int i = 0; i < len; i++)
		arr[i] = arr_copy[i];

	merge_start = clock();
	merge_sort(arr, temp, 0, len - 1);
	merge_end = clock();

	merge_time = ((double)(merge_end - merge_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len))
		printf("%.3lf seconds\n", merge_time);

	for (int i = 0; i < len; i++)
		arr[i] = arr_copy[i];

	qsort_start = clock();
	qsort(arr, len, sizeof(int), compare);
	qsort_end = clock();
	qsort_time = ((double)(qsort_end - qsort_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len))
		printf("%.3lf seconds\n", qsort_time);

	free(arr);
	free(arr_copy);
	if (len <= (4 * base_len)) {
		sorting_time_test(arr, arr_copy, 2 * len, base_len, error);
	}
}


int main(void) {
	int* arr = NULL, * arr_copy = NULL;
	int len, error = 0;

	printf("enter length of the array to fill it with random numbers\n");
	scanf("%d", &len);

	sorting_time_test(arr, arr_copy, len, len, &error);

	if (error)
		printf("memory allocation error\n");

	return 0;
}
