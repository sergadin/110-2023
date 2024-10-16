#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define EQUAL 1
#define NO_EQUAL 0

#define LEN 1000

// Лексикографическая проверка строк
int equal_lines(const char* lineA, const char* lineB) {
	if (strcmp(lineA, lineB) == 0) {
		return EQUAL;
	} else {
		return NO_EQUAL;
	}
}

void find_diff(const char* file_A, const char* file_B, const char* file_out, error *err) {
	FILE *fA;
	FILE *fB;
	FILE *out;
	char lineA[LEN]; 
	char lineB[LEN];
	int equal = 0; 
	*err = OK;

	fA = fopen(file_A, "r");
	if (fA == NULL) {
		*err = FILE_ERR;
		return;
	}
	fB = fopen(file_B, "r");
	if (fB == NULL) {
		*err = FILE_ERR;
		fclose(fA);
		return;
	}
	out = fopen(file_out, "w");
	if (out == NULL) {
		*err = FILE_ERR;
		fclose(fA);
		fclose(fB);
		return;
	}

	fprintf(out, "строки, удаленные из файла A:\n");

	while (fgets(lineA, LEN, fA) != NULL) { 
		equal = NO_EQUAL;
		rewind(fB); // Перематываем файл B в начало перед каждым сравнением
		while (fgets(lineB, LEN, fB) != NULL) { 		
			if ((equal = equal_lines(lineA, lineB)) == EQUAL) break;
		}
		if (equal == NO_EQUAL) { 
			fprintf(out, "   %s", lineA);
		}
	}

	rewind(fA); // Перематываем файл A в начало
	rewind(fB); // Перематываем файл B в начало

	fprintf(out, "\nстроки, добавленные в файл A:\n");
	while (fgets(lineB, LEN, fB) != NULL) {
		equal = NO_EQUAL;
		rewind(fA); // Перематываем файл A в начало перед каждым сравнением
		while (fgets(lineA, LEN, fA) != NULL) {
			if ((equal = equal_lines(lineB, lineA)) == EQUAL) break;
		}
		if (equal == NO_EQUAL) { 
			fprintf(out, "   %s", lineB);
		}
	}

	fclose(fA);
	fclose(fB);
	fclose(out);
}
