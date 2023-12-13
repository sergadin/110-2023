#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max_number_of_element(int len, int* arr);
int max_number_of_element(int len, int* arr)
{
    int qua_of_cur_el = 0, max_qua_of_cur_el = 0, max_el = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] == arr[j])
            {
                qua_of_cur_el++;
            }
        }
        if (max_qua_of_cur_el < qua_of_cur_el)
        {
            max_qua_of_cur_el = qua_of_cur_el;
            max_el = arr[i];
        }
    }
    return max_el;
}


int main(void)
{
    FILE* input;
    int res;
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
    res = max_number_of_element(len, arr);
    printf("%d\n", res);
    free(arr);
    fclose(input);
    A:
    return 0;
}
