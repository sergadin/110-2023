//3.2 Сортировка пузырьком (медленная)
  //3.5 Сортировка слиянием (быстрая)
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define Yes 1
#define No  -1


void random_array(int len, int *array1, int *array2, int *array); //генерирование рандомного массива
void puz_sort(int *array1, int len); //3.2 сортировка пузырьком
void merge(int *array2, int l, int m, int r);  //3.5 сортировка слиянием
int test_upor(int *array, int len); //проверка упорядоченности массива
int comp(const void* i, const void* j); 
static void MergeSort(int *array2, int l, int r);//

//генерирование рандомного массива:
void random_array(int len, int *array1, int *array2, int *array) {
	int r;
	for(int i = 0; i < len; i++){
		r = rand()% 1000;		 
		array1[i] = r;
		array2[i] = r;
		array[i] = r;
	}
}

//медленная сортировка пузырьком:

void puz_sort(int *array1, int len) {
       int c;
       for(int i = 0; i < len - 1; i++){ //индексация с 0, поэтому -1
	       for(int j = 0; j < len - i - 1; j++){
		       if(array1[j] > array1[j + 1]) {
			       c = array1[j];
			       array1[j] = array1[j + 1];
			       array1[j + 1] = c;
		       }
	       }
       }
}


//сортировка слиянием
void merge(int *array2, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int Left[n1], Right[n2];

    for (int i = 0; i < n1; i++)
        Left[i] = array2[l + i];
    for (int j = 0; j < n2; j++)
        Right[j] = array2[m + 1 + j];
    
  
    int i, j, k;
    i = 0; 
    j = 0; 
    k = 0; 

    while (i < n1 && j < n2)
    {
        if (Left[i] <= Right[j])
        {
            array2[k] = Left[i];
            i++;

        }
        else
        {
            array2[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < n1)//выбираем оставшиеся элементы
    {
        array2[k] = Left[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        array2[k] = Right[j];
        j++;
        k++;
    }
}

static void MergeSort(int *array2, int l, int r){
	int q;

	if(l < r)
	{
		q = (1 + r)/2;
		MergeSort(array2, l, q);
		MergeSort(array2, q + 1, r);
		merge(array2, l, q, r);//слияние
}
}

// проверка упорядоченности:
int test_upor(int *arr, int len) { // возвращает Yas, если массив отсортирован, и No в противном случае
	int k = Yes;
	for (int i = 0; i < len - 1; i++) {
		if (arr[i+1] < arr[i]) {
			k = No;
		}
	}
	return k;
}

// для qsort:
int comp(const void* i, const void* j)
{
	return (*(int*)i - *(int*)j);
}



int main(void) {
	int len;  // длина массива
	int test_1, test_2; // для проверки массива на упорядоченность
	clock_t start_1, start_2, start_3, fin_1, fin_2, fin_3; // для подсчета времени работы сортировок
	double time_1, time_2, time_3; // для подсчета времени работы сортировок
	int *array1 = NULL; // для сортировки пузырьком
	int *array2 = NULL; // для сортировки слиянием
	int *array = NULL; // сортировка с помощью функции qsort
	
	printf("введите длину массива : len = \n"); 
	if ((scanf ("%d", &len) != 1) || (len < 1)) {
		printf ("некорректная длина\n");
		return -1;
	}
	
	array1 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	array2 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	array = (int *) malloc((len * pow(2, 3)) * sizeof(int));
	
	if (array1 == NULL) {
		printf ("Memory error array1\n");
		return -1;
	}
	if (array2 == NULL) {
		printf ("Memory error array2\n");
		return -1;
	}
	if (array == NULL) {
		printf ("Memory error array\n");
		return -1;
	}
	
	for (int i = 0; i < 4; i++) { //цикл для просмотра разных длин рандомных массивов
		//заполнение массивов случайными целыми числами:
		random_array(len, array1, array2, array);
		
		//выполняем сортировку пузырьком:
		start_1 = clock();
		puz_sort(array1, len);
		fin_1 = clock();
		
		//выполняем сортировку слиянием:
		start_2 = clock();
	        merge(array2, 0, (i-1)/2, i-1); 
		fin_2 = clock();
		
		//выполняем qsort:
		start_3 = clock();
		qsort(array, len, sizeof(int), comp);
		fin_3 = clock();
		
		//записываем полученное время в типе double:
		time_1 = (double)(fin_1 - start_1)/CLOCKS_PER_SEC;
		time_2 = (double)(fin_2 - start_2)/CLOCKS_PER_SEC;
		time_3 = (double)(fin_3 - start_3)/CLOCKS_PER_SEC;
		
		//проверка массивов на упорядоченность:
		test_1 = test_upor(array1, len);
		test_2 = test_upor(array2, len);
		
		//вывод:
		if (test_1 == No) {
			//медленная сортировка пузырьком неккоректна при длине:
			printf("сортировка пузырьком некорректная длина: %d \n", len);
		}
		else {
			//время медленной сортировки пузырьком:   при длине:
			printf("время сортировки пузырьком: %lf    pri len: %d \n", time_1, len);
		}
		
		if (test_2 == No) {
			// сортировка слиянием неккоректна при длине:
			printf("сортировка слиянием не корректна при длине: %d \n", len);
		}
		else { 
			//время сортировки слиянием:    при длине:
			printf("время сортировки слиянием: %lf    pri len: %d \n", time_2, len);

		}
		//время функции qsort:
		printf("время qsort: %lf\n", time_3);
		printf("\n");

		len = len * 2;
	}
    
    free(array1);
	free(array2);
	free(array);

	return 0;
}
