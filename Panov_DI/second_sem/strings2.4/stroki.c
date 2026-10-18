#include "stroki.h"

void split_long_lines(FILE* input, FILE* output, size_t max_length, error_t* err) {

	char* line = NULL;
	size_t line_cap = 0, line_len;

	while ((line_len = getline(&line, &line_cap, input)) != -1) {
		size_t start = 0;

		while (start < (size_t)line_len) {
			size_t end = start + max_length;

			// Если строка короче max_length, просто печатаем её
			if (end > (size_t)line_len) {
				end = (size_t)line_len;
			}
			else {
				// Найти последний пробел перед max_length, чтобы не разрывать слова
				while (end > start && line[end] != ' ' && line[end] != '\0' && line[end] != '\n') {
					end--;
				}

				if (end == start) {
					end = start + max_length; // Принудительный разрыв строки, если нет пробелов
				}
			}

			// Печать текущего фрагмента строки
			fprintf(output, "%.*s\n", (int)(end - start), line + start);

			start = end;
			// Пропускаем пробелы после текущего фрагмента
			while (start < (size_t)line_len && (line[start] == ' ' || line[start] == '\n')) {
				start++;
			}
		}
	}

	free(line);
}