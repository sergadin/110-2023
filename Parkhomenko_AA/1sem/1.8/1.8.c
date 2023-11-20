#include <stdio.h>
#include <string.h>
#include <math.h>

int OSHIBKA = 0;
int vozr_ili_ybiv_posl(FILE *f);

int vozr_ili_ybiv_posl(FILE *f)
{
	int vozr_posl = 0, ybiv_posl = 0, ne_to = 0, schit_tek;
	double tek, pred;

	if (fscanf(f, "%lf", &pred) != 1)
	{
		OSHIBKA = -1;
		return -1;
	}

	while ((schit_tek = fscanf(f, "%lf", &tek)) != EOF)
	{
		if (schit_tek != 1)
		{
			OSHIBKA = -1;
			return -1;
		}

		if (tek > pred)
		{
			vozr_posl = 1;
		}
		else if (tek < pred)
		{
			ybiv_posl = 1;
		}
		else if (tek == pred)
		{
			ne_to = -1;
			return -1;
		}

		pred = tek;
	}

	if (vozr_posl == 1 && ybiv_posl == 0)
		return 1;
	else if (vozr_posl == 0 && ybiv_posl == 1)
		return 0;
	else
		return -1;
}

int main(void)
{
	int opred_posl;
	FILE *f = fopen("1.8.txt", "r");
	if (f == NULL)
	{
		printf("error opening the file\n");
		return -1;
	}

	opred_posl = vozr_ili_ybiv_posl(f);

	if (opred_posl == OSHIBKA)
	{
		printf("Пустой файл\n");
	}
	else if (opred_posl == 1)
	{
		printf("Последовательность возрастает\n");
	}
	else if (opred_posl == 0)
	{
		printf("Последовательность убывает\n");
	}
	else if (opred_posl == -1)
	{
		printf("Последовательность не возрастает и не убывает\n");
	}

	fclose(f);

	return 0;
}