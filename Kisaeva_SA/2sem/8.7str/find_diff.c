#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_diff.h"

#define RAVN 1
#define NE_RAVN -1

// Функция для сравнения строк
int sravn_lines(const char* lineA, const char* lineB) {
	if (strcmp(lineA, lineB) == 0) {
		return RAVN;
	}
	else {
		return NE_RAVN;
	}
}

void find_diff(const char* file_A, const char* file_B, const char* file_out, error *err) {
	FILE *fA;
	FILE *fB;
	FILE *out;
	char *lineA = NULL;
	char *lineB = NULL;
	size_t lenA = 0;
	size_t lenB = 0;
	int ravn = 0; // для определения равности строк
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
	
	while (getline(&lineA, &lenA, fA) != -1) { // прочитали строчку в файле A
		ravn = 0;
		fseek(fB, 0, SEEK_SET); 
		while (getline(&lineB, &lenB, fB) != -1) { // прочитали строчку в файле B		
			if (sravn_lines(lineA, lineB) == 1) { // определили нашли ли равную строку из файла А в файле В
				ravn = 1; // нашли равную
				break;
			}
		}
		if (ravn == 0) { // если не нашли равную строку в файле В, значит эта строка была удалена из файла А 
			fprintf(out, "   %s", lineA);
		}
	}
	//вернулись в начала файлов
	fseek(fA, 0, SEEK_SET);
	fseek(fB, 0, SEEK_SET);
	
	fprintf(out, "\nстроки, добавленные в файл A:\n");
	
	while (getline(&lineB, &lenB, fB) != -1) {
		ravn = 0;
		fseek(fA, 0, SEEK_SET);
		while (getline(&lineA, &lenA, fA) != -1) {
			if (sravn_lines(lineB, lineA) == 1) {
				ravn = 1;
				break;
			}
		}
		// не нашли строчку в файле А, которая бы равнялась строчке из файла В, значит произошло добавление строчек в файл А
		if (ravn == 0) { 
			fprintf(out, "   %s", lineB);
		}
	}
	
	free(lineA);
	free(lineB);
	fclose(fA);
	fclose(fB);
	fclose(out);
}