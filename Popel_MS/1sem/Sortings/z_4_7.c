#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Corr_ord 0
#define Uncorr_ord -1
#define Memory_err -2

void heap_sort(double *arr, int len);
void go_up(double *arr, int k);
void go_down(double *arr, int k);
void swap(double *a, double *b);
int compare(const void* i, const void* j);
void sorting_comparing(double *arr, double *arr_copy, int len, FILE * f_out);



int sort_insert(double *arr, int len); //Функция сортирует массив методом вставок в неубывающем порядке.
					//Также замеряется время работы этой функции, и оно же выводится на экран при успешном завершении программы.
int ordered_seq(double *arr, int len); //Функция проверяет итоговый массив на упорядоченность.
int random_array(double *arr, int len_n);//Функция записывает массив случайных действительных значений 
                                               //(размер этого массива считывается с клавиатуры.)
int compare(const void* i, const void* j){
    return (*(double*)i - *(double*)j);
    
}

int sort_insert( double *arr, int len){
	double ins_val = 0.;
    int j=0;
	 
	for (int i = 0; i< len-1; i++){
		
		ins_val = arr[i+1];
		j = i;

		while ((j >= 0) && (arr[j] > ins_val)){
			
			arr[j+1] = arr[j];
			j--;
		}
		
		arr[j+1] = ins_val;
	}
	
	return 0;
}

void swap(double *a, double *b){
	double c = *a;
	*a = *b;
	*b = c;
}

void go_up(double *arr, int k){
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
void go_down(double *arr, int k){
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
void heap_sort(double *arr, int len){
	int k;
	for (k = 1; k < len; k++){
		go_up(arr, k);
	}
	for (k = len - 1; k > 0; k--){
		swap(arr, arr+k);
		go_down(arr, k);
	}
}


int ordered_seq(double *arr, int len){
	double last_val = arr[0];
	for (int i = 1; i < len; i++){
		if (last_val > arr[i]){
			return Uncorr_ord;
		}
		last_val = arr[i];
	}
	return Corr_ord;
}

int random_array(double *arr, int len_n){
	
	srand(time(NULL));
	
	for (int i=0; i < len_n; i++){
		arr[i] = rand()*0.01;
	}
	return 0;
}

void sorting_comparing(double *arr, double *arr_copy, int len, FILE * f_out){
    double st_heap, end_heap, sec_heap, st_ins, end_ins, sec_ins, st_q, end_q, sec_q;
	random_array(arr, len);
	for (int i =0; i<len; i++){
        arr_copy[i] = arr[i];
    }
    
    st_q = clock();
    qsort(arr, len, sizeof(double), compare);
    end_q = clock();
    sec_q = (double)(end_q-st_q);
    //if (ordered_seq(arr, len) == Uncorr_ord){
        //printf("Не отсoртировано\n");
    //}
    //else{
        fprintf(f_out, "Длина массива: %d   время: %lf    ", len, sec_q);
   // }
    
    for (int i = 0; i<len; i++){
        arr[i] = arr_copy[i];
    }
    
    st_ins = clock();
    sort_insert(arr, len);
    end_ins = clock();
    sec_ins = (double)(end_ins-st_ins);
    //if (ordered_seq(arr, len) == Uncorr_ord){
     //   printf("Не отсoртировано\n");
    //}
    //else{
        fprintf(f_out, "время: %lf    ", sec_ins);
    //}
    
    for (int i = 0; i<len; i++){
        arr[i] = arr_copy[i];
    }
    
    st_heap = clock();
    heap_sort(arr, len);
    end_heap = clock();
    sec_heap = (double)(end_heap-st_heap);
    //if (ordered_seq(arr, len) == Uncorr_ord){
        //printf("Не отсoртировано\n");
    //}
   // else{
        fprintf(f_out, "время: %lf\n", sec_heap);
    //}
}

int main(void){
	double *Array_rand = NULL, *arr_copy = NULL;
	FILE *f_out; 
	int len_n, main_return_code = 0;
	
	
	printf("Введите максимальную длину случайного массива: \n");
	if (scanf("%d", & len_n)!=1){
        printf("Вы ввели некорректные значения\n");
		return -1;
	}
	
	
	f_out = fopen("output.txt", "w");
	
	if (f_out == NULL){
	
		printf("Файл не открывается\n");
		return -1;
	}
	
	

	
	Array_rand = (double *)malloc(len_n*sizeof(double));
	if (Array_rand == NULL){
		printf("Оперативная память не выделена\n");
		goto terminate;
	}
	
	if (random_array( Array_rand, len_n) == -1){
		goto terminate_1;	
	}
	
    arr_copy = (double *)malloc(len_n*sizeof(double));
	if (arr_copy == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
	}
	fprintf(f_out,"Сортировки:\n                     Qsort               Вставки              Пирамидальная\n");
    for (int i = len_n; i>0; i=i/2){
        sorting_comparing(Array_rand, arr_copy, i, f_out);
    }
	
	
	printf("Ответ выведен в файл output.txt\n");
	
    
    terminate_1:

	free(Array_rand);
	
	
	terminate:
	fclose(f_out);

	return main_return_code;
}
