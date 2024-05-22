#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "paragraph.h"

/*Parameters:
 *         *f - The original file.
 *         *fout - Modified file.
 *         line - The number of the strings.
 *         *err - Error code.
 */

#define MAX_LINE_LENGTH 80 // Maximum line length
#define RED_LINE_LENGTH 20 // Red line length

// Function to display a paragraph with given borders and a red line
void format_paragraph(char* paragraph, Error* err)
{
    char* word;
    int remaining_space = MAX_LINE_LENGTH; // Remaining space in line
    int is_first_word = 1; // Flag to define the first word
    err = OK;

    // Splitting a string into words
    word = strtok(paragraph, " ");
    while (word != NULL) 
    {
        int word_length = strlen(word);

        // If the word fits into the remaining space, add it
        if (word_length <= remaining_space) 
        {
            if (is_first_word) 
            {
                printf("%s", word); // First word without space
                remaining_space -= word_length;
                is_first_word = 0;
            }
            else 
            {
                printf(" %s", word); // The following words with a leading space
                remaining_space -= (word_length + 1); // Add 1 for space
            }
        }
        else 
        {
            // If the word does not fit, go to a new line and add a red line
            printf("\n");
            for (int i = 0; i < RED_LINE_LENGTH; i++) 
            {
                printf("-");
            }
            printf("\n");
            printf("%s", word);
            remaining_space = MAX_LINE_LENGTH - word_length;
            is_first_word = 0;
        }

        word = strtok(NULL, " "); // We get the next word
    }

    printf("\n"); // Go to new line after paragraph
}