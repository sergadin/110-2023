#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// меняет значения двух переменных местами
void swap(int* a, int* b);

// сортировка обменами в порядке возрастания 
void swap_sort(int* arr, int len);

// слияние двух массивов, сортируя элементы в порядке возрастания
void merge(int* arr, int left, int mid, int right, int* error);

// сортировка слиянием
void merge_sort(int* arr, int left, int right, int* error);

// сравнение двух элементов на равенство(вспомог. функ. для qsort)
int compare(const int* i, const int* j);

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


void merge(int* arr, int left, int mid, int right, int* error) {
	int i = 0, j = 0, k = left;
	int l_size = mid + 1 - left, r_size = right - mid;

	int* l_array = (int*)malloc(l_size * sizeof(int));
	if (l_array == NULL)
		*error = -1;
	int* r_array = (int*)malloc(r_size * sizeof(int));
	if (r_array == NULL)
		*error = -1;

	for (int q = 0; q < l_size; q++)
		l_array[q] = arr[left + q];
	for (int q = 0; q < r_size; q++)
		r_array[q] = arr[mid + q + 1];

	while ((i < l_size) && (j < r_size)) {
		if (l_array[i] < r_array[j]) {
			arr[k++] = l_array[i++];
		}
		else {
			arr[k++] = r_array[j++];
		}
	}

	while (i < l_size)
		arr[k++] = l_array[i++];
	
	while (j < r_size)
		arr[k++] = r_array[j++];

	free(l_array);
	free(r_array);
}


void merge_sort(int* arr, int left, int right, int* error) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(arr, left, mid, error);
		merge_sort(arr, mid + 1, right, error);

		merge(arr, left, mid, right, error);
	}
}


int compare(const int* i, const int* j)
{
	return *i - *j;
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
	merge_sort(arr, 0, len - 1, error);
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


int main() {
	int* arr = NULL, * arr_copy = NULL;
	int len, error = 0;

	printf("enter length of the array to fill it with random numbers\n");
	scanf("%d", &len);

	sorting_time_test(arr, arr_copy, len, len, &error);

	if (error)
		printf("memory allocation error\n");

	return 0;
}
