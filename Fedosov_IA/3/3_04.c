#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void insertion_sort(int *array, int len); 			//сортировка вставками

int check_for_order(int *array, int len);			//проверка массива на упорядоченность

int* generate_random_massive(int len);				//создание случайного массива указанной длины

void compare_algorithms(int* array_1, int* array_2, int* array_3, int len);	//сравнение скорости работы алгоритмов

int* copy_array(int* array, int len);				//создание копии массива

int compare(const void *a, const void *b);			//вспомогательная функция для qsort

int getBit(int num, int pos);					//функция для получения значения бита на данной позиции

void radixSortByBits(int* arr, int n, int numBits);		//поразрядная сортировка


int main(void){
	int rand_len;
	int* rand_array_1;
	int* rand_array_2;
	int* rand_array_3;

	if (scanf("%d", &rand_len) != 1) {
		printf("неверные входные данные\n");
		return -1;
	}
	
	if (rand_len <= 0) { 
		printf("неврные входные данные\n");
		return -1;
	}
    	
	
	rand_array_1 = generate_random_massive(rand_len);
	rand_array_2 = copy_array(rand_array_1, rand_len);
	rand_array_3 = copy_array(rand_array_1, rand_len);
	
	compare_algorithms(rand_array_1, rand_array_2, rand_array_3, rand_len);
	
	free(rand_array_1);
	free(rand_array_2);
	free(rand_array_3);
	
	return 0;
	
	
}


void insertion_sort(int *array, int len){
	int sort_value, j;

	for (int i = 1; i < len; i++){
		sort_value = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > sort_value){
			array[j + 1] = array[j];
	 		j -= 1;
		}

		array[j + 1] = sort_value;
	}
}


int check_for_order(int *array, int len){
	int counter = 0;

	if (len == 1) {
		return 0;
	}

	for (int i = 0; i < len - 1; i++){
		if (array[i] <= array[i + 1]){
			counter++;
		}
	}

	if (counter == len - 1){
		return 0;
	} else {
		return -1;
	}
}

int* generate_random_massive(int len){
	int* rand_array_1 = (int*)malloc(len * sizeof(int));
    	
    	srand(time(NULL));

    	for (int i = 0; i < len; i++) {
        	rand_array_1[i] = rand() % 1000000;  // Генерация случайного числа от 0 до 1000000
    	}	

    	return rand_array_1;
}	
	
	
int* copy_array(int* array, int len){
	int* copied_array = (int*)malloc(len * sizeof(int));
	
	for(int i = 0; i < len; i++) {
		copied_array[i] = array[i];
	}
	
	return copied_array;
}	
	

void compare_algorithms(int* array_1, int* array_2, int* array_3, int len){
	clock_t start, end;
    	double cpu_time_used;
    	int flag;
 
    	// Измерение времени для сортировки вставками
    	start = clock();
    	insertion_sort(array_1, len);
    	end = clock();
    	flag = check_for_order(array_1, len);
    	if (flag == -1) {
    		printf("массив не отсортирован");
    		return;
    	}
    	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    	printf("Время выполнения сортировки вставками: %f сек\n", cpu_time_used);

    	// Измерение времени для сортировки быстрой
    	start = clock();
    	qsort(array_2, len, sizeof(int), compare);
    	end = clock();
    	flag = check_for_order(array_2, len);
    	if (flag == -1) {
    		printf("массив не отсортирован");
    		return;
    	}
    	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    	printf("Время выполнения быстрой сортировки: %f сек\n", cpu_time_used);
   	
   	// Измерение времени для radix sort
    	start = clock();
    	radixSortByBits(array_3, len, 32);
    	end = clock();
    	flag = check_for_order(array_3, len);
    	if (flag == -1) {
    		printf("массив не отсортирован");
    		return;
    	}
    	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    	printf("Время выполнения поразрядной сортировки %f сек\n", cpu_time_used);
}



int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int getBit(int num, int pos) {
    return (num >> pos) & 1;
}


void radixSortByBits(int* arr, int n, int numBits) {
    const int BASE = 2; // Основание системы счисления (0 и 1)

    for (int bitPos = 0; bitPos < numBits; bitPos++) {
        int output[n];
        int count[2] = {0};

        for (int i = 0; i < n; i++) {
            count[getBit(arr[i], bitPos)]++;
        }

        for (int i = 1; i < BASE; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[getBit(arr[i], bitPos)] - 1] = arr[i];
            count[getBit(arr[i], bitPos)]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}









