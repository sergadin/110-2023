#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Corr_ord 0
#define Uncorr_ord -1

void heap_sort(double *arr, int n);
int ordered_seq(double *arr, int len);
int random_array(double *arr, int len_n);
void go_up(double *arr, int k);
void go_down(double *arr, int n);
void swap(double *a, double *b);

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
void go_down(double *arr, int n){ 
	int i, i1, i2;
	if (n < 2) {
		return;
	}
	for (i = 0; i < n; ) {
		i1 = 2 * i + 1;
		i2 = i1 + 1;
		if (i1 >= n) {
			break;
		}
		if ((i2 < n) && (arr[i1] < arr[i2])) {
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
void heap_sort(double *arr, int n){
	int k;
	for (k = 1; k < n; k++){
		go_up(arr, k);
	}
	for (k = n - 1; k > 0; k--){
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
	for (int i = 0; i < len_n; i++){
		arr[i] = rand()*(0.00001);
	}
	return 0;
}

int main(void){
	char input[50];
	int N = 0;
	clock_t start, end;
	double *Array1 = NULL, *Array_rand = NULL, seconds;
	FILE *f_in, *f_out; 
	int len = 0, order1 = 0, order2 = 0, len_n, main_return_code = 0;
	
	printf("Введите имя входного файла: \n");
	scanf("%s" , input);
	
	printf("Введите длину случайного массива: \n");
	scanf("%d", & len_n);
	
	f_in = fopen(input , "r");
	
	if (f_in == NULL){
		printf("Файл не открывается\n");
		return -1;
	}
	
	f_out = fopen("output.txt", "w");
	
	if (f_out == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;
	}
	
	if (fscanf(f_in, "%d", & len) != 1){
		printf("Файл пуст\n");
		main_return_code = -1;
		goto terminate;
		
	}
	
	Array1 = (double *)malloc(len*sizeof(double));
	if (Array1 == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
	}

	
	for (int i = 0; i < len; ++i){
		if (fscanf(f_in, "%lf", &Array1[i]) != 1){
			printf("В файле недостаточно значений\n");
			main_return_code = -1;
			goto terminate_1;
		}
	}
	
	start = clock();
	heap_sort( Array1, len);
	end = clock();
	seconds = (double)(end-start);
	order1 = ordered_seq(Array1, len);
	
	Array_rand = (double *)malloc(len_n*sizeof(double));
	if (Array_rand == NULL){
		printf("Оперативная память не выделена\n");
		goto terminate_1;
	}
	
	if (random_array( Array_rand, len_n) == -1){
		goto terminate_1;	
	}
	
	heap_sort(Array_rand, len_n);
	
	order2 = ordered_seq(Array_rand, len_n);
	
	
	
	if ((order1 == Uncorr_ord) || (order2 == Uncorr_ord)){
		printf("Последоватеьлности не упорядочены\n");
		goto terminate_2;
	}else{
		printf("Последоватеьлности упорядочены по неубыванию\n");
	}
	
	for (int i = 0; i < len; i++){
		fprintf(f_out, "%lf\n", Array1[i]);
	}
	fprintf(f_out, "%s\n", "\nRandom\n");
	for (int i = 0; i < len_n; i++){
		fprintf(f_out, "%lf\n", Array_rand[i]);
	}
	
	
	printf("Ответ выведен в файл output.txt\n");
	printf("Время выполнения алгоритма: %lf\n", seconds);
	
	terminate_2:
	
	free(Array_rand);
		
	terminate_1:

	free(Array1);
	
	terminate:
	
	fclose(f_in);
	fclose(f_out);
	return main_return_code;
}
