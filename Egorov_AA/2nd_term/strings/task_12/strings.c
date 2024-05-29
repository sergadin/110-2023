#include "strings.h"

#define MAX_LINE_LENGTH 2048

typedef struct Define {
	char key[MAX_LINE_LENGTH];
	char value[MAX_LINE_LENGTH];
	struct Define* next;
} Define;


const void addDefine(Define** head, const char* key, const char* value);

const void addDefine(Define** head, const char* key, const char* value) {  // Добавляет дефайн в список
	Define* new_define = (Define*)malloc(sizeof(Define));
	strcpy(new_define->key, key);
	strcpy(new_define->value, value);
	new_define->next = *head;
	*head = new_define;
}


const char* findDefine(Define* head, const char* key);             // Поиск дефайна в списке

const char* findDefine(Define* head, const char* key) {
	Define* current = head;
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}


const void removeDefine(Define** head, const char* key);             // Освобождает определенный дефайн

const void removeDefine(Define** head, const char* key) {
	Define* current = *head;
	Define* prev = NULL;
	
	while (current != NULL) {
		if(strcmp(current->key, key) == 0) {
			if(prev = NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current);
			return;
			}
		prev = current;
		current = current->next;
	}
}


const void freeDefines(Define* head);                  // Очищает связный список (освобождает все дефайны)

const void freeDefines(Define* head) {
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
	char delimiters[] = " \n\t";
	Define* defines = NULL;

	while (fgets(line, sizeof(line), input)) {
		if (strncmp(line, "#define", 7) == 0) {                                   // Если строка с дефайном
			char key[MAX_LINE_LENGTH];
			char value[MAX_LINE_LENGTH];
			if (sscanf(line, "#define %s %[^\n]", key, value) == 2) {         // Заносим дефайн в список
				addDefine(&defines, key, value);
			}
		}
		else if (strncmp(line, "#undef", 6) == 0) {                               // Если строка с андефом
			char key[MAX_LINE_LENGTH];
			if (sscanf(line, "#undef %s", key) == 1)                          // Освобождаем дефайн
				removeDefine(&defines, key);
		}
		else {                                                                    // Строка без дефа и андефа
			char* token = strtok(line, delimiters);                           // Делим строку на слова
			while (token != NULL) {                                           
				const char* replacement = findDefine(defines, token); 
				if (replacement) {                                        // Если слово в списке дефайнов, выписываем замену
					fprintf(output, "%s ", replacement);
				}
				else {                                                    // Слово не в списке, выписывам само слово
					fprintf(output, "%s ", token);
				}
				token = strtok(NULL, " \t\n");
				}
				fprintf(output, "\n");
		}
	}
	freeDefines(defines);
}
