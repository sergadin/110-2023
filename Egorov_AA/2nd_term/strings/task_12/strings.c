#include "strings.h"

#define MAX_LINE_LENGTH 1024

typedef struct Define {
	char key[MAX_LINE_LENGTH];
	char value[MAX_LINE_LENGTH];
	struct Define* next;
} Define;


void add_define(Define** head, const char* key, const char* value);

void add_define(Define** head, const char* key, const char* value) {
	Define* new_define = (Define*)malloc(sizeof(Define));
	strcpy(new_define->key, key);
	strcpy(new_define->value, value);
	new_define->next = *head;
	*head = new_define;
}


const char* find_define(Define* head, const char* key);

const char* find_define(Define* head, const char* key) {
	Define* current = head;
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}


void free_defines(Define* head);

void free_defines(Define* head) {
	Define* current = head;
	while (current != NULL) {
		Define* temp = current;
		current = current->next;
		free(temp);
	}
}


void process_file(FILE* input, FILE* output, error* err) {

	*err = OK;
	char line[MAX_LINE_LENGTH];
	Define* defines = NULL;
	int undef_flag = 0;

	while (fgets(line, sizeof(line), input)) {
		if (strncmp(line, "#define", 7) == 0) {
			char key[MAX_LINE_LENGTH];
			char value[MAX_LINE_LENGTH];
			if (sscanf(line, "#define %s %[^\n]", key, value) == 2) {
				add_define(&defines, key, value);
			}
		}
		else if (strncmp(line, "#undef", 6) == 0) {
			undef_flag = 1;
		}
		else {
			if (!undef_flag) {
				char* token = strtok(line, " \t\n");
				while (token != NULL) {
					const char* replacement = find_define(defines, token);
					if (replacement) {
						fprintf(output, "%s ", replacement);
					}
					else {
						fprintf(output, "%s ", token);
					}
					token = strtok(NULL, " \t\n");
				}
				fprintf(output, "\n");
			}
			else {
				fprintf(output, "%s", line);
			}
		}
	}
	free_defines(defines);
}