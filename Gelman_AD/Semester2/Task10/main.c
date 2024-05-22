#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "paragraph.h"

#define MAX_LINE_LENGTH 80 // Maximum line length
#define RED_LINE_LENGTH 20 // Red line length

// New structure for testing
typedef struct
{
	const char* file_name; // The file with matrix' elements 
	Error err;            // Error code
} TestCase;

int main()
{
	FILE* input_file = fopen("input.txt", "r");
	FILE* output_file = fopen("output.txt", "w");
	Error err;
	err = OK;

	TestCase tests[] =
	{ {"paragraph1.txt", OK},
	  {"paragraph2.txt", OK},
	  {"paragraph3.txt", OK},
	};

	int n_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < n_tasks; n++)
	{
		input_file = fopen(tests[n].file_name, "r");
		if (input_file == NULL)
		{
			printf("Error opening input file\n");
			err = FILE_ERROR;
			goto terminate;
		}
		output_file = fopen("paragraph_correct.txt", "w");
		if (output_file == NULL)
		{
			printf("File did not open\n");
			err = FILE_ERROR;
			fclose(input_file);
			goto terminate;
		}

		char line[MAX_LINE_LENGTH];
		char paragraph[MAX_LINE_LENGTH * 10]; // Maximum paragraph length 10 lines

		// Reading lines from the input file
		while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL)
		{
			// If the line is empty, then the paragraph has ended, format it
			if (strcmp(line, "\n") == 0)
			{
				format_paragraph(paragraph, &err);
				strcpy(paragraph, ""); // Clearing the line for the next paragraph
			}
			else
			{
				strcat(paragraph, line); // Adding a line to a paragraph
			}
		}

		// Format the last paragraph, if it is in the file
		if (strlen(paragraph) > 0)
		{
			format_paragraph(paragraph, &err);
		}

		terminate:
		if (err != tests[n].err)
		{
			printf("The ¹%d test is not completed.\n", n + 1);
		}
		else if (err == OK)
		{
			printf("The ¹%d test is completed. Modified string is written to the file paragraph_correct.txt\n", n + 1);
		}
		else
		{
			printf("The ¹%d test is completed.\n", n + 1);
		}

		fclose(input_file);
		fclose(output_file);
	}

	return 0;
}