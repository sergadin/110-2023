#include "strings.h"

typedef struct Node {
	char* word;
	struct Node* next;
} Node;

static int addWord(Node** head, const char* word, error* err);         // Функция для добавления слова в связный список

static int addWord(Node** head, const char* word, error* err) {
	Node* current = *head;
	while (current != NULL) {
		if (strcmp(current->word, word) == 0) {     // Проверка на наличие слова в списке
			return 0;
		}
		current = current->next;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		exit(-1);
	}

	new_node->word = _strdup(word);
	new_node->next = *head;
	*head = new_node;
	return 1;
}


void copyWords(FILE* input, FILE* output, error* err) {
	int ch, index = 0, buffer_size = 512;
	Node* head = NULL;
	*err = OK;
	char* word = (char*)malloc(buffer_size * sizeof(char));

	while ((ch = fgetc(input)) != EOF) {
		if (isspace((unsigned char)ch) || ispunct((unsigned char)ch)) {        // Если знак пункутации => слово закончилось
			if (index > 0) {
				word[index] = '\0';
				if (addWord(&head, word, err)) {                            // Проверяем находится ли оно в списке, если нет, то выписываем
					fprintf(output, "%s\n", word);
				}
				index = 0;
			}
		}
		else {
			if (index >= buffer_size - 1) {
				buffer_size *= 2;
				char* new_word = (char*)realloc(word, buffer_size * sizeof(char));
				if (new_word == NULL) {
					*err = M_ALLOC_ERR;
					free(word);
					return;
				}
				word = new_word;
			}
			word[index++] = (char)ch;
		}
	}
	if (index > 0) {                                                                // Если после последнего слова нет знака пунктуации
		word[index] = '\0';
		if (addWord(&head, word, err)) {
			fprintf(output, "%s\n", word);
		}
	}

	free(word);

	while (head != NULL) {
		Node* next = head->next;
		free(head->word);
		free(head);
		head = next;
	}
}
