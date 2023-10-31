#include <stdio.h>
#include <math.h>
int main(void)
{

    FILE* f;
    int count = 0;
    f = fopen("input.txt", "r");
    float number1 = 10;
    float number2 = 100;
    float number3 = 1000;
    double armin = 0;
    double res;

    if (f == NULL)
    {
        printf("File did not open\n");
        return -1;
    }

    if (fscanf(f, "%f", &number1) != 1)
    {
        printf("Reading error\n");
            return -1;
    }

    else
    {
        if (fscanf(f, "%f", &number2) != 1)
        {
            printf("Reading error\n");
                return -1;
        }
    }

    while ((fscanf(f, "%f", &number3) == 1))
    {
        if ((number2 > number1 && number2 > number3) || (number2 < number1 && number2 < number3))
        {
            armin += number2;
            count++;
            fclose(f);
            return 0;
        }
        number1 = number2;
        number2 = number3;
    }
    res = armin / count;
    printf("The arithmetical mean = %lf \n", res);
    fclose(f);
    return 0;
}