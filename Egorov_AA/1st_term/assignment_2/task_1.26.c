#include <stdio.h>
#include <math.h>

double a_mean(FILE* input, int* error);

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
	else {
		int error;
		double ans = a_mean(input, &error);
		if (error) {
			fprintf(output, "Input file is empty");
		}
		else {
			fprintf(output, "%lf", ans);
		}
	}
	fclose(input);
	fclose(output);
	return 0;
}

double a_mean(FILE* input, int* error) { /* функция возвращает среднее арифметическое значение */
	int count = 0, last_num, cur_num;    /* чисел последовательности и присваивает значение    */
	double sum = 0;                      /* переменной - флагу error                           */
	if (fscanf(input, "%d", &last_num) == 1) {
		sum += last_num;
		count++;
	}
	while (fscanf(input, "%d", &cur_num) == 1) {
		if (cur_num != last_num) {
			sum += cur_num;
			count++;
			last_num = cur_num;
		}
	}
	if (!count) {
		*error = -1;          // error = -1 - пустой файл
	}
	*error = 0;               // error = 0 - все хорошо
	return sum / count;
}