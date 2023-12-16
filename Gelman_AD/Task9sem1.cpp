#include <stdio.h>

int check_frame(int icon[32])
{
    int correct = 0;

    if (icon[0] == (2^32) - 1)
    {
        correct = 1; // Checking the upper border
    }

    if (icon[31] == (2^32) - 1)
    {
        correct = 1; // Checking the lower border
    }

    if (icon[1] == (2^31) + 1)
    {
        correct = 1; //Left black line
    }

    if (icon[30] == (2^31) + 1)
   {
        correct = 1; //Right black line
   }

   for (int i = 1; i < 31; i++) //No black lines inside the frame
   {
       for (int j = 1; j < 7; j ++)
       {
           if (icon[i * 8 + j] != 0)
           {
               correct = 0;
           }
        }
   }
     

    return correct; //There is a black frame
}


int main() 
{
    int icon[32];
    int correct;

    printf("Enter 32 integers of 0 and 1\n");

    for (int i = 0; i < 32; i++) 
    {
        scanf("%d", &icon[i]);
    }

    correct = check_frame(icon);

    if (correct == 1)
    {
        printf("There is a black frame\n");
    }
    else //correct == 0
    {
        printf("There is no black frame on the icon\n");
    }

    return 0;
}
