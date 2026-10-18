#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pos_word.h"

#define YES_ISOL 1 
#define NO_ISOL -1

// функция isalnum проверяет является ли аргумент типа int буквой или цифрой, возвращает 0 если аргумент не явл цифрой или буквой и ненул значение иначе

// проверка изолировано ли наше слово
int word_is_isolated(char *start, char *pos_after, char *line){ 
	if(start == line || !isalnum(*(start - 1))){ // если началась новая строка или если позиция до первой позиции нашего слова не является буквой или цифрой
		if(*pos_after == '\0' || !isalnum(*pos_after)){ // если позиция после слова это - конец строки или это не является цифрой или буквой
			return YES_ISOL;
		}
	}
	return NO_ISOL;
}


int find_pos_word_in_file(FILE *file, const char *word) {
	char *line = NULL; // указатель на строку, хранит прочитанную строку
	size_t len = 0;
	int line_num = 0; // номер текущей строки
	int count = 0; //счётчик слов
	char *pos;
	int word_len = strlen(word); //длина слова
	char *pos_after; // позиция стразу после слова
	
	while (getline(&line, &len, file) != -1) { // динамичесоке выделение памяти для строк
		if (line == NULL){
			printf("для %d строки не выделилась память\n", line_num);
		}
		line_num++;
		pos = line;
		while ((pos = strstr(pos, word)) != NULL) { 
			pos_after = pos + word_len; 
			if(word_is_isolated(pos, pos_after, line) == YES_ISOL){
				printf("строка: %d   позиция: %ld\n", line_num, pos - line + 1);
				count++;
			}
			pos++;
		}
	}
	
	free(line);
	return count;
}