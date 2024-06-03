#include "str_property.h"

int str_property (char *str, ERR *err)
{
	if (str == NULL)
	{
		*err = ER_NL;
		printf("строка - пуста, ошибка");
		return -1;
	}
		// len - длина строки, quan - количество слов, i - позиция в str, j - позиция в sub_str, lenw - общая длина слов, sub - дополнительная переменная
	int max, min, i = 0, len = strlen(str) - 1, quan = 0, count = 0, j = 0;
	char *sub_str, sub;
	char space[] = "., ()[]{};:'/?!`";
	double aver_len = 0;
	FILE *output;
	output = fopen("output.txt", "w");
	sub_str = (char *)malloc(2 * len * sizeof(char));
	sub_str[0] = 0;
	max = 0;
	min = len;
	while (str[i + 1] != 0)
	{
		if(strchr(sub_str, str[i]) == 0)
		{
			sub_str[j] = str[i];
			j++;
			sub_str[j] = 0;
		}
		if ((strchr(space, str[i]) == 0) && (count == 0))
		{
			quan++;
		}
		if (strchr(space, str[i]) == 0)
		{
			count++;
			aver_len = aver_len + 1;
		}
		else if(count != 0)
		{
			if(count > max)
			{
				max = count;
			}
			if(count < min)
			{
				min = count;
			}
			count = 0;
		}
		else
		{
			count = 0;
		}
		i++;
	}
	if(count > max)
	{
		max = count;
	}
	if (count < min)
	{
		min = count;
	}
	aver_len = aver_len / quan;
	fprintf(output, "максимум = %d \n", max);
	fprintf(output, "минимум = %d \n", min);
	fprintf(output, "средняя длина слова = %lf \n", aver_len);
	j = 0;
	fprintf(output, "частота появления каждого символа \n");
	while (sub_str[j] != 0)
	{
		i = 0;
		count = 0;
		while(str[i] != 0)
		{
			if (sub_str[j] == str[i])
			{
				count++;
			}
			i++;
		}
		sub = sub_str[j + 1];
		sub_str[j + 1] = 0;
		fprintf(output, "%s = %3.2lf %% \n", &sub_str[j], (double) (((double) count / len) * 100));
		sub_str[j + 1] = sub;
		j++;
	}
	free(sub_str);
	fclose(output);
	return 0;
}
