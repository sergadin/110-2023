#include "strings.h"
#define MAX_WORD_LENGTH 512

void copyWords(FILE* input, FILE* output, error* err) {
	int ch, index = 0;
	char word[MAX_WORD_LENGTH + 1];
	*err = OK;

	while ((ch = fgetc(input)) != EOF) {
		if (isspace((unsigned char)ch) || ispunct((unsigned char)ch)) {
			if (index > 0) {
				word[index] = '\0';
				fprintf(output, "%s\n", word);
				index = 0;
			}
		}
		else {
			if (index < MAX_WORD_LENGTH) {
				word[index++] = (char)ch;
			}
			else {
				*err = 	TOO_LONG_WORD;
				return;
			}
		}
	}
	if (index > 0) {
		word[index] = '\0';
		fprintf(output, "%s\n", word);
	}
}
