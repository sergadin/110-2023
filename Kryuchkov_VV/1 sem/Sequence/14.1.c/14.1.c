#include <stdio.h>
#include <math.h>
#define Reading_err -1

int min_counter(FILE *f);


int min_counter(FILE *f)
{
    double min_el;
    int first_check = 1;
    int count = 1;
    double curr;

    while (fscanf(f, "%lf", &curr) == 1)
    {
        if (first_check == 1)
        {
            first_check = 0;
            min_el = curr;
        }

        else if (min_el > curr)
        {
            min_el = curr;
            count = 1;
        }

        else if (min_el == curr)
        {
            count+=1;
        }
    }
    if (!feof(f))
    {
        printf ("reading error\n");
        return Reading_err;
    }
    return count;
}


int main (void)
{
    FILE *f_in, *f_out;
    int count;
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

    count = min_counter(f_in);
    if (count == Reading_err)
    {
        fclose(f_in);
        fclose(f_out);
        return -1;
    }

    fprintf(f_out, "Количество минимальных элементов = %d\n", count);
    fclose(f_in);
    fclose(f_out);
    return 0;
}