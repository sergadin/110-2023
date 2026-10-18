#include "pos_word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//  вводим в консоли сначала make, а потом ввод вида:  ./a.out input2.txt say
int main(int argc, char **argv) {
	const char *filename = argv[1]; // имя файла, где ищем слово
	const char *word = argv[2]; // само слово, которое хотим найти
	FILE *file;
	int kol_word; // кол-во найденных слов
	
	if (argc != 3) {
		printf("недостаточно данных подано на вход \n");
		exit(EXIT_FAILURE);
	}
	printf("*координаты* слова '%s': \n", word);
	    
	file = fopen(filename, "r");
    if (file == NULL) {
        printf("ошибка открытия файла \n");
        exit(EXIT_FAILURE);
    }

    kol_word = find_pos_word_in_file(file, word);
	if (kol_word == 0) {
		printf("такого слова в файле не нашлось \n");
		printf("не расстраивайтесь и попробуйте найти другое слово! \n");
		exit(EXIT_FAILURE);
	}
	
	fclose(file);
    exit(EXIT_SUCCESS);
}

