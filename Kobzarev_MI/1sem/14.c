#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void func(double* arr, double len, int x);

void func(double* arr, double len, int x) {
    int i, j, count;
    double sum, max, min;
    max = 0;
    min = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == x) {
            count = 0;
            if (i != 0) {
                min = arr[i - 1];
            }
            while (i + count < len && arr[i + count] == x) {
                count++;
            }
            if (i + count != len) {
                max = arr[i + count];
            }
            sum = (max + min) / 2;
            for (j = i; j < i + count; j++) {
                arr[j] = sum;
            }
            i = i + count - 1;
            max = 0;
        }
    }
}

int main(void)
{
    FILE* inp;
    double x, len;
    int i;
    double* arr;

    inp = fopen("input.txt", "r");

    if (inp == NULL) {
        printf("No input file");
        return -1;
    }
    if (fscanf(inp, "%lf", &len) != 1) {
        printf("Error reading the file");
        fclose(inp);
        return -1;
    }

    fscanf(inp, "%lf", &x);

    arr = (double*)malloc(len * sizeof(double));

    if (arr == NULL) {
        printf("Memory error");
        fclose(inp);
        return -1;
    }

    for (i = 0; i < len; i++)
    {
        fscanf(inp, "%lf", &arr[i]);
    }

    func(arr, len, x);

    for (i = 0; i < len; i++) {
        printf("%lf\n", arr[i]);
    }
    fclose(inp);
    free(arr);
    return 0;
}