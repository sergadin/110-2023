#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void x_interval(int len, int x, int* arr);
void x_interval(int len, int x, int* arr)
{

    for (int i = 0; i < len; i++)
    {
        int right_border = 0;
        int left_border = 0;
        if (arr[i] == x)
        {
            int count = 0;
            if (i != 0)
            {
                left_border = arr[i-1];
            }
            while (arr[i + count] == x && i + count < len)
            {
                count++;
            }
            if (i + count != len)
            {
                right_border = arr[i + count];
            }
            for(int j = i; j < i + count; j++)
            {
                arr[j] = (right_border + left_border) / 2;
            }
            i += count - 1;
        }
    }
}
int main(void)
{
    FILE* input;
    int len = 0;
    int x = 0;
    int* arr = NULL;
    input = fopen("input.txt", "r");
    if (!input)
    {
        printf("cant open input file");
        goto A;
    }
    if (fscanf(input, "%d", &len) != 1)
    {
        printf("input file is empty");
        return 0;
    }
    fscanf(input, "%d", &x);
    arr = (int*)malloc((len) * sizeof(int));
    if (arr == NULL) {
        printf("memory allocation error");
        fclose(input);
        return 0;
    }

    for(int i = 0; i < len; i++)
    {
        fscanf(input, "%d", &arr[i]);
    }
    x_interval(len, x, arr);
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    fclose(input);
    free(arr);
    A:
    return 0;
}
