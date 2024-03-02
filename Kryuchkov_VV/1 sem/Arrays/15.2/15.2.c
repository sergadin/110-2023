#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void srot(double *arr, int len);

void sort(double *arr, int len)
{
    int t;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (arr[j] < 0)
            {
                if (arr[j+1] >= 0)
                {
                    t = arr[j+1];
                    arr[j+1] = arr[j];
                    arr[j] = t;
                }
            }
        }
    }
}

int main (void)
{
    FILE *f_in, *f_out;
    double *arr;
    int len;
    int cool = 0;

    f_in = fopen ("input.txt", "r");
    if (f_in == NULL)
    {
        printf ("err1\n");
        cool = -1;
    }

    f_out = fopen ("output.txt", "w");
    if (f_out == NULL)
    {
        printf ("err2\n");
        cool = -1;
        goto clean;
    }

    if (fscanf(f_in, "%d", &len)!= 1)
    {
        printf ("err3\n");
        cool = -1;
        goto clean_1;
    }

    arr = (double *)malloc(len*sizeof(double));
    if (arr == NULL)
    {
    printf ("err4\n");
    cool = -1;
    goto clean_2;
    }

    for (int i= 0; i < len; i++)
    {
        if (fscanf(f_in, "%lf", &arr[i])!= 1)
        {
            printf ("err5\n");
            cool = -1;
            goto clean_2;
        }
    }

    sort (arr, len);

    for (int i = 0; i < len; i++)
    {
        fprintf (f_out, "%lf ", arr[i]);
    }

    clean_2:

    free (arr);

    clean_1:

    fclose (f_out);

    clean:
    
    fclose (f_in);

    return cool;
}
