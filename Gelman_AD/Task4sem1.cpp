#include<math.h>
#include<stdio.h>
#include<stdbool.h>

int main()
{
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
}