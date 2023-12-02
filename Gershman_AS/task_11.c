#include <stdio.h>
#include <math.h>


int deriv_and_polinom(FILE* input, double* deriv, double* polinom);


int deriv_and_polinom(FILE* input, double* deriv, double* polinom)
{
    double coef = 0, x = 0;
    *polinom = 0;
    *deriv = 0;
    if (fscanf(input, "%lf", &x) != 1)
    {
        return -1;
    }
    while (fscanf(input, "%lf", &coef))
    {
        *deriv = *deriv * x + *polinom;
        *polinom = *polinom * x + coef;
    }
    if (!feof(input))
    {
        return -2;
    }
    return 0;
}


int main(void)
{
    FILE* input;
    int check;
    double deriv, polinom;
    input = fopen("input.txt", "r");
    if (!input)
    {
        printf("cant open input file");
    }
    check = deriv_and_polinom(input, &deriv, &polinom);
    if (check == -1)
    {
        printf("input file is empty");
    }
    if (check == -2)
    {
        printf("incorrect type of input data");
    }
    printf("%lf %lf", deriv, polinom);
    fclose(input);
    return 0;
}
