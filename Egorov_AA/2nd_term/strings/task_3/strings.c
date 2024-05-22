#include "strings.h"

void copyWords(FILE* input, FILE* output, error* err) {
	int ch, index = 0;
	char word[121];
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
			word[index++] = (char)ch;
		}
	}
	if (index > 0) {
		word[index] = '\0';
		fprintf(output, "%s\n", word);
	}
}
