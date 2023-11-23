#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int armin(double a, double b, double average, FILE* input);
int armin(double a, double b, double average, FILE* input)
{
    int n;
    double current;
    double sum;
    double c;

    sum = 0;
    n = 1;

    while (fscanf(input, "%d", &c) == 1)
    {
        if (b > a && b > c) 
        {
            sum += b;
            current = a;
            a = b;
            b = current;
            n++;
        }
        else
        {
            if (b < a && b < c)
            {
                sum += b;
                current = a;
                a = b; 
                b = current;
                n++
            }
        }

        a = b;
        b = current;
    }

    average = sum / n;
    printf("average of constant section of the sequence: %f\n", average);
    return 0;
}

int main(void) 
{

    double a;
    double b;
    double c;
    double average;
    int n;
    FILE* input;

    input = fopen("input.txt", "r");

    if (input == NULL) 
    {
        printf("File did not open.\n");
        return -1;
    }

    if (fscanf(inp, "%f", &a) != 1)
    {
        printf("Unable to read the first element\n");
        return 0;
    }

    if (fscanf(inp, "%f", &b) != 1)
    {
        printf("Unable to read the second element\n");
        return 0;
    }

    armin(a, b, average, input);

    fclose(input);
    return 0;

}