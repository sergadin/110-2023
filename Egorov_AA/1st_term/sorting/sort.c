#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b);


void swap_sort(int* arr, int len);


void merge(int* arr, int left, int mid, int right);


void merge_sort(int* arr, int left, int right);


int check_sorted_array(int* arr, int len);


void generate_array(int* arr, int len);


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


int check_sorted_array(int* arr, int len) {
	for (int i = 0; i < (len - 1); i++) {
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


int main() {
	int len;
	printf("enter length of the array to fill it with random numbers\n");
	scanf("%d", &len);
	int* arr = (int*)malloc(len * sizeof(double));

	generate_array(arr, len);

	for (int i = 0; i < len; i++)
		printf("%d  ", arr[i]);
	printf("\n\n");
	swap_sort(arr, len);
	for (int i = 0; i < len; i++)
		printf("%d  ", arr[i]);
	printf("\n\n");
	merge_sort(arr, 0, len - 1);

	for (int i = 0; i < len; i++)
		printf("%d  ", arr[i]);
	printf("\n\n");
	return 0;
}