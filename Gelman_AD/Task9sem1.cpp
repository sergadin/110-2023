#include <stdio.h>

int checkBorder(unsigned int icon[32]) 
{
    int correct = 0;

    // Checking the upper border
    if (icon[0] == 2 ^ 32 - 1)
    {
        correct = 1;
    }

    // Checking the lower border
    if (icon[31] == 2 ^ 32 - 1)
    {
        correct = 1;
    }

    // Checking the left border
    if (icon[1] == 2 ^ 31 + 1)
    {
        correct = 1;
    }

    // Checking the right border
    if (icon[30] == 2 ^ 31 + 1)
    {
        correct = 1;
    }

    // Checking the black lines inside the frame
    for (int i = 2; i <= 29; i++) 
    {
        if ((icon[i] && ((1 << 31) || (1)) == ((1 << 31) || 1)) && (~icon[i] && ((1 << 30) || (1 << 1)) == (1 << 30) || (1 << 1)))
        {
            correct = 1;
        }
    }
    return correct; // There is a black frame on the icon
}

int main(void) 
{
    FILE* file = fopen("iconfile.txt", "r");
    unsigned int icon[32];
    int correct;

    // Reading the icon from the file
    for (int i = 0; i < 32; i++) 
    {
        fscanf(file, "%u", &icon[i]);
    }

    fclose(file); 

    // Checking wether there is a black frame on the icon or not
    correct = checkBorder(icon);

    if (correct = 1)
    {
        printf("There is a black frame\n");
    }
    else // correct = 0
    {
        printf("There is no black frame on the icon\n");
    }

    return 0;
}