#include "strings.h"
#define MAX_WORD_LENGTH 512

static int add_word(Node** head, const char* word); // Функция для добавления слова в список, если его там еще нет

static int add_word(Node** head, const char* word) {
	Node* current = *head;
	while (current != NULL) {
		if (strcmp(current->word, word) == 0) {
			return 0; // Слово уже есть в списке
		}
		current = current->next;
	}
	// Добавляем новое слово в начало списка
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		perror("Ошибка выделения памяти");
		exit(-1);
	}
	strcpy(new_node->word, word);
	new_node->next = *head;
	*head = new_node;
	return 1;
}


void copyWords(FILE* input, FILE* output, error* err) {
	int ch, index = 0;
	char word[MAX_WORD_LENGTH + 1];
	Node* head = NULL;

	*err = OK;

	while ((ch = fgetc(input)) != EOF) {
		if (isspace((unsigned char)ch) || ispunct((unsigned char)ch)) {
			if (index > 0) {
				word[index] = '\0';
				if (add_word(&head, word)) {
					fprintf(output, "%s\n", word);
				}
				index = 0;
			}
		}
		else {
			if (index < MAX_WORD_LENGTH) {
				word[index++] = (char)ch;
			}
			else {
				*err = TOO_LONG_WORD;
				return;
			}
		}
	}
	if (index > 0) {
		word[index] = '\0';
		if (add_word(&head, word)) {
			fprintf(output, "%s\n", word);
		}
	}

	while (head != NULL) {
		Node* next = head->next;
		free(head);
		head = next;
	}
}
