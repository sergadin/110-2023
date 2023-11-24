#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b);
void swap_sort(int* arr, int len);
void merge(int* arr, int left, int mid, int right);
void merge_sort(int* arr, int left, int right);
int compare(const int* i, const int* j);
int check_sorted_array(int* arr, int len);
void generate_array(int* arr, int len);
void read_array(int* arr, int len, FILE* input);
void sorting_time_test(int* arr, int len, FILE* input);



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


void merge(int* arr, int left, int mid, int right) {
	int i = 0, j = 0, k = left;
	int l_size = mid + 1 - left, r_size = right - mid;

	int* l_array = (int*)malloc(l_size * sizeof(int));
	int* r_array = (int*)malloc(r_size * sizeof(int));

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


void merge_sort(int* arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
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


void generate_array(int* arr, int len) {
	srand(time(NULL));
	for (int i = 0; i < len; i++)
		arr[i] = rand();
}


void read_array(int* arr, int len, FILE* input) {
	for (int i = 0; i < len; i++)
		fscanf(input, "%d", &arr[i]);
}


void sorting_time_test(int* arr, int len, FILE* input) {
	double swap_time, merge_time, qsort_time;
	clock_t swap_start, swap_end, merge_start,
			merge_end, qsort_start, qsort_end;

	swap_start = clock();
	swap_sort(arr, len);
	swap_end = clock();
	swap_time = ((double)(swap_end - swap_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len)) {
		printf("%lf miliseconds", swap_time);
	}

	read_array(arr, len, input);

	merge_start = clock();
	merge_sort(arr, 0, len - 1);
	merge_end = clock();
	merge_time = ((double)(merge_end - merge_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len)) {
		printf("%lf miliseconds", merge_time);
	}

	read_array(arr, len, input);

	qsort_start = clock();
	qsort(arr, len, sizeof(int), compare);
	qsort_end = clock();
	qsort_time = ((double)(qsort_end - qsort_start)) / CLOCKS_PER_SEC;

	if (check_sorted_array(arr, len)) {
		printf("%lf miliseconds", qsort_time);
	}
}


int main() {
	FILE* input;
	int len;

	input = fopen("input.txt", "r");

	printf("enter length of the array to fill it with random numbers\n");
	scanf("%d", &len);

	int* arr = (int*)malloc(len * sizeof(double));

	generate_array(arr, len);

	for (int i = 0; i < len; i++)
		fscanf(input, "%d", arr[i]);

	sorting_time_test(arr, len, input);

	return 0;
}
