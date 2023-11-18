#include <stdio.h>
#include <math.h>


int quantity_elements_greater_previous(FILE* input);


int quantity_elements_greater_previous(FILE* input)
{
    double cur_number = 0, prev_number = 0;
    int cnt = 0;
    if (fscanf(input, "%lf", &prev_number) != 1)
    {
        return -1;
    }
    fscanf(input, "%lf", &prev_number);
    while (fscanf(input, "%lf", & cur_number) == 1)
    {
        if (cur_number < prev_number)
        {
            cnt ++;
        }
        prev_number = cur_number;
    }
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
    res = quantity_elements_greater_previous(input);
    if (res == -1)
    {
        printf("input file is empty");
    }
    if (res == -2)
    {
        printf("incorrect type of input data");
    }
    fprintf(output, "%d", res);
    fclose(input);
    fclose(output);
    return 0;
}
