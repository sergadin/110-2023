#include <stdio.h>

int checkBorder(unsigned int icon[32]) 
{
    unsigned int top = icon[0];  // Upper border of the icon
    unsigned int bottom = icon[31]; // Lower border of the icon

    // Checking the upper and the lower border
    for (int i = 0; i < 32; i++) 
    {
        if (top != icon[i] || bottom != icon[i]) 
        {
            // If there is at least one pixel == 0 we return 0
            return 0; 
        }
    }

    // Checking the left and the right border
    for (int i = 1; i < 31; i++) 
    {
        if ((icon[i] & 1) == 0 || (icon[i] & (1 << 31)) == 0) 
        {
            // If there is at least one pixel == 0 we return 0
            return 0; 
        }
    }


    // Checking the black lines inside the frame
    for (int i = 1; i < 31; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            if (icon[i * 8 + j] != 0)
            {
                return 0;
            }
        }
    }

    return 1; // There is a black frame on the icon
}

int main(void) 
{
    FILE* file = fopen("iconfile.txt", "r");
    unsigned int icon[32];

    // Reading the icon from the file
    for (int i = 0; i < 32; i++) 
    {
        fscanf(file, "%u", &icon[i]);
    }

    fclose(file); 

    // ѕровер€ем наличие рамки в иконке и выводим соответствующее сообщение
    if (checkBorder(icon)) // return == 1
    {
        printf("There is a black frame\n");
    }
    else // return == 0
    {
        printf("There is no black frame on the icon\n");
    }

    return 0;
}