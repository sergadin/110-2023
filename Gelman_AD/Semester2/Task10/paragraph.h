#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    OK,
    MEMORY_ERROR,
    FILE_ERROR,
}Error;

void format_paragraph(char* paragraph, Error* err);

/*Parameters:
 *         *f - The original file.
 *         *fout - Modified file.
 *         line - The number of the strings.
 *         *err - Error code.
 */
 // The program reads lines from the file "input.txt", and formats them into paragraphs with specified borders and a red line
 // And then writes them to a new file "output.txt".
 // The "strtok" function is used to split a string into words, "strcpy" and "strcat" for working with character arrays.
 // Conclusion: 
 // If the code is executed without errors, the error code OK is displayed and the corrected text is written to the file.
 // Also, the last corrected line is output to the file string_correct.txt
 // If an error occurs while allocating memory, the error code MEMORY_ERROR is printed and -1 is returned.
 // If there are problems opening the file, the error code FILE_ERROR and the value -1 are returned.
