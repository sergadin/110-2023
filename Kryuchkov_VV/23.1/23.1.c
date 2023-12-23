#include <stdio.h>
#include <math.h>
#define Reading_err -1

int max_zna_sum(FILE *f);


int max_zna_sum(FILE *f)
{
    double max_sum = 0.;
    double summa = 0.;
    double last_el;
    double first_el;
    int rise = 0;
    double curr;
    
    if (fscanf(f, "%lf", &curr)!=1)
    {
        printf("reading error 1\n");
        return -1;
    }
    last_el = curr;
    first_el = last_el;
    while (fscanf(f,"%lf", & curr)== 1)
    {
        if (curr > last_el)
        {
        rise = 1;
        summa += last_el;
        }
        else if (rise == 1 && (curr <= last_el))
        {
            rise = 0;
            summa += last_el;
            if (max_sum < summa)
            {
                max_sum = summa;
            }
            summa = 0;
        }
        last_el = curr;
    }
    if (rise == 1)
    {
        summa += curr;
        if (max_sum < summa)
        {
            max_sum = summa;
        }
    }
    if (!feof(f))
    {
        printf("reading error\n");
        return Reading_err;
    }
    if (max_sum == 0)
    {
        return first_el;
    }
    return max_sum;
    

}

int main (void)
{
    FILE *f_in, *f_out;
    double max_sum;

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

    fprintf(f_out, "Максимальная сумма возрастающей последовательности = %lf\n", max_sum);
    fclose(f_in);
    fclose(f_out);
    return 0;
}