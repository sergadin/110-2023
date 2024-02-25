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
                return 1;
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
    int len;
    float check;
    float Q;
    double *arr = NULL;
    FILE *f_in, *f_out;

    f_in = fopen ("input.txt", "r");
    if (f_in == NULL)
    {
        printf ("err1\n");
        return -1;
    }

    f_out = fopen ("output.txt", "w");
    if (f_out == NULL)
    {
        ("err2\n");
        return -1;
    }

    if (fscanf (f_in, "%f", &check) != 1)
    {
        printf ("err3\n");
        fclose (f_in);
        fclose (f_out);
        return -1;
    }

    if (0 > check)
    {
        printf ("err4\n");
        fclose (f_in);
        fclose (f_out);
        return -1;
    }

    len = check;

    if (len < check)
    {
        printf ("err5\n");
        fclose (f_in);
        fclose (f_out);
        return -1;
    }

    arr = (double *) malloc ((len) * sizeof (double));

    if (arr == NULL)
    {
        printf ("err6\n");
        fclose (f_in);
        fclose (f_out);
        return -1;
    }

    for (int i = 0; i < len; i++)
    {
        if (fscanf (f_in, "%lf", &arr[i]) != 1)
        {
            printf ("err7\n");
            free (arr);
            fclose (f_in);
            fclose (f_out);
            return -1;
        }
    }

    while (!feof (f_in))
        if (fscanf (f_in, "%f", &Q) != -1)
        {
            printf ("err8\n");
            return -1;
        }


    Delete_Values (arr, len);

    for (int i = 0; i < len - count; i++)
        fprintf (f_out, "%lf ", arr[i]);
    fprintf (f_out, "\n%d", len - count);
    free (arr);
    fclose (f_in);
    fclose (f_out);
    return 0;
}
