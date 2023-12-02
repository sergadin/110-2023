#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define Uncorr_ord -1
#define Corr_ord 0
#define mem_err -2
 
//Функция sorting_comparing сравнивает скорости сортировок qsort и sort_bin.

int compare(const void* i, const void* j);
int ordered_seq(int *arr, int len);
int ordered_bin_seq(int *arr, int len);
int bin1(int num);
int rand_array(int *arr, int len);
int sorting_comparing(int *arr, int *arr_copy, int len, FILE * f_out, int *bin_arr);
void heap_sort(int *arr, int len);
void go_up(int *arr, int k);
void go_down(int *arr, int k);
void swap(int *a, int *b);

int compare(const void* i, const void* j){
    return (*(int*)i - *(int*)j);
    
}

int ordered_seq(int *arr, int len){
	int last_val = arr[0];
	for (int i = 1; i < len; i++){
		if (last_val > arr[i]){
			return Uncorr_ord;
		}
		last_val = arr[i];
	}
	return Corr_ord;
}

int ordered_bin_seq(int *arr, int len){
    int a;
	int lv = bin1(arr[0]);
	for (int i = 1; i < len; i++){
        a = bin1(arr[0]);
		if (lv > a){
			return Uncorr_ord;
		}
		lv = a;
	}
	return Corr_ord;
}

int bin1(int num){
	int count = 0;
    
	while (num) {
        num &= (num - 1);
        count+=1;
    }
	return count;
}

int rand_array(int *arr, int len){
	srand(time(NULL));
	
	for (int i = 0; i < len; i++){
		arr[i] = rand()%1000;
	}
	return 0;
}

void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}

void go_up(int *arr, int k){
	int j, a1, a2;
	while(k > 0){
		j = (k - 1) / 2;
        a1 = bin1(arr[k]);
        a2 = bin1(arr[j]);
		if (a1 > a2) {
			swap(arr + k, arr + j);
		}
		else {
			break;
		}
		k = j;
	}
}
void go_down(int *arr, int k){
	int i, i1, i2, a1, a2, a;
	if (k < 2) {
		return;
	}
	for (i = 0; i < k; ) {
		i1 = 2 * i + 1;
		i2 = i1 + 1;
        a1 = bin1(arr[i1]);
        a2 = bin1(arr[i2]);
        a = bin1(arr[i]);
		if (i1 >= k) {
			break;
		}
		if ((i2 < k) && (a1 < a2)) {
			i1 = i2;
		}
		if (a < a1) {
			swap(arr+i, arr+i1);
			i = i1;
		} else {
			break;
		}
	}
}

void heap_sort(int *arr, int len){
	int k;
	for (k = 1; k < len; k++){
		go_up(arr, k);
	}
	for (k = len - 1; k > 0; k--){
		swap(arr, arr+k);
		go_down(arr, k);
	}
}

int sorting_comparing(int *arr, int *arr_copy, int len, FILE * f_out, int *bin_arr){
    clock_t st_bin, end_bin, sec_bin, st_q, end_q, sec_q;
    	arr_copy = (int *)malloc(len*sizeof(int));
	if (arr_copy == NULL){
		printf("Оперативная память не выделена\n");
		return mem_err;
	}
	
	bin_arr = (int *)malloc(len*sizeof(int));
	if (bin_arr == NULL){
		printf("Оперативная память не выделена\n");
		free(arr_copy);
		return mem_err;
	}
	rand_array(arr, len);
    
	for (int i =0; i<len; i++){
        	arr_copy[i] = arr[i];
    	}
    
    for (int i=0; i<len; i++){
		bin_arr[i] = bin1(arr[i]);
	}
    st_q = clock();
    qsort(bin_arr, len, sizeof(int), compare);
    end_q = clock();
    sec_q = (double)(end_q-st_q);
    if (ordered_seq(bin_arr, len) == Uncorr_ord){
        printf("Не отсoртировано\n");
    }
    else{
        fprintf(f_out, "\tДлина массива: %7d   время: %10ld    ", len, sec_q);
    }
    
    for (int i = 0; i<len; i++){
        arr[i] = arr_copy[i];
    }
    
    st_bin = clock();
    heap_sort(arr, len);
    end_bin = clock();
    sec_bin = (double)(end_bin-st_bin);
    if (ordered_bin_seq(arr, len) == Uncorr_ord){
        printf("Не отсoртировано\n");
    }
    else{
        fprintf(f_out, "время: %10ld    \n", sec_bin);
    }
    free(arr_copy);
    free(bin_arr);
    return 0;
}

int main(void){
	FILE *f_out;
	int len, *arr_rand = NULL, *bin_arr=NULL, *arr_copy = NULL; 
	int main_return_code = 0;
	
	
	printf("Введите максимальную длину случайного массива:\n");
	scanf("%d", &len);
	
	f_out = fopen("output.txt","w");
	
	if (f_out == NULL){
		printf("Файл не открывается\n");
		return -1;
	}	
	
	arr_rand = (int *)malloc(len*sizeof(int));
	if (arr_rand == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate;
	}
	
	
	
	fprintf(f_out,"Сортировки:\n                                       Qsort                 Бинарные\n");
    for (int i = 1; i<=len; i = i*2){
        if(sorting_comparing(arr_rand, arr_copy, i, f_out, bin_arr)==mem_err){
        	printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
        }
    }
	printf("Ответ записан в файл output.txt\n");
	
	terminate_1:
	free(arr_rand);
	
	terminate:
	
	fclose(f_out);
	return main_return_code;
}
