#include <stdio.h>
#include <math.h>
#define Reading_err -1

int max_dev(FILE *f);

int max_dev(FILE *f)
{
    double min_el;
    double max_el;
    int first_check = 1;
    int count = 0;
    double curr;
    double summ;
    double aver;
    double MAX_DEV;

    while (fscanf(f, "%lf", &curr) == 1)
    {
        if (first_check == 1)
        {
            first_check = 0;
            min_el = curr;
            max_el = curr;
            summ = 0;
            count = 0;
        }

        summ += curr;

        if (min_el > curr)
        {
            min_el = curr;
        }

        if (max_el < curr)
        {
            max_el = curr;
        }

        count += 1;
    }

    aver = summ / count;

    if (aver - max_el <= aver - min_el)
    {
        MAX_DEV = aver - min_el;
    }

    if (aver - max_el > aver - min_el)
    {
        MAX_DEV = aver - max_el;
    }
    if (!feof(f))
    {
        printf ("reading error\n");
        return Reading_err;
    }
    return MAX_DEV;
}

int main (void)
{
    FILE *f_in, *f_out;
    int MAX_DEV;
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

    MAX_DEV = max_dev(f_in);
        if (MAX_DEV == Reading_err)
    {
        fclose(f_in);
        fclose(f_out);
        return -1;  
    }

    fprintf(f_out, "Величина максимального отклонения = %d\n", MAX_DEV);
    fclose(f_in);
    fclose(f_out);
    return 0;
}
