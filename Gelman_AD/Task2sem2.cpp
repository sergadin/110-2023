#include <stdio.h>
#include <math.h>
int main(void)
{

    FILE* f;
    int count = 3;
    f = fopen("input.txt", "r");
    float a = 10;
    float b = 100;
    float c = 1000;
    int d = 0;
    int res;

    if (f == NULL)
    {
        printf("File did not open\n");
        return -1;
    }

    if ((fscanf(f, "%f", &a) != 1)
    {
        printf("Reading error\n");
            return -1;
    }

    else
    {
        if (fscanf(f, "%f", &b) != 1)
        {
            printf("Reading error\n");
                return -1;
        }
    }

    while ((fscanf(f, "%f", &ñ) == 1))
    {
        if ((b > a && b > c) || (b < a && b < c))
        {
            d += b;
            count++;
        }
        a = b;
        b = c;
    }
    res = d / count;
    printf("The arithmetical mean = %lf \n", res);
    fclose(f);
    return 0;
}