#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paragraph.h"

// New structure for testing
typedef struct
{
	const char* input;   // The original file 
	const char* output; // Modified file
	error err;         // Error code
} TestCase;

int main()
{
	FILE* input_file;
	FILE* output_file;
	error err;

	TestCase tests[] =
	{ {"paragraph1.txt", "paragrapgh_correct1.txt", OK},
	  {"paragraph2.txt", "paragrapgh_correct2.txt", OK},
	  {"paragraph3.txt", "paragrapgh_correct3.txt", OK},
	};

	int number_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < number_tasks; n++)
	{
		input_file = fopen(tests[n].input, "r");
		if (input_file == NULL)
		{
			printf("Error opening input file\n");
			goto terminate;
		}
		output_file = fopen(tests[n].output, "w");
		if (output_file == NULL)
		{
			printf("File did not open\n");
			fclose(input_file);
			goto terminate;
		}

		process_file(input_file, output_file, &err);

		terminate:
		if (err != tests[n].err)
		{
			printf("The %d test is not completed.\n", n + 1);
		}
		else if (err == OK)
		{
			printf("The %d test is completed. Modified string is written to the file paragraph_correct.txt\n", n + 1);
		}
		else
		{
			printf("The %d test is completed.\n", n + 1);
		}

		fclose(input_file);
		fclose(output_file);
	}

	return 0;
}