#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max_count_number(int *arr, int len);


int max_count_number(int *arr, int len)
{
    int maxcount = 0;
    int max_count_number = arr[0];

    for (int i = 0; i < len; i++)
    {
        int count = 0;

        for (int j = 0; j < len; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }
        if (count > maxcount)
        {
            maxcount = count;
            max_count_number = arr[i];
        }
    }

    return max_count_number;
}

int main (void)
{
    FILE *f_in, *f_out;
    int *arr;
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
        fclose (f_in);
        cool = -1;
    }

    if (fscanf(f_in, "%d", &len)!= 1)
    {
        printf ("err3\n");
        fclose(f_in);
        cool = -1;
        goto clean;
    }

    arr = (int *)malloc(len*sizeof(int));
    if (arr == NULL)
    {
    printf ("err4\n");
    cool = -1;
    goto clean_1;
    }

    for (int i= 0; i < len; i++)
    {
        if (fscanf(f_in, "%d", &arr[i])!= 1)
        {
            printf ("err5\n");
            cool = -1;
            goto clean_1;
        }
    }

    int max_count_Number = max_count_number(arr , len);

    fprintf (f_out, "%d\n", max_count_Number);

    clean_1:

    free (arr);

    clean:

    fclose (f_in);
    fclose (f_out);
    return cool;
}

