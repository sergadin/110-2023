#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{
	OK,
	LONG_WORD,
	MALLOC_ERROR
}error;

void process_file(FILE* input, FILE* output, error* err);

/*Parameters:
 *         input - The original file
 *         output - Modified file
 *         err - Error code
 */
// Instructions like #def and #undef are implemented, 
// The specified substitutions are performed in the scope of their assignment
