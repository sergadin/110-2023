#include "strings_cpy.h"

typedef struct Node {
	char* word;
	struct Node* next;
} Node;

static int addWord(Node** head, const char* word, Error* err);         // ������� ��� ���������� ����� � ������� ������

static int addWord(Node** head, const char* word, Error* err) {
	Node* current = *head;
	while (current != NULL) {
		if (strcmp(current->word, word) == 0) {     // �������� �� ������� ����� � ������
			return 0;
		}
		current = current->next;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		exit(-1);
	}

	new_node->word = strdup(word);
	new_node->next = *head;
	*head = new_node;
	return 1;
}


void copyWords(FILE* input, FILE* output, Error* err) {
	int ch, index = 0, max_size = 512;
	Node* head = NULL;
	*err = OK;
	char* word = (char*)malloc(max_size * sizeof(char));

	while ((ch = fgetc(input)) != EOF) {
		if (isspace((unsigned char)ch) || ispunct((unsigned char)ch)) {        // ���� ���� ���������� => ����� �����������
			if (index > 0) {
				word[index] = '\0';
				if (addWord(&head, word, err)) {                            // ��������� ��������� �� ��� � ������, ���� ���, �� ����������
					fprintf(output, "%s\n", word);
				}
				index = 0;
			}
		}
		else {
			if (index >= max_size - 1) {
				max_size *= 2;
				char* new_word = (char*)realloc(word, max_size * sizeof(char));
				if (new_word == NULL) {
					*err = MEM_ERR;
					free(word);
					return;
				}
				word = new_word;
			}
			word[index++] = (char)ch;
		}
	}
	if (index > 0) {                                                                // ���� ����� ���������� ����� ��� ����� ����������
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