#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ERROR -1


int Insert_sort(float *arr, int len){
    int newElement, location;

    for (int i = 1; i < len; i++)
    {
        newElement = arr[i];
        location = i - 1;
        while(location >= 0 && arr[location] > newElement)
        {
            arr[location+1] = arr[location];
            location = location - 1;
        }
        arr[location+1] = newElement;
    }
}


void swap(float *a, float *b){
	double c = *a;
	*a = *b;
	*b = c;
}


void go_up(float *arr, int k){
	int j;
	while(k > 0){
		j = (k - 1) / 2;
		if (arr[k] > arr[j]) {
			swap(arr + k, arr + j);
		}
		else {
			break;
		}
		k = j;
	}
}


void go_down(float *arr, int k){
	int i, i1, i2;
	if (k < 2) {
		return;
	}
	for (i = 0; i < k; ) {
		i1 = 2 * i + 1;
		i2 = i1 + 1;
		if (i1 >= k) {
			break;
		}
		if ((i2 < k) && (arr[i1] < arr[i2])) {
			i1 = i2;
		}
		if (arr[i] < arr[i1]) {
			swap(arr+i, arr+i1);
			i = i1;
		} else {
			break;
		}
	}
}


void heap_sort(float *arr, int len){
	int k;
	for (k = 1; k < len; k++){
		go_up(arr, k);
	}
	for (k = len - 1; k > 0; k--){
		swap(arr, arr+k);
		go_down(arr, k);
	}
}


void fill_random_arr(float *arr, int len){
    srand(time(NULL));
    for (int i = 0 ; i < len; i++){
        arr[i]= rand()*0.01;
    }
}


int check_sorted(float *arr, int len){
	float last_arr = arr[0];
	for (int i = 1; i < len; i++){
		if (last_arr > arr[i]){
			return -1;
		}
		last_arr = arr[i];
	}
	return 0;
}



int compare(const void* i, const void* j){
    return (*(int*)i - *(int*)j);

}


float get_Insertsort_time(float *arr, int len){
    float *arr_copy;
    clock_t insert_start, insert_end;
    arr_copy = (float *)malloc(len * sizeof(float));
    for(int i=0;i<len;i++){
        arr_copy[i] = arr[i];
    }
    insert_start = clock();
	Insert_sort(arr_copy, len);
	insert_end = clock();
	if(check_sorted(arr_copy,len) == -1){
        return -1;
	}
	free(arr_copy);
	return (((float)(insert_end - insert_start)) / CLOCKS_PER_SEC);
}


float get_qsort_time(float *arr, int len){
    float *arr_copy;
    clock_t qsort_start, qsort_end;
    arr_copy = (float *)malloc(len * sizeof(float));
    for(int i=0;i<len;i++){
        arr_copy[i] = arr[i];
    }
    qsort_start = clock();
	qsort(arr_copy, len, sizeof(float), compare);
	qsort_end = clock();
	if(check_sorted(arr_copy,len) == -1){
        return -1;
	}
	free(arr_copy);
	return (((float)(qsort_end - qsort_start)) / CLOCKS_PER_SEC);
}


float get_heapsort_time(float *arr, int len){
    float *arr_copy;
    clock_t heapsort_start, heapsort_end;
    arr_copy = (float *)malloc(len * sizeof(float));
    for(int i=0;i<len;i++){
        arr_copy[i] = arr[i];
    }
    heapsort_start = clock();
	heap_sort(arr_copy, len);
	heapsort_end = clock();
	if(check_sorted(arr_copy,len) == -1){
        return -1;
	}
	free(arr_copy);
	return (((float)(heapsort_end - heapsort_start)) / CLOCKS_PER_SEC);
}





void sorting_time(int len) {
	float insert_time, qsort_time, heapsort_time;
	float *arr;
	arr = (float *)malloc(len * sizeof(float));
	fill_random_arr(arr, len);
	insert_time = get_Insertsort_time(arr,len);
	if(insert_time == -1){
            printf("insertsort failed");
	}
	qsort_time = get_qsort_time(arr, len);
	if(qsort_time == -1){
            printf("qsort failed");
	}
	heapsort_time = get_heapsort_time(arr, len);
	if(heapsort_time == -1){
            printf("heapsort failed");
	}

	printf("len=%d:",len);
	printf(" insert time = %.10f ms; ",insert_time * pow(10,3));
	printf(" qsort time = %.10f ms;",qsort_time * pow(10,3));
	printf(" heapsort time = %.10f ms;",heapsort_time * pow(10,3));
	printf("\n");
	free(arr);
	return;
}



int main(void){
    int len;
    printf("vvedi max dlinu massiva: \n");
    if (scanf("%d", & len)!=1){
        printf("len not int \n");
		return -1;
	}
	for(int k=0;k<5;k++){
        sorting_time(pow(2,k)*len);
	}
    return 0;
}
