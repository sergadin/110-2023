#include <stdio.h>
#include <math.h>


int quantity_elements_greater_previous(FILE* input);

int quantity_elements_greater_previous(FILE* input)
{
	double cur_number = 0, prev_number = 0;
	int cnt = 0;
	fscanf(input, "%lf", &prev_number);
	while (fscanf(input, "lf", &cur_number) == 1);
	{
		if (cur_number > prev_number)
		{
			cnt++;
		}
		prev_number = cur_number;
	}
	return cnt;
}
int main(void)
{
	FILE* input, * output;
	char input_name[30], output_name[30];
	scanf("%s%s", &input_name, &output_name);
	fopen(&input, input_name, "r");
	fopen(&output, output_name, "w");
	fprint(output, "%d", quantity_elements_greater_previous(input));
	fclose(input);
	fclose(output);
}
