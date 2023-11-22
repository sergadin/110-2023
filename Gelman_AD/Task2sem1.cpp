#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int armin(int a, int b, int c, float average, FILE* input);
int armin(int a, int b, int c, float average, FILE* input)
{
    int n;
    int a;
    int b;
    int c;
    int current;
    int sum;

    sum = 0;
    n = 1;
    a = 0; 
    b = 0; 
    c = 0;

    while (fscanf(input, "%d", &a) == 1)
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
    }

    average = sum / n;
    printf("average of constant section of the sequence: %f\n", average);
    return 0;
}

int main(void) 
{

    int a;
    int b;
    int c;
    int sum;
    int current;
    float average;
    int n;
    FILE* input;

    input = fopen("input.txt", "r");

    if (input == NULL) 
    {
        printf("File did not open.\n");
        return -1;
    }

    if (fscanf(input, "%d", &a) != 1) 
    {
        printf("Unable to read first value.\n");
        return -1;
    }

    if (fscanf(inp, "%f", &b) != 1)
    {
        printf("Unable to read the second element\n");
        return 0;
    }

    if (fscanf(inp, "%f", &c) != 1)
    {
        printf("Unable to read the third element\n");
        return 0;
    }

    armin(average, input, a, b, c);

    fclose(input);
    return 0;

}