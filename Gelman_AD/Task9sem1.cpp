#include <stdio.h>

int check_frame(int icon[32])
{
    int i;

    // Checking the upper border
    for (i = 0; i < 32; i++) 
    {
        if (icon[i] != 1) 
        {
            return 0; // There is no black frame on the icon
        }
    }

    // Checking the lower border
    for (i = 31; i < 32; i--) 
    {
        if (icon[i] != 1) 
        {
            return 0; // There is no black frame on the icon
        }
    }

    // Checking the left border
    for (i = 0; i < 32; i += 8) 
    {
        if (icon[i] != 1) 
        {
            return 0; // There is no black frame on the icon
        }
    }

    // Checking the right border
    for (i = 7; i < 32; i += 8) 
    {
        if (icon[i] != 1) 
        {
            return 0; // There is no black frame on the icon
        }
    }

    // Checking pixels inside the frame
    for (i = 1; i < 31; i++) 
    {
        for (int j = 1; j < 7; j++) 
        {
            if (icon[i * 8 + j] != 0) 
            {
                return 0; // There is no black frame on the icon
            }
        }
    }

    return 1; //There is a black frame
}


int main() 
{
    int icon[32];

    printf("Enter 32 integers of 0 and 1\n");

    for (int i = 0; i < 32; i++) 
    {
        scanf("%u", &icon[i]);
    }

    if (check_frame(icon)) //return = 1
    {
        printf("There is a black frame\n");
    }
    else //return = 0
    {
        printf("There is no black frame on the icon\n");
    }

    return 0;
}