#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define Yes 1
#define No  -1


void random_array(int len, int *array1, int *array2, int *array); //генерирование рандомного массива
void puz_sort(int *array1, int  len); //3.2 сортировка пузырьком
void mergeSort(int *array2, int left, int right);//сортировка слиянием
int test_upor(int *array, int len); //проверка упорядоченности массива
int comp(const void* i, const void* j);// вспомогательная функция для реализации qsort



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

//сортировка слиянием(снизу вверх)
void mergeSort(int *array2, int left, int right)
{
	int mid;
	int i;
	int j;
        int *new =NULL;

        if( left == right )
                return;
        mid = (left + right) / 2;
        mergeSort(array2, left, mid);
        mergeSort(array2, mid + 1, right);
        i = left; //начало для левой части
        j = mid + 1;//начало для правой части
        new = (int*)malloc((right * pow(2, 3))* sizeof(int));//выделяем память для нового массива
        for(int k = 0; k < right - left + 1; k++){
                if((j > right) || ((i <= mid) && (array2[i] < array2[j])))
                {
                        new[k] = array2[i];
                        i++;
                }
                else
                {
                        new[k] = array2[j];
                        j++;
                }
        }
        for (int k = 0; k < right - left + 1; k++)//записываем то что получилось в массив 
                array2[left + k] = new[k];
}




int test_upor(int *arr, int len) { 
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
 
                array1 = (int *) malloc((len * pow(2, 3)) * sizeof(int));//pow для того чтобы хватило памяти на каждое увеличение длины
                array2 = (int *) malloc((len * pow(2, 3)) * sizeof(int));
                array = (int *) malloc((len * pow(2, 3)) * sizeof(int));


                if (array1 == NULL) {
                        printf ("Ошибка с памятью array1\n");
                        return -1;
                }
                if (array2 == NULL) {
                        printf ("Ошибка с памятью array2\n");
                        return -1;
                }
                if (array == NULL) {
                        printf ("Ошибка с памятью array\n");
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
                        mergeSort(array2, 0, len - 1 );
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


