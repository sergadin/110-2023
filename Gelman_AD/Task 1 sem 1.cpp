#include <stdio.h>
#include <math.h>
#define EPS 1e-5

int main() 
{
    double current = 0, l1 = 0, l2 = 0;
    double c1 = 0, c2 = 0, c3 = 0, b = 0;
    int n = 0;
    FILE* inp;

    inp = fopen("input.txt", "r");
    if (inp == NULL) 
    {
        return -1;
    }

    if (fscanf(inp, "%lf%lf%lf%lf", &c1, &c2, &c3, &b) != 4) 
    {
        printf("Unable to read multipliers\n");
        return -1;
    }

    if (fscanf(inp, "%lf", &current) != 1 || current == 0) 
    {
        printf("Unable to read first element\n");
        return -1;
    }

    l1 = current;

    if (fscanf(inp, "%lf", &current) != 1 || current == 0) 
    {
        printf("Unable to read second element\n");
        return -1;
    }

    l2 = current;

    while (fscanf(inp, "%lf", &current) == 1 && current != 0) 
    {
        if (fabs(c1 * l1 + c2 * l2 + c3 * current - b) > EPS) 
        {
            printf("The sequence does not satisfy the equation\n");
            return 0;
        }

        l1 = l2;
        l2 = current;
        n++;
    }

    if (n == 0) 
    {
        printf("Not enough elements\n");
        return 0;
    }

    printf("The sequence does not satisfy the equation\n");
    fclose(inp);
    return 0;
}