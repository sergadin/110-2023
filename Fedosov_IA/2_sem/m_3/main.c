#include "get_inverse.h"
#include <stdio.h>

typedef struct
{
    const char *file;
    int size;
} TestCase;

static double *make_mat(const char *file_name, Error *error)
{
    double *mat;
    int size;
    FILE *data = fopen(file_name, "r");
    if (data == NULL)
    {
        *error = EMPTY_FILE;
        return 0;
    }

    if (fscanf(data, "%d", &size) != 1)
    {
        *error = EMPTY_FILE;
        fclose(data);
        return 0;
    }

    mat = (double *)malloc(size * size * sizeof(double));
    for (int i = 0; i < size * size; i++)
    {
        fscanf(data, "%lf", &mat[i]);
    }
    *error = OK;
    fclose(data);
    return mat;
}

int main(void)
{
    Error error;
    TestCase tests[] = {
        {"data1.txt", 4},
        {"data2.txt", 2},
        {"data3.txt", 3},
        {"data4.txt", 3},
        {"data5.txt", 4},
        {"data6.txt", 3}};

    double *rez;
    double *mat;

    for (int i = 0; i < 6; i++)
    {
        mat = make_mat(tests[i].file, &error);
        rez = inverse(mat, tests[i].size, &error);
        if (error == NO_INVERSE)
        {
            printf("В тесте %d обратной матрицы не существует тк определитель исходной равен 0\n", i + 1);
        }
        else if (error == EMPTY_FILE)
        {
            printf("В тесте %d файл с входными данными пуст\n", i + 1);
        }
        else if (error == OK)
        {
            for (int k = 0; k < tests[i].size; k++)
            {
                for (int j = 0; j < tests[i].size; j++)
                {
                    printf("%lf ", rez[k * tests[i].size + j]);
                }
                printf("\n");
            }
        }
        printf("\n");
        free(rez);
    }
    return 0;
}