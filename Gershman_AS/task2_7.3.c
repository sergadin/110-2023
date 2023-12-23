#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double bubble_sort(int* a, int len);
void heapify(int* a, int len, int i);
double heap_sort(int* a, int len);
void create_arr(int* a, int len);
void result(int* a,int len);
int compare(const void * a1, const void * a2);


int compare(const void * a1, const void * a2)  
{
  return ( a1 - a2 );              
}


void create_arr(int* a, int len)
{
    for(int i = 0; i < len; i++)
    {
        a[i] = rand() % 100;
    }
}


double bubble_sort(int* a, int len)
{
    int start = clock(), stop;
    for(int i = 0; i < len; i++)
    {
        for(int j = i; j < len; j++)
        {
            if(a[i] > a[j])
            {
                int t = 0;
                t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
    stop = clock();
    return ((double)stop - (double)start) / CLOCKS_PER_SEC;
}


void heapify(int* a, int len, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < len && a[left] > a[largest])
    {
        largest = left;
    }
    if (right < len && a[right] > a[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        int t;
        t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        heapify(a, len, largest);
    }
}


double heap_sort(int* a, int len)
{
    int start = clock(), stop;
    for(int i = len / 2 - 1; i >= 0; i--)
    {
        heapify(a, len, i);
    }
    for(int i = len - 1; i >= 0; i--)
    {
        int t = 0;
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        heapify(a, i, 0);
    }
    stop = clock();
    return ((double)stop - (double)start) / CLOCKS_PER_SEC;
}


void result(int* a, int len)
{
    double bubble_time = bubble_sort(a, len);
    double heap_time = heap_sort(a, len);
    double qsort_time;
    int start = clock(), stop;
    qsort(a, len, sizeof(int), compare);
    stop = clock();
    qsort_time = ((double)stop - (double)start) / CLOCKS_PER_SEC;
    printf("bubble sort time %lf sec\nheap sort time %lf sec\nqsort time %lf sec", bubble_time, heap_time, qsort_time);
}


int main(void)
{
    int len = 0;
    double s, d;
    int* arr1 = NULL,* arr2 = NULL,* arr3 = NULL;
    if (scanf("%d", &len) != 1)
    {
        printf("incorrect len\n");
        return 0;
    }
   
    arr1 = (int*)malloc((len) * sizeof(int));
    if (arr1 == NULL) {
        printf("memory allocation error\n");
        return 0;
    }
    arr2 = (int*)malloc((len * 2) * sizeof(int));
    if (arr2 == NULL) {
        printf("memory allocation error\n");
        return 0;
    }
    arr3 = (int*)malloc((len * 4) * sizeof(int));
    if (arr3 == NULL) {
        printf("memory allocation error\n");
        return 0;
    }
    create_arr(arr1, len);
    result(arr1, len);
    printf("\n%d\n", len * 2);
    create_arr(arr2, 2 * len);
    result(arr2, len * 2);
    printf("\n%d\n", len * 4);
    create_arr(arr3, 4 * len);
    result(arr3, len * 4);
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}