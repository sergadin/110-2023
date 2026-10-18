#include "strings.h"

typedef struct Define {
	char* key;
	char* value;
	struct Define* next;
} Define;


const void addDefine(Define** head, const char* key, const char* value);

const void addDefine(Define** head, const char* key, const char* value) {  // Добавляет дефайн в список
	Define* new_define = (Define*)malloc(sizeof(Define));
	new_define->key = strdup(key);
	new_define->value = strdup(value);
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
			if (prev == NULL) {
				*head = current->next;
			}
			else {
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


const void freeDefines(Define* head);                  // Очищает связный список (освобождает все дефайны)

const void freeDefines(Define* head) {
	Define* current = head;
	while (current != NULL) {
		Define* temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}


void process_file(FILE* input, FILE* output, error* err) {
	int buffer_size = 512;
	size_t len = 0;
	ssize_t read;
	Define* defines = NULL;
	*err = OK;
	char delimiters[] = " \n\t";
	char* line = NULL;

	while ((read = getline(&line, &len, input)) != -1) {
		if (strncmp(line, "#define", 7) == 0) {                                   // Если строка с дефайном
			char* key = strtok(line + 8, " ");
			char* value = strtok(NULL, "\n");
			if (key && value) {         // Заносим дефайн в список
				addDefine(&defines, key, value);
			}
		}
		else if (strncmp(line, "#undef", 6) == 0) {                               // Если строка с андефом
			char* key = strtok(line + 7, "\n");
			if (key) {                          // Освобождаем дефайн
				removeDefine(&defines, key);
			}
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
	if (line)
		free(line);
}
