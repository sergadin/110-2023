#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Delete_Values (double *arr, int len);
int count = 0;

int Delete_Values (double *arr, int len)
{
    int k = 1;

    for (int i = 0; i < len; i++)
        if (arr[i] < 0)
            count++;

    for (int i = 0; i < len - 1; i++)
    {
        if (arr[i] >=  0)
            continue;
        while (arr[i + k] < 0)
        {
            if (i + k >= len)
            {
                return 1;
            }
            k++;
        }
        arr[i] = arr[i + k];
        arr[i + k] = -1;
        k = 1;
    }


    return 1;
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

        Delete_Values (arr, len);

    for (int i = 0; i < len - count; i++)
        fprintf (f_out, "%lf ", arr[i]);
    fprintf (f_out, "\n%d", len - count);

    clean_2:

    free (arr);

    clean_1:

    fclose (f_out);

    clean:
    
    fclose (f_in);

    return cool;
}
