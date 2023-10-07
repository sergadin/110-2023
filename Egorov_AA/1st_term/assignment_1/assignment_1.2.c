#include <stdio.h>
#include <math.h>

int gmean(FILE* input, FILE* output);

int main(void) {
	FILE* input, * output;
	char input_name[32], output_name[32];
	scanf("%s%s", input_name, output_name);
	input = fopen(input_name, "r");
	output = fopen(output_name, "w");
    if (!output) {
        printf("Failed to open output file\n");
        return -1;
    }
	if (input) {
		int res = gmean(input, output);
		if (res) {
			return res;
		}
	}
	else {
		printf("Failed to open input file\n");
		return -2;
	}
	fclose(output);
	fclose(input);
	return 0;
}

int gmean(FILE* input, FILE* output) {
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
			return -4;
			}
		else {
            if (mult < 0) {
			ans = (-1) * pow(mult*(-1), 1.0 / n);
			fprintf(output, "%lf", ans);
            }
            else {
			ans = pow(mult, 1.0 / n);
			fprintf(output, "%lf", ans);
            }
		}
	}
	else {
		fprintf(output, "Input file is empty");
		return -3;
	}
	return 0;
}

