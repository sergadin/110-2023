#include <stdio.h>
#include <math.h>

double extr(FILE* f);

double extr(FILE* f)
{
	int prev, cur, next, count;
	double sum;

	sum = 0;
	count = 0;

	if (fscanf(f, "%d", &prev) != 1)
	{
		return -1;
	}

	if (fscanf(f, "%d", &cur) != 1)
	{
		return -1;
	}

	while (fscanf(f, "%d", &next) == 1)
	{

		if (cur > prev && cur > next)
		{
			sum = sum + cur;
			count++;
		}

		if (cur < prev && cur < next)
		{
			sum = sum + cur;
			count++;
		}

		prev = cur;
		cur = next;
	}

	if (count == 0)
	{
		return 0;
	}
	else
	{
		sum = sum / count;
		return sum;
	}
}

int main(void) {
	double ans;
	FILE* f;
	f = fopen("input.txt", "r");

	if (f == NULL)
	{
		printf("Error: could not open the file.\n");
		return -1;
	}

	ans = extr(f);

	if (ans == 0)
	{
		printf("No extremums");
		fclose(f);
		return 0;
	}

	if (ans == -1)
	{
		printf("Error reading the file");
		fclose(f);
		return -1;
	}

	printf("%lf", ans);
	fclose(f);
	return 0;

}