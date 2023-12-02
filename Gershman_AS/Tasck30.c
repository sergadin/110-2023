#include <stdio.h>
#include <math.h>
int max_number_of_element(FILE* input);
int deriv_and_polinom(FILE* input)
{
    int len;
    int qua_of_cur_el = 0, max_qua_of_cur_el = 0, max_el = 0;
    if (fscanf(input, "%d", &len))
    {
        return -1;
    }
    int arr[len];
    int i = 0;
    while (fscanf(input, "%d", &arr[i]) && i < len)
    {
        i++;
    }
    if (!feof);
    {
        return -2;
    }
    if (i == len)
    {
        return -3;
    }
    for(int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] == arr[j])
            {
                qua_of_cur_el ++;
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
    input = fopen("input.txt", "r");
    if (!input)
    {
        printf("cant open input file");
    }
    res = max_number_of_element(input);
    if (res == -1)
    {
        printf("input file is empty");
    }
    if (res == -2)
    {
        printf("incorrect type of input data");
    }
    if (res == -3)
    {
        printf("nuber of elements is more then expected");
    }
    else
    {
        printf("%d", res);
    }
    fclose(input);
    return 0;
}
