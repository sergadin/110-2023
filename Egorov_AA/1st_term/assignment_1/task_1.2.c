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
	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("Failed to open input file\n");
		return -1;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("Failed to open output file\n");
		fclose(input);
		return -2;
	}
	res = g_mean(input, &error);
	if (error == INPUT_VALUE_ERROR) {
		fprintf(output, "Failed to read input sequence");
		fclose(output);
		fclose(input);
		return -3;
	}
	if (error == OPERATION_ERROR) {
		fprintf(output, "Operation is impossible");
		fclose(output);
		fclose(input);
		return -4;
	}
	fprintf(output, "%lf", res);
	fclose(output);
	fclose(input);
	return 0;
}


double g_mean(FILE* input, int* error) {
	double mult = 1, temp;
	int n = 0;
	while (fscanf(input, "%lf", &temp) == 1) {
		mult = mult * temp;
		n++;
	}
	if (!n) {
		*error = INPUT_VALUE_ERROR; // error = INPUT_VALUE_ERROR - файл пуст
		return 0;
	}
	if ((n % 2 == 0) && (mult < 0)) {
		*error = OPERATION_ERROR; // error = OPERATION_ERROR - операция не может быть выполнена (т.к. подкорневое - отриц.)
		return 0;
	}
	*error = OK; // error = OK - все хорошо
	if (mult < 0) {
		return ((-1) * pow(mult * (-1), 1.0 / n));
	}
	return pow(mult, 1.0 / n);
}
