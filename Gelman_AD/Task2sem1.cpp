#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int armin(int number1, int number2, FILE* input);
int armin(int number1, int number2, FILE* input)
{
    int n;
    double average;
    double current;
    double sum;
    int number3;;

    sum = 0;
    n = 1;

    while (fscanf(input, "%d", &number3) == 1)
    {
        if (number2 > number1 && number2 > number3) 
        {
            sum += number2;
            current = number1;
            number1 = number2;
            number2 = current;
            n++;
        }
        else
        {
            if (number2 < number1 && number2 < number3)
            {
                sum += number2;
                current = number1;
                number1 = number2; 
                number2 = current;
                n++
            }
        }

        number1 = number2;
        number2 = current;
    }

    average = sum / n;
    printf("average of constant section of the sequence: %f\n", average);
    return 0;
}

int main(void) 
{

    int number1;
    int number2;
    FILE* input;

    input = fopen("input.txt", "r");

    if (input == NULL) 
    {
        printf("File did not open.\n");
        return -1;
    }

    if (fscanf(inp, "%f", &number1) != 1)
    {
        printf("Unable to read the first element\n");
        return 0;
    }

    if (fscanf(inp, "%f", &number2) != 1)
    {
        printf("Unable to read the second element\n");
        return 0;
    }

    armin(number1, number2, input);

    fclose(input);
    return 0;

}