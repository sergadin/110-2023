#include <stdio.h>
#include <math.h>
#define OK 0
#define INPUT_VALUE_ERROR -1


double a_mean(FILE* input, int* error);


int main(void) {
	int error;
    double ans;
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
	ans = a_mean(input, &error);
	if (error) {
		fprintf(output, "Failed to read input sequence");
		return -3;
	}
	fprintf(output, "%lf", ans);
	fclose(input);
	fclose(output);
	return 0;
}


double a_mean(FILE* input, int* error) {     /* функция возвращает среднее арифметическое значение */
	int count = 0, last_num, cur_num;        /* чисел последовательности и присваивает значение    */
	double sum = 0;                          /* переменной - флагу error                           */
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
		*error = INPUT_VALUE_ERROR;          // error = INPUT_VALUE_ERROR - пустой файл/не числовые значения
		return 0;
	}
	*error = OK;               // error = OK - все хорошо
	return sum / count;
}
