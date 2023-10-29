#include <stdio.h>
#include <math.h>
#define OK 0
#define INPUT_VALUE_ERROR -1


// функция возвращает среднее арифметическое значение чисел последовательности 
double a_mean(FILE* input, int* error);


int main(void) {
	int error;
	double ans;
	FILE* input, * output;
	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("Failed to open input file\n");
		return -1;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("Failed to open output file\n");
		fclose(input);
		return -2;
	}
	ans = a_mean(input, &error);
	if (error) {
		fprintf(output, "Failed to read input sequence");
		fclose(input);
		fclose(output);
		return -3;
	}
	fprintf(output, "%lf", ans);
	fclose(input);
	fclose(output);
	return 0;
}


double a_mean(FILE* input, int* error) {
	int count = 0, last_num, cur_num;
	double sum = 0;
	if (fscanf(input, "%d", &last_num) == 1) {
		sum = last_num;
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
		*error = INPUT_VALUE_ERROR;          // error = INPUT_VALUE_ERROR - пустой файл
		return 0;
	}
	*error = OK;               // error = OK - все хорошо
	return sum / count;
}
