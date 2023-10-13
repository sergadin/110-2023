#include <stdio.h>
#include <math.h>

int num_of_different_values(FILE* input, int* error);

int main(void) {
	FILE* input, * output;
	char input_name[32], output_name[32];
	scanf("%s%s", input_name, output_name);
	input = fopen(input_name, "r");
	output = fopen(output_name, "w");
	if (!input) {
		printf("Failed to open input file\n");
		return -1;
	}
	if (!output) {
		printf("Failed to open output file\n");
		return -2;
	}
	int error;
	int ans = num_of_different_values(input, &error);
	if (error == -1) {
		fprintf(output, "Input file is empty");
	}
	else if (error == -2) {
		fprintf(output, "Sequence is not neubivayuschaya");
	}
	else {
		fprintf(output, "%d", ans);
	}
	fclose(input);
	fclose(output);
	return 0;
}

int num_of_different_values(FILE* input, int* error) { /* функция возвращает кол-во различных    */
	int count = 0, last_num, cur_num;                  /* чисел последовательности и присваивает */
	if (fscanf(input, "%d", &last_num) == 1) {         /* значение переменной - флагу error      */
		count++;
	}
	while (fscanf(input, "%d", &cur_num) == 1) {
		if (cur_num > last_num) {
			count++;
			last_num = cur_num;
		}
		else if (cur_num < last_num) {
			*error = -2;         // error = -2 - последовательность НЕ неубывающая
			return -2;
		}
	}
	if (!count) {
		*error = -1;             // error = -1 - пустой файл
		return -1;
	}
	*error = 0;                  // error = 0 - все хорошо
	return count;
}