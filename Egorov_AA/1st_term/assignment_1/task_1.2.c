#include <stdio.h>
#include <math.h>
#define INPUT_VALUE_ERROR -2
#define OPERATION_ERROR -1
#define OK 0


double g_mean(FILE* input, int* error);


int main(void) {
	FILE* input, * output;
	int error;
	double res;
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
	res = g_mean(input, &error);
	if (error == INPUT_VALUE_ERROR) {
		fprintf(output, "Failed to read input sequence");
		return -3;
	}
	if (error == OPERATION_ERROR) {
		fprintf(output, "Operation is impossible");
		return -4;
	}
	fprintf(output, "%lf", res);
	fclose(output);
	fclose(input);
	return 0;
}


double g_mean(FILE* input, int* error) {
	double mult = 1;
	int n = 0;
	while (!feof(input)) {
		double temp;
		if (fscanf(input, "%lf", &temp) != 1) {
			break;
		}
		mult = mult * temp;
		n++;
	}
	if (!n) {
		*error = INPUT_VALUE_ERROR; // error = INPUT_VALUE_ERROR - файл пуст / не числовые значения
		return 0;
	}
	if ((n % 2 == 0) && (mult < 0)) {
		*error = OPERATION_ERROR; // error = OPERATIONERR - операция не может быть выполнена (т.к. подкорневое - отриц.)
		return 0;
	}
	*error = OK; // error = OK - все хорошо
	if (mult < 0) {
		return ((-1) * pow(mult * (-1), 1.0 / n));
	}
	return pow(mult, 1.0 / n);
}
