#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int* arr, int len);
int func(int* arr, int len);

void sort(int* arr, int len)
{
    int i, j, t;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

int func(int* arr, int len)
{
    int a, i;
    a = arr[0];
    for (i = 0; i < len; i++) {
        if (arr[i] != a)
        {
            return 0;
        }
        a++;
    }
    return 1;
}

int main(void)
{
    FILE* inp;
    int len, i, check;
    int* arr;

    inp = fopen("input.txt", "r");

    if (inp == NULL)
    {
        printf("No input file");
        return -1;
    }
    if (fscanf(inp, "%d", &len) != 1)
    {
        printf("Error reading the file");
        fclose(inp);
        return -1;
    }

    arr = (int*)malloc(len * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation error");
        fclose(inp);
        return -1;
    }

    for (i = 0; i < len; i++)
    {
        fscanf(inp, "%int", &arr[i]);
    }

    sort(arr, len);

    check = func(arr, len);

    if (check == 1)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    fclose(inp);
    free(arr);
    return 0;
}