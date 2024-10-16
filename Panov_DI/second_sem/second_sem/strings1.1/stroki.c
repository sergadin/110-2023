#include "stroki.h"

#define CHUNK_SIZE 64  // Размер порции, на который будем увеличивать память

// Функция для проверки, является ли символ "заданным"
const int is_delimiter(char c);

const int is_delimiter(char c) {
	char delimiters[] = ".,;!?()[]";  // Заданные символы
	for (int i = 0; delimiters[i] != '\0'; i++) {
		if (c == delimiters[i]) {
			return 1;  // Если символ найден в списке, вернуть 1
		}
	}
	return 0;  // Иначе вернуть 0
}


// Функция для обработки строки и работы с файлами
void process_string(FILE* input, FILE* output, error_t* err) {
	*err = SUCCESS;
	size_t buffer_size = CHUNK_SIZE;
	char* buffer = (char*)malloc(buffer_size * sizeof(char));
	if (!buffer) {
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	size_t len = 0;
	int ch;
	// Чтение содержимого файла
	while ((ch = fgetc(input)) != EOF) {
		// Если буфер переполнен, увеличиваем его
		if (len >= buffer_size - 1) {
			buffer_size += CHUNK_SIZE;
			buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
			if (!buffer) {
				printf("Ошибка перераспределения памяти.\n");
				exit(1);
			}
		}
		buffer[len++] = (char)ch;
	}
	buffer[len] = '\0';  // Завершаем строку

	// Обработка строки
	size_t output_size = CHUNK_SIZE;
	char* processed = (char*)malloc(output_size * sizeof(char));
	if (!processed) {
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	size_t i = 0, j = 0;
	while (i < len) {
		// Если буфер переполнен, увеличиваем его
		if (j >= output_size - 1) {
			output_size += CHUNK_SIZE;
			processed = (char*)realloc(processed, output_size * sizeof(char));
			if (!processed) {
				printf("Ошибка перераспределения памяти.\n");
				exit(1);
			}
		}

		processed[j] = buffer[i];

		// Если текущий символ входит в заданный набор, пропускаем все последующие такие же символы
		if (is_delimiter(buffer[i])) {
			while (buffer[i] == buffer[i + 1]) {
				i++;
			}
		}

		i++;
		j++;
	}
	processed[j] = '\0';  // Завершаем строку

	// Запись обработанной строки в выходной файл
	fprintf(output, "%s", processed);

	// Освобождение памяти
	free(buffer);
	free(processed);
}