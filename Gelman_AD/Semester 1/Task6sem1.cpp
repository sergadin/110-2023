#include <stdio.h>
#include <stdlib.h>

//Array union
int combinate_arrays(double* mas1, double* mas2, double* mas3, int lngth1, int lngth2);

int combinate_arrays(double* mas1, double* mas2, double* mas3, int lngth1, int lngth2)
{
    int first_index = 0;
    int second_index = 0;

    for (int i = 0; i < (lngth1 + lngth2); i++)
    {
        if ((first_index < lngth1) && (second_index >= lngth2))
        {
            mas3[i] = mas1[first_index]; //The first element from the first array goes to the third array
            first_index += 1; //Continuing the process
        }
        else if ((first_index >= lngth1) && (second_index < lngth2)) //all of the first array has gone to the third array
        {
            mas3[i] = mas2[second_index]; //The first element from the second array goes to the third array
            second_index += 1; //Continueing the process
        }
        else
        {
            if (mas1[first_index] <= mas2[second_index])
            {
                mas3[i] = mas1[first_index];
                first_index += 1;
            }
            else
            {
                mas3[i] = mas3[second_index];
                second_index += 1;

            }
        }
    }

    return 0;
}

int main(void)
{

    double* mas1 = NULL;
    double* mas2 = NULL;
    double* mas3 = NULL; //array union
    FILE* file_in = fopen("input.txt", "r");
    FILE* file_out = fopen("output.txt", "w");
    int lngth1 = 0;
    int lngth2 = 0;
    int  main_return_code = 0;

    //Checking opening files
    if (file_in == NULL)
    {
        printf("Unable to open the file input.txt\n");
        return -1;
    }

    if (file_out == NULL)
    {
        printf("Unable to open the file output.txt\n");
        fclose(file_in);
        return -1;
    }

    if (fscanf(file_in, "%d", &lngth1) != 1)
    {
        printf("Unable to read the file\n");
        fclose(file_in);
        fclose(file_out);
        return -1;
    }

    //Checking the arrays
    mas1 = (double*)malloc(lngth1 * sizeof(double));

    if (mas1 == NULL)
    {
        printf("Memory error\n");
        fclose(file_in);
        fclose(file_out);
        return -1;
    }

    mas2 = (double*)malloc(lngth2 * sizeof(double));

    if (mas2 == NULL)
    {
        printf("Memory error\n");
        fclose(file_in);
        fclose(file_out);
        return -1;
    }

    mas3 = (double*)malloc((lngth1 + lngth2) * sizeof(double));

    if (mas3 == NULL)
    {
        printf("Memory error\n");
        fclose(file_in);
        fclose(file_out);
        return -1;
    }
    if (fscanf(file_in, "%lf", &mas1[0]) != 1)
    {
        printf("Problems with array (1)\n");
        free(mas1);
        fclose(file_in);
        fclose(file_out);
        return -1;
    }
    //Checking wether the array is nondecreasing
    for (int i = 1; i < lngth1; i++)
    {
        if (fscanf(file_in, "%lf", &mas1[i]) != 1)
        {
            printf("Problems with array (1)\n");
            free(mas1);
            fclose(file_in);
            fclose(file_out);
            return -1;
        }

        if (mas1[i] < mas1[i - 1])
        {
            printf("The sequence of the array (1) is not nondecreasing\n");
            main_return_code = -1;
            free(mas1);
        }
    }

    for (int i = 1; i < lngth2; i++)
    {
        if (fscanf(file_in, "%lf", &mas2[i]) != 1)
        {
            printf("Problems with array (2)\n");
            free(mas2);
            fclose(file_in);
            fclose(file_out);
            return -1;
        }

        if (mas2[i] < mas2[i - 1])
        {
            printf("The sequence of the array(2) is not nondecreasing\n");
            main_return_code = -1;
            free(mas2);
        }
    }

    //Array union
    combinate_arrays(mas1, mas2, mas3, lngth1, lngth2);

    for (int i = 0; i < (lngth1 + lngth2); i++)
    {
        fprintf(file_out, "%lf\n", mas3[i]);

    }

    printf("The result is printed\n");

    free(mas3);
    free(mas2);
    free(mas1);

    fclose(file_in);
    fclose(file_out);
    return main_return_code;
}