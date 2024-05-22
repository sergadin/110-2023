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

int split_string(FILE* f, FILE* fout, Error* err);

/*Parameters:
 *         *f - The original file.
 *         *fout - Modified file.
 *         line - The number of the strings.
 *         *err - Error code.
 */
// The program reads lines from the file "input.txt", splits them into substrings by spaces
// And writes them to a new file "output.txt" taking into account the specified maximum string length.
// The "strtok" function is used to split a string into tokens using the specified separator.
// Conclusion: 
// If the code is executed without errors, the error code OK is displayed and the corrected text is written to the file.
// Also, the last corrected line is output to the file string_correct.txt
// If an error occurs while allocating memory, the error code MEMORY_ERROR is printed and -1 is returned.
// If there are problems opening the file, the error code FILE_ERROR and the value -1 are returned.