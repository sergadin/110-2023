#include "get_inverse.h"
#include <stdio.h>

typedef struct
{
    const char *file;
    int size;
} TestCase;

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

    for (int i = 0; i < 6; i++)
    {
        rez = inverse(tests[i].file, &error);
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