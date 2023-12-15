#include <stdio.h>

// Function for counting the number of digits in which numbers contain 1
int countOnes(int number_1, int number_2)
{
    int count = 0;

    // Checking each digit of numbers, starting with the least one
    for (int i = 0; i < 32; i++) 
    { 
        //Checking wether the i-st digit includes both 1
        if ((number_1 & (1 << i)) && (number_2 & (1 << i)))
        {
            count++;
        }
    }

    return count;
}

int main() 
{
    int number_1;
    int number_2;

    printf("Enter two integers");
    scanf("%d %d", &number_1, &number_2);

    // Counting the number of digits of the numbers in which both of them contains 1
    int result = countOnes(number_1, number_2);

    printf("Number of digits of the numbers in which both of them contains 1: %d\n", result);

    return 0;
}