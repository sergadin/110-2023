#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define EQUAL 1
#define NO_EQUAL -1

// Лексикографическая проверка строк
int equal_lines(const char* lineA, const char* lineB) {
	if (strcmp(lineA, lineB) == 0) {
		return EQUAL;
	}
	else {
		return NO_EQUAL;
	}
}

void find_diff(const char* file_A, const char* file_B, const char* file_out, error *err) {
	FILE *fA;
	FILE *fB;
	FILE *out;
	char lineA[1000]; 
	char lineB[1000];
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
	
	while (fgets(lineA, sizeof(lineA), fA) != NULL) { 
		equal  = 0;
		fseek(fB, 0, SEEK_SET);
		while (fgets(lineB, sizeof(lineB), fB) != NULL) { 		
		 	if (equal_lines(lineA, lineB) == 1) { 
				equal = 1;
				break;
			}
		}
		if (equal == 0) { 
			fprintf(out, "   %s", lineA);
		}
	}
	fseek(fA, 0, SEEK_SET);
	fseek(fB, 0, SEEK_SET);
	
	fprintf(out, "\nстроки, добавленные в файл A:\n");
	
	while (fgets(lineB, sizeof(lineB), fB) != NULL) {
		equal = 0;
		fseek(fA, 0, SEEK_SET);
		while (fgets(lineA, sizeof(lineA), fA) != NULL) {
			if (equal_lines(lineB, lineA) == 1) {
				equal = 1;
				break;
			}
		}
		if (equal == 0) { 
			fprintf(out, "   %s", lineB);
		}
	}
	
	fclose(fA);
	fclose(fB);
	fclose(out);
}
