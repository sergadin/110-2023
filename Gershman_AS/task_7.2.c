#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max_number_of_element(FILE* input, int* len, int** arr);
int max_number_of_element(FILE* input, int* len, int** arr)
{
    int qua_of_cur_el = 0, max_qua_of_cur_el = 0, max_el = 0;
    for (int i = 0; i < *len; i++) {
        for (int j = i + 1; j < *len; j++)
        {
            if (arr[i] == arr[j])
            {
                qua_of_cur_el++;
            }
        }
        if (max_qua_of_cur_el < qua_of_cur_el)
        {
            max_qua_of_cur_el = qua_of_cur_el;
            max_el = *arr[i];
        }
    }
    return max_el;
}
int main(void)
{
    FILE* input;
    int res;
    int len = 0;
    input = fopen("input.txt", "r");
    if (!input)
    {
        printf("cant open input file");
    }
    if (fscanf(input, "%d", &len) != 1)
    {
        printf("input file is empty");
        return 0;
    }
    int* arr = NULL;

    arr = (int*)malloc((len + 1) * sizeof(int));

    if (arr == NULL) {
        printf("memory allocation error");
        fclose(input);
        return 0;
    }
    int i = 0;
    while((fscanf(input, "%d", &arr[i]) == 1) && (i < len))
    {
        i++;
    }
    if (!feof(input))
    {
        printf("incorrect type of input data");
        free(arr);
        fclose(input);
        return 0;
    }
    if (i > len)
    {
        printf("nuber of elements is more then expected");
        free(arr);
        fclose(input);
        return 0;
    }
    res = max_number_of_element(input, &len, &arr);
    printf("%d", res);
    fclose(input);
    return 0;
}
