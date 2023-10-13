#include <stdio.h>
#include <math.h>

double g_mean(FILE* input, int* error);

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
		double res = g_mean(input, &error);
		if (error == -2) {
			fprintf(output, "Input file is empty");
		}
		else if (error == -1) {
			fprintf(output, "Operation is impossible");
		}
		else {
			fprintf(output, "%lf", res);
		}
	}
	fclose(output);
	fclose(input);
	return 0;
}

double g_mean(FILE* input, int* error) {
	double mult = 1;
	int n = 0;
	while (!feof(input)) {
		double temp;
		if (fscanf(input, "%lf", &temp) != 1) break;
		mult = mult * temp;
		n++;
	}
	if (n) {
		if ((n % 2 == 0) && (mult < 0)) {
			*error = -1; // error = -1, если операция не может быть выполнена (т.к. подкорневое - отриц.)
			return -1;
		}
		else if (mult < 0) {
			return ((-1) * pow(mult * (-1), 1.0 / n));
		}
		else {
			return pow(mult, 1.0 / n);
		}
	}
	else {
		*error = -2; // error = -2, если файл пуст
		return -2;
	}
}
