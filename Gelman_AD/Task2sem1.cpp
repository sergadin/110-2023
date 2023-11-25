#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void) 
{

    int a;
    int sum;
    int previos;
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

    n = 1;
    sum = a;
    previos = a;

    while (fscanf(input, "%d", &a) == 1) 
    {
        if (a != previos) {
            sum += a;
            n++;
            previos = a;
        }
    }

    fclose(input);
    average = sum / n;
    printf("average of constant section of the sequence: %f\n", average);
    return 0;
}