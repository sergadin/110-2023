#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define Uncorr_ord -1
#define Corr_ord 0
#define mem_err -2

//Функция sort_bin сортирует числа по количеству единиц в двиочной записи. 
//Функция sorting_comparing сравнивает скорости сортировок qsort и sort_bin.

int compare(const void* i, const void* j);
int ordered_seq(int *arr, int len);
int bin1(int num);
int rand_array(int *arr, int len);
int sort_bin(int *arr, int len, int *bin_arr);
int sorting_comparing(int *arr, int *arr_copy, int len, FILE * f_out, int *bin_arr);

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

int bin1(int num){
	int count = 0;
	while (num > 0){
		if (num & 1){
			count++;
		}
		num = num >> 1;
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

int sort_bin(int *arr, int len, int *bin_arr){
	int c, d;
	
	
	for (int i = 0; i < len; i++){
		for (int j = i+1; j < len; j++){
			if (bin_arr[i] > bin_arr[j]){
				c = bin_arr[i];
				bin_arr[i] = bin_arr[j];
				bin_arr[j] = c;
				d = arr[i];
				arr[i] = arr[j];
				arr[j] = d;
			}
		}
	}
	if (ordered_seq(bin_arr, len) == Uncorr_ord){
		return Uncorr_ord;
	    }
	
	return Corr_ord;
}

int sorting_comparing(int *arr, int *arr_copy, int len, FILE * f_out, int *bin_arr){
    clock_t st_bin, end_bin, sec_bin, st_q, end_q, sec_q;
    	int answ;
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
        fprintf(f_out, "Длина массива: %d   время: %ld    ", len, sec_q);
    }
    
    for (int i = 0; i<len; i++){
        arr[i] = arr_copy[i];
    }
    
    for (int i=0; i<len; i++){
		bin_arr[i] = bin1(arr[i]);
	}
    
    st_bin = clock();
    answ = sort_bin(arr, len, bin_arr);
    end_bin = clock();
    sec_bin = (double)(end_bin-st_bin);
    if (answ == Uncorr_ord){
    	printf("Не отсoртировано\n");
    }else{
    fprintf(f_out, "время: %ld\n", sec_bin);
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
	
	
	
	fprintf(f_out,"Сортировки:\n                     Qsort               Бинарные\n");
    for (int i = len; i>0; i = i/2){
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
