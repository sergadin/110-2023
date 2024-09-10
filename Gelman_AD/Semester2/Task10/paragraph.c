#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "paragraph.h"

/*Parameters:
 *         input - The original file
 *         output - Modified file
 *         err - Error code
 */

typedef struct Define 
{
	char* key;
	char* value;
	struct Define* next;
} Define;

// Function adding define to the list
const void add_define(Define** head, const char* key, const char* value);
const void add_define(Define** head, const char* key, const char* value) 
{
	Define* new_define = (Define*)malloc(sizeof(Define));
	new_define->key = strdup(key);
	new_define->value = strdup(value);
	new_define->next = *head;
	*head = new_define;
}

// Searching define on the list
const char* find_define(Define* head, const char* key);
const char* find_define(Define* head, const char* key) 
{
	Define* current = head;
	while (current != NULL) 
	{
		if (strcmp(current->key, key) == 0) 
		{
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}

// Removing the specified define
const void remove_define(Define** head, const char* key);
const void remove_define(Define** head, const char* key) 
{
	Define* current = *head;
	Define* prev = NULL;

	while (current != NULL) 
	{
		if (strcmp(current->key, key) == 0) 
		{
			if (prev == NULL) 
			{
				*head = current->next;
			}
			else 
			{
				prev->next = current->next;
			}
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

// Clearing the list (removing all the defines)
const void free_defines(Define* head);
const void free_defines(Define* head) 
{
	Define* current = head;

	while (current != NULL) 
	{
		Define* temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void process_file(FILE* input, FILE* output, error* err) 
{
	int buffer_size = 1024;
	size_t length = 0;
	ssize_t read;
	Define* defines = NULL;
	*err = OK;
	char delimiters[] = " \n\t";
	char* line = NULL;

	while ((read = getline(&line, &length, input)) != -1) 
	{
		if (strncmp(line, "#define", 7) == 0) // If there is a line with a define
		{
			char* key = strtok(line + 8, " ");
			char* value = strtok(NULL, "\n");

			// Adding the define to the list
			if (key && value) 
			{
				add_define(&defines, key, value);
			}
		}

		else if (strncmp(line, "#undef", 6) == 0) // If there is a line with an undefine
		{
			char* key = strtok(line + 7, "\n");

			// Removing the specified define
			if (key) 
			{
				remove_define(&defines, key);
			}
		}

		else // If there is a line without the define and without the undefine
		{
			char* token = strtok(line, delimiters); // Dividing the line into words

			while (token != NULL) 
			{
				const char* replacement = find_define(defines, token);

				if (replacement) // If the word is on the list of defines, write out a replacement
				{
					fprintf(output, "%s ", replacement);
				}

				else // If the word is not on the list, write out the word itself
				{
					fprintf(output, "%s ", token);
				}
				token = strtok(NULL, " \t\n");
			}
			fprintf(output, "\n");
		}
	}
	free_defines(defines);
	if (line) 
	{
		free(line);
	}
}