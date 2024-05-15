#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Gaussian_method.h"

typedef struct
{
    const char *file;
    int rows;
    int cols;
} TestCase;

double **create_mat(const char *file)
{
    FILE *fin = fopen(file, "r");
    int rows, cols;
    double **matrix;
    if (fin == NULL)
    {
        printf("FILE DOESNT EXIST\n");
        return NULL;
    }
    if (fscanf(fin, "%d%d", &rows, &cols) != 2)
    {
        printf("FILE IS EMPTY\n");
        fclose(fin);
        return NULL;
    }
    matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(fin, "%lf", &matrix[i][j]);
        }
    }
    fclose(fin);
    return matrix;
}

int main()
{
    double *solution;
    Error error;
    TestCase tests[] = {
        {"file.txt", 3, 4},
        {"data2.txt", 4, 5},
        {"data3.txt", 3, 4},
        {"data4.txt", 4, 5},
    };

    for (int i = 0; i < 4; i++)
    {
        double **mat = create_mat(tests[i].file);
        if (mat == NULL)
        {
            printf("MATRIX IS NULL\n");
            continue;
        }
        solution = gauss(mat, tests[i].rows, tests[i].cols, &error);
        if (error == SIZE)
        {
            printf("MATRIX IS WRONG SIZE\n");
            for (int j = 0; j < tests[i].rows; j++)
            {
                free(mat[j]);
            }
            free(mat);
            continue;
        }
        if (error == NOT_DET)
        {
            printf("SYSTEM IS NOT DETERMINED\n");
            printf("\n");
            for (int j = 0; j < tests[i].rows; j++)
            {
                free(mat[j]);
            }
            free(mat);
            continue;
        }
        printf("столбец решений:\n");
        for (int j = 0; j < tests[i].rows; j++)
        {
            printf("%lf\n", solution[j]);
        }
        printf("\n");
        free(solution);
        for (int j = 0; j < tests[i].rows; j++)
        {
            free(mat[j]);
        }
        free(mat);
    }
    return 0;
}
