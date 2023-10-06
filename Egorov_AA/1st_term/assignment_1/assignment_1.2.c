#include <stdio.h>
#include <math.h>

int func(FILE *input, FILE *output) {
	double ans, mult = 1;
	int n = 0;
	while (!feof(input)) {
		double temp;
		if (fscanf(input, "%lf", &temp) != 1)
		break;
		mult = mult * temp;
		n++;
	}
	if (n) {
		if ((n % 2 == 0) && (mult < 0 )) {
			fprintf(output, "Operation is impossible");
			return -3;
			}
		else {
			ans = pow(mult, 1.0 / n);
			fprintf(output, "%lf", ans);
		}
	}
	else {
		fprintf(output, "Input file is empty");
		return -2;
	}
	return 0;
}

int main() {
	char input_name[32], output_name[32];
	scanf("%s%s", input_name, output_name);
	FILE *input, *output;
	input = fopen(input_name, "r");
	output = fopen(output_name, "w");
	if (input) {
		int res = func(input, output);
		if (res) {
			return res;
		}
	}
	else {
		fprintf(output, "Failed to open input file");
		return -1;
	}
	fclose(output);
	fclose(input);
	return 0;
}

