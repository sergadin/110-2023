#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "strings.h"

/*Parameters:
 *         *f - The original file.
 *         *fout - Modified file.
 *         line - The number of the strings.
 *         *err - Error code.
 */

// Function for splitting a string into substrings using a specified delimiter
char* space_split(char str[], char delimiter);
char* space_split(char str[], char delimiter)
{
    // The "strtok" function splits a string into tokens using a specified delimiter
    char* token = strtok(str, &delimiter);
    return token;
}

int split_string(FILE* f, FILE* fout, Error* err)
{
    FILE *inputFile, *outputFile;
    char inputFileName[] = "input.txt";
    char outputFileName[] = "output.txt";
    char buffer[1000];
    int max_length = 50; // Maximum string length
    *err = OK;

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");
    
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) 
    {
        char* token = space_split(buffer, ' '); // Split a string by spaces

        while (token != NULL) 
        {
            if (strlen(token) > max_length) 
            { // If the length of the substring is greater than the maximum, split it
                int length = strlen(token);
                for (int i = max_length; i < length; i += max_length) 
                {
                    fprintf(outputFile, "%.*s\n", max_length, token + i - max_length);
                }
                fprintf(outputFile, "%s\n", token + length - length % max_length);
            }
            else 
            {
                fprintf(outputFile, "%s\n", token);
            }

            token = strtok(NULL, " ");
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}