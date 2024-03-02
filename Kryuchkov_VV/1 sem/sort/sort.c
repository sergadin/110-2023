#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define PROBLEM -1
#define NO_PROBLEM 0

int bubble (double *arr, int len); //Сортировка пузырьком
void sort_heap (double *arr, int len); //Пирамидальная сортировка
void swap_el (double *a, double *b);
void to_up (double *arr, int q);
void to_down (double *arr, int q);
int random_arr (double *arr, int len_n); //Создает массивы
int Check (double *arr, int len); // Проверка массива
int compar (const void *i, const void *j);
void sorting (double *arr, double *arr_copy, int len, FILE *f_out); //Конечная функция




int bubble (double *arr, int len)
{
    int t;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    return 0;
}

void sort_heap (double *arr, int len)
{
	for (int k = 1; k < len; k++)
    {
		to_up(arr, k);
	}
	for (int k = len - 1; k > 0; k--)
    {
		swap_el(arr, arr + k);
		to_down(arr, k);
	}
}

void swap_el (double *a, double *b)
{
    double t;
    t = *a;
    *a = *b;
    *b = t;
}

void to_up (double *arr, int k)
{
    int j;
    while (k > 0)
    {
        j = (k - 1) / 2;
        if (arr[k] > arr[j])
        {
            swap_el (arr + k, arr + j);
        }
        else 
        {
            break;
        }
        k = j;
    }
}

void to_down (double *arr, int k)
{
    int i, i1, i2;
    if (k < 2)
    {
        return;
    }
    for (i = 0; i < k; )
    {
        i1 = 2 * i + 1;
        i2 = i1 + 1;
        if (i1 >= k)
        {
            break;
        }
        if ((i2 < k) && (arr[i1] < arr[i2]))
        {
            i1 = i2;
        }
        if (arr[i] < arr [i1])
        {
            swap_el (arr + i, arr + i1);
            i = i1;
        }
        else 
        {
            break;
        }
    }
}

int random_arr (double *arr, int len_n)
{
    srand (time (NULL));
    for (int i = 0; i < len_n; i++)
    {
        arr[i] = rand();
    }
    return 0;
}

int Check (double *arr, int len)
{
    double last_el = arr[0];
    for (int i = 1; i <len; i++)
    {
        if (last_el > arr[i])
        {
            return PROBLEM;
        }
        last_el = arr[i];
    }
    return NO_PROBLEM;
}

int compare(const void* i, const void* j)
{
    return (*(double*)i - *(double*)j);
}

void sorting (double *arr, double *arr_copy, int len, FILE *f_out)
{
    double st_b, end_b, time_b, st_h, end_h, time_h, st_q, end_q, time_q;
    random_arr (arr, len);
    for (int i = 0; i < len; i++)
    {
        arr_copy[i] = arr[i];
    }
    st_b = clock();
    bubble (arr, len);
    end_b = clock();
    time_b = (double) (end_b - st_b);
    if (Check(arr, len) == PROBLEM)
    {
        printf("err5\n");
    }
    else
    {
        fprintf(f_out, "Длина массива: %d   время: %lf    ", len, time_b);
    }

    for (int i = 0; i < len; i++)
    {
        arr[i] = arr_copy[i];
    }
    st_h = clock();
    sort_heap (arr, len);
    end_h = clock();
    time_h = (double) (end_h - st_h);
    if (Check(arr, len) == PROBLEM)
    {
        printf("err5\n");
    }
    else
    {
        fprintf(f_out, "время: %lf    ", time_h);
    }

    for (int i = 0; i < len; i++)
    {
        arr[i] = arr_copy[i];
    }
    st_q = clock();
    qsort(arr, len, sizeof(double), compare);
    end_q = clock();
    time_q = (double) (end_q - st_q);
    if (Check(arr, len) == PROBLEM)
    {
        printf("err5\n");
    }
    else
    {
        fprintf(f_out, "время: %lf\n", time_q);
    }
}




int main (void)
{
    FILE *f_out;
    double *arr = NULL, *arr_copy = NULL;
    int len_n;

	printf("Введите максимальную длину случайного массива: \n");
	if (scanf("%d", & len_n)!=1)
    {
        printf("err1\n");
		return -1;
	}

    f_out = fopen ("output.txt", "w");
    if (f_out == NULL)
    {
        printf ("err2\n");
        return -1;
    }

    arr = (double*)malloc(len_n*sizeof(double));
    if (arr == NULL)
    {
	    printf("err3\n");
    	fclose (f_out);
        return -1;
    }
    if (random_arr (arr, len_n) == -1)
    {
        free (arr);
        fclose (f_out);
    }
    arr_copy = (double*)malloc(len_n*sizeof(double));
    if (arr_copy == NULL)
    {
        printf("err4\n");
        free (arr);
        fclose (f_out);
    }
    fprintf (f_out, "Сортировки:\n                       Пузырек                  Пирамида                 Быстрая\n ");
    for (int i = len_n; i > 0; i = i / 2)
    {
        sorting (arr, arr_copy, i, f_out);
    }

    printf ("Ответ получен\n");
    free (arr_copy);
    free (arr);
    fclose (f_out);

return 0;
}