#include <stdio.h>
#include <math.h>


int quantity__constant_elements(FILE* input);


int quantity__constant_elements(FILE* input)
{
    int cur_number = 0, prev_number = 0;
    int cnt = 0, flag = 0;
    if (fscanf(input, "%d", &prev_number) != 1)
    {
        return -1;
    }
    while (fscanf(input, "%d", &cur_number) == 1)
    {
        if (cur_number == prev_number)
        {
            cnt++;
            flag = 1;
        }
        else
        {
            cnt += flag;
            flag = 0;
        }
        prev_number = cur_number;
    }
    cnt += flag;
    if (!feof(input))
    {
        return -2;
    }
    return cnt;

}


int main(void)
{
    FILE* input, * output;
    int res;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (!input)
    {
        printf("cant open input file");
    }
    res = quantity__constant_elements(input);
    if (res == -1)
    {
        printf("input file is empty");
    }
    if (res == -2)
    {
        printf("incorrect type of input data");
    }
    else
        fprintf(output, "%d", res);
    fclose(input);
    fclose(output);
    return 0;
}
