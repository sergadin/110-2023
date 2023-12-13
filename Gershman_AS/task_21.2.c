#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void put_elements_with_even_index_in_front(int len, int* arr);
void put_elements_with_even_index_in_front(int len, int* arr)
{
    for(int i = 0; i <= (len - 1) / 2; i++)
    {
        for(int j = 2 * i; j > i; j--)
        {
            int a = 0;
            a = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = a;
        }
    }
}

int main(void)
{
    FILE* input;
    int len = 0;
    int* arr = NULL;
    input = fopen("input.txt", "r");
    if (!input)
    {
        printf("cant open input file\n");
        goto A;
    }
    if (fscanf(input, "%d", &len) != 1)
    {
        printf("input file is empty\n");
        return 0;
    }
   
    arr = (int*)malloc((len) * sizeof(int));
    if (arr == NULL) {
        printf("memory allocation error\n");
        fclose(input);
        return 0;
    }

    for(int i = 0; i < len; i++)
    {
        fscanf(input, "%d", &arr[i]);
    }
    put_elements_with_even_index_in_front(len, arr);
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    free(arr);
    fclose(input);
    A:
    return 0;
}