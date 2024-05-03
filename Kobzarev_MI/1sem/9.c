#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1e-5

int check(FILE* f, double c1, double c2, double c3, double b);

int check(FILE* f, double c1, double c2, double c3, double b)
{
    double curr, prev, sec;
    int count;

    count = 0;

    if (fscanf(f, "%lf", &curr) != 1)
    {
        return -1;
    }

    sec = curr;

    if (fscanf(f, "%lf", &curr) != 1)
    {
        return -1;
    }

    prev = curr;

    while (fscanf(f, "%lf", &curr) == 1)
    {
        if (fabs(c1 * sec + c2 * prev + c3 * curr - b) > EPS)
        {
            return 0;
        }

        sec = prev;
        prev = curr;
        count++;
    }

    if (count == 0)
    {
        return 1;
    }

    return 2;
}


int main(void)
{
    int ans;
    double c1, c2, c3, b;
    FILE* input;

    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Error: empty file");
        return -1;
    }

    if (fscanf(input, "%lf%lf%lf%lf", &c1, &c2, &c3, &b) != 4)
    {
        printf("Error reading the file");
        fclose(input);
        return -1;
    }

    ans = check(input, c1, c2, c3, b);

    if (ans == -1)
    {
        printf("Error reading the file");
        fclose(input);
        return -1;
    }

    if (ans == 0)
    {
        printf("Does not satisfy the equation");
        fclose(input);
        return 0;
    }

    if (ans == 1)
    {
        printf("Less than three elements");
        fclose(input);
        return 0;
    }

    if (ans == 2)
    {
        printf("Does satisfy the equation");
        fclose(input);
        return 0;
    }
}