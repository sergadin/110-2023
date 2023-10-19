#include <stdio.h>
#include <string.h>
#include <math.h>

int fun(FILE *f) 
{
    int i, k = 90;
    double x, y;
    i = 0;
    while (fscanf(f, "%lf", &x) == 1) {
        if (i != 0) {
            if (k == 90 || k == -1) {
                if (x == y) {k = -1};
                if (x > y) {k = 1};
                if (x < y) {k = 2};
            }
            if (k == 1) {
                if (x <= y) { k = 0; return k; }
            }
            if (k == 2) {
                if (x >= y) { k = 0; return k; }
            }
        }

        // printf("%lf ", x);
        y = x;
        i++;
    }

    return k;
}

int main(void) 
{
    FILE *f;
    char name[100] = {0};

    int k;

    printf("File: ");
    fgets(name, sizeof(name)-1, stdin);
    name[strlen(name)-1] = 0;
    f = fopen(name, "r");
    if (f == NULL) {
        printf("Can't open file \n");
        return -1;
    }

    k = fun(f);
    if (k == 0) {printf("\n Не возрастает, не убывает\n")};
    if (k == 1) {printf("\n Возрастает\n")};
    if (k == 2) {printf("\n Убывает\n")};
    return 0;
}