#include <stdio.h>
#include <math.h>
#define OK 0
#define INPUT_VALUE_ERROR -1
#define WRONG_SEQUENCE -2


int num_of_different_values(FILE* input, int* error);


int main(void) {
	FILE* input, * output;
	int error, ans;
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
	ans = num_of_different_values(input, &error);
	if (error == INPUT_VALUE_ERROR) {
		fprintf(output, "Failed to read input sequence");
		return -3;
	}
	if (error == WRONG_SEQUENCE) {
		fprintf(output, "Sequence is not non-decreasing");
		return -4;
	}
	fprintf(output, "%d", ans);
	fclose(input);
	fclose(output);
	return 0;
}


int num_of_different_values(FILE* input, int* error) {    /* функция возвращает кол-во различных    */
	int count = 0, last_num, cur_num;                 /* чисел последовательности и присваивает */
	if (fscanf(input, "%d", &last_num) == 1) {        /* значение переменной - флагу error      */
		count++;
	}
	while (fscanf(input, "%d", &cur_num) == 1) {
		if (cur_num > last_num) {
			count++;
			last_num = cur_num;
		}
		else if (cur_num < last_num) {
			*error = WRONG_SEQUENCE;   // error = WRONG_SEQUENCE - последовательность НЕ неубывающая
			return 0;
		}
	}
	if (!count) {
		*error = INPUT_VALUE_ERROR;   // error = INPUT_VALUE_ERROR - пустой файл / не числовые значения
		return 0;
	}
	*error = OK;   // error = OK - все хорошо
	return count;
}
