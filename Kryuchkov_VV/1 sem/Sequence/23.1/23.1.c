#include <stdio.h>
#include <math.h>
#define Reading_err -1

int max_zna_sum(FILE *f);


int max_zna_sum(FILE *f)
{
    int max_sum;
    int summ = 0;
    int last_el;
    int rise;
    int curr;
    
    if (fscanf(f, "%d", &curr)!=1)
    {
        printf("reading error 1\n");
        return -1;
    }
    last_el = curr;
    summ = curr;
    while ((fscanf(f, "%d", & curr)== 1 ) && (curr >= last_el))
    {
        summ += curr;
        last_el = curr;
    }
    last_el = curr;
    max_sum = summ;
    summ = curr;
    while (fscanf(f,"%d", & curr) == 1)
    {
        if (curr >= last_el)
        {
            summ += curr;
            if (rise == 0)
            {
                summ += last_el;
            }
            rise = 1;
        }
        if (curr < last_el)
        {
            if(max_sum < summ)
            {
                max_sum = summ;
            }
            summ = 0;
            rise = 0;
        }
        last_el = curr;
    }
    
    if (max_sum < summ)
    {
        max_sum = summ;
    }
    return max_sum;
}

int main (void)
{
    FILE *f_in, *f_out;
    int max_sum;

    f_in = fopen ("input.txt", "r");
    if (f_in == NULL)
    {
        printf ("err1\n");
        return -1;
    }

    f_out = fopen("output.txt", "w");
    if (f_out == NULL)
    {
        printf("err2\n");
        fclose(f_in);
        return -1;
    }

    max_sum = max_zna_sum(f_in);
    if (max_sum == Reading_err)
    {
        fclose(f_in);
        fclose(f_out);
        return -1;
    }

    fprintf(f_out, "Максимальная сумма возрастающей последовательности = %d\n", max_sum);
    fclose(f_in);
    fclose(f_out);
    return 0;
}